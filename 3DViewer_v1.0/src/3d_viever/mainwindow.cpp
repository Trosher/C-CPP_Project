#include "mainwindow.h"

#include <QMovie>
#include <iostream>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  loadSettings();

  ui->openGLWidget->edges_c = ui->Rebra->toPlainText().toInt();
  ui->openGLWidget->vertices_c = ui->Versh->toPlainText().toInt();

  ui->openGLWidget->mods_check = !ui->ed_s->isChecked();
}

MainWindow::~MainWindow() {
  saveSettings();
  if (!ui->openGLWidget->Malock_target) {
    free_struct(&ui->openGLWidget->obj);
  }
  delete ui;
}

void MainWindow::saveSettings() {
  QSettings settings("settings_3D", "Conf");

  settings.setValue("X_os", ui->X_os->value());
  settings.setValue("Y_os", ui->Y_os->value());
  settings.setValue("Z_os", ui->Z_os->value());

  settings.setValue("X_mv", ui->X_mv->value());
  settings.setValue("Y_mv", ui->Y_mv->value());
  settings.setValue("Z_mv", ui->Z_mv->value());

  settings.setValue("vertices_red", ui->vertices_red->value());
  settings.setValue("vertices_green", ui->vertices_green->value());
  settings.setValue("vertices_blu", ui->vertices_blu->value());

  settings.setValue("edges_red", ui->edges_red->value());
  settings.setValue("edges_green", ui->edges_green->value());
  settings.setValue("edges_blu", ui->edges_blu->value());

  settings.setValue("pole_red", ui->pole_red->value());
  settings.setValue("pole_green", ui->pole_green->value());
  settings.setValue("pole_blue", ui->pole_blue->value());

  settings.setValue("edges_format", ui->ed_s->isChecked());
  settings.setValue("vertices_format", ui->ver_qa->isChecked());

  settings.setValue("Mash", ui->Mash->value());

  settings.setValue("vertices_p", ui->vertices_p->checkState());
  settings.setValue("edges_p", ui->edges_p->checkState());

  settings.setValue("size_v", ui->size_v->value());
  settings.setValue("size_e", ui->size_e->value());

  settings.setValue("frum", ui->frum->isChecked());
}

void MainWindow::loadSettings() {
  QSettings settings("settings_3D", "Conf");

  ui->X_os->setValue(settings.value("X_os", 0).toInt());
  ui->openGLWidget->xRoat = ui->X_os->value();
  ui->Y_os->setValue(settings.value("Y_os", 0).toInt());
  ui->openGLWidget->yRoat = ui->Y_os->value();
  ui->Z_os->setValue(settings.value("Z_os", 0).toInt());
  ui->openGLWidget->zRoat = ui->Z_os->value();

  ui->X_mv->setValue(settings.value("X_mv", 0).toDouble());
  ui->openGLWidget->xMove = ui->X_mv->value();
  ui->Y_mv->setValue(settings.value("Y_mv", 0).toDouble());
  ui->openGLWidget->yMove = ui->Y_mv->value();
  ui->Z_mv->setValue(settings.value("Z_mv", 0).toDouble());
  ui->openGLWidget->zMove = ui->Z_mv->value();

  ui->vertices_red->setValue(settings.value("vertices_red", 0).toInt());
  ui->openGLWidget->r_point = ui->vertices_red->value();
  ui->vertices_green->setValue(settings.value("vertices_green", 0).toInt());
  ui->openGLWidget->g_point = ui->vertices_green->value();
  ui->vertices_blu->setValue(settings.value("vertices_blu", 0).toInt());
  ui->openGLWidget->b_point = ui->vertices_blu->value();

  ui->edges_red->setValue(settings.value("edges_red", 0).toInt());
  ui->openGLWidget->r_line = ui->edges_red->value();
  ui->edges_green->setValue(settings.value("edges_green", 0).toInt());
  ui->openGLWidget->g_line = ui->edges_green->value();
  ui->edges_blu->setValue(settings.value("edges_blu", 0).toInt());
  ui->openGLWidget->b_line = ui->edges_blu->value();

  ui->pole_red->setValue(settings.value("pole_red", 255).toInt());
  ui->openGLWidget->r_pole = ui->pole_red->value();
  ui->pole_green->setValue(settings.value("pole_green", 255).toInt());
  ui->openGLWidget->g_pole = ui->pole_green->value();
  ui->pole_blue->setValue(settings.value("pole_blue", 255).toInt());
  ui->openGLWidget->b_pole = ui->pole_blue->value();

  if (settings.value("edges_format", 1).toInt())
    ui->ed_s->setChecked(1);
  else
    ui->ed_pu->setChecked(1);
  ui->openGLWidget->mods_check = !ui->ed_s->isChecked();

  if (settings.value("vertices_format", 1).toInt())
    ui->ver_qa->setChecked(1);
  else
    ui->ver_ci->setChecked(1);
  ui->openGLWidget->mod_point = !ui->ver_qa->isChecked();

  ui->Mash->setValue(settings.value("Mash", 0).toDouble());
  ui->openGLWidget->Mash = ui->Mash->value();

  ui->vertices_p->setChecked(settings.value("vertices_p", 1).toInt());
  ui->size_v->setValue(settings.value("size_v", 1).toInt());
  if (ui->vertices_p->checkState()) {
    ui->openGLWidget->point_size = ui->size_v->value();
  } else {
    ui->openGLWidget->point_size = 0;
  }

  ui->edges_p->setChecked(settings.value("edges_p", 1).toInt());
  ui->size_e->setValue(settings.value("size_e", 1).toInt());
  if (ui->edges_p->checkState()) {
    ui->openGLWidget->line_size = ui->size_e->value();
  } else {
    ui->openGLWidget->line_size = 0;
  }

  if (settings.value("frum", 1).toInt())
    ui->frum->setChecked(1);
  else
    ui->ortho->setChecked(1);
  ui->openGLWidget->perspect = ui->frum->isChecked();
}

void MainWindow::on_X_os_valueChanged(int arg1) {
  ui->openGLWidget->xRoat = arg1;
}

void MainWindow::on_Y_os_valueChanged(int arg1) {
  ui->openGLWidget->yRoat = arg1;
}

void MainWindow::on_Z_os_valueChanged(int arg1) {
  ui->openGLWidget->zRoat = arg1;
}

void MainWindow::on_X_mv_valueChanged(double arg1) {
  ui->openGLWidget->xMove = arg1;
}

void MainWindow::on_Y_mv_valueChanged(double arg1) {
  ui->openGLWidget->yMove = arg1;
}

void MainWindow::on_Z_mv_valueChanged(double arg1) {
  ui->openGLWidget->zMove = arg1;
}

void MainWindow::on_Edit_file_clicked() {
  ui->openGLWidget->Path_to_file =
      QFileDialog::getOpenFileName(this, "Выбор файла", "/Users", "*.obj");
  ui->openGLWidget->obj_form();
  QString Str_file = ui->openGLWidget->Path_to_file;
  int last_index_slash = 0, index_point = 0, len_str = Str_file.length();
  for (int i = 0; i < len_str; i++) {
    if (Str_file[i] == '/') last_index_slash = i;
    if (Str_file[i] == '.') index_point = i;
  }
  last_index_slash++;
  if (len_str != 0) {
    ui->File_name->setText("");
    while (last_index_slash < index_point) {
      ui->File_name->setText(ui->File_name->toPlainText() +
                             Str_file[last_index_slash]);
      last_index_slash++;
    }
  }
  ui->Versh->setText(QString::number(ui->openGLWidget->vertices_c));
  ui->Rebra->setText(QString::number(ui->openGLWidget->edges_c / 2));
  ui->openGLWidget->repaint();
}

void MainWindow::on_Mash_valueChanged(double arg1) {
  ui->openGLWidget->Mash = arg1;
}

void MainWindow::on_size_v_valueChanged(int arg1) {
  ui->openGLWidget->point_size = ui->vertices_p->isChecked() ? arg1 : 0;
}

void MainWindow::on_size_e_valueChanged(int arg1) {
  ui->openGLWidget->line_size = ui->edges_p->isChecked() ? arg1 : 0;
}

void MainWindow::on_frum_toggled(bool checked) {
  ui->openGLWidget->perspect = checked;
}

void MainWindow::on_ortho_toggled(bool checked) {
  ui->openGLWidget->perspect = !checked;
}

void MainWindow::on_vertices_p_stateChanged(int arg1) {
  ui->openGLWidget->point_size = arg1 ? ui->size_v->value() : 0;
}

void MainWindow::on_edges_p_stateChanged(int arg1) {
  ui->openGLWidget->line_size = arg1 ? ui->size_e->value() : 0;
}

void MainWindow::on_vertices_red_valueChanged(int value) {
  ui->openGLWidget->r_point = (float)value;
}

void MainWindow::on_vertices_green_valueChanged(int value) {
  ui->openGLWidget->g_point = (float)value;
}

void MainWindow::on_vertices_blu_valueChanged(int value) {
  ui->openGLWidget->b_point = (float)value;
}

void MainWindow::on_edges_red_valueChanged(int value) {
  ui->openGLWidget->r_line = (float)value;
}

void MainWindow::on_edges_green_valueChanged(int value) {
  ui->openGLWidget->g_line = (float)value;
}

void MainWindow::on_edges_blu_valueChanged(int value) {
  ui->openGLWidget->b_line = (float)value;
}

void MainWindow::on_pole_red_valueChanged(int value) {
  ui->openGLWidget->r_pole = (float)value;
}

void MainWindow::on_pole_green_valueChanged(int value) {
  ui->openGLWidget->g_pole = (float)value;
}

void MainWindow::on_pole_blue_valueChanged(int value) {
  ui->openGLWidget->b_pole = (float)value;
}

void MainWindow::on_ed_s_toggled(bool checked) {
  ui->openGLWidget->mods_check = !checked;
}

void MainWindow::on_ed_pu_toggled(bool checked) {
  ui->openGLWidget->mods_check = checked;
}

void MainWindow::on_ver_qa_toggled(bool checked) {
  ui->openGLWidget->mod_point = !checked;
}

void MainWindow::on_ver_ci_toggled(bool checked) {
  ui->openGLWidget->mod_point = checked;
}

void MainWindow::on_pushButton_3_clicked() {
  check = 0;
  timer_gif = new QTimer();
  connect(timer_gif, SIGNAL(timeout()), this, SLOT(timer_grab()));
  timer_gif->start(100);
  ui->pushButton_3->setEnabled(0);
}

void MainWindow::timer_grab() {
  if (check > 49) {
    timer_gif->stop();
    disconnect(timer_gif);
    check = 0;
    for (int i = 0; i < 50; gif.addFrame(mp[i++], 200)) {
    }
    QString str =
        QFileDialog::getSaveFileName(0, "Сохранить файл как", "", "*.gif");
    gif.save(str);
    ui->pushButton_3->setText("Записать GIF");
    ui->pushButton_3->setEnabled(1);
  } else {
    mp[check] = ui->openGLWidget->grab().toImage();
    check += 1;
    ui->pushButton_3->setText(QString::number(check / 10));
  }
}

void MainWindow::print_grab() {
  if (check > 49) {
    timer_gif->stop();
    disconnect(timer_gif);
  } else {
    gif.addFrame(mp[check]);
    check += 1;
  }
}

void MainWindow::on_skrin_button_clicked() {
  QString str = QFileDialog::getSaveFileName(0, "Сохранить файл как", "",
                                             ui->img_format->currentText());
  if (!str.isEmpty()) {
    ui->openGLWidget->grab().save(str);
  }
}

void MainWindow::on_pushButton_clicked() {
  ui->X_os->setValue(0);
  ui->openGLWidget->xRoat = ui->X_os->value();
  ui->Y_os->setValue(0);
  ui->openGLWidget->yRoat = ui->Y_os->value();
  ui->Z_os->setValue(0);
  ui->openGLWidget->zRoat = ui->Z_os->value();

  ui->X_mv->setValue(0);
  ui->openGLWidget->xMove = ui->X_mv->value();
  ui->Y_mv->setValue(0);
  ui->openGLWidget->yMove = ui->Y_mv->value();
  ui->Z_mv->setValue(0);
  ui->openGLWidget->zMove = ui->Z_mv->value();

  ui->vertices_red->setValue(0);
  ui->openGLWidget->r_point = ui->vertices_red->value();
  ui->vertices_green->setValue(0);
  ui->openGLWidget->g_point = ui->vertices_green->value();
  ui->vertices_blu->setValue(0);
  ui->openGLWidget->b_point = ui->vertices_blu->value();

  ui->edges_red->setValue(0);
  ui->openGLWidget->r_line = ui->edges_red->value();
  ui->edges_green->setValue(0);
  ui->openGLWidget->g_line = ui->edges_green->value();
  ui->edges_blu->setValue(0);
  ui->openGLWidget->b_line = ui->edges_blu->value();

  ui->pole_red->setValue(255);
  ui->openGLWidget->r_pole = ui->pole_red->value();
  ui->pole_green->setValue(255);
  ui->openGLWidget->g_pole = ui->pole_green->value();
  ui->pole_blue->setValue(255);
  ui->openGLWidget->b_pole = ui->pole_blue->value();

  ui->ed_s->setChecked(1);
  ui->openGLWidget->mods_check = !ui->ed_s->isChecked();

  ui->ver_qa->setChecked(1);
  ui->openGLWidget->mod_point = !ui->ver_qa->isChecked();

  ui->Mash->setValue(1);
  ui->openGLWidget->Mash = ui->Mash->value();

  ui->vertices_p->setChecked(1);
  ui->size_v->setValue(1);

  ui->edges_p->setChecked(1);
  ui->size_e->setValue(1);
  ui->openGLWidget->line_size = ui->size_e->value();

  ui->frum->setChecked(1);
  ui->openGLWidget->perspect = ui->frum->isChecked();
}
