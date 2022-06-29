#ifndef VERSIONUPDATE_H
#define VERSIONUPDATE_H

#include <QWidget>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QString>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QMessageBox>

namespace Ui {
class VersionUpdate;
}

class VersionUpdate : public QWidget
{
    Q_OBJECT

public:
    explicit VersionUpdate(QWidget *parent = nullptr);
    ~VersionUpdate();
    void openDataBase();
    void queryTable();
    void setStatus(int);

private:
    Ui::VersionUpdate *ui;
    QSqlDatabase db;
    QSqlQueryModel *model;
    int editType=0;

private slots:
    void on_updateButton_clicked();

    void on_insertButton_clicked();

    void on_delButton_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_cancelButton_clicked();

    void on_saveButton_clicked();

    void on_backButton_clicked();
};

#endif // VERSIONUPDATE_H
