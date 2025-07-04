#pragma once
#include "Folder.h"

#include <qhash.h>

class FoldersManager {
    Folder* YourInstallationsFolder;
    Folder* DependenciesFolder;
    Folder* AURFolder;
    void InitDefaultFolders();

    QHash<QString, Folder*> UserFolders;

public:
    void CreateFolder(const QString &FolderName);

    Folder* GetMainPackagesFolder() const;
    Folder* GetDependenciesFolder() const;
    Folder* GetAURFolder() const;
    QList<Folder*> GetUserFolders() const;
    std::optional<Folder*> GetFolderByName(const QString &FolderName);

    void Init();

private:
    FoldersManager();
public:
    // Delete copy and move operations
    FoldersManager(const FoldersManager &) = delete;
    FoldersManager &operator=(const FoldersManager &) = delete;
    FoldersManager(FoldersManager &&) = delete;
    FoldersManager &operator=(FoldersManager &&) = delete;

    static FoldersManager *GetInstance();
};
