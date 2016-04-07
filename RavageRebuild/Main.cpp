#include "Application.h"
#include "RavRenderCore.h"


INT WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, INT)
{
	Ravage::RenderCore* core = Ravage::RenderCore::instance();
	
	Application app;
	app.run();

	core->freeInst();
	return 0;
}