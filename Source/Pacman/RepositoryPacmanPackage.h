#pragma once
#include "PacmanPackage.h"

class RepositoryPacmanPackage : public PacmanPackage
{
public:
    RepositoryPacmanPackage(const QByteArray& deskFileData);
};