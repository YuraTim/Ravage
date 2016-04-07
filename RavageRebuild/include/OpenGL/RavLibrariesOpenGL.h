#ifndef RAVLIBRARIESOPENGL_H_INCLUDED
#define RAVLIBRARIESOPENGL_H_INCLUDED

#include "RavDefines.h"

#if RAV_PLATFORM == RAV_PLATFORM_WIN32 && RAV_COMPILER == RAV_COMPILER_MSVC
#	include <Windows.h>
#	include "gl\glew.h"
#	include "gl\wglew.h"

#	pragma comment(lib, "OpenGL32.lib")
#	pragma comment(lib, "Glew32.lib")

#else
#	error "RAVAGE ERROR: Not implemented."
#endif

#endif /* RAVLIBRARIESOPENGL_H_INCLUDED */