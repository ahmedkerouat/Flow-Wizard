#include "mainwindow.h"

#include <QApplication>
#include <QSettings>
#include <QInputDialog>
#include <QFont>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //create settings to remember stuff
    QSettings settings("./myappsettings.ini", QSettings::IniFormat);
    QVariant valFirstTime = settings.value("first-time");
    QVariant valUsername = settings.value("Username");

    MainWindow w;

    //set custom font
    QFontDatabase::addApplicationFont(":/fonts/SourceSerifPro-Regular.ttf");
    QFont font("Source Serif Pro");
    font.setPointSize(12);
    qApp->setFont(font);

    QIcon appIcon(":/imgs/icon.png");
    a.setWindowIcon(appIcon);
    w.show();

    if (!valFirstTime.isValid()) {
        // ... first run
        settings.setValue("first-time", false);
        //settings.setValue("Username", inputText);
    } else {
        // ... not first run
    }

    return a.exec();
}
