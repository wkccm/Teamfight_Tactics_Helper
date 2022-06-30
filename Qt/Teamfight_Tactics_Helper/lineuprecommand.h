#ifndef LINEUPRECOMMAND_H
#define LINEUPRECOMMAND_H

#include <QWidget>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QString>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QStandardItemModel>

#include <algorithm>
#include <vector>
#include <utility>
#include <string>

namespace Ui {
class LineupRecommand;
}

class LineupRecommand : public QWidget
{
    Q_OBJECT

public:
    explicit LineupRecommand(QWidget *parent = nullptr);
    ~LineupRecommand();
    void openDataBase();
    void queryTable();
    void updateFunc();

private:
    Ui::LineupRecommand *ui;
    QSqlDatabase db;
    QSqlQueryModel *model;
    QStandardItemModel *output;

private slots:
    void on_backButton_clicked();

    void on_resetButton_clicked();

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

#endif // LINEUPRECOMMAND_H
