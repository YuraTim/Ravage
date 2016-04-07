#ifndef RAVOPENGLRENDERER_H_INCLUDED
#define RAVOPENGLRENDERER_H_INCLUDED

#include "RavBase.h"
#include "RavListener.h"
#include "RavRenderer.h"
#include "RavSettings.h"

#include "OpenGL/RavLibrariesOpenGL.h"

namespace Ravage
{
	class RendererOpenGL : public Renderer
	{
	public:
		RendererOpenGL();
		virtual ~RendererOpenGL();

		virtual String getRendererName();

		virtual DisplayWindow* initialize();
		virtual DisplayWindow* reinitialize();
		virtual void shutdown();

		virtual bool beginScene(RenderTexture* target);
		virtual void endScene();

		virtual bool loadShaderPass(ShaderPass* shader);
		virtual bool unloadShaderPass();

		virtual bool loadVertexData(VertexData* data);
		virtual bool unloadVertexData();

		virtual bool loadIndexData(IndexBuffer* data);
		virtual bool unloadIndexData();

		virtual bool clear(unsigned mask);

		virtual bool draw(DrawOperation* oper);

		virtual VertexBuffer* createVertexBuffer(unsigned size, 
												 GraphicResourceType type);
		virtual void release(VertexBuffer* buffer);

		virtual IndexBuffer* createIndexBuffer(unsigned size,
											   IndexBufferType type,
											   GraphicResourceType pool);
		virtual void release(IndexBuffer* buffer);
		
		virtual VertexData* createVertexData(VertexDeclaration* decl);
		virtual void release(VertexData* data);

		virtual ShaderPass* createShaderPass();
		virtual void release(ShaderPass* shader);

		virtual RenderTexture* createRenderTexture(const Vector2& size, RenderTextureFormat fmt, int depth);
		virtual void release(RenderTexture* texture);

		virtual Texture2D* createTexture2D(const Vector2& size, TextureFormat fmt);
		virtual void release(Texture2D* texture);

		virtual GraphicCoordSystem getCoordSystem();
		
		virtual bool setRenderState(RenderState state, int value);
		virtual bool setRenderState(RenderState state, const Color& value);
		virtual bool setRenderState(RenderState state, bool value);
		virtual bool setRenderState(RenderState state, Real value);

		virtual Listener* getListener()
		{ return &mListener; }
	private:
		bool isDeviceLost();
		bool initContext();
		bool initOpenGL();
	private:
		Listener mListener;

		DisplayWindow* mDisplayWindow;
		Settings*      mSettings;

		bool mIsLeftHanded;
		int mUseIndexes;

		Blend mSourceBlend;
		Blend mDestBlend;

		RenderTexture* mCurrentTarget;

#if RAV_PLATFORM == RAV_PLATFORM_WIN32
		
		HGLRC mHGLRC;

#else /* RAV_PLATFORM */
#	error "RAVAGE ERROR: Not implemented."
#endif /* RAV_PLATFORM */
	};
}

#endif /* RAVOPENGLRENDERER_H_INCLUDED */