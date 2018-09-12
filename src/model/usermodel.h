#ifndef USERMODEL_H
#define USERMODEL_H

#include <QObject>
#include <QByteArray>

typedef struct{
    int uuid;
    QString name;
    QString email;
    QString countryCode;
    QString phone;
    qint64 createTime;
    QString createIp;
    QString icon;
    qint64 spaceUsed;
    qint64 spaceCapacity;
    int type;
    int status;
}UserInfo;

typedef struct{
    int status;
    UserInfo result;
    QString code;
    bool success;
    QString token;
}User;

class UserModel : public QObject
{
    Q_OBJECT
public:
    explicit UserModel(QObject *parent = nullptr);

    void setUserModel(QByteArray &ba);
    User getUserModel() const;

signals:

public slots:

private:
    User user;
};

typedef struct{
    int status;
    bool result;
    QString code;
    bool success;
}LoginOutInfo;

class LoginOutModel : public QObject
{
    Q_OBJECT
public:
    explicit LoginOutModel(QObject *parent = nullptr);

    void setLoginOutModel(QByteArray &ba);
    LoginOutInfo getLoginOutModel() const;

signals:

public slots:

private:
    LoginOutInfo loginOut;
};

#endif // USERMODEL_H
