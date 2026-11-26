#pragma once

#include "QObject"
#include "ProjectConfig.h"

#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H

class Project : public QObject {
    Q_OBJECT
public:
    explicit Project(QObject *parent = nullptr) : QObject(parent) {}

    QString filePath() const { return m_filePath; }
    QString name() const { return m_name; }
    // TODO: Add more information of project if needed in future.

    void setName(const QString &v) {
        if (v == m_name)
            return;
        m_name = v;
    }

    bool save(QString *error = nullptr) {
        if (m_filePath.isEmpty()) {
            if (error) *error = tr("Project has no file path yet.");
            return false;
        }
        return saveAs(m_filePath, error);
    }

    bool saveAs (const QString &filePath, QString *error = nullptr) {
        ProjectConfig cfg;
        cfg.setValue("project.name", m_name);
        // TODO: For now we just save project name yet, change it later.
        if (!cfg.save(filePath, error))
            return false;
        m_filePath = QDir::cleanPath(QFileInfo(filePath).absolutePath());
        return true;
    }

    bool load(const QString &filePath, QString *error = nullptr) {
        ProjectConfig cfg;
        if (cfg.load(m_filePath, error))
            return false;
        m_name = cfg.value("project.name").toString();
        m_filePath = QDir::cleanPath(QFileInfo(filePath).absolutePath());
    }

private:
    QString m_name;
    QString m_filePath;
};

// Project Manager for managing all projects.

class ProjectManager : public QObject {
    Q_OBJECT
public:
    bool newProject(const QString &name, const QString &filePath, QString *error = nullptr) {
        auto p = std::make_unique<Project>();
        p->setName(name);
        if (!p->saveAs(filePath, error))
            return false;
        return true;
    }

    bool openProject(const QString &filePath, QString *error) {
        auto p = std::make_unique<Project>();
        if (!p->load(filePath, error))
            return false;
        return true;
    }
};
#endif // PROJECTMANAGER_H
