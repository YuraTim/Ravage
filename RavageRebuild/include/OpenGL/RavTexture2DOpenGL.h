#ifndef RAVTEXTURE2DOPENGL_H_INCLUDED
#define RAVTEXTURE2DOPENGL_H_INCLUDED

#include "RavBase.h"
#include "RavTexture2D.h"
#include "RavGraphicEnum.h"
#include  "OpenGL\RavTextureOpenGL.h"

namespace Ravage
{
	class Texture2DOpenGL : public Texture2D, public TextureOpenGL
	{
	public:
		Texture2DOpenGL();
		virtual ~Texture2DOpenGL();

		bool create(const Vector2& size, TextureFormat format);

		virtual Vector2 getSize();
		virtual void setSize(const Vector2& v);

		virtual void setFilterMode(FilterMode mode);
		virtual void setAnisoLevel(int level);
		virtual void setWrapMode(TexWrapMode mode);

		virtual TextureFormat getFormat() const;

		virtual GLenum getTarget();

		virtual void setPixels(Byte* buffer, int offset, int size);
		virtual void apply(bool updateMipmaps = true);
	private:
		Byte* mImageBuffer;

		Vector2 mSize;
		TextureFormat mFormat;
	};
}

#endif /* RAVTEXTURE2DOPENGL_H_INCLUDED */