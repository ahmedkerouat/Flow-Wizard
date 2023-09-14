#include "mainwindow.h"

#include <QApplication>
#include <QInputDialog>
#include <QFont>
#include <QFontDatabase>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    MainWindow w;

    //set custom font
    QFont font("Source Serif Pro");
    font.setPointSize(12);
    qApp->setFont(font);

    QIcon appIcon(":/imgs/icon.png");
    a.setWindowIcon(appIcon);
    w.show();

    return a.exec();
}
