#ifndef RAVFILEUTILS_H_INCLUDED
#define RAVFILEUTILS_H_INCLUDED

#include "RavBase.h"

namespace Ravage
{
	class FileUtils
	{
	public:
		static String getEngineFolder();
		static String getProfileFolder();
		static String getFolder(const String& filepath);
	};
}

#endif /* RAVFILEUTILS_H_INCLUDED */