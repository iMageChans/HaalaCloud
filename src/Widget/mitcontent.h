#ifndef MITCONTENT_H
#define MITCONTENT_H

#include <QDialog>
#include <QFrame>
#include <QStackedWidget>
#include "progresslist.h"
#include "trash.h"
#include "clearlist.h"

class mitContent : public QFrame
{
    Q_OBJECT
public:
    explicit mitContent(QWidget *parent = nullptr);
	QStackedWidget *stack;
    ProgressList *Upload;
    ProgressList *Download;
    ClearList *mitDone;
	trash *Trash;
};

#endif // MITCONTENT_H
