#include "RavResourceAsset.h"

namespace Ravage
{
	ResourceAssetStruct::ResourceAssetStruct(const String& t, const String& n) :
		type(t),
		name(n)
	{}

	ResourceAssetStruct::~ResourceAssetStruct()
	{
		std::vector<ResourceAssetStruct*>::iterator iter = structs.begin();
		for(; iter != structs.end(); ++iter)
			delete *iter;
	}

	ResourceAsset::ResourceAsset()
	{
		mMainStruct.name = mMainStruct.type = RAV_TXT("Main");
	}

	bool ResourceAsset::load(Byte* byte, int size)
	{
		return false;
	}

	bool ResourceAsset::load(File& file)
	{
		String result;
		if (!file.readLine(result, StringUtils::BLANK))
		{
			//TODO: Error log.
			return false;
		}
		return parseStruct(&mMainStruct, result) && result.empty();
	}

	bool ResourceAsset::load(const String& filename)
	{
		File file;
		if (!file.open(filename, RAV_FMODE_READ | RAV_FMODE_TEXT))
		{
			//TODO: Error log.
			return false;
		}
		return load(file);
	}

	bool ResourceAsset::parseStruct(ResourceAssetStruct* current, String& code)
	{
		StringUtils::trimLeft(code);
		while (!code.empty() && code.at(0) != RAV_TXT('}'))
		{
			String::size_type offset = code.find_first_of(StringUtils::DELIMETER);
			String name = code.substr(0, offset);

			if (offset == String::npos)
				code = StringUtils::BLANK;
			else
				code = code.substr(offset + 1);

			if (!parseParameter(current, name, code))
				return false;
			
			StringUtils::trimLeft(code);
		}
		return true;
	}

	bool ResourceAsset::parseParameter(ResourceAssetStruct* current, const String& name, String& code)
	{
		//Impossible situation.
		if (name.empty())
		{
			//TODO: Error log.
			return false;
		}

		//Check extended parameter.
		String::size_type size = name.size();
		if (size >= 3 && name.at(0) == RAV_TXT('[') && name.at(size - 1) == RAV_TXT(']'))
		{
			String type = name.substr(1, size - 2);
			String end = RAV_TXT("[/") + type + RAV_TXT("]");
			String::size_type offset = code.find(end);

			if (offset == String::npos)
			{
				//TODO: Error log.
				return false;
			}

			String value = code.substr(0, offset);
			code = code.substr(offset + end.size());

			ResourceAssetStruct* extparameter = new ResourceAssetStruct(type, value);
			current->structs.push_back(extparameter);
			return true;
		}

		//Read parameter value.
		String::size_type offset = 0;
		String value;
		if (!code.empty() && code.at(0) == RAV_TXT('"'))
		{
			offset = code.find(RAV_TXT('"'), 1);
			if (offset == String::npos)
			{
				//TODO: Error log.
				return false;
			}

			value = code.substr(1, offset - 1);
			code = code.substr(offset + 1);
		}
		else
		{
			offset = code.find_first_of(StringUtils::DELIMETER + RAV_TXT("{,;"));
		
			value = code.substr(0, offset);
			if (offset == String::npos)
				code = StringUtils::BLANK;
			else
				code = code.substr(offset);
		}

		ResourceAssetStruct* parameter = new ResourceAssetStruct(name, value);

		//Check struct type.
		StringUtils::trimLeft(code);
		if (!code.empty() && code.at(0) == RAV_TXT('{'))
		{
			offset = code.find(RAV_TXT('}'), 1);
			if (offset == String::npos)
			{
				//TODO: Error log.
				delete parameter;
				return false;
			}

			code = code.substr(1);

			if (!parseStruct(parameter, code))
			{
				delete parameter;
				return false;
			}

			code = code.substr(1);

			StringUtils::trimLeft(code);
		}

		current->structs.push_back(parameter);
		StringUtils::trimLeft(code, RAV_TXT(",;"));
		return true;
	}
}