#include "OpenGL\RavRenderTextureOpenGL.h"

namespace Ravage
{
	const GLenum RENDER_TEXTURE_FORMAT_MAP[] =
		{GL_R8, GL_RG8, GL_RGB8, GL_RGBA8, GL_R32F, GL_RG32F, GL_RGB32F, GL_RGBA32F};

	const GLenum RENDER_TEXTURE_NRMFMT_MAP[] =
		{GL_R, GL_RG, GL_RGB, GL_RGBA, GL_R, GL_RG, GL_RGB, GL_RGBA};

	RenderTextureOpenGL::RenderTextureOpenGL() :
		mSize(Vector2::ZERO),
		mDepth(0)
	{
		glGenFramebuffers(1, &mFramebuffer);
		glGenRenderbuffers(1, &mDepthBuffer);
	}

	RenderTextureOpenGL::~RenderTextureOpenGL()
	{
		glDeleteFramebuffers(1, &mFramebuffer);
		glDeleteRenderbuffers(1, &mDepthBuffer);
	}

	bool RenderTextureOpenGL::create(const Vector2& size, RenderTextureFormat format, int depth)
	{
		if (!createRenderbuffer(size, depth))
			return false;

		if (!createTexture(size, format))
			return false;

		glBindFramebuffer(GL_FRAMEBUFFER, mFramebuffer);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, getTextureId(), 0);

		if (mDepth > 0)
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, mDepthBuffer);

		GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if(status != GL_FRAMEBUFFER_COMPLETE)
		{
			//TODO: Error log;
			return false;
		}
		
		mSize = size;

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		return true;
	}

	bool RenderTextureOpenGL::createTexture(const Vector2& size, RenderTextureFormat format)
	{
		GLenum target = getTarget();
		glBindTexture(target, getTextureId());
		glTexImage2D(target, 0, RENDER_TEXTURE_FORMAT_MAP[format], (GLsizei)size.x, (GLsizei)size.y, 0,
					 RENDER_TEXTURE_NRMFMT_MAP[format], GL_FLOAT, 0);
		glBindTexture(target, 0);

		setFilterMode(FM_POINT);
		setWrapMode(TWM_CLAMP);
		return true;
	}

	bool RenderTextureOpenGL::createRenderbuffer(const Vector2& size, int depth)
	{
		GLenum format = 0;
		switch(depth)
		{
		case 0:
			format = 0;
			break;
		case 8:
			format = GL_DEPTH_COMPONENT;
			break;
		case 16:
			format = GL_DEPTH_COMPONENT16;
			break;
		case 24:
			format = GL_DEPTH_COMPONENT24;
			break;
		case 32:
			format = GL_DEPTH_COMPONENT32F;
			break;
		default:
			//TODO: Error log.
			return false;
		}

		mDepth = depth;

		if (format == 0)
			return true;

		glBindRenderbuffer(GL_RENDERBUFFER, mDepthBuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, format, (GLsizei)size.x, (GLsizei)size.y);
		return true;
	}

	GLenum RenderTextureOpenGL::getTarget()
	{
		return GL_TEXTURE_2D;
	}

	void RenderTextureOpenGL::setFilterMode(FilterMode mode)
	{
		TextureOpenGL::setFilterMode(mode);
	}

	void RenderTextureOpenGL::setAnisoLevel(int level)
	{
		TextureOpenGL::setAnisoLevel(level);
	}

	void RenderTextureOpenGL::setWrapMode(TexWrapMode mode)
	{
		TextureOpenGL::setWrapMode(mode);
	}

	Vector2 RenderTextureOpenGL::getSize()
	{
		return mSize;
	}

	void RenderTextureOpenGL::setSize(const Vector2& size)
	{
		//TODO
	}
}