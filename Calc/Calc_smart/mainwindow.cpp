#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->Num_0,SIGNAL(clicked()),this,SLOT(digits_sim()));
    connect(ui->Num_1,SIGNAL(clicked()),this,SLOT(digits_sim()));
    connect(ui->Num_2,SIGNAL(clicked()),this,SLOT(digits_sim()));
    connect(ui->Num_3,SIGNAL(clicked()),this,SLOT(digits_sim()));
    connect(ui->Num_4,SIGNAL(clicked()),this,SLOT(digits_sim()));
    connect(ui->Num_5,SIGNAL(clicked()),this,SLOT(digits_sim()));
    connect(ui->Num_6,SIGNAL(clicked()),this,SLOT(digits_sim()));
    connect(ui->Num_7,SIGNAL(clicked()),this,SLOT(digits_sim()));
    connect(ui->Num_8,SIGNAL(clicked()),this,SLOT(digits_sim()));
    connect(ui->Num_9,SIGNAL(clicked()),this,SLOT(digits_sim()));
    connect(ui->Sum,SIGNAL(clicked()),this,SLOT(digits_sim()));
    connect(ui->Sub,SIGNAL(clicked()),this,SLOT(digits_sim()));
    connect(ui->Del,SIGNAL(clicked()),this,SLOT(digits_sim()));
    connect(ui->Mult,SIGNAL(clicked()),this,SLOT(digits_sim()));
    connect(ui->Step,SIGNAL(clicked()),this,SLOT(digits_sim()));
    connect(ui->Tochka,SIGNAL(clicked()),this,SLOT(digits_sim()));
    connect(ui->Mod,SIGNAL(clicked()),this,SLOT(digits_sim()));
    connect(ui->BL,SIGNAL(clicked()),this,SLOT(digits_sim()));
    connect(ui->BR,SIGNAL(clicked()),this,SLOT(digits_sim()));
    connect(ui->Cos,SIGNAL(clicked()),this,SLOT(digits_sim()));
    connect(ui->Sin,SIGNAL(clicked()),this,SLOT(digits_sim()));
    connect(ui->Tan,SIGNAL(clicked()),this,SLOT(digits_sim()));
    connect(ui->ACos,SIGNAL(clicked()),this,SLOT(digits_sim()));
    connect(ui->ASin,SIGNAL(clicked()),this,SLOT(digits_sim()));
    connect(ui->ATan,SIGNAL(clicked()),this,SLOT(digits_sim()));
    connect(ui->Sqrt,SIGNAL(clicked()),this,SLOT(digits_sim()));
    connect(ui->Ln,SIGNAL(clicked()),this,SLOT(digits_sim()));
    connect(ui->Log,SIGNAL(clicked()),this,SLOT(digits_sim()));
    connect(ui->X_num,SIGNAL(clicked()),this,SLOT(digits_sim()));
    connect(ui->res_buton,SIGNAL(clicked()),this,SLOT(res_CCK()));

    h = 0.05;
    xBegin = -10;
    xEnd = 10 + h;

    ui->widget->xAxis->setRange(-10, 10);

    X = xBegin;
    N = (xEnd - xBegin)/h + 2;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_0) {
        if (regim_check == 1 && (len_chek >= 0 && len_chek <= 255)) {
            len_chek++;
            if (clik_t != 0) clik_t++;
            ui->Fun_Win->setText(ui->Fun_Win->toPlainText() + "0");
        }
    } else if(e->key() == Qt::Key_1) {
        if (regim_check == 1 && (len_chek >= 0 && len_chek <= 255)) {
            len_chek++;
            if (clik_t != 0) clik_t++;
            ui->Fun_Win->setText(ui->Fun_Win->toPlainText() + "1");
        }
    } else if(e->key() == Qt::Key_2) {
        if (regim_check == 1 && (len_chek >= 0 && len_chek <= 255)) {
            len_chek++;
            if (clik_t != 0) clik_t++;
            ui->Fun_Win->setText(ui->Fun_Win->toPlainText() + "2");
        }
    } else if(e->key() == Qt::Key_3) {
        if (regim_check == 1 && (len_chek >= 0 && len_chek <= 255)) {
            len_chek++;
            if (clik_t != 0) clik_t++;
            ui->Fun_Win->setText(ui->Fun_Win->toPlainText() + "3");
        }
    } else if(e->key() == Qt::Key_4) {
        if (regim_check == 1 && (len_chek >= 0 && len_chek <= 255)) {
            len_chek++;
            if (clik_t != 0) clik_t++;
            ui->Fun_Win->setText(ui->Fun_Win->toPlainText() + "4");
        }
    } else if(e->key() == Qt::Key_5) {
        if (regim_check == 1 && (len_chek >= 0 && len_chek <= 255)) {
            len_chek++;
            if (clik_t != 0) clik_t++;
            ui->Fun_Win->setText(ui->Fun_Win->toPlainText() + "5");
        }
    } else if(e->key() == Qt::Key_6) {
        if (regim_check == 1 && (len_chek >= 0 && len_chek <= 255)) {
            len_chek++;
            if (clik_t != 0) clik_t++;
            ui->Fun_Win->setText(ui->Fun_Win->toPlainText() + "6");
        }
    } else if(e->key() == Qt::Key_7) {
        if (regim_check == 1 && (len_chek >= 0 && len_chek <= 255)) {
            len_chek++;
            if (clik_t != 0) clik_t++;
            ui->Fun_Win->setText(ui->Fun_Win->toPlainText() + "7");
        }
    } else if(e->key() == Qt::Key_8) {
        if (regim_check == 1 && (len_chek >= 0 && len_chek <= 255)) {
            len_chek++;
            if (clik_t != 0) clik_t++;
            ui->Fun_Win->setText(ui->Fun_Win->toPlainText() + "8");
        }
    } else if(e->key() == Qt::Key_9) {
        if (regim_check == 1 && (len_chek >= 0 && len_chek <= 255)) {
            len_chek++;
            if (clik_t != 0) clik_t++;
            ui->Fun_Win->setText(ui->Fun_Win->toPlainText() + "9");
        }
    } else if(e->key() == Qt::Key_Period) {
        if (regim_check == 1 && (len_chek >= 0 && len_chek <= 255)) {
            len_chek++;
            if (clik_t != 0) clik_t++;
            ui->Fun_Win->setText(ui->Fun_Win->toPlainText() + ".");
        }
    } else if(e->key() == Qt::Key_Plus) {
        if (regim_check == 1 && (len_chek >= 0 && len_chek <= 255)) {
            len_chek++;
            if (clik_t != 0) clik_t++;
            ui->Fun_Win->setText(ui->Fun_Win->toPlainText() + "+");
        }
    } else if(e->key() == Qt::Key_Minus) {
        if (regim_check == 1 && (len_chek >= 0 && len_chek <= 255)) {
            len_chek++;
            if (clik_t != 0) clik_t++;
            ui->Fun_Win->setText(ui->Fun_Win->toPlainText() + "-");
        }
    } else if(e->key() == Qt::Key_ParenLeft) {
        if (regim_check == 1 && (len_chek >= 0 && len_chek <= 255)) {
            len_chek++;
            if (clik_t != 0) clik_t++;
            ui->Fun_Win->setText(ui->Fun_Win->toPlainText() + "(");
        }
    } else if(e->key() == Qt::Key_ParenRight) {
        if (regim_check == 1 && (len_chek >= 0 && len_chek <= 255)) {
            len_chek++;
            if (clik_t != 0) clik_t++;
            ui->Fun_Win->setText(ui->Fun_Win->toPlainText() + ")");
        }
    } else if(e->key() == Qt::Key_Equal) {
        if (regim_check == 1 && (len_chek >= 0 && len_chek <= 255)) {
            len_chek++;
            if (clik_t != 0) clik_t++;
            on_Go_to_res_clicked();
        }
    } else if(e->key() == Qt::Key_Slash) {
        if (regim_check == 1 && (len_chek >= 0 && len_chek <= 255)) {
            len_chek++;
            if (clik_t != 0) clik_t++;
            ui->Fun_Win->setText(ui->Fun_Win->toPlainText() + "/");
        }
    }  else if(e->key() == Qt::Key_AsciiCircum) {
        if (regim_check == 1 && (len_chek >= 0 && len_chek <= 255)) {
            len_chek++;
            if (clik_t != 0) clik_t++;
            ui->Fun_Win->setText(ui->Fun_Win->toPlainText() + "^");
        }
    } else if(e->key() == Qt::Key_Asterisk) {
        if (regim_check == 1 && (len_chek >= 0 && len_chek <= 255)) {
            len_chek++;
            if (clik_t != 0) clik_t++;
            ui->Fun_Win->setText(ui->Fun_Win->toPlainText() + "*");
        }
    } else if(e->key() == Qt::Key_Backspace) {
        QString re_s;
        if (clik_t != 0) clik_t++;
        if (regim_check == 1) {
            if (len_chek > 0) { len_chek--;
                re_s = ui->Fun_Win->toPlainText();
                long long int len = re_s.size();
                re_s.resize(len - 1);
                ui->Fun_Win->setText(re_s);
            }
        }
    }
    if (clik_t == 2) {
        clik_t = 0;
        ui->Resul_show->setText("");
        ui->Fun_Win->setText("");
        ui->widget->clearGraphs();
        x.clear();
        y.clear();
        ui->widget->replot();
        ui->widget->setInteraction(QCP::iRangeZoom, false);
        ui->widget->setInteraction(QCP::iRangeDrag, false);
        len_chek = 0;
    }
}

void MainWindow::digits_sim()
{
    if (clik_t == 1) {
        len_chek = 0;
        clik_t = 0;
        ui->Resul_show->setText("");
        ui->Fun_Win->setText("");
        ui->widget->clearGraphs();
        x.clear();
        y.clear();
        ui->widget->replot();
        ui->widget->setInteraction(QCP::iRangeZoom, false);
        ui->widget->setInteraction(QCP::iRangeDrag, false);
    }
    if (len_chek >= 0 && len_chek <= 255) {
        QPushButton *button = (QPushButton*)sender();
        int len_px = button->text().length();
        len_chek += len_px;
        ui->Fun_Win->setText(ui->Fun_Win->toPlainText() + button->text());
    }
}

void MainWindow::on_Go_to_res_clicked()
{
    clik_t = 1;
    QString text = ui->Fun_Win->toPlainText();
    std::string text_str = text.toStdString();
    char const *mas = text_str.c_str();
    int error_target = prov(mas);
    if (error_target == 0) {
        long double res = pol(mas, &error_target, 0);
        if (error_target == 0) {
            QString strValue = QString::number(res, 'f', 7);
            ui->Resul_show->setText(strValue);
        }
    }

    if (error_target && error_target != -1) {
        if (error_target == 10) {
            QMessageBox::critical(this, "Error", "Неверно составленое выражение\n"
                                                 "Cod error: 10");
        } else if (error_target == 1) {
            QMessageBox::critical(this, "Error", "Неверно составленое выражение\n"
                                                 "Cod error: 1");
        } else if (error_target == 2) {
            QMessageBox::critical(this, "Error", "Неверно составленое выражение\n"
                                                 "Cod error: 2");
        } else if (error_target == 3) {
            QMessageBox::critical(this, "Error", "Неверно составленое выражение\n"
                                                 "Cod error: 3");
        } else if (error_target == 4) {
            QMessageBox::critical(this, "Error", "Неверно используемые скобки\n"
                                                 "Cod error: 4");
        } else if (error_target == 5) {
            QMessageBox::critical(this, "Error", "Неверно составленое выражение\n"
                                                 "Cod error: 5");
        } else if (error_target == 6) {
            QMessageBox::critical(this, "Error", "Неверно используемые скобки\n"
                                                 "Cod error: 6");
        } else if (error_target == 7) {
            QMessageBox::critical(this, "Error", "Неверно составленое выражение\n"
                                                 "Cod error: 7");
        } else if (error_target == 8) {
            QMessageBox::critical(this, "Error", "Неверно составленое выражение\n"
                                                 "Cod error: 8");
        } else if (error_target == 9) {
            QMessageBox::critical(this, "Error", "Невалидный символ\n"
                                                 "Cod error: 9");
        } else if (error_target == 11) {
            QMessageBox::critical(this, "Error", "Вычисление отрицательного корня\n"
                                                 "Cod error: 11");
        } else if (error_target == 12) {
            QMessageBox::critical(this, "Error", "Результат выислений inf или -inf\n"
                                                 "Cod error: 12");
        } else if (error_target == 13) {
            QMessageBox::critical(this, "Error", "Результат выислений nan\n"
                                                 "Cod error: 13");
        } else if (error_target == 14) {
            QMessageBox::critical(this, "Error", "Какя либо из строк пуста\n"
                                                 "Cod error: 14");
        }
        len_chek = 0;
        ui->widget->clearGraphs();
        x.clear();
        y.clear();
        ui->widget->replot();
        ui->Resul_show->setText("");
        error_target = 0;
    }

    if (error_target == -1) {
        long double res_max = 2.22507385850720138e-308, res_min = 1.79769313486231571e+308;
        for (X = xBegin; X <= xEnd; X+=h) {
            long double res = pol(mas, &error_target, X);
            if (res_min > res && error_target == -1) res_min = res;
            if (res_max < res && error_target == -1) res_max = res;
            if (error_target == -1 && res >= -1000000 && res <= 1000000) {
                y.push_back(res);
                x.push_back(X);
            } else {
                error_target = -1;
            }
        }
        ui->widget->yAxis->setRange(res_min, res_max);
        ui->widget->addGraph();
        ui->widget->graph(0)->addData(x,y);
        ui->widget->replot();
        ui->widget->setInteraction(QCP::iRangeZoom, true);
        ui->widget->setInteraction(QCP::iRangeDrag, true);
    }
}


void MainWindow::on_Desroi_clicked()
{
    len_chek = 0;
    ui->widget->clearGraphs();
    x.clear();
    y.clear();
    ui->widget->replot();
    ui->widget->setInteraction(QCP::iRangeZoom, false);
    ui->widget->setInteraction(QCP::iRangeDrag, false);
    ui->Resul_show->setText("");
    ui->Fun_Win->setText("");
}

void MainWindow::on_AN_clicked()
{
    radio_check = 1;
}


void MainWindow::on_DI_clicked()
{
    radio_check = 2;
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    if (index == 0) {
        ui->sum_v->setText("");
        ui->srock_v->setText("");
        ui->proc_v->setText("");
        ui->sum_v_2->setText("");
        ui->proc_v_3->setText("");

        ui->proc_k->setText("");
        ui->data_k->setText("");
        ui->sum_k->setText("");
        ui->res_mes->setText("");
        ui->res_proc->setText("");
        ui->res_d_p_p->setText("");
        regim_check = 1;
    }
    if (index == 1) {
        ui->sum_v->setText("");
        ui->srock_v->setText("");
        ui->proc_v->setText("");
        ui->sum_v_2->setText("");
        ui->proc_v_3->setText("");

        ui->widget->clearGraphs();
        x.clear();
        y.clear();
        ui->widget->replot();
        ui->widget->setInteraction(QCP::iRangeZoom, false);
        ui->widget->setInteraction(QCP::iRangeDrag, false);
        ui->Resul_show->setText("");
        ui->Fun_Win->setText("");
        regim_check = 2;
    }
    if (index == 2) {
        ui->proc_k->setText("");
        ui->data_k->setText("");
        ui->sum_k->setText("");
        ui->res_mes->setText("");
        ui->res_proc->setText("");
        ui->res_d_p_p->setText("");

        ui->widget->clearGraphs();
        x.clear();
        y.clear();
        ui->widget->replot();
        ui->widget->setInteraction(QCP::iRangeZoom, false);
        ui->widget->setInteraction(QCP::iRangeDrag, false);
        ui->Resul_show->setText("");
        ui->Fun_Win->setText("");
        regim_check = 3;
    }
}


void MainWindow::on_res_buton_clicked()
{
    int error_target = 0;
    QString text1 = ui->sum_k->toPlainText();
    std::string text_str1 = text1.toStdString();
    char const *sum_k = text_str1.c_str();

    QString text2 = ui->data_k->toPlainText();
    std::string text_str2 = text2.toStdString();
    char const *data_k = text_str2.c_str();

    QString text3 = ui->proc_k->toPlainText();
    std::string text_str3 = text3.toStdString();
    char const *proc_k = text_str3.c_str();

    ui->proc_k->setText("");
    ui->data_k->setText("");
    ui->sum_k->setText("");

    error_number(sum_k, &error_target);
    error_number(proc_k, &error_target);
    error_number_data(data_k, &error_target);
    if (error_target == 1) {
        QMessageBox::critical(this, "Error", "Введено невалидное число\n"
                                             "Cod error: 1");
    } else if (error_target == 2) {
        QMessageBox::critical(this, "Error", "Наличие невалидных символов\n"
                                             "Cod error: 2");
    } else if (error_target == 3) {
        QMessageBox::critical(this, "Error", "Невалидная дата\n"
                                             "Cod error: 3");
    } else if (error_target == 4) {
        QMessageBox::critical(this, "Error", "Какая либо из строк пуста\n"
                                             "Cod error: 4");
    } else {
        long double proc_k_num = atof(proc_k);
        long double data_k_num = atof(data_k);
        long double sum_k_num = atof(sum_k);
        if (radio_check == 1) {
            long double mes_plata = 0, proc = 0, p_sim_d = 0;
            res_CCKDA(data_k_num, sum_k_num, proc_k_num, &mes_plata, &proc, &p_sim_d);
            QString mes_plataValue = QString::number(mes_plata, 'f', 7);
            QString procValue = QString::number(proc, 'f', 7);
            QString p_sim_dValue = QString::number(p_sim_d, 'f', 7);
            ui->res_mes->setText(mes_plataValue);
            ui->res_proc->setText(procValue);
            ui->res_d_p_p->setText(p_sim_dValue);
        } else if (radio_check == 2) {
            long double mes_plata_max = 0, mes_plata_min = 0, proc = 0, p_sim_d = 0;
            res_CCKDD(data_k_num, sum_k_num, proc_k_num, &mes_plata_min, &mes_plata_max, &proc, &p_sim_d);
            QString mes_plata_minValue = QString::number(mes_plata_min, 'f', 7);
            QString mes_plata_maxValue = QString::number(mes_plata_max, 'f', 7);
            QString procValue = QString::number(proc, 'f', 7);
            QString p_sim_dValue = QString::number(p_sim_d, 'f', 7);
            ui->res_mes->setText(mes_plata_maxValue + " -> " + mes_plata_minValue);
            ui->res_proc->setText(procValue);
            ui->res_d_p_p->setText(p_sim_dValue);
        } else {
            QMessageBox::critical(this, "Error", "Выберите режим расчёта");
        }
    }
}


void MainWindow::on_res_v_clicked()
{

    int error_target = 0;
    QString text1 = ui->sum_v->toPlainText();
    std::string text_str1 = text1.toStdString();
    char const *sum_v = text_str1.c_str();

    QString text2 = ui->srock_v->toPlainText();
    std::string text_str2 = text2.toStdString();
    char const *data_v = text_str2.c_str();

    QString text3 = ui->proc_v->toPlainText();
    std::string text_str3 = text3.toStdString();
    char const *proc_v = text_str3.c_str();

    ui->sum_v->setText("");
    ui->srock_v->setText("");
    ui->proc_v->setText("");

    error_number(sum_v, &error_target);
    error_number(proc_v, &error_target);
    error_number_data(data_v, &error_target);
    if (error_target == 1) {
        QMessageBox::critical(this, "Error", "Введено невалидное число\n"
                                             "Cod error: 1");
    } else if (error_target == 2) {
        QMessageBox::critical(this, "Error", "Наличие невалидных символов\n"
                                             "Cod error: 2");
    } else if (error_target == 3) {
        QMessageBox::critical(this, "Error", "Невалидная дата\n"
                                             "Cod error: 3");
    } else if (error_target == 4) {
        QMessageBox::critical(this, "Error", "Какая либо из строк пуста\n"
                                             "Cod error: 4");
    } else {
        long double proc_k_num = atof(proc_v);
        long double data_k_num = atof(data_v);
        long double sum_k_num = atof(sum_v);
        long double sum_res = 0, proc = 0;
        res_CCD(data_k_num, sum_k_num, proc_k_num, &proc, &sum_res);
        QString procValue = QString::number(proc, 'f', 7);
        QString sumValue = QString::number(sum_res, 'f', 7);
        ui->sum_v_2->setText(sumValue);
        ui->proc_v_3->setText(procValue);
    }
}

