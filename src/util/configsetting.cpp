#include "configsetting.h"

#include <QSettings>

ConfigSetting::ConfigSetting()
{
    UserInfo = "UserInfo";
}

QString ConfigSetting::SystemPath(){
#ifdef Q_OS_MAC
    {
        return QDir::homePath() + "/Library/Preferences/com.HalalCloud.plist";
    }
#else
    {
        return "HKEY_CURRENT_USER\\Software\\Microsoft\\HalalCloud";
    }
#endif
}

void ConfigSetting::setSystemConfig(const QString &key, const QString &value)
{
    QSettings settings(SystemPath(), QSettings::NativeFormat);
    settings.beginGroup(UserInfo);
    settings.setValue(key,value);
    settings.endGroup();
}

void ConfigSetting::deleteSystemConfig(const QString &key)
{
    QSettings setting(SystemPath(),QSettings::NativeFormat);
    if (setting.contains(UserInfo.arg("/").arg(key))){
        setting.beginGroup(UserInfo);
        setting.remove(key);
        setting.endGroup();
    }
}

QString ConfigSetting::getSystemConfig(const QString &key)
{
    QSettings settings(SystemPath(), QSettings::NativeFormat);
    QString value = settings.value(UserInfo.arg("/").arg(key)).toString();
    if (settings.contains(UserInfo.arg("/").arg(key))){
        value = settings.value(UserInfo.arg("/").arg(key)).toString();
    }
    return value;
}
