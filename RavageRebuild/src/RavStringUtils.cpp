#include "RavStringUtils.h"

namespace Ravage
{
    const String StringUtils::DELIMETER = RAV_TXT("\t\n\r ");
    const String StringUtils::BLANK     = RAV_TXT("");

    String& StringUtils::trim(String& str, const String& delim)
    {
        String::size_type first = str.find_first_not_of(delim);
        String::size_type last  = str.find_last_not_of(delim);

        if (first == String::npos || last == String::npos)
            str = StringUtils::BLANK;
        else
        {
            String::size_type size = last - first + 1;
            str = str.substr(first, size);
        }

        return str;
    }

	String& StringUtils::trimLeft(String& str, const String& delim)
    {
        String::size_type first = str.find_first_not_of(delim);

        if (first == String::npos)
            str = StringUtils::BLANK;
        else
            str = str.substr(first);

        return str;
    }

	String& StringUtils::trimRight(String& str, const String& delim)
    {
        String::size_type last  = str.find_last_not_of(delim);

        if (last == String::npos)
            str = StringUtils::BLANK;
        else
            str = str.substr(0, last + 1);

        return str;
    }

	String StringUtils::convert(const char* str, int size)
	{
#ifdef UNICODE
		Symbol* buffer = new Symbol[size + 1];
		mbstowcs(buffer, str, size + 1);
		String result(buffer);
		delete[] buffer;
		return result;
#else
		return String(str);
#endif
	}

	String StringUtils::convert(const wchar_t* str, int size)
	{
#ifndef UNICODE
		Symbol* buffer = new Symbol[size + 1];
		wcstombs(buffer, str, size + 1);
		String result(buffer);
		delete[] buffer;
		return result;
#else
		return String(str);
#endif
	}

	Symbol StringUtils::convert(char symbol)
	{
#ifdef UNICODE
		Symbol result;
		mbstowcs(&result, &symbol, 1);
		return result;
#else
		return symbol;
#endif
	}

	Symbol StringUtils::convert(wchar_t symbol)
	{
#ifndef UNICODE
		Symbol result;
		wcstombs(&result, &symbol, 1);
		return result;
#else
		return symbol;
#endif
	}

	char* StringUtils::newConvertA(const String& str)
	{
		char* result = new char[str.size() + 1];
#ifdef UNICODE
		wcstombs(result, str.c_str(), str.size() + 1);
#else
		memcpy(result, str.c_str(), sizeof(char) * (str.size() + 1));
#endif
		return result;
	}

	wchar_t* StringUtils::newConvertW(const String& str)
	{
		wchar_t* result = new wchar_t[str.size() + 1];
#ifndef UNICODE
		mbstowcs(result, str.c_str(), str.size() + 1);
		return result;
#else
		memcpy(result, str.c_str(), sizeof(wchar_t) * (str.size() + 1));
#endif
		return result;
	}

	template<typename Type>
	inline Type toType(const String& str)
	{
		//TODO: Change this.
		Type result;
		std::basic_istringstream<Symbol> iss(str);
		iss >> result;
		return result;
	}

	Real StringUtils::toReal(const String& str)
	{
		return toType<Real>(str);
	}

	int StringUtils::toInt(const String& str)
	{
		return toType<int>(str);
	}
}
