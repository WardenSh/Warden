#pragma once
#include <QDir>

namespace config {
static const QDir PacmanPackagesDir{"/var/lib/pacman/local"};
static const QDir PackagesDir{"/var/lib/warden/packages"};
}