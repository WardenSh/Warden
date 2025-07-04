#pragma once
#include "RepositoryPacmanPackage.h"

#include <QList>

class InstalledPacmanPackage;
class PacmanHelper
{
    QHash<QString, RepositoryPacmanPackage> CoreRepositoryPackages;
    QHash<QString, RepositoryPacmanPackage> ExtraRepositoryPackages;
    QHash<QString, RepositoryPacmanPackage> MultilibRepositoryPackages;

    QHash<QString, RepositoryPacmanPackage> LoadRepositoryPackages(QFile DbFile);

  public:
    static QList<InstalledPacmanPackage> GetAllPacmanPackages();
    /* Returns the name of the arch repository */
    std::optional<QString> FoundPackageInArchRepo(const QString &packageName) const;

  public:
    // Delete copy and move operations
    PacmanHelper(const PacmanHelper &) = delete;
    PacmanHelper &operator=(const PacmanHelper &) = delete;
    PacmanHelper(PacmanHelper &&) = delete;
    PacmanHelper &operator=(PacmanHelper &&) = delete;

    static PacmanHelper *GetInstance();

  private:
    PacmanHelper();
};
