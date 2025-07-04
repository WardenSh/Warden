#include "PackageManager.h"

#include "Pacman/PacmanHelper.h"
#include "Pacman/InstalledPacmanPackage.h"

#include "Package/InstalledPackage.h"

PackageManager::PackageManager()
{
    for (auto &i : PacmanHelper::GetAllPacmanPackages())
    {
        Packages.insert(i.GetName(), new InstalledPackage(i));
    }
}

PackageManager *PackageManager::GetInstance()
{
    static PackageManager instance;
    return &instance;
}

QHash<QString, InstalledPackage*> &PackageManager::GetPackages()
{
    return Packages;
}
InstalledPackage *PackageManager::GetPackage(const QString& PackageName)
{
    auto it = Packages.find(PackageName);
    if (it != Packages.end()) {
        return it.value();
    }
    return nullptr;
}