#ifndef RAVTIMER_H_INCLUDED
#define RAVTIMER_H_INCLUDED

#if RAV_PLATFORM == RAV_PLATFORM_WIN32

#include "Win32\RavTimerWin32.h"
namespace Ravage
{ typedef TimerWin32 Timer; }

#else
#	error "RAVAGE ERROR: NOT IMPLEMENTED"
#endif


#endif /* RAVTIMER_H_INCLUDED */