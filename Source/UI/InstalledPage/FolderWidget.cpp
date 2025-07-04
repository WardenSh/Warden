#include "FolderWidget.h"

#include "Core/Folder/Folder.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QPainter>
#include <QPainterPath>

FolderWidget::FolderWidget(Folder *folder)
{
    folderPtr = folder;

    auto layout = new QHBoxLayout(this);
    layout->setContentsMargins(5, 5, 5, 5);
    layout->setSpacing(10);

    // Folder cover
    iconLabel = new QLabel(this);
    QPixmap originalPixmap = folder->GetFolderImage().scaled(48, 48, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QPixmap roundedPixmap(originalPixmap.size());
    roundedPixmap.fill(Qt::transparent);
    QPainter painter(&roundedPixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    QPainterPath path;
    path.addRoundedRect(roundedPixmap.rect(), 10, 10);
    painter.setClipPath(path);
    painter.drawPixmap(0, 0, originalPixmap);
    painter.end();
    iconLabel->setPixmap(roundedPixmap);
    layout->addWidget(iconLabel);

    // Title
    auto *titleLayout = new QHBoxLayout();
    QLabel *titleLabel = new QLabel(this);
    titleLabel->setText(folder->GetName());
    titleLayout->addWidget(titleLabel);

    if (folder->IsDefaultFolder())
    {
	auto starLabel = new QLabel("★");
	titleLayout->addWidget(starLabel);
    }

    layout->addLayout(titleLayout);

    layout->addStretch(); // Spacer

    QLabel *yearLabel = new QLabel(QString::number(folder->GetPackages().size()), this);
    yearLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    yearLabel->setObjectName("folderPackagesCount");
    layout->addWidget(yearLabel);
}
Folder *FolderWidget::GetFolder() const
{
    return folderPtr;
}