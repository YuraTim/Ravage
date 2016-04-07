/*
---------------------------------------------------------------------
This source file is part of Ravage 2D Engine.

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

#ifndef RAVDEFINES_H_INCLUDED
#define RAVDEFINES_H_INCLUDED

/* PART OF RAVAGE BASE */

namespace Ravage
{

#define RAV_PLATFORM_WIN32   1
#define RAV_PLATFORM_LINUX   2
#define RAV_PLATFORM_MACOSX  3
#define RAV_PLATFORM_IOS     4
#define RAV_PLATFORM_ANDROID 5
#define RAV_PLATFORM_XBOX360 6

#define RAV_COMPILER_MSVC 1
#define RAV_COMPILER_GCCE 2
#define RAV_COMPILER_GNUC 3

#define RAV_ARCH_TYPE_32 1
#define RAV_ARCH_TYPE_64 2

#define RAV_RENDERER_DIRECTX  1
#define RAV_RENDERER_OPENGL   2
#define RAV_RENDERER_OPENGLES 3

#define RAV_MATH_LIB_STD      1
#define RAV_MATH_LIB_ASM_SSE2 2
#define RAV_MATH_LIB_ASM_PPC  3
#define RAV_MATH_LIB_ASM_ARM  4

//Find compile
#if defined(__GCCE__)
#	define RAV_COMPILER RAV_COMPILER_GCC
#	define RAV_COMPILER_VER _MSC_VER
#elif defined(_MSC_VER)
#	define RAV_COMPILER RAV_COMPILER_MSVC
#	define RAV_COMPILER_VER _MSC_VER
#elif defined( __GNUC__ )
#	define RAV_COMPILER RAV_COMPILER_GNUC
#	define RAV_COMPILER_VER (((__GNUC__)*100) + (__GNUC_MINOR__*10) + __GNUC_PATCHLEVEL__)
#else
#	error "RAVAGE ERROR: This compile is not supported."
#endif

//Find platform
#if defined(__WIN32__) || defined(_WIN32) //WIN32
#	define RAV_PLATFORM RAV_PLATFORM_WIN32
#elif defined (__APPLE_CC__)
#	if __ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__ >= 30000 || __IPHONE_OS_VERSION_MIN_REQUIRED >= 30000
#		define RAV_PLATFORM RAV_PLATFORM_IOS //IOS
#	else
#		define RAV_PLATFORM RAV_PLATFORM_MACOSX //MACOSX
#	endif
#else
#	define RAV_PLATFORM RAV_PLATFORM_LINUX //LINUX
#endif

//Find architecture.
#if defined(__x86_64__) || defined(_M_X64) || defined(__powerpc64__) || defined(__alpha__) || defined(__ia64__) || defined(__s390__) || defined(__s390x__)
#	define RAV_ARCH_TYPE RAV_ARCH_TYPE_64
#else
#	define RAV_ARCH_TYPE RAV_ARCH_TYPE_32
#endif

//Set RAV_RENDERER
#if !defined(RAV_RENDERER)
#	if RAV_PLATFORM == RAV_PLATFORM_WIN32
#		define RAV_RENDERER RAV_RENDERER_DIRECTX
#	elif RAV_PLATFORM == RAV_PLATFORM_IOS || RAV_PLATFORM == RAV_PLATFORM_ANDROID
#		define RAV_RENDERER RAV_RENDERER_OPENGLES
#	else
#		define RAV_RENDERER RAV_RENDERER_OPENGL
#	endif
#endif

//Set RAV_TXT
#ifdef UNICODE
#	define RAV_TXT(text) L##text
#else //UNICODE
#	define RAV_TXT(text) text
#endif //UNICODE

//Set RAV_MATH_LIB
#define RAV_MATH_LIB RAV_MATH_LIB_STD

//Set RAV_DEBUG & RAV_NDEBUG
#if defined(_DEBUG) || defined(DEBUG)
#	define RAV_DEBUG
#elif defined(NDEBUG)
#	define RAV_NDEBUG
#else
#	error "RAVAGE ERROR: Invalid debug/release preprocessor defines."
#endif


//TODO: Other defines (export, etc).

}

#endif // RAVDEFINES_H_INCLUDED
