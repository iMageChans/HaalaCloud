#include "src/Widget/login.h"
#include "ui_login.h"
#include "src/Widget/mainwindow.h"

#include "src/util/request.h"

#include <QNetworkReply>
#include <QJsonDocument>
#include <QDebug>

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    setting = new ConfigSetting;
    setting->deleteSystemConfig("token");

    if(setting->getSystemConfig("Remember") == "2"){
        ui->Password->setText("12345678");
        ui->Remember->setCheckState(Qt::Checked);
    }

    if(setting->getSystemConfig("AotuLogin") == "2"){
        ui->Remember->setCheckState(Qt::Checked);
        ui->AotuLogin->setCheckState(Qt::Checked);
    }

    if (setting->getSystemConfig("token").length() > 0){
        Token = setting->getSystemConfig("token");
        connect(ui->LogonButton, SIGNAL(clicked()), this, SLOT(Token_Login()));
    }else{
        ui->Password->setText("");
        connect(ui->LogonButton, SIGNAL(clicked()), this, SLOT(UserInfo_Login()));
    }

    if(ui->AotuLogin->checkState() == Qt::Checked){
        if (setting->getSystemConfig("token").length() > 0){
            ui->LogonButton->setCheckable(true);
            autoTime = 1;
            timer = new QTimer(this);
            connect(timer, SIGNAL(timeout()), this, SLOT(showTimelimit()));
            qDebug() << "1";
            timer->start(500);
        }
    }


}

void Login::Token_Login()
{
    ui->LogonButton->setCheckable(true);
    QByteArray ba;
    QNetworkReply::NetworkError ret= WebServiceHelp::getInstance()->sendPostRequest("/v1/user/info", Token, QByteArray(), ba);
    if(ret==QNetworkReply::NoError)
    {
        UserModel *model = new UserModel;
        model->setUserModel(ba);
        user = model->getUserModel();
        setting->setSystemConfig("username", user.result.phone);
        setting->setSystemConfig("token", user.token);
        MainWindow *main = new MainWindow;
        main->show();
        main->setUserInfo(user);
        this->close();
    }
    else
    {
        qDebug() << QStringLiteral("%1 error:%2").arg("/v1/user/infon").arg(ret);
        ui->LogonButton->setCheckable(false);
        ui->Remember->setCheckState(Qt::Unchecked);
        ui->AotuLogin->setCheckState(Qt::Unchecked);

        if (setting->getSystemConfig("token").length() > 0)
            setting->deleteSystemConfig("token");
    }
}

void Login::UserInfo_Login()
{
    ui->LogonButton->setCheckable(true);
    QByteArray ba;
    QByteArray postBa;
    QJsonObject Json;
    Json.insert("value", ui->UserName->text());
    Json.insert("password", ui->Password->text());
    QJsonDocument docum;
    docum.setObject(Json);
    postBa = docum.toJson(QJsonDocument::Compact);
    QNetworkReply::NetworkError ret= WebServiceHelp::getInstance()->sendPostRequest("/v1/user/login", postBa, ba);
    if(ret==QNetworkReply::NoError)
    {
        UserModel *model = new UserModel;
        model->setUserModel(ba);
        user = model->getUserModel();
        setting->setSystemConfig("username", user.result.phone);
        setting->setSystemConfig("token", user.token);
        MainWindow *main = new MainWindow;
        main->show();
        main->setUserInfo(user);
        this->close();
    }
    else
    {
        qDebug() << QStringLiteral("%1 error:%2").arg("/v1/user/login").arg(ret);
        ui->LogonButton->setCheckable(false);
        ui->Remember->setCheckState(Qt::Unchecked);
        ui->AotuLogin->setCheckState(Qt::Unchecked);

        if (setting->getSystemConfig("token").length() > 0)
            setting->deleteSystemConfig("token");
    }
}

Login::~Login()
{
    delete ui;
}

void Login::on_AotuLogin_stateChanged(int state)
{
    setting->setSystemConfig("AotuLogin", QString::number(state));
    if(state == 2){
        ui->Remember->setCheckState(Qt::Checked);
    }else{
        ui->Remember->setCheckState(Qt::Unchecked);
    }
}

void Login::on_Remember_stateChanged(int state)
{
    setting->setSystemConfig("Remember", QString::number(state));
}

void Login::showTimelimit()
{
    if(autoTime != 0)
     {
         autoTime -= 1;
     }
     else
     {
        ui->LogonButton->clicked();
        timer->stop();
     }

}
