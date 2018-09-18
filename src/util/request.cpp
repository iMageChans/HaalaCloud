#include "request.h"

#include <QNetworkReply>


NetDataListenerThread::NetDataListenerThread(QNetworkAccessManager *manager, QNetworkReply *reply, int timeoutms, QObject *parent)
    :QThread(parent),mManager(manager),m_TimeOutms(timeoutms),m_reply(reply)
{
    m_waitTimeOut = false;
    m_isWaitTimeOut = false;
}
NetDataListenerThread::~NetDataListenerThread()
{
}
void NetDataListenerThread::run()
{
    m_isWaitTimeOut = waitForConnect();
}
bool NetDataListenerThread::waitForConnect()
{
    QEventLoop eventLoop;
    QTimer * timer = nullptr;
    m_waitTimeOut = false;
    bool bWaitTimeOut = false;
    if (m_TimeOutms > 0)
    {
        timer = new QTimer;
        connect(timer, SIGNAL(timeout()), this, SLOT(slot_waitTimeout()));
        timer->setSingleShot(true);
        timer->start(m_TimeOutms);
        connect(this, SIGNAL(sig_waitTimeout()), &eventLoop, SLOT(quit()));
    }
    connect(mManager, SIGNAL(finished(QNetworkReply *)), &eventLoop, SLOT(quit()));
    if (m_reply != nullptr)
    {
        connect(m_reply, SIGNAL(readyRead()), &eventLoop, SLOT(quit()));
    }
    eventLoop.exec();
    if (timer != nullptr)
    {
        timer->stop();
        delete timer;
        timer = nullptr;
    }
    bWaitTimeOut = m_waitTimeOut;
    m_waitTimeOut = false;
    return !bWaitTimeOut;
}
void NetDataListenerThread::slot_waitTimeout()
{
    m_waitTimeOut = true;
    emit sig_waitTimeout();
}
bool NetDataListenerThread::getIsWaitTimeOut() const
{
    return m_isWaitTimeOut;
}

WebServiceHelp * WebServiceHelp::serverHelp = nullptr;
WebServiceHelp::Dispose WebServiceHelp::disp;


WebServiceHelp::WebServiceHelp(QObject *parent):QObject(parent)
{
    manager = new QNetworkAccessManager();
    m_errCode= QNetworkReply::NoError;
    baseUrl = "https://api.6pan.cn";
}
WebServiceHelp::~WebServiceHelp()
{
    manager->deleteLater();
}
WebServiceHelp *WebServiceHelp::getInstance()
{
    if(serverHelp==nullptr)
    {
        serverHelp = new WebServiceHelp();
    }
    return serverHelp;
}
QNetworkReply::NetworkError WebServiceHelp::sendGetRequest(QString urlStr, QByteArray &ba,int timeOutms)
{
    QNetworkReply::NetworkError retError = QNetworkReply::NoError;
    m_errCode= QNetworkReply::NoError;
    QNetworkRequest request;
    QUrl url(QString("https://api.6pan.cn%1").arg(urlStr));
    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    QNetworkReply *reply = manager->get(request);
    connect(reply,static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error),this,&WebServiceHelp::slot_error);
    QEventLoop eventLoop;
    NetDataListenerThread * thread = new NetDataListenerThread(manager,reply,timeOutms);
    connect(thread, &NetDataListenerThread::finished,&eventLoop,&QEventLoop::quit);
    thread->start();
    eventLoop.exec();
    if(thread->getIsWaitTimeOut())
    {
        ba = reply->readAll();
    }
    else
    {
        m_errCode=QNetworkReply::TimeoutError;
    }
    thread->deleteLater();
    delete reply;
    delete thread;
    thread = nullptr;
    retError = m_errCode;
    m_errCode= QNetworkReply::NoError;
    return retError;
}

QNetworkReply::NetworkError WebServiceHelp::sendGetRequest(QString urlStr, QString Token,QByteArray &ba,int timeOutms)
{
    QNetworkReply::NetworkError retError = QNetworkReply::NoError;
    m_errCode= QNetworkReply::NoError;
    QByteArray bearer;
    QNetworkRequest request;
    QUrl url(QString("https://api.6pan.cn%1").arg(urlStr));
    request.setUrl(url);
    bearer.append("Bearer " + Token);
    request.setRawHeader("Authorization", bearer);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    QNetworkReply *reply = manager->get(request);
    connect(reply,static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error),this,&WebServiceHelp::slot_error);
    QEventLoop eventLoop;
    NetDataListenerThread * thread = new NetDataListenerThread(manager,reply,timeOutms);
    connect(thread, &NetDataListenerThread::finished,&eventLoop,&QEventLoop::quit);
    thread->start();
    eventLoop.exec();
    if(thread->getIsWaitTimeOut())
    {
        ba = reply->readAll();
    }
    else
    {
        m_errCode=QNetworkReply::TimeoutError;
    }
    thread->deleteLater();
    delete reply;
    delete thread;
    thread = nullptr;
    retError = m_errCode;
    m_errCode= QNetworkReply::NoError;
    return retError;
}

QNetworkReply::NetworkError WebServiceHelp:: sendPostRequest(QString website, const QByteArray &postBa, QByteArray &retBa, int timeOutms)
{
    QString urlStr =website;
    QNetworkReply::NetworkError retError = QNetworkReply::NoError;
    m_errCode= QNetworkReply::NoError;
    QNetworkRequest request;
    QSslConfiguration config;
    config.setPeerVerifyMode(QSslSocket::VerifyNone);
    config.setProtocol(QSsl::TlsV1SslV3);
    request.setSslConfiguration(config);
    QUrl url(QString("https://api.6pan.cn%1").arg(urlStr));
    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    QNetworkReply *reply = manager->post(request,postBa);
    connect(reply,static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error),this,&WebServiceHelp::slot_error);
    QEventLoop eventLoop;
    NetDataListenerThread * thread = new NetDataListenerThread(manager,reply,timeOutms);
    connect(thread, &NetDataListenerThread::finished,&eventLoop,&QEventLoop::quit);
    thread->start();
    eventLoop.exec();
    if(thread->getIsWaitTimeOut())
    {
        retBa = reply->readAll();
    }
    else
    {
        m_errCode=QNetworkReply::TimeoutError;
    }
    thread->deleteLater();
    delete reply;
    delete thread;
    thread = nullptr;
    retError = m_errCode;
    m_errCode= QNetworkReply::NoError;
    return retError;
}

QNetworkReply::NetworkError WebServiceHelp:: sendPostRequest(QString website, QString Token, const QByteArray &postBa, QByteArray &retBa, int timeOutms)
{
    QString urlStr =website;
    QNetworkReply::NetworkError retError = QNetworkReply::NoError;
    m_errCode= QNetworkReply::NoError;
    QByteArray bearer;
    QNetworkRequest request;
    QSslConfiguration config;
    config.setPeerVerifyMode(QSslSocket::VerifyNone);
    config.setProtocol(QSsl::TlsV1SslV3);
    request.setSslConfiguration(config);
    QUrl url(QString("https://api.6pan.cn%1").arg(urlStr));
    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader,postBa.length());
    bearer.append("Bearer " + Token);
    request.setRawHeader("Authorization", bearer);
    QNetworkReply *reply = manager->post(request,postBa);
    connect(reply,static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error),this,&WebServiceHelp::slot_error);
    QEventLoop eventLoop;
    NetDataListenerThread * thread = new NetDataListenerThread(manager,reply,timeOutms);
    connect(thread, &NetDataListenerThread::finished,&eventLoop,&QEventLoop::quit);
    thread->start();
    eventLoop.exec();
    if(thread->getIsWaitTimeOut())
    {
        retBa = reply->readAll();
    }
    else
    {
        m_errCode=QNetworkReply::TimeoutError;
    }
    thread->deleteLater();
    delete reply;
    delete thread;
    thread = nullptr;
    retError = m_errCode;
    m_errCode= QNetworkReply::NoError;
    return retError;
}

QNetworkReply::NetworkError WebServiceHelp:: uploadRequest(QString website, QString uuid, QString Token, const QByteArray &postBa, QByteArray &retBa, int timeOutms)
{
    QString urlStr =website;
    QNetworkReply::NetworkError retError = QNetworkReply::NoError;
    m_errCode= QNetworkReply::NoError;
    QByteArray bearer;
    QNetworkRequest request;
    QSslConfiguration config;
    config.setPeerVerifyMode(QSslSocket::VerifyNone);
    config.setProtocol(QSsl::TlsV1SslV3);
    request.setSslConfiguration(config);
     QUrl url(QString("https://upload-vod-v1.qiecdn.com%1").arg(urlStr));
    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader,postBa.length());
    bearer.append(Token);
    request.setRawHeader("Authorization", bearer);
    request.setRawHeader("uploadBatch", uuid.toLatin1());
    QNetworkReply *reply = manager->post(request,postBa);
    connect(reply,static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error),this,&WebServiceHelp::slot_error);
    QEventLoop eventLoop;
    NetDataListenerThread * thread = new NetDataListenerThread(manager,reply,timeOutms);
    connect(thread, &NetDataListenerThread::finished,&eventLoop,&QEventLoop::quit);
    thread->start();
    eventLoop.exec();
    if(thread->getIsWaitTimeOut())
    {
        retBa = reply->readAll();
    }
    else
    {
        m_errCode=QNetworkReply::TimeoutError;
    }
    thread->deleteLater();
    delete reply;
    delete thread;
    thread = nullptr;
    retError = m_errCode;
    m_errCode= QNetworkReply::NoError;
    return retError;
}
void WebServiceHelp::slot_error(QNetworkReply::NetworkError code)
{
    m_errCode = code;
}
WebServiceHelp::Dispose::~Dispose()
{
    if(WebServiceHelp::serverHelp!=nullptr)
    {
        delete WebServiceHelp::serverHelp;
        WebServiceHelp::serverHelp=nullptr;
    }
}
