#include "SidePanelWidget.h"

#include "Core/Folder/FoldersManager.h"
#include "FolderWidget.h"

#include <QListWidget>
#include <QVBoxLayout>

SidePanelWidget::SidePanelWidget(QWidget *Parent) : QWidget(Parent)
{
    setObjectName("widgetElement");
    setAttribute(Qt::WA_StyledBackground, true);
    setMinimumWidth(350);

    QVBoxLayout *layout = new QVBoxLayout(this);

    listWidget = new QListWidget(this);
    layout->addWidget(listWidget);

    listWidget->setSpacing(2);

    auto folderManger = FoldersManager::GetInstance();
    AddSectionTitle("DEFAULT:");
    AddFolder(folderManger->GetMainPackagesFolder());
    AddFolder(folderManger->GetDependenciesFolder());
    AddFolder(folderManger->GetAURFolder());
    AddSectionTitle("YOUR FOLDERS:");

    connect(listWidget, &QListWidget::itemClicked, this, [&](QListWidgetItem* item)->void {
        auto folderWidget = static_cast<FolderWidget*>(listWidget->itemWidget(item));
        onFolderSelected(folderWidget->GetFolder());
    });

}
void SidePanelWidget::AddFolder(Folder *folder)
{
    auto item = new QListWidgetItem(listWidget);
    item->setSizeHint(QSize(300, 60));
    listWidget->addItem(item);
    listWidget->setItemWidget(item, new FolderWidget(folder));
}

void SidePanelWidget::AddSectionTitle(const QString &title)
{
    auto *item = new QListWidgetItem(title);
    QFont font = item->font();
    font.setBold(true);
    item->setFont(font);
    item->setFlags(Qt::NoItemFlags);
    listWidget->addItem(item);
}
