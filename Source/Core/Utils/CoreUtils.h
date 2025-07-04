#pragma once

struct InstalledPackage;

#include <QtTypes>
class QString;

class CoreUtils {
public:
    static QString bitsToGigabytes(qint64 bits);
};