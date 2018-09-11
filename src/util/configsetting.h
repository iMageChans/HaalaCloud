#ifndef CONFIGSETTING_H
#define CONFIGSETTING_H

#include <QString>


class ConfigSetting
{
public:
    ConfigSetting();
    void setConfig(QString key, QString value);
    void setSystemConfig(const QString &key, const QString &value);
    void deleteSystemConfig(const QString &key);
    QString getSystemConfig(const QString &keyp);

private:
    QString UserInfo;

    QString SystemPath();
};

#endif // CONFIGSETTING_H
