#ifndef FILEDOWNLOADTHREAD_H
#define FILEDOWNLOADTHREAD_H

#include <QObject>
#include <QThread>
#include "src/model/progressmodel.h"

class FileDownloadThread : public QThread
{
    Q_OBJECT
public:
    explicit FileDownloadThread(QObject *parent = nullptr);
    ~FileDownloadThread() override;

protected:
    virtual void run() Q_DECL_OVERRIDE;

signals:
    void transfer(QList<FilesStatusInfo> filesStatusInfo);

public slots:

private:

};

#endif // FILEDOWNLOADTHREAD_H
