
#include "src/Widget/login.h"
#include "src/Widget/messagebox.h"

#include <QApplication>

int main(int argc, char *argv[])
{

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    Login w;
    w.show();

    return a.exec();
}
