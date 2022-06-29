#include "versionupdate.h"
#include "ui_versionupdate.h"
#include "config.h"
#include "mainwindow.h"


VersionUpdate::VersionUpdate(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VersionUpdate)
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

VersionUpdate::~VersionUpdate()
{
    delete ui;
}

void VersionUpdate::openDataBase()
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

void VersionUpdate::on_updateButton_clicked()
{
    setStatus(2);

}


void VersionUpdate::on_insertButton_clicked()
{
    setStatus(1);
}


void VersionUpdate::on_delButton_clicked()
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

void VersionUpdate::queryTable(){
    editType=0;
    model->setQuery("select * from equipment");
    ui->tableView->setModel(model);
    model->setHeaderData(0, Qt::Horizontal, tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, tr("装备名称"));
}


void VersionUpdate::on_tableView_clicked(const QModelIndex &index)
{

    int row =index.row();

    ui->idEdit->setText(ui->tableView->model()->index(row,0).data().toString());
    ui->nameEdit->setText(ui->tableView->model()->index(row,1).data().toString());

}
void VersionUpdate::setStatus(int status){
    editType=status;
    if(status==1){
        ui->idEdit->setText("");
        ui->nameEdit->setText("");
        ui->idEdit->setEnabled(true);
        ui->nameEdit->setEnabled(true);
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
    ui->idEdit->setEnabled(false);
    ui->nameEdit->setEnabled(false);
    ui->cancelButton->setEnabled(false);
    ui->saveButton->setEnabled(false);
    ui->insertButton->setEnabled(true);
    ui->updateButton->setEnabled(true);
    ui->delButton->setEnabled(true);
}

void VersionUpdate::on_cancelButton_clicked()
{
    setStatus(0);
}

void VersionUpdate::on_saveButton_clicked()
{
    if(ui->idEdit->text() == ""||!ui->idEdit->text().toInt()){
          QMessageBox::critical(this,"提示","id不能为空且必须为数字！");
          return;
    }
    if(ui->nameEdit->text() == ""){
          QMessageBox::critical(this,"提示","装备名称不能为空！");
          return;
    }

    int id = ui->idEdit->text().toInt();
    QString name = ui->nameEdit->text();

    QSqlQuery query;
    if(editType==1){
        QSqlQuery query;
        query.prepare("insert into equipment(id,name) values(:id,:name)");
        query.bindValue(":id", id);
        query.bindValue(":name", name);
        if(!query.exec()){
            QMessageBox::critical(this,"提示","新增失败！"+query.lastError().text());
            return;
        }
    }
    if(editType==2){
        query.prepare("update equipment set name = :name where id =:id");
        query.bindValue(":id", id);
        query.bindValue(":name", name);
        if(!query.exec()){
            QMessageBox::critical(this,"提示","修改失败！"+query.lastError().text());
            return;
        }
    }
    QMessageBox::critical(this,"提示","保存成功！");
    setStatus(0);
    queryTable();
}

void VersionUpdate::on_backButton_clicked()
{
    this->hide();
    MainWindow *mw=new MainWindow;
    mw->show();
}
