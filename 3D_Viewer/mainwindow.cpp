#include "mainwindow.h"

#include <chrono>
#include <iostream>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->openGLWidget->init();
  settings = new QSettings("3dviewer", "3D_Viewer", this);
  load_settings();
}

MainWindow::~MainWindow() {
    save_settings();
    delete ui;
}

void MainWindow::save_settings() {
  settings->setValue("background color_r", ui->openGLWidget->object->background_color[0]);
  settings->setValue("background color_g", ui->openGLWidget->object->background_color[1]);
  settings->setValue("background color_b", ui->openGLWidget->object->background_color[2]);
  settings->setValue("background color_a", ui->openGLWidget->object->background_color[3]);
  settings->setValue("vertex color_r", ui->openGLWidget->object->vertex_color[0]);
  settings->setValue("vertex color_g", ui->openGLWidget->object->vertex_color[1]);
  settings->setValue("vertex color_b", ui->openGLWidget->object->vertex_color[2]);
  settings->setValue("vertex color_a", ui->openGLWidget->object->vertex_color[3]);
  settings->setValue("line color_r", ui->openGLWidget->object->line_color[0]);
  settings->setValue("line color_g", ui->openGLWidget->object->line_color[1]);
  settings->setValue("line color_b", ui->openGLWidget->object->line_color[2]);
  settings->setValue("line color_a", ui->openGLWidget->object->line_color[3]);
  settings->setValue("vertex size", ui->openGLWidget->object->vertex_size);
  settings->setValue("line width", ui->openGLWidget->object->line_width);
  settings->setValue("vertex type", ui->openGLWidget->object->vertex_type);
  settings->setValue("line type", ui->openGLWidget->object->line_type);
  settings->setValue("projection type", ui->openGLWidget->object->projection);
}

void MainWindow::load_settings() {
    ui->openGLWidget->object->background_color[0] = settings->value("background color_r","1").toDouble();
    ui->openGLWidget->object->background_color[1] = settings->value("background color_g","1").toDouble();
    ui->openGLWidget->object->background_color[2] = settings->value("background color_b","1").toDouble();
    ui->openGLWidget->object->background_color[3] = settings->value("background color_a","1").toDouble();
    ui->openGLWidget->object->vertex_color[0] = settings->value("vertex color_r","0").toDouble();
    ui->openGLWidget->object->vertex_color[1] = settings->value("vertex color_g","0").toDouble();
    ui->openGLWidget->object->vertex_color[2] = settings->value("vertex color_b","0").toDouble();
    ui->openGLWidget->object->vertex_color[3] = settings->value("vertex color_a","1").toDouble();
    ui->openGLWidget->object->line_color[0] = settings->value("line color_r","0").toDouble();
    ui->openGLWidget->object->line_color[1] = settings->value("line color_g","0").toDouble();
    ui->openGLWidget->object->line_color[2] = settings->value("line color_b","0").toDouble();
    ui->openGLWidget->object->line_color[3] = settings->value("line color_a","1").toDouble();
    ui->openGLWidget->object->vertex_size = settings->value("vertex size","1").toDouble();
    ui->openGLWidget->object->line_width = settings->value("line width","1").toDouble();
    ui->openGLWidget->object->vertex_type = settings->value("vertex type","0").toDouble();
    ui->openGLWidget->object->line_type = settings->value("line type","0").toDouble();
    ui->openGLWidget->object->projection = settings->value("projection type","0").toDouble();
}

void MainWindow::on_pushButton_OpenFile_clicked() {
  ui->openGLWidget->x_rotate = 0.;
  ui->openGLWidget->y_rotate = 0.;
  ui->textEdit_info->clear();
  QString full_filename = QFileDialog::getOpenFileName(
      this, "Choose file...", QDir::homePath(), "*.obj");
  QString filename = full_filename.right(full_filename.length() -
                                         full_filename.lastIndexOf('/') - 1);
  QByteArray path_to_file = full_filename.toLocal8Bit().data();
  char* path_to_obj = path_to_file.data();
  ui->textEdit_info->insertPlainText(filename + "\n");
  ui->openGLWidget->draw(path_to_obj);
  int vertex_count = ui->openGLWidget->object->vertex_count;
  int facets_count = ui->openGLWidget->object->facets_count;
  if (vertex_count > 0 && facets_count > 0){
    ui->textEdit_info->insertPlainText(
        "Vertex: " + QString::number(vertex_count) + "\n" +
        "Facets: " + QString::number(facets_count) + "\n");
  } else
    ui->textEdit_info->insertPlainText("ERROR!");
  ui->openGLWidget->update();
}

void MainWindow::on_pushButton_reprint_clicked() {
  ui->openGLWidget->object->move[0] = ui->doubleSpinBox_xMove->value();
  ui->openGLWidget->object->move[1] = ui->doubleSpinBox_yMove->value();
  ui->openGLWidget->object->move[2] = ui->doubleSpinBox_zMove->value();

  ui->openGLWidget->object->angles[0] = ui->doubleSpinBox_xTurn->value();
  ui->openGLWidget->object->angles[1] = ui->doubleSpinBox_yTurn->value();
  ui->openGLWidget->object->angles[2] = ui->doubleSpinBox_zTurn->value();

  ui->openGLWidget->object->scale = ui->doubleSpinBox_scale->value();

  if (ui->openGLWidget->reprint_model())
    ui->textEdit_info->insertPlainText("ERROR_REPRINT!\n");
}

void MainWindow::on_pushButton_backgroundcolor_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "Choose color");
    ui->openGLWidget->object->background_color[0] = color.red()/255.;
    ui->openGLWidget->object->background_color[1] = color.green()/255.;
    ui->openGLWidget->object->background_color[2] = color.blue()/255.;
    ui->openGLWidget->object->background_color[3] = color.alpha()/255.;
    ui->openGLWidget->update();
}


void MainWindow::on_comboBox_projection_currentIndexChanged(int index)
{
        ui->openGLWidget->object->projection = index;
        ui->openGLWidget->update();
}


void MainWindow::on_pushButton_linecolor_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "Choose color");
    ui->openGLWidget->object->line_color[0] = color.red()/255.;
    ui->openGLWidget->object->line_color[1] = color.green()/255.;
    ui->openGLWidget->object->line_color[2] = color.blue()/255.;
    ui->openGLWidget->object->line_color[3] = color.alpha()/255.;
    ui->openGLWidget->update();
}


void MainWindow::on_doubleSpinBox_linesize_valueChanged(double arg1)
{
    ui->openGLWidget->object->line_width = arg1;
    ui->openGLWidget->update();
}


void MainWindow::on_comboBox_linetype_currentIndexChanged(int index)
{
    ui->openGLWidget->object->line_type = index;
    ui->openGLWidget->update();
}


void MainWindow::on_pushButton_vertexcolor_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "Choose color");
    ui->openGLWidget->object->vertex_color[0] = color.red()/255.;
    ui->openGLWidget->object->vertex_color[1] = color.green()/255.;
    ui->openGLWidget->object->vertex_color[2] = color.blue()/255.;
    ui->openGLWidget->object->vertex_color[3] = color.alpha()/255.;
    ui->openGLWidget->update();
}


void MainWindow::on_comboBox_vertextype_currentIndexChanged(int index)
{
    ui->openGLWidget->object->vertex_type = index;
    ui->openGLWidget->update();
}


void MainWindow::on_doubleSpinBox_vertexsize_valueChanged(double arg1)
{
    ui->openGLWidget->object->vertex_size = arg1;
    ui->openGLWidget->update();
}


void MainWindow::on_pushButton_saveFile_clicked()
{
    QString filename;
    if (ui->comboBox_filetype->currentIndex() == 0) {
      filename = QFileDialog::getSaveFileName(this, "Save as..", "name.bmp",
                                                "BMP (*.bmp)");

    } else if (ui->comboBox_filetype->currentIndex() == 1) {
      filename = QFileDialog::getSaveFileName(this, "Save as..", "name.jpeg",
                                                "JPEG (*.jpeg *.jpg)");
    } else if (ui->comboBox_filetype->currentIndex() == 2){

    }
    ui->openGLWidget->grabFramebuffer().save(filename, nullptr, 100);
}


void MainWindow::on_pushButton_defaultsettings_clicked()
{
    ui->openGLWidget->object->background_color[0] = 1;
    ui->openGLWidget->object->background_color[1] = 1;
    ui->openGLWidget->object->background_color[2] = 1;
    ui->openGLWidget->object->background_color[3] = 1;
    ui->openGLWidget->object->vertex_color[0] = 0;
    ui->openGLWidget->object->vertex_color[1] = 0;
    ui->openGLWidget->object->vertex_color[2] = 0;
    ui->openGLWidget->object->vertex_color[3] = 1;
    ui->openGLWidget->object->line_color[0] = 0;
    ui->openGLWidget->object->line_color[1] = 0;
    ui->openGLWidget->object->line_color[2] = 0;
    ui->openGLWidget->object->line_color[3] = 1;
    ui->openGLWidget->object->vertex_size = 1;
    ui->doubleSpinBox_vertexsize->setValue(ui->openGLWidget->object->vertex_size);
    ui->openGLWidget->object->line_width = 1;
    ui->doubleSpinBox_linesize->setValue(ui->openGLWidget->object->line_width);
    ui->openGLWidget->object->vertex_type = 0;
    ui->comboBox_vertextype->setCurrentIndex(ui->openGLWidget->object->vertex_type);
    ui->openGLWidget->object->line_type = 0;
    ui->comboBox_linetype->setCurrentIndex(ui->openGLWidget->object->line_type);
    ui->openGLWidget->object->projection = 0;
    ui->comboBox_projection->setCurrentIndex(ui->openGLWidget->object->projection);
    ui->openGLWidget->update();
}

