#ifndef RAVDISPLAYWINDOWWIN32_H_INCLUDED
#define RAVDISPLAYWINDOWWIN32_H_INCLUDED

#include "RavDefines.h"

#if RAV_PLATFORM == RAV_PLATFORM_WIN32

#include <Windows.h>
#include "RavBase.h"
#include "RavSettings.h"

namespace Ravage
{
	class DisplayWindowWin32
	{
	public:
        explicit DisplayWindowWin32();
        ~DisplayWindowWin32();

        inline bool isNull() const
		{ return mWindow == 0; }

        bool keepAlive();
		void stop();

		HWND getWindow()
		{ return mWindow; }

		HDC getDC()
		{ return mDC; }
    private:
		Settings* mSettings;
        HWND mWindow;
		HDC  mDC;
	};
}

#endif /* RAV_PLATFORM */
#endif /* RAVDISPLAYWINDOWWIN32_H_INCLUDED */