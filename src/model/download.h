#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTime>

class Download : public QObject
{
    Q_OBJECT
public:
    explicit Download(QObject *parent = nullptr);
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
    QNetworkAccessManager *m_networkManager;
    QNetworkReply *m_reply;
    QUrl m_url;
    QString m_fileName;

    bool m_isSupportBreakPoint;

    qint64 m_bytesReceived;
    qint64 m_bytesTotal;
    qint64 m_bytesCurrentReceived;

    bool m_isStop;
public slots:

};

class Download;
class HttpDownload : public QObject
{
    Q_OBJECT

public:
    HttpDownload(QObject *parent = nullptr);

private:
    QString transformUnit(qint64 bytes , bool isSpeed = false);
    QString transformTime(qint64 seconds);

public slots:
    void onStartDownload();
    void onStopDownload();
    void onCloseDownload();

    void onReplyFinished(int);

private:

    QString m_url;
    Download *m_downloadManager;
    uint m_timeInterval;
    qint64 m_currentDownload;
    qint64 m_intervalDownload;
    QTime m_timeRecord;
};

#endif // DOWNLOAD_H
