#ifndef MYWIDGET_H
#define MYWIDGET_H

#define GL_SILENCE_DEPRECATION
#include <QKeyEvent>
#include <QtOpenGLWidgets/QtOpenGLWidgets>
#include <vector>

extern "C" {
#include "C_file/Afina/afina.h"
#include "C_file/pars_obj/pars_obj.h"
#include "C_file/struct.h"
}

class MyWidget : public QOpenGLWidget {
  Q_OBJECT

 public:
  MyWidget(QWidget *parent = nullptr);
  unsigned long int vertices_c;
  unsigned long int edges_c;

  int perspect;

  double xRoat;
  double yRoat;
  double zRoat;
  double last_xRoat;
  double last_yRoat;
  double last_zRoat;

  double xMove;
  double yMove;
  double zMove;
  double last_xMove;
  double last_yMove;
  double last_zMove;

  double Mash;

  int Malock_target = 1;

  int mods_check;
  GLenum mods_line[2] = {GL_LINES, GL_LINE_STIPPLE};
  int mod_point;
  GLenum mods_point[2] = {GL_POINTS, GL_POINT_SMOOTH};
  int line_size;
  float r_line;
  float g_line;
  float b_line;

  int point_size;
  float r_point;
  float g_point;
  float b_point;

  float r_pole;
  float g_pole;
  float b_pole;

  data_t obj = init_struct();

  QString Path_to_file;
  void obj_form();
  void Roat_all();

 protected:
  void draw_points();
  void draw_lines();
  void initializeGL() override;
  void resizeGL(int nWidth, int nHeight) override;
  void paintGL() override;
};

#endif  // MYWIDGET_H
