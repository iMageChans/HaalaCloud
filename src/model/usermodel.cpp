#include "usermodel.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

//{
//    "status": 200,
//    "result": {
//        "uuid": 5,
//        "name": "eric2",
//        "email": "",
//        "countryCode": "86",
//        "phone": "13627140483",
//        "createTime": 1532526039883,
//        "createIp": "::ffff:123.59.101.208",
//        "ssid": {},
//        "icon": "default.jpg",
//        "spaceUsed": 0,
//        "spaceCapacity": 8192,
//        "type": 0,
//        "status": 0
//    },
//    "code": "OK",
//    "success": true,
//    "token": "..."
//}

UserModel::UserModel(QObject *parent) : QObject(parent)
{

}

void UserModel::setUserModel(QByteArray &ba)
{
    QJsonParseError Error;
    QJsonDocument Json = QJsonDocument::fromJson(ba, &Error);
    if(Error.error == QJsonParseError::NoError){
        if(Json.isObject()){

            QJsonObject UserModels = Json.object();
            if(UserModels.contains("status")){
                QJsonValue status = UserModels.value("status");
                if(!status.isString())
                    user.status = status.toInt();
            }

            if(UserModels.contains("result")){
                QJsonValue result = UserModels.value("result");
                if(result.isObject()){
                    QJsonObject Result = result.toObject();
                    if(Result.contains("uuid")){
                        QJsonValue uuid = Result.value("uuid");
                        if(!uuid.isString())
                            user.result.uuid = uuid.toInt();
                    }

                    if(Result.contains("name")){
                        QJsonValue name = Result.value("name");
                        if(name.isString())
                            user.result.name = name.toString();
                    }

                    if(Result.contains("email")){
                        QJsonValue email = Result.value("email");
                        if(email.isString())
                            user.result.email = email.toString();
                    }

                    if(Result.contains("countryCode")){
                        QJsonValue countryCode = Result.value("countryCode");
                        if(countryCode.isString())
                            user.result.countryCode = countryCode.toString();
                    }

                    if(Result.contains("phone")){
                        QJsonValue phone = Result.value("phone");
                        if(phone.isString())
                            user.result.phone = phone.toString();
                    }

                    if(Result.contains("createTime")){
                        QJsonValue createTime = Result.value("createTime");
                        if(!createTime.isString())
                            user.result.createTime = qint64(createTime.toDouble());
                    }

                    if(Result.contains("createIp")){
                        QJsonValue createIp = Result.value("createIp");
                        if(createIp.isString())
                            user.result.createIp = createIp.toString();
                    }

                    if(Result.contains("icon")){
                        QJsonValue icon = Result.value("icon");
                        if(icon.isString())
                            user.result.icon = icon.toString();
                    }

                    if(Result.contains("spaceUsed")){
                        QJsonValue spaceUsed = Result.value("spaceUsed");
                        if(!spaceUsed.isString())
                            user.result.spaceUsed = spaceUsed.toInt();
                    }

                    if(Result.contains("spaceCapacity")){
                        QJsonValue spaceCapacity = Result.value("spaceCapacity");
                        if(!spaceCapacity.isString())
                            user.result.spaceCapacity = spaceCapacity.toInt();
                    }

                    if(Result.contains("type")){
                        QJsonValue type = Result.value("type");
                        if(!type.isString())
                            user.result.type = type.toInt();
                    }

                    if(Result.contains("status")){
                        QJsonValue status = Result.value("status");
                        if(!status.isString())
                            user.result.status = status.toInt();
                    }
                }
            }

            if(UserModels.contains("code")){
                QJsonValue code = UserModels.value("code");
                if(code.isString())
                    user.code = code.toString();
            }

            if(UserModels.contains("success")){
                QJsonValue success = UserModels.value("success");
                if(success.isBool())
                    user.success = success.toBool();
            }

            if(UserModels.contains("token")){
                QJsonValue token = UserModels.value("token");
                if(token.isString())
                    user.token = token.toString();
            }
        }
    }
}

User UserModel::getUserModel() const
{
    return user;
}

LoginOutModel::LoginOutModel(QObject *parent) : QObject(parent)
{

}

void LoginOutModel::setLoginOutModel(QByteArray &ba)
{
    QJsonParseError Error;
    QJsonDocument Json = QJsonDocument::fromJson(ba, &Error);
    if(Error.error == QJsonParseError::NoError){
        if(Json.isObject()){

            QJsonObject LoginOutModels = Json.object();
            if(LoginOutModels.contains("status")){
                QJsonValue status = LoginOutModels.value("status");
                if(!status.isString())
                    loginOut.status = status.toInt();
            }

            if(LoginOutModels.contains("result")){
                QJsonValue result = LoginOutModels.value("result");
                if(result.isBool()){
                    loginOut.result = result.toBool();
                }
            }

            if(LoginOutModels.contains("code")){
                QJsonValue code = LoginOutModels.value("code");
                if(code.isString())
                    loginOut.code = code.toString();
            }

            if(LoginOutModels.contains("success")){
                QJsonValue success = LoginOutModels.value("success");
                if(success.isBool())
                    loginOut.success = success.toBool();
            }
        }
    }
}

LoginOutInfo LoginOutModel::getLoginOutModel() const
{
    return loginOut;
}
