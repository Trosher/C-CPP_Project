#include "mywidget.h"

MyWidget::MyWidget(QWidget *parent) : QOpenGLWidget(parent) {}

void MyWidget::initializeGL() {
  glEnable(GL_DEPTH_TEST);
  obj.count_of_vertexes = 0;
  obj.count_of_facets = 0;
  obj.max_x = obj.max_y = obj.max_z = -4294967294;
  obj.min_x = obj.min_y = obj.min_z = 4294967295;
}

void MyWidget::resizeGL(int nWidth, int nHeight) {
  glViewport(0, 0, nWidth, nHeight);
  glClearDepth(1.0);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void MyWidget::draw_points() {
  glEnable(mods_point[mod_point]);
  glPointSize(point_size);
  glColor3f(r_point / 255.f, g_point / 255.f, b_point / 255.f);
  glBegin(GL_POINTS);
  for (unsigned long i = 0; i < vertices_c; i++) {
    glVertex3d((obj.matrix_print[i][0] + xMove) * Mash,
               (obj.matrix_print[i][1] + yMove) * Mash,
               (obj.matrix_print[i][2] + zMove) * Mash);
  }
  glEnd();
  glDisable(mods_point[mod_point]);
}

void MyWidget::draw_lines() {
  glEnable(mods_line[mods_check]);
  glLineWidth(line_size);
  glColor3f(r_line / 255.f, g_line / 255.f, b_line / 255.f);
  glLineStipple(2, 0X00FF);
  glBegin(GL_LINES);
  for (unsigned long i = 0; i < edges_c; i++) {
    glVertex3d((obj.matrix_print[obj.facets[i]][0] + xMove) * Mash,
               (obj.matrix_print[obj.facets[i]][1] + yMove) * Mash,
               (obj.matrix_print[obj.facets[i]][2] + zMove) * Mash);
    i++;
    glVertex3d((obj.matrix_print[obj.facets[i]][0] + xMove) * Mash,
               (obj.matrix_print[obj.facets[i]][1] + yMove) * Mash,
               (obj.matrix_print[obj.facets[i]][2] + zMove) * Mash);
  }
  glEnd();
  glDisable(mods_line[mods_check]);
}

void MyWidget::paintGL() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (!perspect) {
    glOrtho(-1.5, 1.5, -1.5, 1.5, -2, 1000);
  } else {
    glFrustum(-1.5, 1.5, -1.5, 1.5, 0.8, 1000);
    glTranslatef(0, 0, -2);
  }
  Roat_all();

  glMatrixMode(GL_MODELVIEW);
  glClearColor(r_pole / 255.f, g_pole / 255.f, b_pole / 255.f, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if (point_size) draw_points();
  if (line_size) draw_lines();

  update();
}

void MyWidget::Roat_all() {
  copy_state(&obj);
  rotation_by_oz(&obj, zRoat);
  rotation_by_oy(&obj, yRoat);
  rotation_by_ox(&obj, xRoat);
}

void MyWidget::obj_form() {
  obj.max_x = obj.max_y = obj.max_z = -4294967294;
  obj.min_x = obj.min_y = obj.min_z = 4294967295;
  char path_to_file_c[1000] = "";
  strlcpy(path_to_file_c, Path_to_file.toStdString().c_str(),
          Path_to_file.size() + 1);
  Malock_target = pars_control(path_to_file_c, &obj);
  if (!Malock_target) {
    normalization(&obj);
  }
  vertices_c = obj.count_of_vertexes;
  edges_c = obj.count_of_facets;
}
