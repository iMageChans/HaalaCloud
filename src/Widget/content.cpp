#include "content.h"
#include <QHBoxLayout>

Content::Content(QWidget *parent) : QWidget(parent)
{
    stack = new QStackedWidget(this);
    stack->setFrameStyle(QFrame::Panel | QFrame::Raised);
    stack->setStyleSheet("border: 1px solid #E9E9E9;background: #E9E9E9;");

    Files = new detail();
    ImageFiles = new detail();
    VideoFiles = new detail();
    stack->addWidget(Files);
    stack->addWidget(ImageFiles);
    stack->addWidget(VideoFiles);

	QHBoxLayout *MainLayout = new QHBoxLayout(this);
	MainLayout->addWidget(stack);
	MainLayout->setSpacing(0);
	MainLayout->setMargin(0);
}
