#ifndef SECONDWIN_H
#define SECONDWIN_H
#include <QDialog>
#include"third.h"

namespace Ui {
class secondwin;
}

class secondwin : public QDialog
{
    Q_OBJECT

public:
    explicit secondwin(QWidget *parent = nullptr);
    ~secondwin();

private slots:

    void on_secondwin_accepted();

    void on_submit_clicked();

    void on_Reset_clicked();

private:
    Ui::secondwin *ui;
    third *resultwin;
};
#endif // SECONDWIN_H
