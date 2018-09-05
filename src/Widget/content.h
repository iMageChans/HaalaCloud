#ifndef CONTENT_H
#define CONTENT_H

#include <QDialog>
#include <QFrame>
#include <QStackedWidget>
#include "detail.h"

class Content : public QWidget
{
    Q_OBJECT
public:
    explicit Content(QWidget *parent = nullptr);
    QStackedWidget *stack;
    detail *Files;
    detail *ImageFiles;
    detail *VideoFiles;

signals:

public slots:
};

#endif // CONTENT_H
