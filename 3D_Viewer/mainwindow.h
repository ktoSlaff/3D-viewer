#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileDialog>
#include <QMainWindow>
#include <QColor>
#include <QColorDialog>
#include <QSettings>

//extern "C" {
//#include "../s21_3DViewer.h"
//}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  void save_settings();
  void load_settings();

 private slots:
  void on_pushButton_OpenFile_clicked();

  void on_pushButton_reprint_clicked();

  void on_pushButton_backgroundcolor_clicked();

  void on_comboBox_projection_currentIndexChanged(int index);

  void on_pushButton_linecolor_clicked();

  void on_doubleSpinBox_linesize_valueChanged(double arg1);

  void on_comboBox_linetype_currentIndexChanged(int index);

  void on_pushButton_vertexcolor_clicked();

  void on_comboBox_vertextype_currentIndexChanged(int index);

  void on_doubleSpinBox_vertexsize_valueChanged(double arg1);

  void on_pushButton_saveFile_clicked();

  void on_pushButton_defaultsettings_clicked();

private:
  Ui::MainWindow *ui;
  QSettings *settings;
};
#endif  // MAINWINDOW_H
