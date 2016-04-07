#include "RavConfigFile.h"

namespace Ravage
{
    const String ConfigFile::SEPARATORS = RAV_TXT("\t=:");

    ConfigFile::ConfigFile()
    {}

    ConfigFile::~ConfigFile()
    {
        clear();
    }

    void ConfigFile::load(const String& filename, const String& separator, bool trim)
    {
        File file;
		if (!file.open(filename, RAV_FMODE_READ | RAV_FMODE_TEXT))
		{
			//TODO: Error log.
			return;
		}
		load(file, separator, trim);
	}

    void ConfigFile::load(File& file, const String& separator, bool trim)
    {
        String            curSection     = StringUtils::BLANK;
        SettingsMultiMap* curSettingsMap = new SettingsMultiMap;

        mSettings[curSection] = curSettingsMap;

        String line, resKey, resValue, trimline;
		while(!file.isEnd())
        {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           ;
			file.readLine(line, RAV_TXT("\n"));

            //Remove comments from string.
            String::size_type offset = line.find_first_of(RAV_TXT("#@"));
            if (offset != String::npos)
                line = line.substr(0, offset);

            trimline = line;
            StringUtils::trim(trimline);

            String::size_type length = trimline.length();

            if (length >= 2 && trimline.at(0) == '[' && trimline.at(length - 1) == ']')
            {
                //Analize section.
                curSection = trimline.substr(1, length - 2);

                SettingsSections::iterator sect = mSettings.find(curSection);
                if (sect == mSettings.end())
                {
                    curSettingsMap = new SettingsMultiMap;
                    mSettings[curSection] = curSettingsMap;
                }
                else
                {
                    curSettingsMap = sect->second;
                }
            }
            else
            {
                String::size_type separator_start = line.find_first_of(separator);
                if (separator_start != String::npos)
                {
                    String::size_type separator_end = line.find_first_not_of(separator, separator_start);

                    resKey   = line.substr(0, separator_start);
                    resValue = (separator_end != String::npos) ? line.substr(separator_end) : StringUtils::BLANK;

                    if (trim)
                    {
                        StringUtils::trim(resKey);
                        StringUtils::trim(resValue, StringUtils::DELIMETER + String(RAV_TXT("\"")));
                    }
                    curSettingsMap->insert(std::make_pair(resKey, resValue));
                }
            }
        }
    }

    void ConfigFile::save(const String& filename, const Symbol& separator, bool insSpace) const
    {
        FOStream filestream;

        //TODO: Open file from virtual file system.
        filestream.open(filename.c_str(), std::ios::out | std::ios::binary);
        if (!filestream)
        {
            //TODO: Throw exception.
            return;
        }

        save(filestream, separator, insSpace);
    }

    void ConfigFile::save(OStream& stream, const Symbol& separator, bool insSpace) const
    {
        SettingsSections::const_iterator sect_cur;

        sect_cur = mSettings.find(StringUtils::BLANK);
        if (sect_cur != mSettings.end())
            saveSection(stream, sect_cur->first, sect_cur->second, separator, insSpace);

        SettingsSections::const_iterator sect_end = mSettings.end();
        for (sect_cur = mSettings.begin(); sect_cur != sect_end; ++sect_cur)
        {
            if (sect_cur->first == StringUtils::BLANK)
                continue;

            saveSection(stream, sect_cur->first, sect_cur->second, separator, insSpace);
        }
    }

    String ConfigFile::getSetting(const String& key, const String& section, const String& defaultVal) const
    {
        SettingsSections::const_iterator sect = mSettings.find(section);
        if (sect == mSettings.end())
            return defaultVal;

        SettingsMultiMap::const_iterator settings = sect->second->find(key);

        if (settings == sect->second->end())
            return defaultVal;

        return settings->second;
    }

    int ConfigFile::getIntSetting(const String& key, const String& section, int defaultVal) const
    {
        SettingsSections::const_iterator sect = mSettings.find(section);
        if (sect == mSettings.end())
            return defaultVal;

        SettingsMultiMap::const_iterator settings = sect->second->find(key);

        if (settings == sect->second->end())
            return defaultVal;

        int value = 0;
        std::basic_istringstream<Symbol> sstream(settings->second);
        sstream >> value;
        return value;
    }

    Real ConfigFile::getRealSetting(const String& key, const String& section, Real defaultVal) const
    {
        SettingsSections::const_iterator sect = mSettings.find(section);
        if (sect == mSettings.end())
            return defaultVal;

        SettingsMultiMap::const_iterator settings = sect->second->find(key);

        if (settings == sect->second->end())
            return defaultVal;

        Real value = 0;
        std::basic_istringstream<Symbol> sstream(settings->second);
        sstream >> value;
        return value;
    }

    bool ConfigFile::getBoolSetting(const String& key, const String& section, bool defaultVal) const
    {
        SettingsSections::const_iterator sect = mSettings.find(section);
        if (sect == mSettings.end())
            return defaultVal;

        SettingsMultiMap::const_iterator settings = sect->second->find(key);

        if (settings == sect->second->end())
            return defaultVal;

        Real value = 0;
        std::basic_istringstream<Symbol> sstream(settings->second);
        sstream >> value;
        return value > 0;
    }

    StringVector ConfigFile::getSettings(const String& key, const String& section) const
    {
        StringVector result;

        SettingsSections::const_iterator sect = mSettings.find(section);
        if (sect == mSettings.end())
            return result;

        SettingsMultiMap::const_iterator settings = sect->second->find(key);

        while (settings != sect->second->end() && settings->first == key)
        {
            result.push_back(settings->second);
            ++settings;
        }
        return result;
    }

    const ConfigFile::SettingsMultiMap* ConfigFile::getSection(const String& section) const
    {
        SettingsSections::const_iterator sect = mSettings.find(section);
        if (sect == mSettings.end())
            return 0;

        return sect->second;
    }

    void ConfigFile::clear()
    {
        SettingsSections::iterator sect_end = mSettings.end();
        for (SettingsSections::iterator sect = mSettings.begin(); sect != sect_end; ++sect)
        {
            delete sect->second;
            sect->second = 0;
        }

        mSettings.clear();
    }

    void ConfigFile::saveSection(OStream& stream,
                                 const String& section,
                                 const SettingsMultiMap* settings,
                                 const Symbol& separator,
                                 bool insSpace) const
    {
        if (!section.empty())
            stream << '[' << section << ']' << std::endl;

        SettingsMultiMap::const_iterator set_end = settings->end();
        for (SettingsMultiMap::const_iterator set_iter = settings->begin(); set_iter != set_end; ++set_iter)
        {
            stream << set_iter->first;

            if (insSpace)
                stream << ' ';

            stream << separator;

            if (insSpace)
                stream << ' ';

            stream << set_iter->second << std::endl;
        }

        stream << std::endl;
    }

    void ConfigFile::deleteKey(const String& key,
                               const String& section)
    {
        SettingsSections::iterator sect = mSettings.find(section);
        if (sect == mSettings.end())
            return;

        sect->second->erase(key);
    }

    void ConfigFile::deleteSection(const String& section)
    {
        mSettings.erase(section);
    }

    void ConfigFile::setSetting(const String& key,
                                const String& value,
                                const String& section)
    {
        deleteKey(key, section);
        addSetting(key, value, section);
    }

    void ConfigFile::addSetting(const String& key,
                                const String& value,
                                const String& section)
    {
        SettingsSections::iterator sect = mSettings.find(section);
        if (sect == mSettings.end())
            mSettings.insert(std::make_pair(section, new SettingsMultiMap));

        sect->second->insert(std::make_pair(key, value));
    }

    void ConfigFile::copy(const ConfigFile& file)
    {
        clear();

        SettingsSections::const_iterator sect_end = file.mSettings.end();
        for (SettingsSections::const_iterator sect = file.mSettings.begin(); sect != sect_end; ++sect)
        {
            SettingsMultiMap* settings = new SettingsMultiMap (*(sect->second));
            mSettings.insert(std::make_pair(sect->first, settings));
        }
    }

    ConfigFile::ConfigFile(const ConfigFile& file)
    {
        copy(file);
    }

    ConfigFile& ConfigFile::operator= (const ConfigFile& file)
    {
        copy(file);
        return *this;
    }
}
