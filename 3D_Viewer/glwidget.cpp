#include "glwidget.h"

#include <iostream>

GLWidget::GLWidget(QWidget* parent) : QOpenGLWidget(parent) {}

GLWidget::~GLWidget() {

}

void GLWidget::init(){
    object = (object_t*)calloc(1, sizeof(object_t));
    init_object(object);
}

void GLWidget::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
}

void GLWidget::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);
  update();
}

void GLWidget::paintGL() {
    glClearColor(object->background_color[0], object->background_color[1], object->background_color[2], object->background_color[3]);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glRotated(x_rotate, 1, 0, 0);
    glRotated(y_rotate, 0, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (object->projection){
       glFrustum(-1, 1, -1, 1, 0.1, 1);
    } else {
       glOrtho(-1, 1, -1, 1, -1, 1);
    }

    glVertexPointer(3, GL_DOUBLE, 0, object->vertex);
    glEnableClientState(GL_VERTEX_ARRAY);

    // point draw
    glPointSize(object->vertex_size);
    glColor4d(object->vertex_color[0], object->vertex_color[1], object->vertex_color[2], object->vertex_color[3]);
    if (object->vertex_type != 0){
        if (object->vertex_type == 1) {
           glEnable(GL_POINT_SMOOTH);
         } else {
            glDisable(GL_POINT_SMOOTH);
        }
        glDrawArrays(GL_POINTS, 0, object->vertex_count);
    }

    // line draw
    glLineWidth(object->line_width);
    glColor4d(object->line_color[0], object->line_color[1], object->line_color[2], object->line_color[3]);
    if (object->line_type == 1) {
       glEnable(GL_LINE_STIPPLE);
       glLineStipple(1, 0x00ff);
     } else {
        glDisable(GL_LINE_STIPPLE);
    }
    glDrawElements(GL_LINES, object->facets_qty, GL_UNSIGNED_INT, object->facets);
    glDisableClientState(GL_VERTEX_ARRAY);

}

void GLWidget::draw(char* filename) {
  if (!parsing_file(object, filename)) {
    normalization(object);
    update();
  }
}

int GLWidget::reprint_model() {
  int out = 0;
  if (fabs(object->angles[0]) > S21_EPS || fabs(object->angles[1]) > S21_EPS ||
      fabs(object->angles[2]) > S21_EPS) {
    out = turn_matrix(object);
  }
  if (fabs(object->move[0]) > S21_EPS || fabs(object->move[1]) > S21_EPS ||
      fabs(object->move[2]) > S21_EPS) {
    out = move_matrix(object);
  }
  if (object->scale > S21_EPS) {
    out = scale_matrix(object);
  }
  update();
  return out;
}

void GLWidget::mousePressEvent(QMouseEvent* mo) { mousePosition = mo->pos(); }

void GLWidget::mouseMoveEvent(QMouseEvent* mo) {
  x_rotate = 1 / M_PI * (mo->pos().y() - mousePosition.y());
  y_rotate = 1 / M_PI * (mo->pos().x() - mousePosition.x());
  update();
}
