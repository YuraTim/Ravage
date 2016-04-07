#ifndef RAVOPENGLUTILITIES_H_INCLUDED
#define RAVOPENGLUTILITIES_H_INCLUDED

#include "RavBase.h"
#include "RavRenderer.h"

namespace Ravage
{
	class UtilitiesOpenGL
	{
	public:
		static void registerLibrary();
		static Renderer* getOpenGLRenderer();
	};
}

#endif /* RAVOPENGLUTILITIES_H_INCLUDED */