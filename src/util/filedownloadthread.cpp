#include "filedownloadthread.h"
#include <QTime>
#include <QDebug>

#include <QMetaType>

FileDownloadThread::FileDownloadThread(QObject *parent) : QThread(parent)
{
    qRegisterMetaType<QList<FilesStatusInfo>>("QList<FileDownloadRecord>");
}

FileDownloadThread::~FileDownloadThread()
{
    requestInterruption();
    wait();
}

void FileDownloadThread::run()
{
    while (!isInterruptionRequested())
    {
        QTime time;
        time= QTime::currentTime();
        qsrand(time.msec()+time.second()*1000);

        QList<FilesStatusInfo> list;
        qRegisterMetaType<QList<FilesStatusInfo> > ("QList<FilesStatusInfo>");
        for (int i = 0; i < 5; ++i)
        {
            FilesStatusInfo record;
            record.FileName = QString("/root/user/file%1.log").arg(i + 1);
            record.Size = 1024 / ((i + 2) *(i + 2)) ;
            record.nStatus = i;
            record.nProgress = qrand() % 100 + 1;

            list.append(record);
        }

        emit transfer(list);
        msleep(1000);
    }
}
