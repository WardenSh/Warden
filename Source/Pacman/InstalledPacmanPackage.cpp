#include "InstalledPacmanPackage.h"
#include <QIcon>


InstalledPacmanPackage::InstalledPacmanPackage(const QDir &packageDir) : PackageDir(packageDir)
{
    auto descFile = QFile(PackageDir.path() + "/desc");
    if (!descFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    auto data = descFile.readAll();
    ParseDescFile(data);
}

QFile InstalledPacmanPackage::GetDesktopFile() const
{
    auto filesFile = QFile(PackageDir.path() + "/files");
    if (!filesFile.open(QIODevice::ReadOnly | QIODevice::Text))
	return {};

    QTextStream in(&filesFile);

    while (!in.atEnd())
    {
	QString line = in.readLine().trimmed();
	if (line.startsWith("usr/share/applications/") && line.endsWith(".desktop")) // Hardcode
	{
	    QFile file("/" + line);

	    if (QFile::exists("/" + line))
	    {
		return QFile{"/" + line};
	    }

	    return {};
	}
    }

    return {};
}
std::optional<QIcon> InstalledPacmanPackage::FindingIconInDesktopFile() const
{
    auto desktopFile = GetDesktopFile();
    if (!desktopFile.exists() || !desktopFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return std::nullopt;

    QTextStream in(&desktopFile);

    while (!in.atEnd())
    {
        QString line = in.readLine().trimmed();
        if (line.startsWith("Icon="))
        {
            line.replace("Icon=", "");
            return QIcon::fromTheme(line);
        }
    }
    return std::nullopt;
}

QIcon InstalledPacmanPackage::GetIcon() const
{
    auto icon = FindingIconInDesktopFile();


    if (icon.has_value() && !icon.value().isNull())
    {
	return icon.value();
    }

    return QIcon(":/Resources/Icons/Package.svg");
}

QDateTime InstalledPacmanPackage::GetInstallDate() const
{
    return QDateTime::fromSecsSinceEpoch(DescData["INSTALLDATE"].value(0).toInt());
}
bool InstalledPacmanPackage::isDependency() const
{
    return DescData["REASON"].value(0).toInt();
}