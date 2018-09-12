#ifndef CONFIGSETTING_H
#define CONFIGSETTING_H

#include <QString>


class ConfigSetting
{
public:
    ConfigSetting();
    void setSystemConfig(const QString &key, const QString &value);
    void deleteSystemConfig(const QString &key);
    QString getSystemConfig(const QString &keyp);

private:
    QString SystemPath();
};

#endif // CONFIGSETTING_H
