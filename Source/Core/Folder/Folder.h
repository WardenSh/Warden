#pragma once
#include <QIcon>

#include <QString>

class Package;

class Folder {
    QString Name;
    QPixmap FolderImage;
    bool bIsDefaultFolder = false;
    QList<Package*> Packages;
    bool bIsShared = false;

public:
    Folder(QString Name);
    Folder(QString Name, QPixmap folderImage);
    Folder(QString Name, QPixmap folderImage, bool bIsDefaultFolder);

    void SetFolderImage(const QPixmap &folderImage);
    void SetName(const QString &Name);

    [[nodiscard]] QString GetName();
    [[nodiscard]] QPixmap GetFolderImage();
    [[nodiscard]] bool IsDefaultFolder() const;
    [[nodiscard]] QList<Package*> GetPackages();


    bool AddPackage(Package* package);
    bool RemovePackage(Package* package);

    [[nodiscard]] bool IsShared() const;
    //void ShareFolder();
    //void UnShareFolder();

};
