#pragma once
#include "PacmanPackage.h"

class InstalledPacmanPackage : public PacmanPackage
{
    QDir PackageDir;
    /* If the desktop file is not found, an empty QFile be returned */
    [[nodiscard]] QFile GetDesktopFile() const;
    [[nodiscard]] std::optional<QIcon> FindingIconInDesktopFile() const;

public:
    InstalledPacmanPackage(const QDir &packageDir);
    [[nodiscard]] QIcon GetIcon() const;
    [[nodiscard]] QDateTime GetInstallDate() const;
    [[nodiscard]] bool isDependency() const;
};
