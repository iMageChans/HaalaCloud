#include "filesmodel.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

FilesModel::FilesModel(QObject *parent) : QObject(parent)
{

}

void FilesModel::setFilesModel(QByteArray &ba)
{
    QJsonParseError Error;
    QJsonDocument Json = QJsonDocument::fromJson(ba, &Error);
    if(Error.error == QJsonParseError::NoError){
        if(Json.isObject()){

            QJsonObject FilesModel = Json.object();
            if(FilesModel.contains("status")){
                QJsonValue status = FilesModel.value("status");
                if(!status.isString())
                    files.status = status.toInt();
            }

            if(FilesModel.contains("result")){
                QJsonValue result = FilesModel.value("result");
                if(result.isObject()){
                    QJsonObject Result = result.toObject();
                    if(Result.contains("page")){
                        QJsonValue page = Result.value("page");
                        if(!page.isString())
                            files.result.page = page.toInt();
                    }

                    if(Result.contains("pageSize")){
                        QJsonValue pageSize = Result.value("pageSize");
                        if(!pageSize.isString())
                            files.result.pageSize = pageSize.toInt();
                    }

                    if(Result.contains("totalCount")){
                        QJsonValue totalCount = Result.value("totalCount");
                        if(!totalCount.isString())
                            files.result.totalCount = totalCount.toInt();
                    }

                    if(Result.contains("totalPage")){
                        QJsonValue totalPage = Result.value("totalPage");
                        if(!totalPage.isString())
                            files.result.totalPage = totalPage.toInt();
                    }

                    if(Result.contains("list")){
                        QJsonValue list = Result.value("list");
                        if(list.isArray()){
                            QJsonArray FilesArray = list.toArray();
                            for(int i = 1; i < FilesArray.size(); ++i){
                                QJsonObject listInfo = FilesArray.at(i).toObject();
                                if(listInfo.contains("uuid")){
                                    QJsonValue uuid = listInfo.value("uuid");
                                    if(uuid.isString())
                                        fileInfo.uuid = uuid.toString();
                                }

                                if(listInfo.contains("storeId")){
                                    QJsonValue storeId = listInfo.value("storeId");
                                    if(storeId.isString())
                                        fileInfo.storeId = storeId.toString();
                                }

                                if(listInfo.contains("userId")){
                                    QJsonValue userId = listInfo.value("userId");
                                    if(!userId.isString())
                                        fileInfo.userId = userId.toInt();
                                }

                                if(listInfo.contains("path")){
                                    QJsonValue path = listInfo.value("path");
                                    if(path.isString())
                                        fileInfo.path = path.toString();
                                }

                                if(listInfo.contains("name")){
                                    QJsonValue name = listInfo.value("name");
                                    if(name.isString())
                                        fileInfo.name = name.toString();
                                }

                                if(listInfo.contains("ext")){
                                    QJsonValue ext = listInfo.value("ext");
                                    if(ext.isString())
                                        fileInfo.ext = ext.toString();
                                }

                                if(listInfo.contains("size")){
                                    QJsonValue size = listInfo.value("size");
                                    if(!size.isString())
                                        fileInfo.size = size.toInt();
                                }

                                if(listInfo.contains("parent")){
                                    QJsonValue parent = listInfo.value("parent");
                                    if(parent.isString())
                                        fileInfo.parent = parent.toString();
                                }

                                if(listInfo.contains("type")){
                                    QJsonValue type = listInfo.value("type");
                                    if(!type.isString())
                                        fileInfo.type = type.toInt();
                                }

                                if(listInfo.contains("atime")){
                                    QJsonValue atime = listInfo.value("atime");
                                    if(atime.isDouble())
                                        fileInfo.atime = QDateTime::fromTime_t(uint(qint64(atime.toDouble()) / 1000));
                                }

                                if(listInfo.contains("ctime")){
                                    QJsonValue ctime = listInfo.value("ctime");
                                    if(ctime.isDouble())
                                        fileInfo.ctime = QDateTime::fromTime_t(uint(qint64(ctime.toDouble()) / 1000));
                                }

                                if(listInfo.contains("mtime")){
                                    QJsonValue mtime = listInfo.value("mtime");
                                    if(mtime.isDouble())
                                        fileInfo.mtime = int(mtime.toDouble());
                                }

                                if(listInfo.contains("version")){
                                    QJsonValue version = listInfo.value("version");
                                    if(version.isDouble())
                                        fileInfo.version = int(version.toDouble());
                                }

                                if(listInfo.contains("locking")){
                                    QJsonValue locking = listInfo.value("locking");
                                    if(locking.isBool())
                                        fileInfo.locking = locking.toBool();
                                }

                                if(listInfo.contains("mime")){
                                    QJsonValue mime = listInfo.value("mime");
                                    if(mime.isString())
                                        fileInfo.mime = mime.toString();
                                }

                                if(listInfo.contains("preview")){
                                    QJsonValue preview = listInfo.value("preview");
                                    if(preview.isDouble())
                                        fileInfo.preview = preview.toInt();
                                }

                                if(listInfo.contains("flag")){
                                    QJsonValue flag = listInfo.value("flag");
                                    if(flag.isDouble())
                                        fileInfo.flag = flag.toInt();
                                }
                                fileInfo.bChecked = false;
                                lists.append(fileInfo);
                            }
                            files.result.list = lists;
                        }
                    }

                    if(Result.contains("info")){
                        QJsonValue info = Result.value("info");
                        if(info.isObject()){
                            QJsonObject Info = info.toObject();
                            if(Info.contains("uuid")){
                                QJsonValue uuid = Info.value("uuid");
                                if(uuid.isString())
                                    files.result.info.uuid = uuid.toString();
                            }

                            if(Info.contains("storeId")){
                                QJsonValue storeId = Info.value("storeId");
                                if(storeId.isString())
                                    files.result.info.storeId = storeId.toString();
                            }

                            if(Info.contains("userId")){
                                QJsonValue userId = Info.value("userId");
                                if(!userId.isString())
                                    files.result.info.userId = userId.toInt();
                            }

                            if(Info.contains("path")){
                                QJsonValue path = Info.value("path");
                                if(path.isString())
                                    files.result.info.path = path.toString();
                            }

                            if(Info.contains("ext")){
                                QJsonValue ext = Info.value("ext");
                                if(ext.isString())
                                    files.result.info.ext = ext.toString();
                            }

                            if(Info.contains("size")){
                                QJsonValue size = Info.value("size");
                                if(!size.isString())
                                    files.result.info.size = size.toInt();
                            }

                            if(Info.contains("parent")){
                                QJsonValue parent = Info.value("parent");
                                if(parent.isString())
                                    files.result.info.parent = parent.toString();
                            }

                            if(Info.contains("type")){
                                QJsonValue type = Info.value("type");
                                if(!type.isString())
                                    files.result.info.type = type.toInt();
                            }

                            if(Info.contains("atime")){
                                QJsonValue atime = Info.value("atime");
                                if(atime.isDouble())
                                    files.result.info.atime = QDateTime::fromTime_t(uint(qint64(atime.toDouble()) / 1000));
                            }

                            if(Info.contains("ctime")){
                                QJsonValue ctime = Info.value("ctime");
                                if(ctime.isDouble())
                                    files.result.info.ctime = QDateTime::fromTime_t(uint(qint64(ctime.toDouble()) / 1000));
                            }

                            if(Info.contains("mtime")){
                                QJsonValue mtime = Info.value("mtime");
                                if(mtime.isDouble())
                                    files.result.info.mtime = QDateTime::fromTime_t(uint(qint64(mtime.toDouble()) / 1000));
                            }

                            if(Info.contains("version")){
                                QJsonValue version = Info.value("version");
                                if(version.isDouble())
                                    files.result.info.version = int(version.toDouble());
                            }

                            if(Info.contains("locking")){
                                QJsonValue locking = Info.value("locking");
                                if(locking.isBool())
                                    files.result.info.locking = locking.toBool();
                            }
                        }
                    }
                }
            }

            if(FilesModel.contains("code")){
                QJsonValue code = FilesModel.value("code");
                if(code.isString())
                    files.code = code.toString();
            }

            if(FilesModel.contains("success")){
                QJsonValue success = FilesModel.value("success");
                if(success.isBool())
                    files.success = success.toBool();
            }

            if(FilesModel.contains("token")){
                QJsonValue token = FilesModel.value("token");
                if(token.isString())
                    files.token = token.toString();
            }
        }
    }
}

Files FilesModel::getFilesModel() const
{
    return files;
}
