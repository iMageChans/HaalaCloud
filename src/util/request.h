#ifndef REQUEST_H
#define REQUEST_H

#include <QByteArray>
#include <QNetworkReply>
#include <QThread>
#include <QEventLoop>
#include <QTimer>


class NetDataListenerThread:public QThread
{
    Q_OBJECT
public:
    NetDataListenerThread(QNetworkAccessManager *manager,QNetworkReply * reply,int timeoutms,QObject *parent = 0);
    ~NetDataListenerThread();
    QByteArray getBa() const;
    bool getIsWaitTimeOut() const;
protected:
    virtual void run();
private:
    bool waitForConnect();
protected slots:
    void slot_waitTimeout();
signals:
    void sig_waitTimeout();
private:
    QNetworkAccessManager *mManager;
    int m_TimeOutms;
    bool m_waitTimeOut;
    bool m_isWaitTimeOut;
    QNetworkReply * m_reply;
};


class   WebServiceHelp:public QObject
{
    Q_OBJECT
private:
    class Dispose
    {
    public:
        ~Dispose();
    };
public:
    static WebServiceHelp * getInstance();
    ~WebServiceHelp();
public:
    /**
     * @brief sendGetRequest 发送Get请求
     * @param urlStr  url
     * @param ba      返回数据
     * @param timeOutms 超时时间
     * @return  返回错误代码
     */
    QNetworkReply::NetworkError sendGetRequest(QString urlStr, QByteArray & ba, int timeOutms=3000);
    QNetworkReply::NetworkError sendGetRequest(QString urlStr, QString Token, QByteArray & ba, int timeOutms=3000);
    /**
     * @brief sendPostRequest 发送post请求
     * @param website  网址
     * @param methodName 方法名称
     * @param param 参数
     * @param postBa    post数据
     * @param code      返回代码
     * @param message   返回信息
     * @param data      返回数据
     * @param timeOutms 超时时间
     * @return 返回错误代码
     */
    QNetworkReply::NetworkError sendPostRequest(QString website, const QByteArray & postBa, QByteArray& retBa, int timeOutms=3000);
    QNetworkReply::NetworkError sendPostRequest(QString website, QString Token, const QByteArray &postBa, QByteArray &retBa, int timeOutms=3000);
    QNetworkReply::NetworkError uploadRequest(QString website, QString uuid, QString Token, const QByteArray &postBa, QByteArray &retBa, int timeOutms=3000);
protected slots:
    void slot_error(QNetworkReply::NetworkError code);
private:
    static WebServiceHelp * serverHelp;
    static WebServiceHelp::Dispose disp;
    QNetworkAccessManager *manager;
    QNetworkReply::NetworkError m_errCode;
    QString baseUrl;

private:
    WebServiceHelp(QObject *parent=0);
};

#endif // REQUEST_H
