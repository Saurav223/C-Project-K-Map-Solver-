#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include"secondwin.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_Submit_clicked();

    void on_exit_clicked();

private:
    Ui::MainWindow *ui;
    secondwin *sec;
  //  KMap * map;
};
#endif // MAINWINDOW_H
