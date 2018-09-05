#ifndef TOOLCLASS_H
#define TOOLCLASS_H

#include <QString>

const int GB = 1024 * 1024 * 1024;
const int MB = 1024 * 1024;
const int KB = 1024;

QString bytesToGBMBKB(qint64 size)
{
    if (size / GB >= 1)
        return QString("%1 GB").arg(QString::number(size / (double)GB, 'f', 2));
    else if (size / MB >= 1)
        return QString("%1 MB").arg(QString::number(size / (double)MB, 'f', 2));
    else if (size / KB >= 1)
        return QString("%1 KB").arg(QString::number(size / (double)KB, 'f', 2));
    else
        return QString("%1 Bytes").arg(size);
}

#endif // TOOLCLASS_H
