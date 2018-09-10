#ifndef TOOL_H
#define TOOL_H

#include <QObject>

const int GB = 1024 * 1024 * 1024;
const int MB = 1024 * 1024;
const int KB = 1024;

class Tool
{
public:
    Tool();
    QString bytesToGBMBKB(qint64 size);
};

#endif // TOOL_H
