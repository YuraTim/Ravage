#include "RavFileUtils.h"

#if RAV_PLATFORM == RAV_PLATFORM_WIN32
#	include <Windows.h>
#endif

namespace Ravage
{
	String FileUtils::getFolder(const String& filepath)
	{
		String::size_type offset = filepath.find_last_of(RAV_PATH_DELIM);
		return filepath.substr(0, offset);
	}

//Platform specific functions.
#if RAV_PLATFORM == RAV_PLATFORM_WIN32
	String FileUtils::getEngineFolder()
	{
		Symbol* result = new Symbol[MAX_PATH];

		DWORD cursize = MAX_PATH;
		DWORD size    = GetModuleFileName(0, result, MAX_PATH);

		while (size == cursize)
		{
			delete[] result;
			result = new Symbol[cursize *= 2];
			size = GetModuleFileName(0, result, cursize);
		}

		

		String path(result);
		delete[] result;
		return getFolder(path);
	}

	String FileUtils::getProfileFolder()
	{
		return getEngineFolder();
	}
#else
#	error "RAVAGE ERROR: Not implemented."
#endif
}