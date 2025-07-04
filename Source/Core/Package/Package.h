#pragma once
#include <QIcon>
#include <qdatetime.h>

class Package  : public QObject
{
    Q_OBJECT

protected:
    QString Name;
    QString Description;
    QString Version;
    QIcon Icon;
    qint64 PackageSize = 0;
    QString Base;
    QStringList Dependencies;
    bool bFromPacmanRepository = false;

public:
    Package(QObject *parent = nullptr);

    [[nodiscard]] QString GetName() const;
    [[nodiscard]] QString GetVersion() const;
    [[nodiscard]] QString GetBase() const;
    [[nodiscard]] QString GetDescription() const;
    [[nodiscard]] qint64 GetSize() const;
    [[nodiscard]] QStringList GetDependencies() const;
    [[nodiscard]] virtual QIcon GetIcon() const;
    [[nodiscard]] bool isPackageFromPacmanRepository() const;
    [[nodiscard]] QString GetSource() const;
};