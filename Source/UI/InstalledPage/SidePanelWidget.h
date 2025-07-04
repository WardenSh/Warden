#pragma once
#include <QWidget>

class Folder;
class QListWidget;

class SidePanelWidget : public QWidget{
    Q_OBJECT

public:
    SidePanelWidget(QWidget* Parent);

signals:
    void onFolderSelected(Folder* folder);

private:
    QListWidget* listWidget;

    void AddFolder(Folder* folder);
    void AddSectionTitle(const QString &title);
};
