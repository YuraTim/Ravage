#include "OpenGL/RavRendererOpenGL.h"

#include "OpenGL/RavIndexBufferOpenGL.h"
#include "OpenGL/RavVertexBufferOpenGL.h"
#include "OpenGL/RavShaderPassOpenGL.h"
#include "OpenGL/RavVertexDataOpenGL.h"
#include "OpenGL/RavRenderTextureOpenGL.h"
#include "OpenGL/RavTexture2DOpenGL.h"

namespace Ravage
{
	const GLenum FILLMODE_MAP[] = {GL_POINT, GL_LINE, GL_FILL};
	const GLenum BLEND_MAP[] = {GL_ZERO, 
								GL_ONE, 
								GL_SRC_COLOR, 
								GL_ONE_MINUS_SRC_COLOR, 
								GL_SRC_ALPHA, 
								GL_ONE_MINUS_SRC_ALPHA, 
								GL_DST_ALPHA,
								GL_ONE_MINUS_DST_ALPHA,
								GL_DST_COLOR,
								GL_ONE_MINUS_DST_COLOR,
								GL_CONSTANT_COLOR,
								GL_ONE_MINUS_CONSTANT_COLOR};
	const GLenum BLENDOP_MAP[] = {GL_FUNC_ADD, GL_FUNC_SUBTRACT, GL_FUNC_REVERSE_SUBTRACT, GL_MIN, GL_MAX};
	const GLenum CMPFUNC_MAP[] = {GL_NEVER, GL_LESS, GL_EQUAL, GL_LEQUAL, GL_GREATER, GL_NOTEQUAL, GL_GEQUAL, GL_GEQUAL, GL_ALWAYS};

	RendererOpenGL::RendererOpenGL() :
		mListener(Renderer::EVENT_SIZE),
		mDisplayWindow(0),
		mSettings(Settings::instance()),
		mIsLeftHanded(false),
		mUseIndexes(0),
		mSourceBlend(BLEND_ONE),
		mDestBlend(BLEND_ZERO),
		mCurrentTarget(0)
	{
#if RAV_PLATFORM == RAV_PLATFORM_WIN32
		mHGLRC = 0;
#endif /* RAV_PLATFORM */

	}

	RendererOpenGL::~RendererOpenGL()
	{
		if (mDisplayWindow)
			shutdown();

		mSettings->freeInst();

		//TODO: LOG
	}

	String RendererOpenGL::getRendererName()
	{
		return RAV_TXT("OpenGL3");
	}

#if RAV_PLATFORM == RAV_PLATFORM_WIN32
	DisplayWindow* RendererOpenGL::initialize()
	{
		if (mDisplayWindow)
		{
			//TODO: Log warning.
			return mDisplayWindow;
		}

		mDisplayWindow  = new DisplayWindow();
		DisplaySettings* settings = mSettings->getDisplaySettings();

		if (mDisplayWindow->isNull())
		{
			delete mDisplayWindow;
			mDisplayWindow = 0;
			return 0;
		}

		if (settings->isFullscreen())
		{
			Vector2 resolution = settings->getWindowResolution();

			DEVMODE dmScreenSettings;
    		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
    		dmScreenSettings.dmSize       = sizeof(dmScreenSettings);
    		dmScreenSettings.dmPelsWidth  = (DWORD)resolution.x;
    		dmScreenSettings.dmPelsHeight = (DWORD)resolution.y;				
			dmScreenSettings.dmBitsPerPel = (DWORD)settings->getBPP();				
    		dmScreenSettings.dmFields     = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

    		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
    		{
    			//TODO: Log error.
				delete mDisplayWindow;
				mDisplayWindow = 0;
				return 0;
			}
		}


		if (!initContext())
		{
			delete mDisplayWindow;
			mDisplayWindow = 0;
			return 0;
		}

		if (!initOpenGL())
		{
			delete mDisplayWindow;
			mDisplayWindow = 0;
			return 0;
		}

		return mDisplayWindow;
	}

	bool RendererOpenGL::initContext()
	{
		DisplaySettings* settings = mSettings->getDisplaySettings();

		PIXELFORMATDESCRIPTOR pfd =
		{
    		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
    		1,											// Version Number
    		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
    		PFD_SUPPORT_OPENGL |
			PFD_DOUBLEBUFFER,							// Must Support Double Buffering
    		PFD_TYPE_RGBA,								// Request An RGBA Format
			settings->getBPP(),							// Select Our Color Depth
    		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
    		0,											// No Alpha Buffer
    		0,											// Shift Bit Ignored
    		0,											// No Accumulation Buffer
    		0, 0, 0, 0,									// Accumulation Bits Ignored
    		32,											// 16Bit Z-Buffer (Depth Buffer)  
    		0,											// No Stencil Buffer
    		0,											// No Auxiliary Buffer
    		PFD_MAIN_PLANE,								// Main Drawing Layer
    		0,											// Reserved
    		0, 0, 0										// Layer Masks Ignored
		};

		HWND hwnd = mDisplayWindow->getWindow();
		HDC  hdc  = mDisplayWindow->getDC();

		if (!hwnd || !hdc)
		{
			//TODO: Log error.
			return false;
		}

		int pixformat = 0;
		if (!(pixformat = ChoosePixelFormat(hdc, &pfd)))
		{
			//TODO: Log error.
			return false;
		}

		if (!SetPixelFormat(hdc, pixformat, &pfd))
		{
			//TODO: Log error.
			return false;
		}

		HGLRC hTempRC = wglCreateContext(hdc);
		if (!hTempRC)
		{
			//TODO: Log error.
			return false;
		}

		if (!wglMakeCurrent(hdc, hTempRC))
		{
			//TODO: Log error.
			wglDeleteContext(hTempRC);
			return false;
		}

		if (glewInit() != GLEW_OK)
		{
			//TODO: Log error.
			wglDeleteContext(hTempRC);
			return false;
		}

		wglMakeCurrent(hdc, 0);
		wglDeleteContext(hTempRC);

		//Required for Index and Vertex buffers.
		int attributes[] =
		{
			WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
			WGL_CONTEXT_MINOR_VERSION_ARB, 3,
			WGL_CONTEXT_PROFILE_MASK_ARB,  WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
			0
		};

		if (!wglCreateContextAttribsARB)
		{
			//TODO: Log error.
			return false;
		}

		mHGLRC = wglCreateContextAttribsARB(hdc, 0, attributes);
		if (!mHGLRC)
		{
			//TODO: Log error.
			return false;
		}
		if (!wglMakeCurrent(hdc, mHGLRC))
		{
			//TODO: Log error.
			wglDeleteContext(mHGLRC);
			mHGLRC = 0;
			return false;
		}

		return true;
	}

	DisplayWindow* RendererOpenGL::reinitialize()
	{
		//TODO: NOT IMPLEMENTED
		return mDisplayWindow;
	}

	void RendererOpenGL::shutdown()
	{
		RavAssert(mDisplayWindow);

		wglMakeCurrent(mDisplayWindow->getDC(), 0);
		if (mHGLRC)
			wglDeleteContext(mHGLRC);

		if (mDisplayWindow)
			delete mDisplayWindow;

		mHGLRC = 0;
		mDisplayWindow = 0;
	}
#else /* RAV_PLATFORM */
#	error "RAVAGE ERROR: Not implemented."
#endif /* RAV_PLATFORM */

	bool RendererOpenGL::initOpenGL()
	{
		glClearDepth(1.0);
		glEnable(GL_BLEND);

		return true;
	}

	bool RendererOpenGL::beginScene(RenderTexture* target)
	{
		RenderTextureOpenGL* texture = dynamic_cast<RenderTextureOpenGL*>(target);
		
		//TODO: Viewport

		if (texture)
		{
			Vector2 size = texture->getSize();
			glBindFramebuffer(GL_FRAMEBUFFER, texture->getFramebuffer());
			glViewport(0, 0, (GLsizei)size.x, (GLsizei)size.y);
		}
		else
		{
			Vector2 size = mSettings->getDisplaySettings()->getWindowResolution();
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			glViewport(0, 0, (GLsizei)size.x, (GLsizei)size.y);
		}

		mCurrentTarget = target;

		return true;
	}

	void RendererOpenGL::endScene()
	{
		RenderTextureOpenGL* texture = dynamic_cast<RenderTextureOpenGL*>(mCurrentTarget);

		glFlush();

		if (texture)
		{
			glBindTexture(GL_TEXTURE_2D, texture->getTextureId());
			glGenerateMipmap(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

#if RAV_PLATFORM == RAV_PLATFORM_WIN32
		if (!texture)
			SwapBuffers(mDisplayWindow->getDC());
#else
#	error "RAVAGE ERROR: Not implemented."
#endif
	}

	bool RendererOpenGL::isDeviceLost()
	{
#if RAV_PLATFORM == RAV_PLATFORM_WIN32
		/*int	lost = 0;
		wglQueryPbufferARB ( hBuffer, WGL_PBUFFER_LOST_ARB, &lost );
		return lost != 0;*/
		return false;
#else
#	error "RAVAGE ERROR: Not implemented."
#endif
	}

	bool RendererOpenGL::loadShaderPass(ShaderPass* shader)
	{
		RavAssert(dynamic_cast<ShaderPassOpenGL*>(shader));

		ShaderPassOpenGL* openshader = (ShaderPassOpenGL*)shader;
		glUseProgram(openshader->getProgram());
		//TODO: Check.
		return true;
	}

	//Due every draw require shader, glUseProgram(0) isn't necessary.
	bool RendererOpenGL::unloadShaderPass()
	{
		glUseProgram(0);
		/*ShaderPassOpenGL* openshader = (ShaderPassOpenGL*)shader;*/
		//TODO: Check.
		return true;
	}

	

	bool RendererOpenGL::loadVertexData(VertexData* data)
	{
		if (!data)
			return unloadVertexData();

		RavAssert(dynamic_cast<VertexDataOpenGL*>(data));

		VertexDataOpenGL* vd = (VertexDataOpenGL*)data;
		glBindVertexArray(vd->getVertexArray());
		return true;
	}

	bool RendererOpenGL::unloadVertexData()
	{
		glBindVertexArray(0);
		return true;
	}

	bool RendererOpenGL::loadIndexData(IndexBuffer* data)
	{
		if (!data)
			return unloadIndexData();
		
		RavAssert(dynamic_cast<IndexBufferOpenGL*>(data));
		IndexBufferOpenGL* buffer = (IndexBufferOpenGL*)data;

		mUseIndexes = buffer->getBufferType();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer->getBufferID());

		return true;
	}

	bool RendererOpenGL::unloadIndexData()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		mUseIndexes = 0;
		return true;
	}

	bool RendererOpenGL::clear(unsigned mask)
	{
		GLbitfield result = 0;
		if (mask & CM_TARGET)
			result |= GL_COLOR_BUFFER_BIT;
		if (mask & CM_STENCIL)
			result |= GL_STENCIL_BUFFER_BIT;
		if (mask & CM_DEPTH)
			result |= GL_DEPTH_BUFFER_BIT;
		glClear(result);
		return true;
	}

	bool RendererOpenGL::draw(DrawOperation* oper)
	{
		GLenum mode = 0;
		GLsizei count = 0;

		//TODO: Change this with array: mode = DRAW_OPERATION_TYPE[oper->operationType];
		switch (oper->operationType)
		{
		case DrawOperation::TYPE_POINT_LIST:
			mode = GL_POINTS;
			count = oper->primitiveCount;
			break;
		case DrawOperation::TYPE_LINE_LIST:
			mode = GL_LINES;
			count = 2 * oper->primitiveCount;
			break;
		case DrawOperation::TYPE_LINE_STRIP:
			mode = GL_LINE_STRIP;
			count = oper->primitiveCount + 1;
			break;
		case DrawOperation::TYPE_TRIANGLE_LIST:
			mode = GL_TRIANGLES;
			count = 3 * oper->primitiveCount;
			break;
		case DrawOperation::TYPE_TRIANGLE_STRIP:
			mode = GL_TRIANGLE_STRIP;
			count = oper->primitiveCount + 2;
			break;
		case DrawOperation::TYPE_TRIANGLE_FAN:
			mode = GL_TRIANGLE_FAN;
			count = oper->primitiveCount + 2;
			break;
		default:
			mode = GL_POINTS;
		}

		if (mUseIndexes)
		{
			GLenum type = 0;
			unsigned size = 0;
			switch (mUseIndexes)
			{
			case IB_TYPE_16:
				type = GL_UNSIGNED_SHORT;
				size = sizeof(ushort);
				break;
			case IB_TYPE_32:
				type = GL_UNSIGNED_INT;
				size = sizeof(unsigned);
				break;
			default:
				//TODO: Error log.
				return false;
			}

			glDrawElements(mode, count, type, (char*)0 + oper->startIndex * size);
		}
		else
			glDrawArrays(mode, oper->startVertex, count);

		return true;
	}

	VertexBuffer* RendererOpenGL::createVertexBuffer(unsigned size, GraphicResourceType type)
	{
		VertexBufferOpenGL* buffer = new VertexBufferOpenGL();
		
		if (!buffer->create(size, type))
		{
			//TODO: Error log.
			delete buffer;
			return 0;
		}
		return buffer;
	}

	void RendererOpenGL::release(VertexBuffer* buffer)
	{
		delete buffer;
	}

	IndexBuffer* RendererOpenGL::createIndexBuffer(unsigned size, IndexBufferType type, GraphicResourceType pool)
	{
		IndexBufferOpenGL* buffer = new IndexBufferOpenGL();
		
		if (!buffer->create(size, type, pool))
		{
			//TODO: Error log.
			delete buffer;
			return 0;
		}
		return buffer;
	}

	void RendererOpenGL::release(IndexBuffer* buffer)
	{
		delete buffer;
	}

	VertexData* RendererOpenGL::createVertexData(VertexDeclaration* decl)
	{
		VertexData* data = new VertexDataOpenGL(decl);
		return data;
	}

	void RendererOpenGL::release(VertexData* data)
	{
		delete data;
	}

	ShaderPass* RendererOpenGL::createShaderPass()
	{
		ShaderPass* shader = new ShaderPassOpenGL();
		return shader;
	}

	void RendererOpenGL::release(ShaderPass* shader)
	{
		delete shader;
	}

	RenderTexture* RendererOpenGL::createRenderTexture(const Vector2& size, RenderTextureFormat fmt, int depth)
	{
		RenderTextureOpenGL* texture = new RenderTextureOpenGL();

		if (!texture->create(size, fmt, depth))
		{
			//TODO: Error log.
			return 0;
		}
		return texture;
	}

	void RendererOpenGL::release(RenderTexture* texture)
	{
		delete texture;
	}

	Texture2D* RendererOpenGL::createTexture2D(const Vector2& size, TextureFormat fmt)
	{
		Texture2DOpenGL* texture = new Texture2DOpenGL();

		if (!texture->create(size, fmt))
		{
			//TODO: Error log.
			return 0;
		}
		return texture;
	}

	void RendererOpenGL::release(Texture2D* texture)
	{
		delete texture;
	}

	GraphicCoordSystem RendererOpenGL::getCoordSystem()
	{
		return GCS_RIGHT_HANDED;
	}

	bool RendererOpenGL::setRenderState(RenderState state, int value)
	{
		switch(state)
		{
		case RS_ZFUNC:
			RavAssert(0 <= value && value < sizeof(CMPFUNC_MAP) / sizeof(CMPFUNC_MAP[0]));
			glDepthFunc(CMPFUNC_MAP[value]);
			break;
		case RS_FILLMODE:
			RavAssert(0 <= value && value < sizeof(FILLMODE_MAP) / sizeof(FILLMODE_MAP[0]));
			glPolygonMode(GL_FRONT_AND_BACK, FILLMODE_MAP[value]);
			break;
		case RS_SRCBLEND:
			RavAssert(0 <= value && value < sizeof(BLEND_MAP) / sizeof(BLEND_MAP[0]));
			mSourceBlend = (Blend)value;
			glBlendFunc(BLEND_MAP[mSourceBlend], BLEND_MAP[mDestBlend]);
			break;
		case RS_DSTBLEND:
			RavAssert(0 <= value && value < sizeof(BLEND_MAP) / sizeof(BLEND_MAP[0]));
			mDestBlend = (Blend)value;
			glBlendFunc(BLEND_MAP[mSourceBlend], BLEND_MAP[mDestBlend]);
			break;
		case RS_BLENDOP:
			RavAssert(0 <= value && value < sizeof(BLENDOP_MAP) / sizeof(BLENDOP_MAP[0]));
			glBlendEquation(BLENDOP_MAP[value]);
			break;
		default:
			return false;
		}
		return true;
	}
	
	bool RendererOpenGL::setRenderState(RenderState state, bool value)
	{
		GLenum cap = 0xFFFFFFFF;

		switch(state)
		{
		case RS_ZENABLE:
			cap = GL_DEPTH_TEST;
			break;
		default:
			return false;
		}

		if (value)
			glEnable(cap);
		else
			glDisable(cap);
		return true;
	}

	bool RendererOpenGL::setRenderState(RenderState state, const Color& value)
	{
		switch(state)
		{
		case RS_BLENDFACTOR:
			glBlendColor(value.r, value.g, value.b, value.a);
			break;
		case RS_CLEARCOLOR:
			glClearColor(value.r, value.g, value.b, value.a);
		default:
			return false;
		}
		return true;
	}

	bool RendererOpenGL::setRenderState(RenderState state, Real value)
	{
		switch(state)
		{
		case RS_ZVALUE:
			glClearDepth(value);
			break;
		default:
			return false;
		}
		return true;
	}
}