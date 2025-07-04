#pragma once

#include <QObject>

class DBusClient : public QObject  {
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "dev.warden.PackageEvents")

public:
    explicit DBusClient(QObject* parent = nullptr);

private slots:
    void packageLaunch(const QString &packageName);
    void packageStop(const QString &packageName);
};
