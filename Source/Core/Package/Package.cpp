#include "Package.h"

#include "Pacman/PacmanHelper.h"

Package::Package(QObject *parent) : QObject(parent)
{
}

QString Package::GetName() const
{
    return Name;
}
QString Package::GetVersion() const
{
    return Version;
}
QString Package::GetBase() const
{
    return Base;
}
QString Package::GetDescription() const
{
    return Description;
}
qint64 Package::GetSize() const
{
    return PackageSize;
}
QStringList Package::GetDependencies() const
{
    return Dependencies;
}
QIcon Package::GetIcon() const
{
    return Icon;
}
bool Package::isPackageFromPacmanRepository() const
{
    return bFromPacmanRepository;
}
QString Package::GetSource() const
{
    if (isPackageFromPacmanRepository())
    {
        auto ArchRep = PacmanHelper::GetInstance()->FoundPackageInArchRepo(GetName());
        if (ArchRep.has_value())
        {
            return ArchRep.value();
        }
    }

    return "AUR"; // Todo: Always returns AUR
}