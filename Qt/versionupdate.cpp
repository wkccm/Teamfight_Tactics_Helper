#include "versionupdate.h"
#include "ui_versionupdate.h"

VersionUpdate::VersionUpdate(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VersionUpdate)
{
    ui->setupUi(this);
}

VersionUpdate::~VersionUpdate()
{
    delete ui;
}
