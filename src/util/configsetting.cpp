#include "configsetting.h"

#include <QSettings>
#include <QDir>

ConfigSetting::ConfigSetting()
{

}

QString ConfigSetting::SystemPath(){
#ifdef Q_OS_MAC
    {
        return QDir::homePath() + "/Library/Preferences/com.HaalalCloud.plist";
    }
#else
    {
        return "HKEY_CURRENT_USER\\Software\\Microsoft\\HaalalCloud";
    }
#endif
}

void ConfigSetting::setSystemConfig(const QString &key, const QString &value)
{
    QSettings settings(SystemPath(), QSettings::NativeFormat);
    settings.beginGroup(QString("UserInfo"));
    settings.setValue(key,value);
    settings.endGroup();
}

void ConfigSetting::deleteSystemConfig(const QString &key)
{
    QSettings setting(SystemPath(),QSettings::NativeFormat);
    if (setting.contains(QString("UserInfo%1%2").arg("/").arg(key))){
        setting.beginGroup(QString("UserInfo"));
        setting.remove(key);
        setting.endGroup();
    }
}

QString ConfigSetting::getSystemConfig(const QString &key)
{
    QSettings settings(SystemPath(), QSettings::NativeFormat);
    QString value = settings.value(QString("UserInfo%1%2").arg("/").arg(key)).toString();
    if (settings.contains(QString("UserInfo%1%2").arg("/").arg(key))){
        value = settings.value(QString("UserInfo%1%2").arg("/").arg(key)).toString();
    }
    return value;
}
