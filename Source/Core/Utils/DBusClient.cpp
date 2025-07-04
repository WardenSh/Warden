#include "DBusClient.h"

#include "Core/PackageManager.h"

#include <QDBusInterface>
#include <QDBusReply>

DBusClient::DBusClient(QObject *parent) : QObject(parent)
{
    QDBusConnection systemBus = QDBusConnection::systemBus();

    if (!systemBus.isConnected())
    {
	qFatal("DBusClient| Failed to connect D-Bus");
    }

    bool ok = systemBus.connect(
	/* service */ "dev.warden.WardenObserver",
	/* path */ "/dev/warden/PackageEvents",
	/* interface */ "dev.warden.PackageEvents",
	/* signal name */ "packageLaunch",
	/* receiver */ this,
	/* slot */ SLOT(packageLaunch(QString)));

    if (!ok)
    {
	qWarning() << "DBusClient| Failed to subscribe 'packageLaunch' signal";
    }

    ok = systemBus.connect(
	/* service */ "dev.warden.WardenObserver",
	/* path */ "/dev/warden/PackageEvents",
	/* interface */ "dev.warden.PackageEvents",
	/* signal name */ "packageStop",
	/* receiver */ this,
	/* slot */ SLOT(packageStop(QString)));

    if (!ok)
    {
	qWarning() << "DBusClient| Failed to subscribe 'packageStop' signal";
    }
}

void DBusClient::packageLaunch(const QString &packageName)
{
    qInfo() << "DBusClient::packageLaunch: " << packageName;
    PackageManager::GetInstance()->GetPackage(packageName)->SetStatus(ePackageStatus::Running);
}

void DBusClient::packageStop(const QString &packageName)
{
    PackageManager::GetInstance()->GetPackage(packageName)->SetStatus(ePackageStatus::Stopped);
}