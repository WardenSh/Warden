#include "TableWidget.h"

#include "Core/Folder/FoldersManager.h"
#include "Core/Package/InstalledPackage.h"
#include "PackageItemRow.h"

#include <QHeaderView>
#include <QStandardItemModel>
#include <QTreeView>
#include <QVBoxLayout>

TableWidget::TableWidget(SidePanelWidget *sidePanel, QWidget *Parent) : QWidget(Parent), SidePanelPtr(sidePanel)
{
    setObjectName("widgetElement");
    setAttribute(Qt::WA_StyledBackground, true);

    auto layout = new QVBoxLayout(this);

    PackageTree = new QTreeView(this);

    PackageTree->setIconSize(QSize(42, 42));
    PackageModel = new QStandardItemModel(0, 7, this);
    PackageTree->setModel(PackageModel);
    PackageTree->setRootIsDecorated(false);
    PackageTree->setAlternatingRowColors(true);
    PackageTree->setUniformRowHeights(true);
    PackageTree->setEditTriggers(QAbstractItemView::NoEditTriggers); // Disable edit text in Items
    PackageTree->setSortingEnabled(true);

    // Configure headers
    QStringList headers = {"Name",  "Description", "Size", "Install date", "Source", "Last launch date",
			   "Uptime", "Status"};
    PackageTree->header()->setMaximumSectionSize(600);
    PackageModel->setHorizontalHeaderLabels(headers);
    PackageTree->header()->setStretchLastSection(true);
    PackageTree->header()->setDefaultAlignment(Qt::AlignLeft);
    PackageTree->header()->setSectionsMovable(false);

    layout->addWidget(PackageTree);

    Init();

    connect(sidePanel, &SidePanelWidget::onFolderSelected, this, [this](Folder *folder)->void {
        OpenFolder(folder);
    });
}

void TableWidget::OpenFolder(Folder *folder)
{
    CurrentFolder = folder;

    // Clear
    auto model = qobject_cast<QStandardItemModel*>(PackageTree->model());
    if (model) {
        int rowCount = model->rowCount();
        if (rowCount > 0) {
            model->removeRows(0, rowCount);
        }
    }
    for (auto i : PackageRows)
    {
        delete i;
    }
    PackageRows.clear();

    // Add packages from the folder
    for (auto i : CurrentFolder->GetPackages())
    {
        auto* installedPackage = static_cast<InstalledPackage*>(i);
        AddPackage(PackageModel->invisibleRootItem(), installedPackage);
    }

    // Column size
    for (int i = 0; i < PackageModel->columnCount(); ++i)
    {
        PackageTree->resizeColumnToContents(i);
    }
}

void TableWidget::AddPackage(QStandardItem *parent, InstalledPackage *package)
{
    auto rowItem = new PackageItemRow(package);
    PackageRows.push_back(rowItem);

    parent->appendRow(rowItem->GetItems());
}

void TableWidget::Init()
{
    OpenFolder(FoldersManager::GetInstance()->GetAURFolder());
}
