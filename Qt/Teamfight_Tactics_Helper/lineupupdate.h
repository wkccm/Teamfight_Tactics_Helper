#ifndef LINEUPUPDATE_H
#define LINEUPUPDATE_H

#include <QWidget>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QString>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QMessageBox>

namespace Ui {
class LineupUpdate;
}

class LineupUpdate : public QWidget
{
    Q_OBJECT

public:
    explicit LineupUpdate(QWidget *parent = nullptr);
    ~LineupUpdate();
    void openDataBase();
    void queryTable();
    void setStatus(int);

private:
    Ui::LineupUpdate *ui;
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

    void on_shovelMinusButton_clicked();
    void on_shovelPlusButton_clicked();

    void on_swordMinusButton_clicked();
    void on_swordPlusButton_clicked();

    void on_rodMinusButton_clicked();
    void on_rodPlusButton_clicked();

    void on_bowMinusButton_clicked();
    void on_bowPlusButton_clicked();

    void on_tearMinusButton_clicked();
    void on_tearPlusButton_clicked();

    void on_glovesMinusButton_clicked();
    void on_glovesPlusButton_clicked();

    void on_vestMinusButton_clicked();
    void on_vestPlusButton_clicked();

    void on_beltMinusButton_clicked();
    void on_beltPlusButton_clicked();

    void on_cloakMinusButton_clicked();
    void on_cloakPlusButton_clicked();
};

#endif // LINEUPUPDATE_H
