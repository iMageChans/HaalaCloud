#ifndef LOGIN_H
#define LOGIN_H

#include "src/util/configsetting.h"
#include "src/model/usermodel.h"

#include <QWidget>
#include <QCloseEvent>
#include <QJsonObject>

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

public slots:
    void UserInfo_Login();
    void Token_Login();

private slots:
    void on_AotuLogin_stateChanged(int state);

    void on_Remember_stateChanged(int state);

    void showTimelimit();

protected:

private:
    Ui::Login *ui;

    ConfigSetting *setting;
    UserModel *model;
    QString Token;
    User user;

    int autoTime;
    QTimer *timer;

};

#endif // LOGIN_H
