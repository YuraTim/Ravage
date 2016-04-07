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

    //! @brief Класс для работы над строками
    class StringUtils
    {
        public:
            //! @brief Очищает строку от ненужных символов.
            //! @param string Изменяемая строка.
            //! @return Изменённая строка.
            static String& trim(String& string, const String& delim = DELIMETER);
			 
			//! @brief Очищает строку от ненужных символов слева.
            //! @param string Изменяемая строка.
            //! @return Изменённая строка.
            static String& trimLeft(String& string, const String& delim = DELIMETER);
			
			//! @brief Очищает строку от ненужных символов справа.
            //! @param string Изменяемая строка.
            //! @return Изменённая строка.
            static String& trimRight(String& string, const String& delim = DELIMETER);

			//! @brief Преобразует C строку в String.
			//! @param string Входная C строка.
			//! @param size Максимальный размер строки.
			//! @return Новая строка.
			static String convert(const char* string, int size);

			//! @brief Преобразует C строку в String.
			//! @param string Входная C строка.
			//! @param size Максимальный размер строки.
			//! @return Новая строка.
			static String convert(const wchar_t* string, int size);

			//! @brief Преобразует символ в Symbol.
			//! @param symbol Входной символ.
			//! @return Тот же символ в формате Symbol.
			static Symbol convert(char symbol);

			//! @brief Преобразует символ в Symbol.
			//! @param symbol Входной символ.
			//! @return Тот же символ в формате Symbol.
			static Symbol convert(wchar_t symbol);

			//! @brief Создаёт C строку из String (должна быть освобождена).
			//! @param str Входная строка.
			//! @return Новая строка.
			static char* newConvertA(const String& str);
			
			//! @brief Создаёт C строку в String (должна быть освобождена).
			//! @param str Входная C строка.
			//! @return Новая строка.
			static wchar_t* newConvertW(const String& str);

			static Real toReal(const String& str);
			static int  toInt(const String& str);

            //! @brief Пустая строка.
            static const String BLANK;

            //! @brief Строка с разделительными символами.
            static const String DELIMETER;
    };

} //namespace Ravage

#endif // RAVSTRINGUTILS_H_INCLUDED
