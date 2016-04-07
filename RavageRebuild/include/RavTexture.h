#ifndef RAVTEXTURE_H_INCLUDED
#define RAVTEXTURE_H_INCLUDED

#include "RavBase.h"
#include "RavMath.h"
#include "RavGraphicEnum.h"

namespace Ravage
{
	class Texture
	{
	public:
		virtual ~Texture() = 0 {}

		virtual Vector2 getSize() = 0;
		virtual void setSize(const Vector2& v) = 0;

		virtual void setFilterMode(FilterMode mode) = 0;
		virtual void setAnisoLevel(int level) = 0;
		virtual void setWrapMode(TexWrapMode mode) = 0;
	};
}

#endif /* RAVTEXTURE_H_INCLUDED */