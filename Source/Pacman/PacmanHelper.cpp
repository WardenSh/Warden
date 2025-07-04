#include "Pacman/PacmanHelper.h"

#include "InstalledPacmanPackage.h"
#include "RepositoryPacmanPackage.h"
#include "config.h"

#include <archive.h>
#include <archive_entry.h>

QHash<QString, RepositoryPacmanPackage> PacmanHelper::LoadRepositoryPackages(QFile DbFile)
{
     QHash<QString, RepositoryPacmanPackage> packages;

    if (!DbFile.open(QIODevice::ReadOnly))
    {
        return packages; // TODO: Add runtime error
    }

    QByteArray ArchiveData = DbFile.readAll();
    DbFile.close();

    archive *Archive = archive_read_new();
    archive_read_support_filter_all(Archive);
    archive_read_support_format_all(Archive);

    if (archive_read_open_memory(Archive, ArchiveData.data(), ArchiveData.size()) != ARCHIVE_OK)
    {
        archive_read_free(Archive);
        return packages; // TODO: Add runtime error
    }

    archive_entry* entry;

    while (archive_read_next_header(Archive, &entry) == ARCHIVE_OK)
    {
        QString entryPath = QString::fromUtf8(archive_entry_pathname(entry));
        if (entryPath.isEmpty())
        {
            archive_read_data_skip(Archive);
            continue;
        }

        if (archive_entry_filetype(entry) == AE_IFREG && entryPath.endsWith("/desc"))
        {
            QByteArray deskFileData;
            size_t size = archive_entry_size(entry);
            deskFileData.resize(static_cast<int>(size));
            archive_read_data(Archive, deskFileData.data(), size);
            RepositoryPacmanPackage package{deskFileData};
            packages.insert(package.GetName(), package); // Todo: Make std::move()
        }
    }

    archive_read_free(Archive);
    return packages;
}

QList<InstalledPacmanPackage> PacmanHelper::GetAllPacmanPackages()
{
    QList<InstalledPacmanPackage> packages;

    for (const auto &dirName : config::PacmanPackagesDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot))
    {
	auto packageDir = config::PacmanPackagesDir.path() + "/" + dirName;
	auto package = InstalledPacmanPackage(packageDir);

	if (!package.isValid()) continue;
	packages.push_back(std::move(package));
    }

    return packages;
}

std::optional<QString> PacmanHelper::FoundPackageInArchRepo(const QString &packageName) const
{
    if (CoreRepositoryPackages.contains(packageName))
	return "Core";
    if (ExtraRepositoryPackages.contains(packageName))
	return "Extra";
    if (MultilibRepositoryPackages.contains(packageName))
	return "Multilib";
    return std::nullopt;
}

PacmanHelper *PacmanHelper::GetInstance()
{
    static PacmanHelper instance;
    return &instance;
}

PacmanHelper::PacmanHelper()
{
    // Todo: It might be worth moving the arch repositories to config (QHash<QString, QFile>)
    CoreRepositoryPackages = LoadRepositoryPackages(QFile("/var/lib/pacman/sync/core.db"));
    ExtraRepositoryPackages = LoadRepositoryPackages(QFile("/var/lib/pacman/sync/extra.db"));
    MultilibRepositoryPackages = LoadRepositoryPackages(QFile("/var/lib/pacman/sync/multilib.db"));
}