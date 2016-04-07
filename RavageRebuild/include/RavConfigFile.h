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
//! @brief   Содержит класс обработки файлов конфигурации
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
    //! @brief Класс для обработки файлов конфигурации.
    class ConfigFile
    {
    public:
        //! @brief Хранит все значения ключа по его имени.
        typedef std::multimap<String, String> SettingsMultiMap;
        //! @brief Хранит все ключи по секцям.
        typedef std::map<String, SettingsMultiMap*> SettingsSections;

        //! @brief Стандартные сепараторы.
        static const String SEPARATORS;
    public:
        //! @brief Конструктор.
        ConfigFile();

        //! @brief Деструктор.
        virtual ~ConfigFile();

        //! @brief Конструктор копирования (не реализован)!
        //! @param config Ссылка на объект ConfigFile.
        ConfigFile(const ConfigFile& config);

        //! @brief Оператор присваивания (не реализован)!
        //! @param config Ссылка на объект ConfigFile.
        //! @return Ссылка на текущий объект.
        ConfigFile& operator= (const ConfigFile& config);

        //! @brief Загружает данные из конфигурационного файла.
        //! @param filename   Имя файла для загрузки.
        //! @param separators Строка, содержащая разделительные символы между ключом и значением.
        //! @param trim       Удалять ли пробельные символы из полученных строк.
        void load(const String& filename, const String& separators = SEPARATORS, bool trim = true);

        //! @brief Загружает данные из потока.
        //! @param file       Файл.
        //! @param separators Строка, содержащая разделительные символы между ключом и значением.
        //! @param trim       Удалять ли пробельные символы из полученных строк.
        void load(File& file, const String& separators = SEPARATORS, bool trim = true);

        //! @brief Сохраняет данные в файл.
        //! @param stream    Имя файла для сохранения.
        //! @param separator Разделительный символ между ключом и значением.
        //! @param insSpace  Вставлять ли пробельные символы к сепаратору.
        void save(const String& filename, const Symbol& separator = RAV_TXT('='), bool insSpace = true) const;

        //! @brief Сохраняет данные в поток.
        //! @param stream    Поток.
        //! @param separator Разделительный символ между ключом и значением.
        //! @param insSpace  Вставлять ли пробельные символы к сепаратору.
        void save(OStream& stream, const Symbol& serarator = RAV_TXT('='), bool insSpace = true) const;

        //! @brief Возвращает последнее значение ключа.
        //! @param key        Ключ, по которому берётся значение.
        //! @param section    Секция, в которой находится ключ.
        //! @param defaultVal Значение возвращаемое при отсутствии ключа в секции.
        //! @return Найденное значение, либо defaultVal, если такого значания нет.
        String getSetting(const String& key,
                            const String& section = StringUtils::BLANK,
                            const String& defaultVal = StringUtils::BLANK) const;

        //! @brief Возвращает последнее значение ключа.
        //! @param key        Ключ, по которому берётся значение.
        //! @param section    Секция, в которой находится ключ.
        //! @param defaultVal Значение возвращаемое при отсутствии ключа в секции.
        //! @return Найденное значение, либо defaultVal, если такого значения нет.
        int getIntSetting(const String& key,
                            const String& section = StringUtils::BLANK,
                            int defaultVal = 0) const;

        //! @brief Возвращает последнее значение ключа.
        //! @param key        Ключ, по которому берётся значение.
        //! @param section    Секция, в которой находится ключ.
        //! @param defaultVal Значение возвращаемое при отсутствии ключа в секции.
        //! @return Найденное значение, либо defaultVal, если такого значения нет.
        Real getRealSetting(const String& key,
                            const String& section = StringUtils::BLANK,
                            Real defaultVal = 0) const;

        //! @brief Возвращает последнее значение ключа.
        //! @param key        Ключ, по которому берётся значение.
        //! @param section    Секция, в которой находится ключ.
        //! @param defaultVal Значение возвращаемое при отсутствии ключа в секции.
        //! @return Найденное значение, либо defaultVal, если такого значения нет.
        bool getBoolSetting(const String& key,
                            const String& section = StringUtils::BLANK,
                            bool defaultVal = 0) const;

        //! @brief Возвращает все значения ключа.
        //! @param key     Ключ, по которому берётся значение.
        //! @param section Секция, в которой находится ключ.
        //! @return Вектор из найденных значений.
        StringVector getSettings(const String& key, const String& section = StringUtils::BLANK) const;

        //! @brief Возвращает все ключи и их значения, хранящиеся в секции.
        //! @param section Название секции.
        const SettingsMultiMap* getSection(const String& section = StringUtils::BLANK) const;

        //! @brief Удалят все хранящиеся данные.
        void clear();

        //! @brief Копирует в класс данные из другого ConfigFile.
        //! @param file ConfigFile, из которого копируются данные.
        void copy(const ConfigFile& file);

        //! @brief Удаляет ключ.
        //! @param key     Ключ, который удаляется.
        //! @param section Секция, в которой находится ключ.
        void deleteKey(const String& key,
                        const String& section = StringUtils::BLANK);

        //! @brief Удаляет секцию.
        //! @param section Секция, которая удаляется.
        void deleteSection(const String& section = StringUtils::BLANK);

        //! @brief Задаёт новое значение для ключа, стирая старые.
        //! @param key     Ключ, по которому задаётся значение.
        //! @param value   Значение, которое задётся ключу.
        //! @param section Секция, в которой находится ключ.
        void setSetting(const String& key,
                        const String& value,
                        const String& section = StringUtils::BLANK);

        //! @brief Добавляет значение для ключа.
        //! @param key     Ключ, по которому задаётся значение.
        //! @param value   Значение, которое задётся ключу.
        //! @param section Секция, в которой находится ключ.
        void addSetting(const String& key,
                        const String& value,
                        const String& section = StringUtils::BLANK);


    protected:
        //! @brief Сохраняет секцию в поток.
        //! @param stream    Поток.
        //! @param section   Название секции.
        //! @param settings  Указатель на значения этой секции.
        //! @param separator Разделительный символ между ключом и значением.
        //! @param insSpace  Вставлять ли пробельные символы к сепаратору.
        void saveSection(OStream& stream,
                            const String& section,
                            const SettingsMultiMap* settings,
                            const Symbol& separator,
                            bool insSpace) const;

        //! @brief Хранит все данные класса.
        SettingsSections mSettings;
    };
} //namespace Ravage


#endif // RAVCONFIGFILE_H_INCLUDED
