#ifndef RAVDISPLAYSETTINGS_H_INCLUDED
#define RAVDISPLAYSETTINGS_H_INCLUDED

#include "RavBase.h"
#include "RavMath.h"

namespace Ravage
{
	class DisplaySettings
	{
	public:
		DisplaySettings();

		inline Vector2 getWindowResolution() const
		{ return mWindowResolution; }

		inline bool isFullscreen() const
		{ return mIsFullscreen; }

		inline bool showTitle() const
		{ return mShowTitle; }

		inline int getBPP() const
		{ return mBPP; }

		inline void setWindowResolution(const Vector2& res)
		{ mWindowResolution = res; }

		inline void setFullscreen(bool mode)
		{ mIsFullscreen = mode; }

		inline void setShowTitle(bool show)
		{ mShowTitle = mShowTitle; }

		inline void setBPP(int bpp)
		{ mBPP = bpp; }
	private:
		Vector2 mWindowResolution;

		bool mIsFullscreen;
		bool mShowTitle;

		int mBPP;
	};
}

#endif /* RAVDISPLAYSETTINGS_H_INCLUDED */