#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <OpenGL.h>
#include <string.h>

#include <QFileDialog>
#include <QMainWindow>
#include <QSettings>

#include "ima/qgifimage_p.h"
#include "mywidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT
  QImage mp[50];
  int check;
  QTimer *timer_gif;

 public:
  QSettings *settings;
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  QGifImage gif;

 public slots:
  void on_X_os_valueChanged(int arg1);
  void on_Y_os_valueChanged(int arg1);
  void on_Z_os_valueChanged(int arg1);
  void on_X_mv_valueChanged(double arg1);
  void on_Y_mv_valueChanged(double arg1);
  void on_Z_mv_valueChanged(double arg1);
  void loadSettings();
  void saveSettings();

 private slots:
  void on_Edit_file_clicked();
  void on_Mash_valueChanged(double arg1);
  void on_size_v_valueChanged(int arg1);
  void on_size_e_valueChanged(int arg1);
  void on_frum_toggled(bool checked);
  void on_ortho_toggled(bool checked);
  void on_vertices_p_stateChanged(int arg1);
  void on_edges_p_stateChanged(int arg1);
  void on_vertices_red_valueChanged(int value);
  void on_vertices_green_valueChanged(int value);
  void on_vertices_blu_valueChanged(int value);
  void on_edges_red_valueChanged(int value);
  void on_edges_green_valueChanged(int value);
  void on_edges_blu_valueChanged(int value);
  void on_pole_red_valueChanged(int value);
  void on_pole_green_valueChanged(int value);
  void on_pole_blue_valueChanged(int value);
  void on_ed_s_toggled(bool checked);
  void on_ed_pu_toggled(bool checked);
  void on_ver_qa_toggled(bool checked);
  void on_ver_ci_toggled(bool checked);
  void on_pushButton_3_clicked();
  void timer_grab();
  void print_grab();
  void on_skrin_button_clicked();
  void on_pushButton_clicked();

 private:
  Ui::MainWindow *ui;
};
#endif  // MAINWINDOW_H
