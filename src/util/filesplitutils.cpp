﻿#include "filesplitutils.h"
#include <QFileInfo>
#include <QDebug>

FileSplitUtils::FileSplitUtils(){

}

FileSplitUtils::~FileSplitUtils(){

}

bool FileSplitUtils::islegalFilePath(const QString& path){
    if(path.isEmpty()){
        return false;
    }
    QFileInfo fileInfo(path);
    if(!fileInfo.exists()||!fileInfo.isFile()){
        return false;
    }
    return true;
}
bool FileSplitUtils::islegalDirPath(const QString& path){
    if(path.isEmpty()){
        return false;
    }
    QFileInfo dirInfo(path);
    if(!dirInfo.exists()||!dirInfo.isDir()){
        return false;
    }
    return true;
}

bool FileSplitUtils::islegalSplitSize(const QString& path,const qint64 splitSize){
    if(splitSize<1){
        return false;
    }
    QFileInfo fileInfo(path);
    if(splitSize>fileInfo.size()){
        return false;
    }
    return true;
}

qint64 FileSplitUtils::getBlockFileSize(){

    if(!size.isEmpty()){
        return 4 * 1024 * 1024;
    }
    return 0;
}

qint64 FileSplitUtils::getBputFileSize(){

    if(!size.isEmpty()){
        return 512 * 1024;
    }
    return 0;
}



QString FileSplitUtils::getFileName(const QString& filePath){
    QFileInfo fileInfo(filePath);
    if(fileInfo.exists()){
        return fileInfo.fileName();
    }
    return QString("");
}
