#ifndef RAVFILEBUFFER_H_INCLUDED
#define RAVFILEBUFFER_H_INCLUDED

//SYSTEM SPECIFIC
#include "RavDefines.h"

#if RAV_PLATFORM == RAV_PLATFORM_WIN32

#include "Win32/RavFileBufferWin32.h"

namespace Ravage
{ typedef FileBufferWin32 FileBuffer; }

#else /* RAV_PLATFORM */
#	error "RAVAGE ERROR: Not implemented"
#endif /* RAV_PLATFORM */


#endif /* RAVFILEBUFFER_H_INCLUDED */