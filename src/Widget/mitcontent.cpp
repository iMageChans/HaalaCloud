#include "mitcontent.h"
#include <QHBoxLayout>

mitContent::mitContent(QWidget *parent) : QFrame(parent)
{
	stack = new QStackedWidget(this);
	stack->setFrameStyle(QFrame::Panel | QFrame::Raised);
    stack->setStyleSheet("border: 1px solid #E9E9E9;background: #F5F5F5;");

    Upload = new ProgressList();
    Download = new ProgressList();
    mitDone = new ClearList();
	Trash = new trash();
	stack->addWidget(Upload);
	stack->addWidget(Download);
	stack->addWidget(mitDone);
	stack->addWidget(Trash);

	QHBoxLayout *MainLayout = new QHBoxLayout(this);
	MainLayout->addWidget(stack);
	MainLayout->setSpacing(0);
	MainLayout->setMargin(0);
}
