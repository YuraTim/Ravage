#include "RavDisplaySettings.h"

namespace Ravage
{
	DisplaySettings::DisplaySettings() :
		mWindowResolution(Vector2(800, 600)),
		mIsFullscreen(false),
		mShowTitle(true),
		mBPP(32)
	{}
}