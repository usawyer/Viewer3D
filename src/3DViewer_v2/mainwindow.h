#ifndef SRC_PROJECT_MAINWINDOW_H_
#define SRC_PROJECT_MAINWINDOW_H_

#include <QColorDialog>
#include <QFile>
#include <QFileDialog>
#include <QMainWindow>
#include <QTimer>

#include "mainwidget.h"

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(Controller *controller, QWidget *parent = nullptr);
  ~MainWindow();

  Controller *controller_ = nullptr;

 public slots:
  void MakeGif();

 private slots:
  void on_open_file_clicked();
  void RecordInFile();
  void ResetButtons();
  void Multiply();

  void InstallSettings();
  void on_translate_down_x_clicked();
  void on_translate_up_x_clicked();
  void on_translate_spinBox_x_editingFinished();
  void on_translate_down_y_clicked();
  void on_translate_up_y_clicked();
  void on_translate_spinBox_y_editingFinished();
  void on_translate_down_z_clicked();
  void on_translate_up_z_clicked();
  void on_translate_spinBox_z_editingFinished();

  void on_rotate_down_x_clicked();
  void on_rotate_up_x_clicked();
  void on_rotate_spinBox_x_editingFinished();
  void on_rotate_down_y_clicked();
  void on_rotate_up_y_clicked();
  void on_rotate_spinBox_y_editingFinished();
  void on_rotate_down_z_clicked();
  void on_rotate_up_z_clicked();
  void on_rotate_spinBox_z_editingFinished();

  void on_scale_down_x_clicked();
  void on_scale_up_x_clicked();
  void on_scale_spinBox_x_editingFinished();
  void on_scale_down_y_clicked();
  void on_scale_up_y_clicked();
  void on_scale_spinBox_y_editingFinished();
  void on_scale_down_z_clicked();
  void on_scale_up_z_clicked();
  void on_scale_spinBox_z_editingFinished();

  void on_printscreen_button_pressed();
  void on_gif_button_pressed();

  void on_comboBox_type_of_edges_activated(int index);
  void on_comboBox_type_of_vertices_activated(int index);
  void on_pushButton_color_of_background_clicked();
  void on_comboBox_projection_activated(int index);
  void on_pushButton_color_of_edges_clicked();
  void on_comboBox_vertice_size_activated(int index);
  void on_comboBox_edges_thickness_activated(int index);
  void on_pushButton_color_of_vertices_clicked();

  void on_pushButton_default_clicked();

 private:
  Ui::MainWindow *ui;
  QTimer *timer_;
  int screenshots_count_;
  QGifImage *gif_;
};


#endif  // SRC_PROJECT_MAINWINDOW_H_
