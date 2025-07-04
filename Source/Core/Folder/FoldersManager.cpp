#include "FoldersManager.h"

#include "Core/PackageManager.h"

void FoldersManager::InitDefaultFolders()
{
    YourInstallationsFolder = new Folder("Your installations", QPixmap(":/Resources/FolderCover/CatWithBox.png"), true);
    DependenciesFolder = new Folder("Dependencies", QPixmap(":/Resources/FolderCover/Dependencies.png"), true);
    AURFolder = new Folder("AUR", QPixmap(":/Resources/FolderCover/Rocket.png"), true);

    auto packages = PackageManager::GetInstance()->GetPackages();

    for (auto package : packages)
    {
	if (!package->isDependency() && package->GetName() == package->GetBase())
	{
	    YourInstallationsFolder->AddPackage(package);
	}

	if (package->isDependency() || package->GetName() != package->GetBase())
	{
	    DependenciesFolder->AddPackage(package);
	}
        
        if (package->GetSource() == "AUR")
        {
            AURFolder->AddPackage(package);
        }
    }
}

void FoldersManager::CreateFolder(const QString &FolderName)
{
    UserFolders.insert(FolderName, new Folder(FolderName));
}
Folder *FoldersManager::GetMainPackagesFolder() const
{
    return YourInstallationsFolder;
}
Folder *FoldersManager::GetDependenciesFolder() const
{
    return DependenciesFolder;
}
Folder *FoldersManager::GetAURFolder() const
{
    return AURFolder;
}
QList<Folder *> FoldersManager::GetUserFolders() const
{
    return UserFolders.values();
}
std::optional<Folder*> FoldersManager::GetFolderByName(const QString &FolderName)
{
    if (!UserFolders.contains(FolderName)) return std::nullopt;
    return UserFolders[FolderName];
}

void FoldersManager::Init()
{
    InitDefaultFolders();
}
FoldersManager::FoldersManager()
{
    Init();
}
FoldersManager *FoldersManager::GetInstance()
{
    static FoldersManager instance;
    return &instance;
}