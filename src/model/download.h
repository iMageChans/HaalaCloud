#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class Download : public QObject
{
    Q_OBJECT
public:
    explicit Download(QObject *parent = 0);
    void downloadFile(QString url, QString fileName);
    void setDownInto(bool isSupportBreakPoint);
    void stopDownload();
    void closeDownload();
    QString getDownloadUrl();
    void reset();
private:
    void stopWork();
    void removeFile(QString fileName);

signals:
    void signalDownloadProcess(qint64, qint64);
    void signalReplyFinished(int);
    void signalDownloadError();
private slots:
    void onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void onReadyRead();
    void onFinished();
    void onError(QNetworkReply::NetworkError code);
private:
    QNetworkAccessManager* m_networkManager;
    QNetworkReply* m_reply;
    QUrl m_url;
    QString m_fileName;

    bool m_isSupportBreakPoint;

    qint64 m_bytesReceived;
    qint64 m_bytesTotal;
    qint64 m_bytesCurrentReceived;

    bool m_isStop;
public slots:
};

#endif // DOWNLOAD_H
