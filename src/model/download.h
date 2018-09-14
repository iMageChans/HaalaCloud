#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include <QObject>
#include <QNetworkReply>
#include <QNetworkAccessManager>

class DownloadManager : public QObject
{
    Q_OBJECT
public:
    explicit DownloadManager(QObject *parent = nullptr);

signals:

public slots:
    void signalDownloadProcess(qint64 Received, qint64 Total);
    void signalReplyFinished(int Code);
    void signalDownloadError();

private:
    void setDownInto(bool isSupportBreakPoint);
    QString getDownloadUrl();
    void downloadFile(QString url , QString fileName);
    void onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void onReadyRead();
    void onFinished();
    void onError(QNetworkReply::NetworkError code);
    void stopWork();
    void stopDownload();
    void reset();
    void removeFile(QString fileName);
    void closeDownload();

    QNetworkAccessManager *m_networkManager;
    QNetworkReply *m_reply;
    QUrl m_url;
    QString m_fileName;
    bool m_isSupportBreakPoint;
    qint64 m_bytesReceived;
    qint64 m_bytesTotal;
    qint64 m_bytesCurrentReceived;
    bool m_isStop;
};

#endif // DOWNLOAD_H
