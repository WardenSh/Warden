#pragma once
#include <QDir>
#include <QString>

class PacmanPackage
{
protected:
    QMap<QString, QStringList> DescData;

    void ParseDescFile(const QByteArray & deskFileData);

public:
    bool isValid() const;

    QString GetName() const;
    QString GetVersion() const;
    QString GetDescription() const;
    qint64 GetSize();
    QString GetBase();
    QStringList GetDependencyList();
    QString GetPackager();
};
