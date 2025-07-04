#pragma once
#include <qlistwidget.h>

class Folder;
class QLabel;

class FolderWidget : public QWidget
{
    Folder* folderPtr;

    QLabel *iconLabel;
    QLabel *titleLabel;
    QLabel *yearLabel;

public:
    FolderWidget(Folder* folder);

    [[nodiscard]] Folder* GetFolder() const;
};