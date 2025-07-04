#pragma once

#include "Package.h"

#include <qdatetime.h>

class InstalledPacmanPackage;

enum class ePackageStatus
{
    Stopped,
    Running
};

namespace PackageStatus
{
inline QString ePackageStatusToString(ePackageStatus status)
{
    switch (status)
    {
    case ePackageStatus::Stopped:
        return "Stopped";
    case ePackageStatus::Running:
        return "Running";
    }
    return "Unknown";
}
}

class InstalledPackage : public Package
{
    Q_OBJECT

    signals:
    void statusChanged(ePackageStatus newStatus);

private:
    QDateTime InstallDate;
    bool bDependency;
    ePackageStatus Status = ePackageStatus::Stopped;

  public:
    InstalledPackage(InstalledPacmanPackage &PacmanPackage, QObject *parent = nullptr);

    void SetStatus(ePackageStatus status);

    [[nodiscard]] QDateTime GetInstallDate() const;
    [[nodiscard]] bool isDependency() const;
    [[nodiscard]] std::optional<QDateTime> GetLastLaunchDate() const;
    [[nodiscard]] ePackageStatus GetStatus() const;
    [[nodiscard]] std::optional<QTime> GetUptime() const;
};