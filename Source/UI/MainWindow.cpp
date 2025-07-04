#include "MainWindow.h"

#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QSplitter>
#include <QWidget>

#include "InstalledPage/SidePanelWidget.h"
#include "InstalledPage/TableWidget.h"

MainAppWindow::MainAppWindow(QWidget *parent) : QMainWindow(parent)
{
    setObjectName("main");
    resize(1920, 1080);
    setWindowTitle("Warden - Package Manager");

    setupUI();
}

void MainAppWindow::setupUI()
{
    const auto centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    const auto mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setContentsMargins(20, 20, 20, 20);

    const auto mainSplitter = new QSplitter(Qt::Horizontal, centralWidget);
    mainSplitter->setHandleWidth(10);
    mainSplitter->setChildrenCollapsible(false);
    mainLayout->addWidget(mainSplitter, 1);


    const auto sidePanel = new SidePanelWidget(mainSplitter);
    mainSplitter->addWidget(sidePanel);

    const auto tableWidget = new TableWidget(sidePanel, mainSplitter);
    mainSplitter->addWidget(tableWidget);

    mainSplitter->setStretchFactor(0, 0);
    mainSplitter->setStretchFactor(1, 1);


}