#include "OpenGL\RavUtilitiesOpenGL.h"

#include "RavRenderCore.h"
#include "OpenGL\RavRendererOpenGL.h"

namespace Ravage
{
	void UtilitiesOpenGL::registerLibrary()
	{
		RenderCore* core = RenderCore::instance();
		core->registerRenderer(RAV_TXT("OpenGL3"), UtilitiesOpenGL::getOpenGLRenderer);
		core->freeInst();
	}

	Renderer* UtilitiesOpenGL::getOpenGLRenderer()
	{
		return new RendererOpenGL();
	}
}