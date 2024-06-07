#ifndef THIRD_H
#define THIRD_H

#include <QDialog>
#include "SolveKmap.h"
#include "kmap.h"

namespace Ui {
class third;
}

class third : public QDialog
{
    Q_OBJECT

public:
    explicit third(QWidget *parent = nullptr);
    ~third();
    std::string decimalToGray(int,int);

private slots:
    void on_quit_clicked();

    void on_Quit_clicked();

private:
    Ui::third *ui;
    void TableWidgetDisplay();
};

#endif // THIRD_H
