#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include"QMessageBox"
#include<QPixelFormat>
#include"kmap.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
      ui->setupUi(this);
    this->setWindowTitle("K_MAP SOLVER");

    ui->select->addItem(QIcon(":/img/Img/choice-17-16.png"),"  SELECT");
   // ui->select->addItem(QIcon(":/img/Img/number-1_9180563.png"),"  ONE");
    ui->select->addItem(QIcon(":/img/Img/number-2_6422821.png"),"  TWO");
    ui->select->addItem(QIcon(":/img/Img/number-3.png"),"  THREE");
    ui->select->addItem(QIcon(":/img/Img/number-4.png"),"  FOUR");
    ui->select->addItem(QIcon(":/img/Img/number-5.png"),"  FIVE");
    ui->select->addItem(QIcon(":/img/Img/number-six-13222.png"),"  SIX");
    ui->select->addItem(QIcon(":/img/Img/Eo_circle_blue_number-7.svg.png"),"  SEVEN");
    ui->select->addItem(QIcon(":/img/Img/number-8.png"),"  EIGHT");
    ui->select->addItem(QIcon(":/img/Img/number-9.png"),"  NINE");
    ui->select->addItem(QIcon(":/img/Img/number-10.png"),"  TEN");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Submit_clicked()
{
    if(ui->select->currentText()== "  SELECT"){
        QMessageBox::warning(this,"Error","Select valid no. of variable");
    }
    else{
        //map = new KMap;
        //map->Kmap(4);
        hide();
        sec = new secondwin (this);
        sec->show();

        if(ui->select->currentText()== "  TEN"){
            mapp.Kmap(10);
            mapp.ab="ABCDE";
            mapp.bc="FGHIJ";
        }
        else if(ui->select->currentText()== "  TWO"){
            mapp.Kmap(2);
            mapp.ab="A";
            mapp.bc="B";
        }
        else if(ui->select->currentText()== "  THREE"){
            mapp.Kmap(3);
            mapp.ab="AB";
            mapp.bc="C";
        }
        else if(ui->select->currentText()== "  FOUR"){
           mapp.Kmap(4);
            mapp.ab="AB";
            mapp.bc="CD";
        }
        else if(ui->select->currentText()== "  FIVE"){
            mapp.Kmap(5);
            mapp.ab="ABC";
            mapp.bc="DE";
        }
        else if(ui->select->currentText()== "  SIX"){
           mapp.Kmap(6);
            mapp.ab="ABC";
            mapp.bc="DEF";
        }
        else if(ui->select->currentText()== "  SEVEN"){
          mapp.Kmap(7);
            mapp.ab="ABCD";
            mapp.bc="EFG";
        }
        else if(ui->select->currentText()== "  EIGHT"){
         mapp.Kmap(8);
            mapp.ab="ABCD";
            mapp.bc="EFGH";
        }
        else if(ui->select->currentText()== "  NINE"){
         mapp.Kmap(9);
            mapp.ab="ABCDE";
            mapp.bc="FGHI";
        }


    }
}


void MainWindow::on_exit_clicked()
{
    QApplication::quit();
}

