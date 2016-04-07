#ifndef RAVSETTINGS_H_INCLUDED
#define RAVSETTINGS_H_INCLUDED

#include "RavBase.h"

#include "RavSystemSettings.h"
#include "RavDisplaySettings.h"
#include "RavGraphicSettings.h"

namespace Ravage
{
	class Settings : public Singleton<Settings>
	{
	public:

		inline SystemSettings* getSystemSettings()
		{ return &mSystemSettings; }

		inline DisplaySettings* getDisplaySettings()
		{ return &mDisplaySettings; }

		inline GraphicSettings* getGraphicSettings()
		{ return &mGraphicSettings; }
	private:
		SystemSettings  mSystemSettings;
		DisplaySettings mDisplaySettings;
		GraphicSettings mGraphicSettings;
	};
}

#endif /* RAVSETTINGS_H_INCLUDED */