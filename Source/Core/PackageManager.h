#pragma once

#include "Package/InstalledPackage.h"

class PackageManager
{
    QHash<QString, InstalledPackage*> Packages;

    PackageManager();

  public:
    static PackageManager *GetInstance();
    QHash<QString, InstalledPackage*> &GetPackages();

    InstalledPackage* GetPackage(const QString& PackageName);

    PackageManager(const PackageManager&) = delete;
    PackageManager& operator=(const PackageManager&) = delete;
};
