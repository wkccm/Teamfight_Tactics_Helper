#include "mainwindow.h"
#include "config.h"

#include <QApplication>


//extern QString sqlusername;
//extern QString sqlpassword;

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    return a.exec();
}
