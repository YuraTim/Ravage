/*
---------------------------------------------------------------------
This source file is part of Ravage Engine.

Copyright (c) 2011-2012 Timofeev Yuriy

*License text here*.
---------------------------------------------------------------------
*/

/*
---------------------------------------------------------------------
!!!UNFINISHED CODE!!!

This source file is unfinished.
Probably some parts don't work properly, have some things to fix
or just don't have implementation.
---------------------------------------------------------------------
*/

#ifndef RAVBASE_H_INCLUDED
#define RAVBASE_H_INCLUDED

//----= Standart includes =----
#include <sstream>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

//----= Standart Ravage Utilities =----
#include "RavDefines.h"
#include "RavTypes.h"

//----= Standart Ravage Patterns =----
#include "RavSingleton.h"

//----= Standart Ravage Containers =----
#include "RavList.h"
#include "RavStack.h"

//----= Base Math Functions =----
#include "RavMathBase.h"

//----= Enumerations =----
enum GraphicResourceType
{
	RAV_GRT_STATIC  = 0,
	RAV_GRT_DYNAMIC = 1
};

enum BlendMode
{
    RAV_BLEND_DEFAULT  = 0,
    RAV_BLEND_ALPHA    = 1,
    RAV_BLEND_ZWRITE   = 2,
    RAV_BLEND_COLORADD = 4,
};

enum ScriptState
{
	RAV_SCR_STATE_PLAY  = 0,
	RAV_SCR_STATE_STOP  = 1,
	RAV_SCR_STATE_END   = 2,
};

//----= System specific functions =----
#if RAV_PLATFORM == RAV_PLATFORM_WIN32

#include <Windows.h>

namespace Ravage
{
	inline void Sleep(unsigned milliseconds)
	{ ::Sleep(milliseconds); }

#	define RavAssert assert
}

#else /* RAV_PLATFORM FUNCTIONS */
#	error "RAVAGE ERROR: Not implemented."
#endif /* RAV_PLATFORM FUNCTIONS */

//----= Compiler specific functions =----
#if RAV_COMPILER == RAV_COMPILER_MSVC

#	define RavSprintf sprintf_s

#else /* RAV_COMPILER */
#endif /* RAV_COMPILER */

//----= System specific constants =----
#if RAV_PLATFORM == RAV_PLATFORM_WIN32

const Ravage::String RAV_PATH_DELIM(RAV_TXT("\\"));

#else /* RAV_PLATFORM CONSTANTS */
#	error "RAVAGE ERROR: Not implemented."
#endif /* RAV_PLATFORM CONSTANTS */

#endif // RAVBASE_H_INCLUDED
