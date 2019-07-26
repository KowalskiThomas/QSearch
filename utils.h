#ifndef UTILS_H
#define UTILS_H

#include <QString>

class Utils
{
public:
    Utils() = delete;
    ~Utils() = delete;

    static QString readableSize(qint64 s)
    {
        if (s > 1E9)
            return QStringLiteral("%1 GB").arg(static_cast<double>(s) / 1E9, 0, 'f', 2);
        if (s > 1E6)
            return QStringLiteral("%1 MB").arg(static_cast<double>(s) / 1E6, 0, 'f', 2);
        if (s > 1E3)
            return QStringLiteral("%1 KB").arg(static_cast<double>(s) / 1E3, 0, 'f', 2);

        return QStringLiteral("%1 bytes").arg(s);
    }
};

#endif // UTILS_H
