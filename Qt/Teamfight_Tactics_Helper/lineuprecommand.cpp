#include "lineuprecommand.h"
#include "ui_lineuprecommand.h"
#include "config.h"
#include "mainwindow.h"

LineupRecommand::LineupRecommand(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LineupRecommand)
{
    ui->setupUi(this);
    model=new QSqlQueryModel(this);
    output=new QStandardItemModel(this);
    openDataBase();
    queryTable();
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter);

    ui->shovelEdit->setText("0");
    ui->swordEdit->setText("0");
    ui->rodEdit->setText("0");
    ui->bowEdit->setText("0");
    ui->tearEdit->setText("0");
    ui->glovesEdit->setText("0");
    ui->vestEdit->setText("0");
    ui->beltEdit->setText("0");
    ui->cloakEdit->setText("0");
}

LineupRecommand::~LineupRecommand()
{
    delete ui;
}

void LineupRecommand::openDataBase()
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

    model->setQuery("select * from lineup");

}

void  LineupRecommand::queryTable(){

    ui->tableView->setModel(output);
    int row = model->rowCount();
    output->insertColumns(0,7);
    output->insertRows(0,row);
    output->setHeaderData(0, Qt::Horizontal, tr("阵容名称"));
    output->setHeaderData(1, Qt::Horizontal, tr("权重"));
    output->setHeaderData(2, Qt::Horizontal, tr("第一顺位"));
    output->setHeaderData(3, Qt::Horizontal, tr("第二顺位"));
    output->setHeaderData(4, Qt::Horizontal, tr("第三顺位"));
    output->setHeaderData(5, Qt::Horizontal, tr("第四顺位"));
    output->setHeaderData(6, Qt::Horizontal, tr("第五顺位"));

    updateFunc();
}


void LineupRecommand::updateFunc()
{
    std::vector<std::pair<std::vector<std::string>, double>>vec;
    int row = model->rowCount();
    for(int i=0; i<row; ++i)
    {
        std::string lineupName=model->data(model->index(i,1)).toString().toStdString();

        int shovel=qMax(model->data(model->index(i,2)).toInt()-ui->shovelEdit->text().toInt(),0);
        double shovelValue=shovel==0?0:10*(1+(shovel-1)*0.6);

        int sword=qMax(model->data(model->index(i,3)).toInt()-ui->swordEdit->text().toInt(),0);
        double swordValue=sword==0?0:2*(1+(sword-1)*0.6);

        int rod=qMax(model->data(model->index(i,4)).toInt()-ui->rodEdit->text().toInt(),0);
        double rodValue=rod==0?0:2*(1+(rod-1)*0.6);

        int bow=qMax(model->data(model->index(i,5)).toInt()-ui->bowEdit->text().toInt(),0);
        double bowValue=bow==0?0:2*(1+(bow-1)*0.6);

        int tear=qMax(model->data(model->index(i,6)).toInt()-ui->tearEdit->text().toInt(),0);
        double tearValue=tear==0?0:2*(1+(tear-1)*0.6);

        int gloves=qMax(model->data(model->index(i,7)).toInt()-ui->glovesEdit->text().toInt(),0);
        double glovesValue=gloves==0?0:2*(1+(gloves-1)*0.6);

        int vest=qMax(model->data(model->index(i,8)).toInt()-ui->vestEdit->text().toInt(),0);
        double vestValue=vest==0?0:1*(1+(vest-1)*0.6);

        int belt=qMax(model->data(model->index(i,9)).toInt()-ui->beltEdit->text().toInt(),0);
        double beltValue=belt==0?0:1*(1+(belt-1)*0.6);

        int cloak=qMax(model->data(model->index(i,10)).toInt()-ui->cloakEdit->text().toInt(),0);
        double cloakValue=cloak==0?0:1*(1+(cloak-1)*0.6);

        std::vector<std::pair<std::pair<int, double>,std::string>>v;
        v.push_back(std::make_pair(std::make_pair(shovel, shovelValue), "金铲铲"));
        v.push_back(std::make_pair(std::make_pair(sword, swordValue), "大剑"));
        v.push_back(std::make_pair(std::make_pair(rod, rodValue), "大棒"));
        v.push_back(std::make_pair(std::make_pair(bow, bowValue), "攻速"));
        v.push_back(std::make_pair(std::make_pair(tear, tearValue), "水滴"));
        v.push_back(std::make_pair(std::make_pair(gloves, glovesValue), "拳套"));
        v.push_back(std::make_pair(std::make_pair(vest, vestValue), "护甲"));
        v.push_back(std::make_pair(std::make_pair(belt, beltValue), "腰带"));
        v.push_back(std::make_pair(std::make_pair(cloak, cloakValue), "魔抗"));

        std::sort(v.begin(), v.end(), [](const std::pair<std::pair<int, double>, std::string>a, const std::pair<std::pair<int, double>, std::string>b)
        {
            return a.first.second>b.first.second;
        });

        double sumValue=shovelValue+swordValue+rodValue+bowValue+tearValue+glovesValue+vestValue+beltValue+cloakValue;

        std::vector<std::string>temp;
        temp.push_back(lineupName);

        for(int i=0;i<v.size(); ++i)
        {
            for(int j=0;j<v[i].first.first;++j)
            {
                temp.push_back(v[i].second);
            }
        }
        vec.push_back(std::make_pair(temp, sumValue));
    }

    std::sort(vec.begin(), vec.end(), [](const std::pair<std::vector<std::string>, double>a, const std::pair<std::vector<std::string>, double>b){
        return a.second<b.second;
    });

    for(int i=0;i<vec.size();++i)
    {


        output->setData(output->index(i,0),vec[i].first[0].data());
        output->setData(output->index(i,1), vec[i].second);
        for(int j=1;j<vec[i].first.size() && j<=5;++j)
        {
            qDebug()<<vec[i].first[j].data();
            output->setData(output->index(i,j+1), vec[i].first[j].data());
        }
        for(int j=vec[i].first.size()+1;j<=5;++j)
        {
            output->setData(output->index(i,j+1), "-");
        }
    }
}

void  LineupRecommand::on_backButton_clicked()
{
    this->hide();
    MainWindow *mw=new MainWindow;
    mw->show();
}

void LineupRecommand::on_resetButton_clicked()
{

    ui->shovelEdit->setText("0");
    ui->swordEdit->setText("0");
    ui->rodEdit->setText("0");
    ui->bowEdit->setText("0");
    ui->tearEdit->setText("0");
    ui->glovesEdit->setText("0");
    ui->vestEdit->setText("0");
    ui->beltEdit->setText("0");
    ui->cloakEdit->setText("0");

    updateFunc();
}



void LineupRecommand::on_shovelMinusButton_clicked()
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

    updateFunc();
}

void LineupRecommand::on_shovelPlusButton_clicked()
{
    int shovel = ui->shovelEdit->text().toInt();
    ++shovel;
    ui->shovelEdit->setText(QString::number(shovel, 10));

    updateFunc();
}

void LineupRecommand::on_swordMinusButton_clicked()
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

    updateFunc();
}

void LineupRecommand::on_swordPlusButton_clicked()
{
    int sword = ui->swordEdit->text().toInt();
    ++sword;
    ui->swordEdit->setText(QString::number(sword, 10));

    updateFunc();
}


void LineupRecommand::on_rodMinusButton_clicked()
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

    updateFunc();
}


void LineupRecommand::on_rodPlusButton_clicked()
{
    int rod = ui->rodEdit->text().toInt();
    ++rod;
    ui->rodEdit->setText(QString::number(rod, 10));

    updateFunc();
}


void LineupRecommand::on_bowMinusButton_clicked()
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

    updateFunc();
}


void LineupRecommand::on_bowPlusButton_clicked()
{
    int bow = ui->bowEdit->text().toInt();
    ++bow;
    ui->bowEdit->setText(QString::number(bow, 10));

    updateFunc();
}


void LineupRecommand::on_tearMinusButton_clicked()
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

    updateFunc();
}


void LineupRecommand::on_tearPlusButton_clicked()
{
    int tear = ui->tearEdit->text().toInt();
    ++tear;
    ui->tearEdit->setText(QString::number(tear, 10));

    updateFunc();
}


void LineupRecommand::on_glovesMinusButton_clicked()
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

    updateFunc();
}


void LineupRecommand::on_glovesPlusButton_clicked()
{
    int gloves = ui->glovesEdit->text().toInt();
    ++gloves;
    ui->glovesEdit->setText(QString::number(gloves, 10));

    updateFunc();
}


void LineupRecommand::on_vestMinusButton_clicked()
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

    updateFunc();
}


void LineupRecommand::on_vestPlusButton_clicked()
{
    int vest = ui->vestEdit->text().toInt();
    ++vest;
    ui->vestEdit->setText(QString::number(vest, 10));

    updateFunc();
}


void LineupRecommand::on_beltMinusButton_clicked()
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

    updateFunc();
}


void LineupRecommand::on_beltPlusButton_clicked()
{
    int belt = ui->beltEdit->text().toInt();
    ++belt;
    ui->beltEdit->setText(QString::number(belt, 10));

    updateFunc();
}


void LineupRecommand::on_cloakMinusButton_clicked()
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

    updateFunc();
}


void LineupRecommand::on_cloakPlusButton_clicked()
{
    int cloak = ui->cloakEdit->text().toInt();
    ++cloak;
    ui->cloakEdit->setText(QString::number(cloak, 10));

    updateFunc();
}
