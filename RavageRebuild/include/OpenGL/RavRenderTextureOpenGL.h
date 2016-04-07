#ifndef RAVRENDERTEXTUREOPENGL_H_INCLUDED
#define RAVRENDERTEXTUREOPENGL_H_INCLUDED

#include "RavRenderTexture.h"
#include "RavGraphicEnum.h"
#include "OpenGL\RavTextureOpenGL.h"

namespace Ravage
{
	class RenderTextureOpenGL : public TextureOpenGL, public RenderTexture
	{
	public:
		RenderTextureOpenGL();
		virtual ~RenderTextureOpenGL();

		bool create(const Vector2& size, RenderTextureFormat format, int depth);

		virtual Vector2 getSize();
		virtual void setSize(const Vector2& v);

		virtual void setFilterMode(FilterMode mode);
		virtual void setAnisoLevel(int level);
		virtual void setWrapMode(TexWrapMode mode);

		virtual GLenum getTarget();

		inline GLuint getFramebuffer()
		{ return mFramebuffer; }
	private:
		bool createRenderbuffer(const Vector2& size, int depth);
		bool createTexture(const Vector2& size, RenderTextureFormat format);

		GLuint mFramebuffer;
		GLuint mDepthBuffer;

		Vector2 mSize;
		int mDepth;
	};
}

#endif /* RAVRENDERTEXTUREOPENGL_H_INCLUDED */