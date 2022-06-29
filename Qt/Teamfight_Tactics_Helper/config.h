#ifndef CONFIG_H
#define CONFIG_H

#include <QString>

class Config
{
public:
    Config();
    ~Config(){};

    QString sqlusername;
    QString sqlpassword;
};

#endif // CONFIG_H
