#ifndef RAVRENDERTEXTURE_H_INCLUDED
#define RAVRENDERTEXTURE_H_INCLUDED

#include "RavBase.h"
#include "RavTexture.h"

namespace Ravage
{
	class RenderTexture : public Texture
	{
	public:
		virtual ~RenderTexture() = 0 {}
	};
}

#endif /* RAVRENDERTEXTURE_H_INCLUDED */