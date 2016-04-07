#include "OpenGL\RavTextureOpenGL.h"

namespace Ravage
{
	TextureOpenGL::TextureOpenGL()
	{
		glGenTextures(1, &mTextureId);
	}

	TextureOpenGL::~TextureOpenGL()
	{
		glDeleteTextures(1, &mTextureId);
	}

	void TextureOpenGL::setFilterMode(FilterMode mode)
	{
		GLenum target = getTarget();

		if (target == 0)
			return;
		
		glBindTexture(target, mTextureId);

		switch(mode)
		{
		case FM_POINT:
			glTexParameterf(target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameterf(target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(target, GL_GENERATE_MIPMAP, GL_FALSE);
		case FM_BILINEAR:
			glTexParameterf(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
			glTexParameterf(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(target, GL_GENERATE_MIPMAP, GL_TRUE);
			break;
		case FM_TRILINEAR:
			glTexParameterf(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameterf(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(target, GL_GENERATE_MIPMAP, GL_TRUE);
		}
	}

	void TextureOpenGL::setAnisoLevel(int level)
	{
		GLenum target = getTarget();

		if (target == 0)
			return;
		
		glBindTexture(target, mTextureId);

		if (GL_EXT_texture_filter_anisotropic)
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, (GLfloat)level);
	}

	void TextureOpenGL::setWrapMode(TexWrapMode mode)
	{
		GLenum target = getTarget();

		if (target == 0)
			return;

		glBindTexture(target, mTextureId);

		switch(mode)
		{
		case TWM_REPEAT:
			glTexParameterf(target, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameterf(target, GL_TEXTURE_WRAP_T, GL_REPEAT);
			break;
		case TWM_CLAMP:
			glTexParameterf(target, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameterf(target, GL_TEXTURE_WRAP_T, GL_CLAMP);
			break;
		}
	}
}