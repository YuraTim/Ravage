#include "OpenGL\RavTexture2DOpenGL.h"

namespace Ravage
{
	const GLenum TEXTURE_FORMAT_MAP[] = {GL_R8, GL_RGB, GL_RGBA};
	const GLenum TEXTURE_NRMFMT_MAP[] = {GL_R, GL_RGB, GL_RGBA};
	const int TEXTURE_FORMAT_SIZE[] = {1, 3, 4};

	Texture2DOpenGL::Texture2DOpenGL() :
		mImageBuffer(0),
		mSize(Vector2::ZERO),
		mFormat(TF_RGB24)
	{}

	Texture2DOpenGL::~Texture2DOpenGL()
	{
		delete[] mImageBuffer;
	}

	bool Texture2DOpenGL::create(const Vector2& size, TextureFormat format)
	{
		GLenum target = getTarget();
		glBindTexture(target, getTextureId());
		glTexImage2D(target, 0, TEXTURE_FORMAT_MAP[format], (GLsizei)size.x, (GLsizei)size.y, 0,
					 TEXTURE_NRMFMT_MAP[format], GL_FLOAT, 0);
		glBindTexture(target, 0);

		mImageBuffer = new Byte[TEXTURE_FORMAT_SIZE[format] * int(size.x) * int(size.y)];
		memset(mImageBuffer, 0, TEXTURE_FORMAT_SIZE[format] * int(size.x) * int(size.y));

		mSize = size;
		mFormat = format;

		setFilterMode(FM_POINT);
		setWrapMode(TWM_CLAMP);
		return true;
	}

	Vector2 Texture2DOpenGL::getSize()
	{
		return mSize;
	}

	void Texture2DOpenGL::setSize(const Vector2& size)
	{
		//TODO
	}

	void Texture2DOpenGL::setFilterMode(FilterMode mode)
	{
		TextureOpenGL::setFilterMode(mode);
	}

	void Texture2DOpenGL::setAnisoLevel(int level)
	{
		TextureOpenGL::setAnisoLevel(level);
	}

	void Texture2DOpenGL::setWrapMode(TexWrapMode mode)
	{
		TextureOpenGL::setWrapMode(mode);
	}

	TextureFormat Texture2DOpenGL::getFormat() const
	{
		return mFormat;
	}

	GLenum Texture2DOpenGL::getTarget()
	{
		return GL_TEXTURE_2D;
	}

	void Texture2DOpenGL::setPixels(Byte* buffer, int offset, int size)
	{
		memcpy(mImageBuffer + offset, buffer, size);
	}

	void Texture2DOpenGL::apply(bool updateMipmaps)
	{
		GLenum target = getTarget();
		glBindTexture(target, getTextureId());
		glTexImage2D(target, 0, TEXTURE_FORMAT_MAP[mFormat], (GLsizei)mSize.x, (GLsizei)mSize.y, 0,
					 TEXTURE_NRMFMT_MAP[mFormat], GL_UNSIGNED_BYTE, mImageBuffer);
		if (updateMipmaps)
			glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(target, 0);
	}
}