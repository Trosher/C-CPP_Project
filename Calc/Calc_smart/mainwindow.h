#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QVector>
#include <QKeyEvent>
#include "qcustomplot.h"
extern "C"
{
#include "../c_file/smartcalc.h"
}

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    int clik_t = 0;
    Ui::MainWindow *ui;
    long double xBegin, xEnd, h, X;
    int N;
    int radio_check = 0;
    int regim_check = 0;
    int len_chek = 0;

    QVector<double> x,y;

protected:
    void keyPressEvent(QKeyEvent *e) override;

private slots:
    void digits_sim();
    void on_Go_to_res_clicked();
    void on_Desroi_clicked();
    void on_AN_clicked();
    void on_DI_clicked();
    void on_tabWidget_currentChanged(int index);
    void on_res_buton_clicked();
    void on_res_v_clicked();
};

#endif // MAINWINDOW_H
