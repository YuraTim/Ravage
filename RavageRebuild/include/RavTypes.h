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

#ifndef RAVTYPES_H_INCLUDED
#define RAVTYPES_H_INCLUDED

//Временное решение из-за отсутствия других
#define RAV_USE_STL

#ifdef RAV_USE_STL

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <ios>
#include <utility>

namespace Ravage
{
    #ifdef UNICODE
        typedef std::wfstream  FStream;
        typedef std::wifstream FIStream;
        typedef std::wofstream FOStream;

        typedef std::wstring String;
        typedef wchar_t      Symbol;
    #else //UNICODE
        typedef std::ifstream FIStream;
        typedef std::ofstream FOStream;
        typedef std::fstream  FStream;

        typedef std::string String;
        typedef char        Symbol;
    #endif //UNICODE

    typedef std::basic_iostream<Symbol> Stream;
    typedef std::basic_istream<Symbol>  IStream;
    typedef std::basic_ostream<Symbol>  OStream;

    typedef std::ios ios;

    typedef std::vector<String> StringVector;
	typedef char Byte;
	typedef unsigned int Word;

	typedef unsigned short ushort;
	typedef unsigned char uchar;

	typedef char               S8;
	typedef unsigned char      U8;
	typedef short int          S16;
	typedef unsigned short int U16;
	typedef int                S32;
	typedef unsigned int       U32;

#if RAV_COMPILER == RAV_COMPILER_MSVC
	typedef unsigned __int64   U64;
	typedef __int64            S64;
#else /* RAV_COMPILER */
#	error "RAVAGE ERROR: Not implemented"
#endif
}

#endif //RAV_USE_STL

#endif // RAVTYPES_H_INCLUDED
