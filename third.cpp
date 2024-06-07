#include "third.h"
#include "ui_third.h"
#include<QTableWidget>
#include<QTableWidgetItem>
#include<bitset>
#include<cmath>
#include<QStringList>
#include <sstream>

third::third(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::third)
{
    ui->setupUi(this);
    QString resultt = QString ::fromStdString(mapp.get());
    ui->Display->setText(resultt);
      TableWidgetDisplay();
    ui->label_ab->setText(QString ::fromStdString(mapp.ab));
    ui->label_cd->setText(QString ::fromStdString(mapp.bc));
    mapp.repeat();
    std::string str = mapp.results.str();
    ui->label_2->setText(QString::fromStdString(str));
}

third::~third()
{
    delete ui;
}

void third::on_quit_clicked()
{
}

void third::TableWidgetDisplay(){
    QTableWidget *table = new QTableWidget(this);
    table->setGeometry(440, 300, 400, 200);
    table->setColumnCount(pow(2,mapp.size/2));
    QFont font("Arial", 13);
    table->setFont(font);
    if(mapp.size % 2 == 0){
        table->setRowCount(pow(2,mapp.size/2));
    }
    else{
        table->setRowCount(pow(2,((mapp.size/2)+1)));
    }
    int graycodec[table->columnCount()];
    int graycoder[table->rowCount()];

    for(int i=0; i < table->columnCount();i++){
        int gray = i^(i>>1);
        graycodec[i] = gray;
    }
    for(int i=0; i < table->rowCount();i++){
        int gray = i^(i>>1);
        graycoder[i] = gray;
    }
    QTableWidgetItem *item;
    for(int i=0; i< table->rowCount();i++){
        for(int j=0; j< table->columnCount();j++){
            int check = graycoder[i] * table->columnCount() + graycodec[j];
            item = new QTableWidgetItem;
            item->setText("0");

            for(int num:mapp.ones){
                if(num == check){
                    item->setText("1");
                }
            }
            for(int num:mapp.dontCares){
                if(num==check){
                    item->setText("X");

                }
            }
            table->setItem(i,j,item);
        }
    }
    QStringList header1;
    QStringList header2;
    for(int i=0;i< table->columnCount();i++){
        QString head = QString::fromStdString( decimalToGray(i,mapp.size/2));
        header1 << head;
    }
    if(mapp.size %2 ==0){
    for(int i=0;i< table->rowCount();i++){
        QString head = QString::fromStdString( decimalToGray(i,mapp.size/2 ));
        header2 << head;
    }
    }
    else{
        for(int i=0;i< table->rowCount();i++){
            QString head = QString::fromStdString( decimalToGray(i,mapp.size/2 +1));
            header2 << head;
        }
    }
    table->setVerticalHeaderLabels(header2);
    table->setHorizontalHeaderLabels(header1);

    // this->setCentralWidget(table);
      int color = 0;
    for(int i=0;i<mapp.groups.size();++i){
        for(int numm:mapp.groups[i]){
            int rr = numm / (table->columnCount());
            int r = rr ^ (rr >> 1);
            int cc = numm - (rr * (table->columnCount()));
            int c = cc ^ (cc >> 1);
            QString val;
            val = "1";
            for(int num:mapp.dontCares){
            if(numm==num)
            {
                val = "X";
            }
            }
             QTableWidgetItem *backgroundItem = new QTableWidgetItem(val);
            if(color == 0){
                  backgroundItem->setBackground(Qt::red);
             }
            else if(color == 1){
                backgroundItem->setBackground(Qt::blue);
            }
            else if(color == 2){
                backgroundItem->setBackground(Qt::green);
            }
            else if(color == 3){
                backgroundItem->setBackground(Qt::yellow);
            }
            else if(color == 4){
                backgroundItem->setBackground(Qt::gray);
            }
            else if(color == 5){
                backgroundItem->setBackground(Qt::magenta);
            }
            table->setItem(r,c, backgroundItem);
        }
        color ++;
    }

}

std::string third::decimalToGray(int num, int numBits) {
    int gray = num ^ (num >> 1);
    std::string binaryGray = std::bitset<32>(gray).to_string();
    return binaryGray.substr(32 - numBits);
}


void third::on_Quit_clicked()
{
     QApplication::quit();
}

