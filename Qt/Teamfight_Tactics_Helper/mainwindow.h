#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "versionupdate.h"
#include "lineupupdate.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    VersionUpdate *v;
    LineupUpdate *l;

private slots:
    void on_versionUpdateButton_clicked();
    void on_lineupUpdateButton_clicked();
};
#endif // MAINWINDOW_H
