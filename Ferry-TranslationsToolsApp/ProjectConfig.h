#pragma once

#include "QString"
#include "QVariant"
#include "QVariantMap"
#include "QDir"
#include "QFile"
#include "QFileInfo"
#include "QSaveFile"
#include "QJsonDocument"
#include "QJsonObject"
#include "QJsonParseError"

#ifndef PROJECTCONFIG_H
#define PROJECTCONFIG_H

class ProjectConfig {
public:
    static constexpr int kCurrentVersion = 1;
    static inline const QString kFormatName = QStringLiteral("FerryProject");

    ProjectConfig() = default;

    // Generic key/value access (Use dotted keys like "editor.fontSize")
    void setValue(const QString &key, const QVariant &value) {
        m_values.insert(key, value);
    }
    QVariant value(const QString &key, const QVariant &defaultValue = QVariant()) {
        return m_values.value(key, defaultValue);
    }
    bool contains(const QString &key) const { return m_values.contains(key); }
    void remove(const QString &key) { m_values.remove(key); }
    void clear() { m_values.clear(); }
    QStringList keys() const { return m_values.keys(); }

    // TODO: Convience helpers for types JSON can't store nativly.

    // File I/O
    // Both return false on failure and fill *error (if given) with a message.
    bool save(const QString &filePath, QString *error = nullptr) const {
        const QDir dir = QFileInfo(filePath).absoluteDir();
        if (!dir.exists() && !dir.mkpath("."))
            return fail(error, QObject::tr("Cannot create directory: %1").arg(dir.absolutePath()));
        // QSaveFile writes to a temp file and renames on commit, so a crash
        // mid-write can't corrupt an existing project file.
        QSaveFile file(filePath);
        if (!file.open(QIODevice::WriteOnly))
            return fail(error, QObject::tr("Cannot open file for writing: %1").arg(file.errorString()));
        const QByteArray data = QJsonDocument(toJson()).toJson(QJsonDocument::Indented);
        if (file.write(data) != data.size())
            return fail(error, QObject::tr("Write failed: %1").arg(file.errorString()));
        if (!file.commit())
            return fail(error, QObject::tr("Cannot save file: %1").arg(file.errorString()));
        return true;
    }

    bool load(const QString &filePath, QString *error = nullptr) {
        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly))
            return fail(error, QObject::tr("Cannot open file: %1").arg(file.errorString()));
        QJsonParseError parseError;
        const QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &parseError);
        if (parseError.error != QJsonParseError::NoError)
            return fail(error, QObject::tr("Invalid JSON (offset %1): %2")
                                   .arg(parseError.offset)
                                   .arg(parseError.errorString()));
        if (!doc.isObject())
            return fail(error, QObject::tr("Project file root must be an object."));
        return fromJson(doc.object(), error);
    }

    QJsonObject toJson() const {
        QJsonObject root;
        root["format"] = kFormatName;
        root["version"] = kCurrentVersion;
        root["settings"] = QJsonObject::fromVariantMap(m_values);
        return root;
    }

    bool fromJson(const QJsonObject &root, QString *error = nullptr) {
        if (root.value("format").toString() != kFormatName)
            return fail(error, QObject::tr("Not a valid project file."));
        const int version = root.value("version").toInt(-1);
        if (version < 1)
            return fail(error, QObject::tr("Project file has a missing or invalid version."));
        if (version > kCurrentVersion)
            return fail(error, QObject::tr("Project file was created by a newer version of the application (v%1).").arg(version));
        QJsonObject settings = root.value("settings").toObject();
        m_migrated = false;
        if (version < kCurrentVersion) {
            migrate(settings, version);
            m_migrated = true;
        }
        m_values = settings.toVariantMap();
        return true;
    }

    bool wasMigrated() const { return m_migrated; }

private:
    static bool fail(QString *error, const QString &message) {
        if (error)
            *error = message;
        return false;
    }

    static void migrate(QJsonObject &settings, int fromVersion) {
        Q_UNUSED(settings);
        switch (fromVersion) {
        case 1:
            // TODO: v1 -> v2: rename keys, defaults, and etc.
            Q_FALLTHROUGH();
        default:
            break;
        }
    }

    QVariantMap m_values;
    bool m_migrated = false;
};

#endif // PROJECTCONFIG_H
