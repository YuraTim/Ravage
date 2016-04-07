#if RAV_PLATFORM == RAV_PLATFORM_WIN32

#include "Win32/RavDisplayWindowWin32.h"

namespace Ravage
{
    const Symbol WINDOW_CLASS_NAME[] = RAV_TXT("RAVAGE_ENGINE_WNDCLASS");
    LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

    DisplayWindowWin32::DisplayWindowWin32() :
        mWindow(0),
		mDC(0),
		mSettings(Settings::instance())
    {
		DisplaySettings* displaySettings = mSettings->getDisplaySettings();
		SystemSettings* systemSettings = mSettings->getSystemSettings();
		
		WNDCLASS  wndclass;
        HINSTANCE curInstance = GetModuleHandle(0);
        memset(&wndclass, 0, sizeof(wndclass));

        //Register window class
        wndclass.style          = CS_OWNDC | CS_VREDRAW | CS_HREDRAW;
        wndclass.lpfnWndProc    = WindowProc;
        wndclass.hInstance      = curInstance;
        wndclass.hCursor        = LoadCursor(0, IDC_ARROW);
        wndclass.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
        wndclass.lpszMenuName	= 0;
        wndclass.lpszClassName	= WINDOW_CLASS_NAME;

        /*if(!settings.getIcon().empty())
            wndclass.hIcon = LoadIcon(curInstance, mSettings.getIcon().c_str());
        else*/
        wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);

        if (!RegisterClass(&wndclass))
        {
            //TODO: ERROR("Can't register window class");
            return;
        }

        //Create window
		Vector2 wndSize = displaySettings->getWindowResolution();

        int width  = int(wndSize.x) + GetSystemMetrics(SM_CXFIXEDFRAME) * 2;
        int height = int(wndSize.y) + GetSystemMetrics(SM_CYFIXEDFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION);

        RECT wndRect;
        DWORD style = 0;

        if (displaySettings->isFullscreen())
        {
            style = WS_POPUP | WS_VISIBLE;

            mWindow = CreateWindowEx(WS_EX_TOPMOST,
                                     WINDOW_CLASS_NAME,
                                     systemSettings->getTitle().c_str(),
                                     style,
                                     0,
                                     0,
                                     (int)wndSize.x,
                                     (int)wndSize.y,
                                     NULL,
                                     NULL,
                                     curInstance,
                                     NULL);
        }
        else
        {
            wndRect.left   = (GetSystemMetrics(SM_CXSCREEN) - width) / 2;
            wndRect.top    = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;
            wndRect.right  = wndRect.left + width;
            wndRect.bottom = wndRect.top  + height;

            style = WS_POPUP | WS_CAPTION | WS_SYSMENU | WS_VISIBLE;

            mWindow = CreateWindowEx(0,
                                     WINDOW_CLASS_NAME,
                                     systemSettings->getTitle().c_str(),
                                     style,
                                     wndRect.left,
                                     wndRect.top,
                                     wndRect.right - wndRect.left,
                                     wndRect.bottom - wndRect.top,
                                     NULL,
                                     NULL,
                                     curInstance,
                                     NULL);
        }

        if (!mWindow)
        {
            //TODO: ERROR("Can't create window");
            return;
        }

		mDC = GetDC(mWindow);

        ShowWindow(mWindow, SW_SHOW);		
		SetForegroundWindow(mWindow);
		SetFocus(mWindow);
    }

    DisplayWindowWin32::~DisplayWindowWin32()
    {
        if(mWindow)
        {
			ReleaseDC(mWindow, mDC);
            DestroyWindow(mWindow);
            mWindow = 0;
        }

        HINSTANCE curInstance = GetModuleHandle(0);
        if(curInstance)
            UnregisterClass(WINDOW_CLASS_NAME, curInstance);

		mSettings->freeInst();
    }

    bool DisplayWindowWin32::keepAlive()
    {
		bool quit = false;

        MSG msg;
        if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                quit = true;
			TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        return !quit;
    }

	void DisplayWindowWin32::stop()
	{
		PostQuitMessage(0);
	}

    LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
    {
		PAINTSTRUCT ps;

        switch(msg)
        {
            case WM_CREATE:
                return 0;

            case WM_PAINT:
				BeginPaint(hwnd, &ps);
				EndPaint(hwnd, &ps);
                return 0;
				
            case WM_DESTROY:
                PostQuitMessage(0);
                return 0;
        }

        return DefWindowProc(hwnd, msg, wparam, lparam);
    }

}

#endif //RAV_PLATFORM
