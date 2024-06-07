#include "secondwin.h"
#include "ui_secondwin.h"
#include<QMessageBox>
#include"kmap.h"
#include"SolveKmap.h"

secondwin::secondwin(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::secondwin)
{
    ui->setupUi(this);

   // QPixmap image(":/img/Img/secondwin.png");
   // int h = ui->label_pic->height();
   // int w = ui->label_pic->width();
   // ui->label_pic->setPixmap(image.scaled(w,h,Qt::KeepAspectRatio,Qt::SmoothTransformation));
}

secondwin::~secondwin()
{
    delete ui;
}
void secondwin::on_secondwin_accepted(){

}
void secondwin::on_submit_clicked()
{
    QString ones = ui->textones->toPlainText();
    QString dont = ui->textdont->toPlainText();
    if(ones.isEmpty()) {
        QMessageBox::warning(this, "Error", "Enter Valid Position");
    } else {
        if(dont.isEmpty()){
            dont = "-1";
        }
        std::string str = ones.toStdString();
        std::string str2 = dont.toStdString();
        mapp.getOnes(str);
        mapp.getDontCares(str2);
        std::vector<Implicant> ess_prime_implicant = solveKmap(mapp.size,mapp.ones,mapp.dontCares);
        mapp.set(get_sop(ess_prime_implicant));
        mapp.groups=get_groups(ess_prime_implicant);
        resultwin = new third(this);
        resultwin->show();
        hide();


    }
}


void secondwin::on_Reset_clicked()
{
    ui->textones->clear();
    ui->textdont->clear();
}

