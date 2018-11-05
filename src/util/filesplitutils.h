#ifndef FILESPLITUTILS_H
#define FILESPLITUTILS_H

#include <QString>

class FileSplitUtils{

public:
    FileSplitUtils();

public:
   static bool islegalFilePath(const QString& path);
   static bool islegalDirPath(const QString& path);
   static bool islegalSplitSize(const QString& path,const qint64 splitSize);
   static qint64 getBlockFileSize();
   static qint64 getBputFileSize();
   static QString getFileName(const QString& filePath);
};

#endif // FILESPLITUTILS_H
