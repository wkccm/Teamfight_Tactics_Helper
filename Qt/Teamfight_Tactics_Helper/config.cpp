#include "config.h"

#include <QDebug>
#include <QFile>
#include <QTextStream>

Config::Config()
{
    QFile file("D:/Code/CPP/Teamfight_Tactics_Helper/qt/Teamfight_Tactics_Helper/configPassword.txt");
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    sqlusername=in.readLine();
    sqlpassword=in.readLine();
}
