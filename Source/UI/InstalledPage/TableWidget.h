#pragma once
#include "SidePanelWidget.h"

#include <QWidget>

class QTreeView;
class QStandardItemModel;
class QStandardItem;
class InstalledPackage;
class Folder;
class PackageItemRow;

class TableWidget : public QWidget
{
    Q_OBJECT

    SidePanelWidget *SidePanelPtr;
    Folder *CurrentFolder;

    QList<PackageItemRow*> PackageRows;

  public:
    TableWidget(SidePanelWidget *sidePanel, QWidget *Parent);

  private:
    QTreeView *PackageTree;
    QStandardItemModel *PackageModel;

    void OpenFolder(Folder *folder);
    void AddPackage(QStandardItem *parent, InstalledPackage *package);

    void Init();
};
