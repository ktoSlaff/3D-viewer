#ifndef GLWIDGET_H
#define GLWIDGET_H

#define GL_SILENCE_DEPRECATION
#include <QApplication>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QWidget>
extern "C" {
#include "../s21_3DViewer.h"
}

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT
 public:
  GLWidget(QWidget* parent = nullptr);
  ~GLWidget();
  object_t *object;
    void init();
  void draw(char* filename);
  int reprint_model();
  double x_rotate, y_rotate;

 protected:
  void initializeGL();
  void resizeGL(int w, int h);
  void paintGL();
  QPoint mousePosition;
  void mousePressEvent(QMouseEvent*);
  void mouseMoveEvent(QMouseEvent*);
};

#endif  // GLWIDGET_H
