#include "InstalledPackage.h"
#include "Pacman/InstalledPacmanPackage.h"
#include "Pacman/PacmanHelper.h"
#include "config.h"

#include <QJsonObject>

#include <alpm.h>

InstalledPackage::InstalledPackage(InstalledPacmanPackage &PacmanPackage, QObject *parent) : Package(parent)
{
    Name = PacmanPackage.GetName();
    Version = PacmanPackage.GetVersion();
    Description = PacmanPackage.GetDescription();
    Icon = PacmanPackage.GetIcon();
    InstallDate = PacmanPackage.GetInstallDate();
    PackageSize = PacmanPackage.GetSize();
    bDependency = PacmanPackage.isDependency();
    Base = PacmanPackage.GetBase();
    Dependencies = PacmanPackage.GetDependencyList();
    auto packager = PacmanPackage.GetPackager();
    bFromPacmanRepository = !packager.isEmpty() && packager != "Unknown Packager";
}

void InstalledPackage::SetStatus(ePackageStatus status)
{
    Status = status;
    statusChanged(status);
}
QDateTime InstalledPackage::GetInstallDate() const
{
    return InstallDate;
}
bool InstalledPackage::isDependency() const
{
    return bDependency;
}

std::optional<QDateTime> InstalledPackage::GetLastLaunchDate() const
{
    QFile file(config::PackagesDir.path() + "/" + GetName() + "/data");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
	return std::nullopt;
    }

    QByteArray jsonData = file.readAll();
    file.close();

    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);
    if (parseError.error != QJsonParseError::NoError && !jsonDoc.isObject() && !jsonDoc.object().contains("LastLaunch"))
    {
	qWarning() << "InstalledPackage| Json deserialization error:" << parseError.errorString(); // Todo: Make runtime error
	return std::nullopt;
    }

    return QDateTime::fromString(jsonDoc.object().value("LastLaunch").toString(), "yyyy-MM-dd HH:mm:ss");
}
ePackageStatus InstalledPackage::GetStatus() const
{
    return Status;
}

std::optional<QTime> InstalledPackage::GetUptime() const
{
    QFile file(config::PackagesDir.path() + "/" + GetName() + "/uptime");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return std::nullopt;
    }
    QString text = file.readAll();

    return QTime::fromMSecsSinceStartOfDay(text.toInt() * 1000);
}