#include "Pacman/PacmanPackage.h"
#include <QIcon>

bool PacmanPackage::isValid() const
{
    if (DescData.empty()) return false;
    return !GetName().isEmpty();
}

void PacmanPackage::ParseDescFile(const QByteArray & deskFileData)
{
    QTextStream in(deskFileData);

    bool isVariableDetected = false;
    QString currentKey;
    while (!in.atEnd())
    {
        QString line = in.readLine().trimmed();

        if (line.startsWith('%') && line.endsWith('%'))
        {
            isVariableDetected = true;
            currentKey = line.mid(1, line.length() - 2);
            DescData[currentKey] = {};
        }
        else if (isVariableDetected && !line.isEmpty())
        {
            DescData[currentKey].append(line);
        }
        else
        {
            isVariableDetected = false;
        }
    }
}

QString PacmanPackage::GetName() const
{
    return DescData["NAME"].value(0);
}
QString PacmanPackage::GetVersion() const
{
    return DescData["VERSION"].value(0);
}
QString PacmanPackage::GetDescription() const
{
    return DescData["DESC"].value(0);
}
qint64 PacmanPackage::GetSize()
{
    return DescData["SIZE"].value(0).toInt();
}
QString PacmanPackage::GetBase()
{
    return DescData["BASE"].value(0);
}
QStringList PacmanPackage::GetDependencyList()
{
    return QStringList(DescData["DEPENDS"].join("\n"));
}
QString PacmanPackage::GetPackager()
{
    return DescData["PACKAGER"].value(0);
}