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

//!
//! @file    RavConfigFile.h
//! @brief   �������� ����� ��������� ������ ������������
//! @version 0.9
//! @author  Yuriy Timofeev
//! @date    2011

#ifndef RAVCONFIGFILE_H_INCLUDED
#define RAVCONFIGFILE_H_INCLUDED

#include "RavBase.h"
#include "RavStringUtils.h"
#include "RavFile.h"

namespace Ravage
{
    //! @brief ����� ��� ��������� ������ ������������.
    class ConfigFile
    {
    public:
        //! @brief ������ ��� �������� ����� �� ��� �����.
        typedef std::multimap<String, String> SettingsMultiMap;
        //! @brief ������ ��� ����� �� ������.
        typedef std::map<String, SettingsMultiMap*> SettingsSections;

        //! @brief ����������� ����������.
        static const String SEPARATORS;
    public:
        //! @brief �����������.
        ConfigFile();

        //! @brief ����������.
        virtual ~ConfigFile();

        //! @brief ����������� ����������� (�� ����������)!
        //! @param config ������ �� ������ ConfigFile.
        ConfigFile(const ConfigFile& config);

        //! @brief �������� ������������ (�� ����������)!
        //! @param config ������ �� ������ ConfigFile.
        //! @return ������ �� ������� ������.
        ConfigFile& operator= (const ConfigFile& config);

        //! @brief ��������� ������ �� ����������������� �����.
        //! @param filename   ��� ����� ��� ��������.
        //! @param separators ������, ���������� �������������� ������� ����� ������ � ���������.
        //! @param trim       ������� �� ���������� ������� �� ���������� �����.
        void load(const String& filename, const String& separators = SEPARATORS, bool trim = true);

        //! @brief ��������� ������ �� ������.
        //! @param file       ����.
        //! @param separators ������, ���������� �������������� ������� ����� ������ � ���������.
        //! @param trim       ������� �� ���������� ������� �� ���������� �����.
        void load(File& file, const String& separators = SEPARATORS, bool trim = true);

        //! @brief ��������� ������ � ����.
        //! @param stream    ��� ����� ��� ����������.
        //! @param separator �������������� ������ ����� ������ � ���������.
        //! @param insSpace  ��������� �� ���������� ������� � ����������.
        void save(const String& filename, const Symbol& separator = RAV_TXT('='), bool insSpace = true) const;

        //! @brief ��������� ������ � �����.
        //! @param stream    �����.
        //! @param separator �������������� ������ ����� ������ � ���������.
        //! @param insSpace  ��������� �� ���������� ������� � ����������.
        void save(OStream& stream, const Symbol& serarator = RAV_TXT('='), bool insSpace = true) const;

        //! @brief ���������� ��������� �������� �����.
        //! @param key        ����, �� �������� ������ ��������.
        //! @param section    ������, � ������� ��������� ����.
        //! @param defaultVal �������� ������������ ��� ���������� ����� � ������.
        //! @return ��������� ��������, ���� defaultVal, ���� ������ �������� ���.
        String getSetting(const String& key,
                            const String& section = StringUtils::BLANK,
                            const String& defaultVal = StringUtils::BLANK) const;

        //! @brief ���������� ��������� �������� �����.
        //! @param key        ����, �� �������� ������ ��������.
        //! @param section    ������, � ������� ��������� ����.
        //! @param defaultVal �������� ������������ ��� ���������� ����� � ������.
        //! @return ��������� ��������, ���� defaultVal, ���� ������ �������� ���.
        int getIntSetting(const String& key,
                            const String& section = StringUtils::BLANK,
                            int defaultVal = 0) const;

        //! @brief ���������� ��������� �������� �����.
        //! @param key        ����, �� �������� ������ ��������.
        //! @param section    ������, � ������� ��������� ����.
        //! @param defaultVal �������� ������������ ��� ���������� ����� � ������.
        //! @return ��������� ��������, ���� defaultVal, ���� ������ �������� ���.
        Real getRealSetting(const String& key,
                            const String& section = StringUtils::BLANK,
                            Real defaultVal = 0) const;

        //! @brief ���������� ��������� �������� �����.
        //! @param key        ����, �� �������� ������ ��������.
        //! @param section    ������, � ������� ��������� ����.
        //! @param defaultVal �������� ������������ ��� ���������� ����� � ������.
        //! @return ��������� ��������, ���� defaultVal, ���� ������ �������� ���.
        bool getBoolSetting(const String& key,
                            const String& section = StringUtils::BLANK,
                            bool defaultVal = 0) const;

        //! @brief ���������� ��� �������� �����.
        //! @param key     ����, �� �������� ������ ��������.
        //! @param section ������, � ������� ��������� ����.
        //! @return ������ �� ��������� ��������.
        StringVector getSettings(const String& key, const String& section = StringUtils::BLANK) const;

        //! @brief ���������� ��� ����� � �� ��������, ���������� � ������.
        //! @param section �������� ������.
        const SettingsMultiMap* getSection(const String& section = StringUtils::BLANK) const;

        //! @brief ������ ��� ���������� ������.
        void clear();

        //! @brief �������� � ����� ������ �� ������� ConfigFile.
        //! @param file ConfigFile, �� �������� ���������� ������.
        void copy(const ConfigFile& file);

        //! @brief ������� ����.
        //! @param key     ����, ������� ���������.
        //! @param section ������, � ������� ��������� ����.
        void deleteKey(const String& key,
                        const String& section = StringUtils::BLANK);

        //! @brief ������� ������.
        //! @param section ������, ������� ���������.
        void deleteSection(const String& section = StringUtils::BLANK);

        //! @brief ����� ����� �������� ��� �����, ������ ������.
        //! @param key     ����, �� �������� ������� ��������.
        //! @param value   ��������, ������� ������ �����.
        //! @param section ������, � ������� ��������� ����.
        void setSetting(const String& key,
                        const String& value,
                        const String& section = StringUtils::BLANK);

        //! @brief ��������� �������� ��� �����.
        //! @param key     ����, �� �������� ������� ��������.
        //! @param value   ��������, ������� ������ �����.
        //! @param section ������, � ������� ��������� ����.
        void addSetting(const String& key,
                        const String& value,
                        const String& section = StringUtils::BLANK);


    protected:
        //! @brief ��������� ������ � �����.
        //! @param stream    �����.
        //! @param section   �������� ������.
        //! @param settings  ��������� �� �������� ���� ������.
        //! @param separator �������������� ������ ����� ������ � ���������.
        //! @param insSpace  ��������� �� ���������� ������� � ����������.
        void saveSection(OStream& stream,
                            const String& section,
                            const SettingsMultiMap* settings,
                            const Symbol& separator,
                            bool insSpace) const;

        //! @brief ������ ��� ������ ������.
        SettingsSections mSettings;
    };
} //namespace Ravage


#endif // RAVCONFIGFILE_H_INCLUDED
