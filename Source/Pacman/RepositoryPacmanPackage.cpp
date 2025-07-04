#include "RepositoryPacmanPackage.h"

RepositoryPacmanPackage::RepositoryPacmanPackage(const QByteArray &deskFileData)
{
    ParseDescFile(deskFileData);
}