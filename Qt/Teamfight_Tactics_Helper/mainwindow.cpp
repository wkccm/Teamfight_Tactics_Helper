#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_versionUpdateButton_clicked()
{
    this->hide();
    v=new VersionUpdate;
    v->show();
}

void MainWindow::on_lineupUpdateButton_clicked()
{
    this->hide();
    l=new LineupUpdate;
    l->show();
}


void MainWindow::on_currentStateButton_clicked()
{
    this->hide();
    r=new LineupRecommand;
    r->show();
}

