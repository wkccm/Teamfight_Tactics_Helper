#include "lineupupdate.h"
#include "ui_lineupupdate.h"
#include "config.h"
#include "mainwindow.h"

LineupUpdate::LineupUpdate(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LineupUpdate)
{
    ui->setupUi(this);
    model=new QSqlQueryModel(this);
    openDataBase();
    queryTable();
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter);
    setStatus(0);
}

LineupUpdate::~LineupUpdate()
{
    delete ui;
}

void LineupUpdate::openDataBase()
{
    Config config;
    db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setUserName(config.sqlusername);
    db.setPassword(config.sqlpassword);
    db.setDatabaseName("teamfight");
    if(db.open()==true)
    {
        qDebug()<<"数据库打开成功";
    }
    else
    {
        qDebug()<<"数据库打开失败";
    }
}

void  LineupUpdate::on_updateButton_clicked()
{
    setStatus(2);

}


void  LineupUpdate::on_insertButton_clicked()
{
    setStatus(1);
}


void  LineupUpdate::on_delButton_clicked()
{
    QSqlQuery query;
    query.prepare("delete from equipment where id = :id");
    query.bindValue(":id", ui->idEdit->text().toInt());
    if(QMessageBox::question(this,"删除","确定要删除该数据吗？",QMessageBox::Yes|QMessageBox::No) == QMessageBox::No)
        return;

    if(!query.exec()){
        QMessageBox::critical(this,"提示","删除失败！"+query.lastError().text());
        return;
    }
    queryTable();
    QMessageBox::critical(this,"提示","删除成功！");
}

void  LineupUpdate::queryTable(){
    editType=0;
    model->setQuery("select * from lineup");
    ui->tableView->setModel(model);
    model->setHeaderData(0, Qt::Horizontal, tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, tr("阵容名称"));
    model->setHeaderData(2, Qt::Horizontal, tr("金铲铲"));
    model->setHeaderData(3, Qt::Horizontal, tr("大剑"));
    model->setHeaderData(4, Qt::Horizontal, tr("大棒"));
    model->setHeaderData(5, Qt::Horizontal, tr("攻速"));
    model->setHeaderData(6, Qt::Horizontal, tr("水滴"));
    model->setHeaderData(7, Qt::Horizontal, tr("拳套"));
    model->setHeaderData(8, Qt::Horizontal, tr("护甲"));
    model->setHeaderData(9, Qt::Horizontal, tr("腰带"));
    model->setHeaderData(10, Qt::Horizontal, tr("魔抗"));
}


void  LineupUpdate::on_tableView_clicked(const QModelIndex &index)
{

    int row =index.row();

    ui->idEdit->setText(ui->tableView->model()->index(row,0).data().toString());
    ui->nameEdit->setText(ui->tableView->model()->index(row,1).data().toString());
    ui->shovelEdit->setText(ui->tableView->model()->index(row,2).data().toString());
    ui->swordEdit->setText(ui->tableView->model()->index(row,3).data().toString());
    ui->rodEdit->setText(ui->tableView->model()->index(row,4).data().toString());
    ui->bowEdit->setText(ui->tableView->model()->index(row,5).data().toString());
    ui->tearEdit->setText(ui->tableView->model()->index(row,6).data().toString());
    ui->glovesEdit->setText(ui->tableView->model()->index(row,7).data().toString());
    ui->vestEdit->setText(ui->tableView->model()->index(row,8).data().toString());
    ui->beltEdit->setText(ui->tableView->model()->index(row,9).data().toString());
    ui->cloakEdit->setText(ui->tableView->model()->index(row,10).data().toString());

}
void  LineupUpdate::setStatus(int status){
    editType=status;
    if(status==1){
        ui->idEdit->setText("");
        ui->nameEdit->setText("");
        ui->shovelEdit->setText("0");
        ui->swordEdit->setText("0");
        ui->rodEdit->setText("0");
        ui->bowEdit->setText("0");
        ui->tearEdit->setText("0");
        ui->glovesEdit->setText("0");
        ui->vestEdit->setText("0");
        ui->beltEdit->setText("0");
        ui->cloakEdit->setText("0");

        ui->idEdit->setEnabled(true);
        ui->nameEdit->setEnabled(true);
        ui->shovelEdit->setEnabled(true);
        ui->swordEdit->setEnabled(true);
        ui->rodEdit->setEnabled(true);
        ui->bowEdit->setEnabled(true);
        ui->tearEdit->setEnabled(true);
        ui->glovesEdit->setEnabled(true);
        ui->vestEdit->setEnabled(true);
        ui->beltEdit->setEnabled(true);
        ui->cloakEdit->setEnabled(true);

        ui->shovelMinusButton->setEnabled(true);
        ui->swordMinusButton->setEnabled(true);
        ui->rodMinusButton->setEnabled(true);
        ui->bowMinusButton->setEnabled(true);
        ui->tearMinusButton->setEnabled(true);
        ui->glovesMinusButton->setEnabled(true);
        ui->vestMinusButton->setEnabled(true);
        ui->beltMinusButton->setEnabled(true);
        ui->cloakMinusButton->setEnabled(true);

        ui->shovelPlusButton->setEnabled(true);
        ui->swordPlusButton->setEnabled(true);
        ui->rodPlusButton->setEnabled(true);
        ui->bowPlusButton->setEnabled(true);
        ui->tearPlusButton->setEnabled(true);
        ui->glovesPlusButton->setEnabled(true);
        ui->vestPlusButton->setEnabled(true);
        ui->beltPlusButton->setEnabled(true);
        ui->cloakPlusButton->setEnabled(true);

        ui->cancelButton->setEnabled(true);
        ui->saveButton->setEnabled(true);

        ui->insertButton->setEnabled(false);
        ui->updateButton->setEnabled(false);
        ui->delButton->setEnabled(false);
        ui->idEdit->setFocus();
        return;
    }
    if(status==2){
        ui->idEdit->setEnabled(false);
        ui->nameEdit->setEnabled(true);
        ui->shovelEdit->setEnabled(true);
        ui->swordEdit->setEnabled(true);
        ui->rodEdit->setEnabled(true);
        ui->bowEdit->setEnabled(true);
        ui->tearEdit->setEnabled(true);
        ui->glovesEdit->setEnabled(true);
        ui->vestEdit->setEnabled(true);
        ui->beltEdit->setEnabled(true);
        ui->cloakEdit->setEnabled(true);

        ui->shovelMinusButton->setEnabled(true);
        ui->swordMinusButton->setEnabled(true);
        ui->rodMinusButton->setEnabled(true);
        ui->bowMinusButton->setEnabled(true);
        ui->tearMinusButton->setEnabled(true);
        ui->glovesMinusButton->setEnabled(true);
        ui->vestMinusButton->setEnabled(true);
        ui->beltMinusButton->setEnabled(true);
        ui->cloakMinusButton->setEnabled(true);

        ui->shovelPlusButton->setEnabled(true);
        ui->swordPlusButton->setEnabled(true);
        ui->rodPlusButton->setEnabled(true);
        ui->bowPlusButton->setEnabled(true);
        ui->tearPlusButton->setEnabled(true);
        ui->glovesPlusButton->setEnabled(true);
        ui->vestPlusButton->setEnabled(true);
        ui->beltPlusButton->setEnabled(true);
        ui->cloakPlusButton->setEnabled(true);

        ui->cancelButton->setEnabled(true);
        ui->saveButton->setEnabled(true);

        ui->insertButton->setEnabled(false);
        ui->updateButton->setEnabled(false);
        ui->delButton->setEnabled(false);
        ui->idEdit->setFocus();
        return;
    }
    ui->idEdit->setText("");
    ui->nameEdit->setText("");
    ui->shovelEdit->setText("");
    ui->swordEdit->setText("");
    ui->rodEdit->setText("");
    ui->bowEdit->setText("");
    ui->tearEdit->setText("");
    ui->glovesEdit->setText("");
    ui->vestEdit->setText("");
    ui->beltEdit->setText("");
    ui->cloakEdit->setText("");

    ui->idEdit->setEnabled(false);
    ui->nameEdit->setEnabled(false);
    ui->shovelEdit->setEnabled(false);
    ui->swordEdit->setEnabled(false);
    ui->rodEdit->setEnabled(false);
    ui->bowEdit->setEnabled(false);
    ui->tearEdit->setEnabled(false);
    ui->glovesEdit->setEnabled(false);
    ui->vestEdit->setEnabled(false);
    ui->beltEdit->setEnabled(false);
    ui->cloakEdit->setEnabled(false);

    ui->shovelMinusButton->setEnabled(false);
    ui->swordMinusButton->setEnabled(false);
    ui->rodMinusButton->setEnabled(false);
    ui->bowMinusButton->setEnabled(false);
    ui->tearMinusButton->setEnabled(false);
    ui->glovesMinusButton->setEnabled(false);
    ui->vestMinusButton->setEnabled(false);
    ui->beltMinusButton->setEnabled(false);
    ui->cloakMinusButton->setEnabled(false);

    ui->shovelPlusButton->setEnabled(false);
    ui->swordPlusButton->setEnabled(false);
    ui->rodPlusButton->setEnabled(false);
    ui->bowPlusButton->setEnabled(false);
    ui->tearPlusButton->setEnabled(false);
    ui->glovesPlusButton->setEnabled(false);
    ui->vestPlusButton->setEnabled(false);
    ui->beltPlusButton->setEnabled(false);
    ui->cloakPlusButton->setEnabled(false);

    ui->cancelButton->setEnabled(false);
    ui->saveButton->setEnabled(false);
    ui->insertButton->setEnabled(true);
    ui->updateButton->setEnabled(true);
    ui->delButton->setEnabled(true);
}

void  LineupUpdate::on_cancelButton_clicked()
{
    setStatus(0);
}

void  LineupUpdate::on_saveButton_clicked()
{
    if(ui->idEdit->text() == ""||!ui->idEdit->text().toInt()){
          QMessageBox::critical(this,"提示","id不能为空且必须为数字！");
          return;
    }
    if(ui->nameEdit->text() == ""){
          QMessageBox::critical(this,"提示","阵容名称不能为空！");
          return;
    }


    int id = ui->idEdit->text().toInt();
    QString name = ui->nameEdit->text();
    int shovel = ui->shovelEdit->text().toInt();
    int sword = ui->swordEdit->text().toInt();
    int rod = ui->rodEdit->text().toInt();
    int bow = ui->bowEdit->text().toInt();
    int tear = ui->tearEdit->text().toInt();
    int gloves = ui->glovesEdit->text().toInt();
    int vest = ui->vestEdit->text().toInt();
    int belt = ui->beltEdit->text().toInt();
    int cloak = ui->cloakEdit->text().toInt();

    QSqlQuery query;
    if(editType==1){
        QSqlQuery query;
        query.prepare("insert into lineup(id,name,shovel,sword,rod,bow,tear,gloves,vest,belt,cloak) values(:id,:name,:shovel,:sword,:rod,:bow,:tear,:gloves,:vest,:belt,:cloak)");
        query.bindValue(":id", id);
        query.bindValue(":name", name);
        query.bindValue(":shovel", shovel);
        query.bindValue(":sword", sword);
        query.bindValue(":rod", rod);
        query.bindValue(":bow", bow);
        query.bindValue(":tear", tear);
        query.bindValue(":gloves", gloves);
        query.bindValue(":vest", vest);
        query.bindValue(":belt", belt);
        query.bindValue(":cloak", cloak);
        if(!query.exec()){
            QMessageBox::critical(this,"提示","新增失败！"+query.lastError().text());
            return;
        }
    }
    if(editType==2){
        query.prepare("update lineup set name = :name, shovel = :shovel, sword = :sword, rod = :rod, bow = :bow, tear = :tear, "
                      "gloves = :gloves, vest = :vest, belt = :belt, cloak = :cloak where id =:id");
        query.bindValue(":id", id);
        query.bindValue(":name", name);
        query.bindValue(":shovel", shovel);
        query.bindValue(":sword", sword);
        query.bindValue(":rod", rod);
        query.bindValue(":bow", bow);
        query.bindValue(":tear", tear);
        query.bindValue(":gloves", gloves);
        query.bindValue(":vest", vest);
        query.bindValue(":belt", belt);
        query.bindValue(":cloak", cloak);
        if(!query.exec()){
            QMessageBox::critical(this,"提示","修改失败！"+query.lastError().text());
            return;
        }
    }
    QMessageBox::critical(this,"提示","保存成功！");
    setStatus(0);
    queryTable();
}

void  LineupUpdate::on_backButton_clicked()
{
    this->hide();
    MainWindow *mw=new MainWindow;
    mw->show();
}

void LineupUpdate::on_shovelMinusButton_clicked()
{
    int shovel = ui->shovelEdit->text().toInt();
    if(shovel == 0)
    {
        return;
    }
    else
    {
        --shovel;
         ui->shovelEdit->setText(QString::number(shovel, 10));
    }
}

void LineupUpdate::on_shovelPlusButton_clicked()
{
    int shovel = ui->shovelEdit->text().toInt();
    ++shovel;
    ui->shovelEdit->setText(QString::number(shovel, 10));
}

void LineupUpdate::on_swordMinusButton_clicked()
{
    int sword = ui->swordEdit->text().toInt();
    if(sword == 0)
    {
        return;
    }
    else
    {
        --sword;
         ui->swordEdit->setText(QString::number(sword, 10));
    }
}

void LineupUpdate::on_swordPlusButton_clicked()
{
    int sword = ui->swordEdit->text().toInt();
    ++sword;
    ui->swordEdit->setText(QString::number(sword, 10));
}


void LineupUpdate::on_rodMinusButton_clicked()
{
    int rod = ui->rodEdit->text().toInt();
    if(rod == 0)
    {
        return;
    }
    else
    {
        --rod;
         ui->rodEdit->setText(QString::number(rod, 10));
    }
}


void LineupUpdate::on_rodPlusButton_clicked()
{
    int rod = ui->rodEdit->text().toInt();
    ++rod;
    ui->rodEdit->setText(QString::number(rod, 10));
}


void LineupUpdate::on_bowMinusButton_clicked()
{
    int bow = ui->bowEdit->text().toInt();
    if(bow == 0)
    {
        return;
    }
    else
    {
        --bow;
         ui->bowEdit->setText(QString::number(bow, 10));
    }
}


void LineupUpdate::on_bowPlusButton_clicked()
{
    int bow = ui->bowEdit->text().toInt();
    ++bow;
    ui->bowEdit->setText(QString::number(bow, 10));
}


void LineupUpdate::on_tearMinusButton_clicked()
{
    int tear = ui->tearEdit->text().toInt();
    if(tear == 0)
    {
        return;
    }
    else
    {
        --tear;
         ui->tearEdit->setText(QString::number(tear, 10));
    }
}


void LineupUpdate::on_tearPlusButton_clicked()
{
    int tear = ui->tearEdit->text().toInt();
    ++tear;
    ui->tearEdit->setText(QString::number(tear, 10));
}


void LineupUpdate::on_glovesMinusButton_clicked()
{
    int gloves = ui->glovesEdit->text().toInt();
    if(gloves == 0)
    {
        return;
    }
    else
    {
        --gloves;
         ui->glovesEdit->setText(QString::number(gloves, 10));
    }
}


void LineupUpdate::on_glovesPlusButton_clicked()
{
    int gloves = ui->glovesEdit->text().toInt();
    ++gloves;
    ui->glovesEdit->setText(QString::number(gloves, 10));
}


void LineupUpdate::on_vestMinusButton_clicked()
{
    int vest = ui->vestEdit->text().toInt();
    if(vest == 0)
    {
        return;
    }
    else
    {
        --vest;
         ui->vestEdit->setText(QString::number(vest, 10));
    }
}


void LineupUpdate::on_vestPlusButton_clicked()
{
    int vest = ui->vestEdit->text().toInt();
    ++vest;
    ui->vestEdit->setText(QString::number(vest, 10));
}


void LineupUpdate::on_beltMinusButton_clicked()
{
    int belt = ui->beltEdit->text().toInt();
    if(belt == 0)
    {
        return;
    }
    else
    {
        --belt;
         ui->beltEdit->setText(QString::number(belt, 10));
    }
}


void LineupUpdate::on_beltPlusButton_clicked()
{
    int belt = ui->beltEdit->text().toInt();
    ++belt;
    ui->beltEdit->setText(QString::number(belt, 10));
}


void LineupUpdate::on_cloakMinusButton_clicked()
{
    int cloak = ui->cloakEdit->text().toInt();
    if(cloak == 0)
    {
        return;
    }
    else
    {
        --cloak;
         ui->cloakEdit->setText(QString::number(cloak, 10));
    }
}


void LineupUpdate::on_cloakPlusButton_clicked()
{
    int cloak = ui->cloakEdit->text().toInt();
    ++cloak;
    ui->cloakEdit->setText(QString::number(cloak, 10));
}




