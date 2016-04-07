#ifndef RAVSYSTEMSETTINGS_H_INCLUDED
#define RAVSYSTEMSETTINGS_H_INCLUDED

#include "RavBase.h"

namespace Ravage
{
	class SystemSettings
	{
	public:
		SystemSettings();

		inline String getTitle()
		{ return mTitle; }

		inline void setTitle(const String& title)
		{ mTitle = title; }
	private:
		String mTitle;
	};
}

#endif /* RAVSYSTEMSETTINGS_H_INCLUDED */