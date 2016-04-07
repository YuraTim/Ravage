#ifndef RAVTEXTURE2D_H_INCLUDED
#define RAVTEXTURE2D_H_INCLUDED

#include "RavBase.h"
#include "RavTexture.h"
#include "RavGraphicEnum.h"

namespace Ravage
{
	class Texture2D : public Texture
	{
	public:
		virtual ~Texture2D() = 0 {}

		virtual TextureFormat getFormat() const = 0;

		virtual void setPixels(Byte* buffer, int offset, int size) = 0;
		virtual void apply(bool updateMipmaps = true) = 0;
	};
}

#endif /* RAVTEXTURE2D_H_INCLUDED */