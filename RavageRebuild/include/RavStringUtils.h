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

#ifndef RAVSTRINGUTILS_H_INCLUDED
#define RAVSTRINGUTILS_H_INCLUDED

#include "RavBase.h"

namespace Ravage
{

    //! @brief ����� ��� ������ ��� ��������
    class StringUtils
    {
        public:
            //! @brief ������� ������ �� �������� ��������.
            //! @param string ���������� ������.
            //! @return ��������� ������.
            static String& trim(String& string, const String& delim = DELIMETER);
			 
			//! @brief ������� ������ �� �������� �������� �����.
            //! @param string ���������� ������.
            //! @return ��������� ������.
            static String& trimLeft(String& string, const String& delim = DELIMETER);
			
			//! @brief ������� ������ �� �������� �������� ������.
            //! @param string ���������� ������.
            //! @return ��������� ������.
            static String& trimRight(String& string, const String& delim = DELIMETER);

			//! @brief ����������� C ������ � String.
			//! @param string ������� C ������.
			//! @param size ������������ ������ ������.
			//! @return ����� ������.
			static String convert(const char* string, int size);

			//! @brief ����������� C ������ � String.
			//! @param string ������� C ������.
			//! @param size ������������ ������ ������.
			//! @return ����� ������.
			static String convert(const wchar_t* string, int size);

			//! @brief ����������� ������ � Symbol.
			//! @param symbol ������� ������.
			//! @return ��� �� ������ � ������� Symbol.
			static Symbol convert(char symbol);

			//! @brief ����������� ������ � Symbol.
			//! @param symbol ������� ������.
			//! @return ��� �� ������ � ������� Symbol.
			static Symbol convert(wchar_t symbol);

			//! @brief ������ C ������ �� String (������ ���� �����������).
			//! @param str ������� ������.
			//! @return ����� ������.
			static char* newConvertA(const String& str);
			
			//! @brief ������ C ������ � String (������ ���� �����������).
			//! @param str ������� C ������.
			//! @return ����� ������.
			static wchar_t* newConvertW(const String& str);

			static Real toReal(const String& str);
			static int  toInt(const String& str);

            //! @brief ������ ������.
            static const String BLANK;

            //! @brief ������ � ��������������� ���������.
            static const String DELIMETER;
    };

} //namespace Ravage

#endif // RAVSTRINGUTILS_H_INCLUDED
