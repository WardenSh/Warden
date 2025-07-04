#pragma once
#include "Core/Package/InstalledPackage.h"

class QStandardItem;

class PackageItemRow : public QObject
{
    Q_OBJECT

    QMetaObject::Connection updateBinding;
    InstalledPackage *package;

    QStandardItem *Name;
    QStandardItem *Description;
    QStandardItem *Size;
    QStandardItem *InstallDate;
    QStandardItem *Source;
    QStandardItem *LastLaunchDate;
    QStandardItem *Uptime;
    QStandardItem *Status;

  public:
    PackageItemRow(InstalledPackage *package);
    ~PackageItemRow() override;

    QList<QStandardItem *> GetItems();
};