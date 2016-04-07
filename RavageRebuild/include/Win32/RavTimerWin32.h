#ifndef RAVTIMERWIN32_H_INCLUDED
#define RAVTIMERWIN32_H_INCLUDED

#include "RavBase.h"

#include <Windows.h>

namespace Ravage
{
	class TimerWin32
	{
	public:
		TimerWin32();
		~TimerWin32();

		void reset();

		unsigned long getMilliseconds();
		unsigned long getMicroseconds();

	private:
		DWORD mStartTick;
		LONGLONG mLastTime;
        LARGE_INTEGER mStartTime;
        LARGE_INTEGER mFrequency;

		DWORD_PTR mTimerMask;
	};
}

#endif /* RAVTIMERWIN32_H_INCLUDED */