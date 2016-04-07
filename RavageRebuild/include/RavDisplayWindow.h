#ifndef RAVDISPLAYWINDOW_H_INCLUDED
#define RAVDISPLAYWINDOW_H_INCLUDED

#include "RavBase.h"

#if RAV_PLATFORM == RAV_PLATFORM_WIN32

#include "Win32/RavDisplayWindowWin32.h"
namespace Ravage
{ typedef DisplayWindowWin32 DisplayWindow; }

#else /* RAV_PLATFORM */
#	error "RAVAGE ERROR: Not implemented."
#endif /* RAV_PLATFORM */

#endif /* RAVDISPLAYWINDOW_H_INCLUDED */