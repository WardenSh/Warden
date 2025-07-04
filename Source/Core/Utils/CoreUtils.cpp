#include "CoreUtils.h"

#include <QString>
#include <qlocale.h>

QString CoreUtils::bitsToGigabytes(qint64 bits)
{
    const double bytes = static_cast<double>(bits) / 8.0;

    constexpr double KB = 1024.0;
    constexpr double MB = 1024.0 * KB;
    constexpr double GB = 1024.0 * MB;
    constexpr double TB = 1024.0 * GB;

    QString result;
    QLocale locale = QLocale::system();

    if (bytes >= TB)
    {
	result = locale.toString(bytes / TB, 'f', 1) + " Tb";
    }
    else if (bytes >= GB)
    {
	result = locale.toString(bytes / GB, 'f', 1) + " Gb";
    }
    else if (bytes >= MB)
    {
	result = locale.toString(bytes / MB, 'f', 1) + " Mb";
    }
    else if (bytes >= KB)
    {
	result = locale.toString(bytes / KB, 'f', 1) + " Kb";
    }
    else
    {
	result = locale.toString(bytes, 'f', 0) + " b";
    }

    return result;
}