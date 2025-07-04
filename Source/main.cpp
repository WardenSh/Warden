#include <QApplication>

#include "Core/PackageManager.h"
#include "Core/Utils/DBusClient.h"
#include "UI/MainWindow.h"

#include <QFile>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QCoreApplication::setApplicationName("Warden");
    QCoreApplication::setApplicationVersion("0.1");

    MainAppWindow window;
    window.show();

    QFile file(":/Source/UI/style.qss");
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&file);
        QString styleSheet = stream.readAll();
        app.setStyleSheet(styleSheet);
    }

    __attribute__((unused)) auto PackageManager = PackageManager::GetInstance();
    __attribute__((unused)) auto Dbus = new DBusClient();

    return QApplication::exec();
}
