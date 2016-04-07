#ifndef RAVTEXTUREOPENGL_H_INCLUDED
#define RAVTEXTUREOPENGL_H_INCLUDED

#include "RavBase.h"
#include "RavTexture.h"
#include "OpenGL\RavLibrariesOpenGL.h"

namespace Ravage
{
	class TextureOpenGL
	{
	public:
		TextureOpenGL();
		virtual ~TextureOpenGL() = 0;
		
		virtual Vector2 getSize() = 0;
		virtual void setSize(const Vector2& v) = 0;

		virtual void setFilterMode(FilterMode mode);
		virtual void setAnisoLevel(int level);
		virtual void setWrapMode(TexWrapMode mode);

		inline GLuint getTextureId()
		{ return mTextureId; }
		
		virtual GLenum getTarget() = 0;
	private:
		GLuint mTextureId;
	};
}

#endif /* RAVTEXTUREOPENGL_H_INCLUDED */