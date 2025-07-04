#include "Folder.h"

Folder::Folder(QString name) : Name(name)
{
    // Set default Icon
    // Создать в директории файл json куда поместить строку Name, Icon, значение bIsShared
}
Folder::Folder(QString name, QPixmap folderImage) : Name(name), FolderImage(folderImage)
{

}

Folder::Folder(QString name, QPixmap folderImage, bool isDefaultFolder) : Name(name), FolderImage(folderImage), bIsDefaultFolder(isDefaultFolder)
{

}



bool Folder::AddPackage(Package *package)
{
    if (Packages.contains(package)) return false;
    Packages.push_back(package);
    return true;
}
bool Folder::RemovePackage(Package *package)
{
    return Packages.removeOne(package);
}

bool Folder::IsShared() const
{
    return bIsShared;
}

void Folder::SetFolderImage(const QPixmap &folderImage)
{
    FolderImage = folderImage;
}
void Folder::SetName(const QString &name)
{
    Name = name;
}

QString Folder::GetName()
{
    return Name;
}
QPixmap Folder::GetFolderImage()
{
    return FolderImage;
}
bool Folder::IsDefaultFolder() const
{
    return bIsDefaultFolder;
}
QList<Package *> Folder::GetPackages()
{
    return Packages;
}