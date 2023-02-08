#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(Controller *controller, QWidget *parent)
    : QMainWindow(parent), controller_(controller), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  InstallSettings();
  ui->openGLWidget->SetController(controller_);
  screenshots_count_ = 0;
  timer_ = new QTimer(this);
  gif_ = new QGifImage;
  connect(timer_, SIGNAL(timeout()), this, SLOT(MakeGif()));
}

MainWindow::~MainWindow() {
  delete ui;
  RecordInFile();
}

void MainWindow::InstallSettings() {
  QString path = HOME_DIR "/Desktop/3DViewer_v2/setting.txt";
  QFile file(path);
  if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    QTextStream in(&file);
    QColor color;
    QString line = in.readLine();
    unsigned int value = line.toUInt();
    color.setRgba(value);
    SettingsData::GetInstance()->SetBgdColor(color);
    line = in.readLine();
    value = line.toUInt();
    color.setRgba(value);
    SettingsData::GetInstance()->SetLinesColor(color);
    line = in.readLine();
    value = line.toDouble();
    SettingsData::GetInstance()->SetTypeLines(value);
    ui->comboBox_type_of_edges->setCurrentIndex(value);
    ui->comboBox_type_of_edges->update();
    line = in.readLine();
    value = line.toDouble();
    SettingsData::GetInstance()->SetTypeVert(value);
    ui->comboBox_type_of_vertices->setCurrentIndex(value);
    ui->comboBox_type_of_vertices->update();
    line = in.readLine();
    value = line.toDouble();
    SettingsData::GetInstance()->SetFlagProect(value);
    ui->comboBox_projection->setCurrentIndex(value);
    ui->comboBox_projection->update();
    line = in.readLine();
    value = line.toDouble();
    SettingsData::GetInstance()->SetSizeVert(value);
    ui->comboBox_vertice_size->setCurrentIndex(value);
    ui->comboBox_vertice_size->update();
    line = in.readLine();
    value = line.toDouble();
    SettingsData::GetInstance()->SetThicknessLines(value);
    ui->comboBox_edges_thickness->setCurrentIndex(value);
    ui->comboBox_edges_thickness->update();
    line = in.readLine();
    value = line.toUInt();
    color.setRgba(value);
    SettingsData::GetInstance()->SetVertColor(color);
    file.close();
    ui->openGLWidget->update();
  } else {
    SettingsData::GetInstance()->DefaultAllSetting();
    QFile mFile(path);
  }
}

void MainWindow::RecordInFile() {
  QString path = HOME_DIR "/Desktop/3DViewer_v2/setting.txt";
  QFile file(path);
  if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
    QTextStream out(&file);
    QString background_color =
        QString::number(SettingsData::GetInstance()->GetBgdColor().rgba());
    QString line_color = QString::number(
        SettingsData::GetInstance()->GetLinesColor().rgba());
    QString vert_color = QString::number(
        SettingsData::GetInstance()->GetVertColor().rgba());
    QString type_lines =
        QString::number(SettingsData::GetInstance()->GetTypeLines());
    QString type_vert =
        QString::number(SettingsData::GetInstance()->GetTypeVert());
    QString type_proect =
        QString::number(SettingsData::GetInstance()->GetFlagProect());
    QString size_vert =
        QString::number(SettingsData::GetInstance()->GetSizeVertIndex());
    QString thickness_of_lines = QString::number(
        SettingsData::GetInstance()->GetThicknessLinesIndex());
    out << background_color << "\n"
        << line_color << "\n"
        << type_lines << "\n"
        << type_vert << "\n"
        << type_proect << "\n"
        << size_vert << "\n"
        << thickness_of_lines << "\n"
        << vert_color;
    file.close();
  }
}

void MainWindow::ResetButtons() {
  ui->translate_spinBox_x->setValue(0);
  ui->translate_spinBox_y->setValue(0);
  ui->translate_spinBox_z->setValue(0);

  ui->rotate_spinBox_x->setValue(0);
  ui->rotate_spinBox_y->setValue(0);
  ui->rotate_spinBox_z->setValue(0);

  ui->scale_spinBox_x->setValue(1);
  ui->scale_spinBox_y->setValue(1);
  ui->scale_spinBox_z->setValue(1);

  ui->comboBox_projection->setCurrentText("central");
  ui->comboBox_type_of_edges->setCurrentText("solid");
  ui->comboBox_edges_thickness->setCurrentText("1.0");
  ui->comboBox_vertice_size->setCurrentText("1.0");
  ui->comboBox_type_of_vertices->setCurrentText("non");
}

void MainWindow::on_open_file_clicked() {
  QString str = QFileDialog::getOpenFileName(
      this, "Open a file...", QDir::homePath(), "OBJ-file (*.obj)");
  if (!str.isEmpty()) {
    QFileInfo path(str);
    QString name = path.fileName();
    controller_->ParsingFile(str.toStdString());
    ui->openGLWidget->SetController(controller_);
    ui->file_name->setText(name);
    ui->num_of_vert->setText(
        QString::number(controller_->GetNumberOfVertexes()));
    ui->num_of_edges->setText(
        QString::number(controller_->GetNumberOfFacets()));
  }
}

void MainWindow::on_translate_down_x_clicked() {
  if (ui->translate_spinBox_x->value() > -1000.0) {
    ui->translate_spinBox_x->setValue(ui->translate_spinBox_x->value() - 0.1);
    Multiply();
  }
}

void MainWindow::on_translate_up_x_clicked() {
  if (ui->translate_spinBox_x->value() < 1000.0) {
    ui->translate_spinBox_x->setValue(ui->translate_spinBox_x->value() + 0.1);
    Multiply();
  }
}

void MainWindow::on_translate_spinBox_x_editingFinished() { Multiply(); }

void MainWindow::on_translate_down_y_clicked() {
  if (ui->translate_spinBox_y->value() > -1000.0) {
    ui->translate_spinBox_y->setValue(ui->translate_spinBox_y->value() - 0.1);
    Multiply();
  }
}

void MainWindow::on_translate_up_y_clicked() {
  if (ui->translate_spinBox_y->value() < 1000.0) {
    ui->translate_spinBox_y->setValue(ui->translate_spinBox_y->value() + 0.1);
    Multiply();
  }
}

void MainWindow::on_translate_spinBox_y_editingFinished() { Multiply(); }

void MainWindow::on_translate_down_z_clicked() {
  if (ui->translate_spinBox_z->value() > -1000.0) {
    ui->translate_spinBox_z->setValue(ui->translate_spinBox_z->value() - 0.1);
    Multiply();
  }
}

void MainWindow::on_translate_up_z_clicked() {
  if (ui->translate_spinBox_z->value() < 1000.0) {
    ui->translate_spinBox_z->setValue(ui->translate_spinBox_z->value() + 0.1);
    Multiply();
  }
}

void MainWindow::on_translate_spinBox_z_editingFinished() { Multiply(); }

void MainWindow::on_rotate_down_x_clicked() {
  if (ui->rotate_spinBox_x->value() > -360) {
    ui->rotate_spinBox_x->setValue(ui->rotate_spinBox_x->value() - 1.0);
    Multiply();
  }
}

void MainWindow::on_rotate_up_x_clicked() {
  if (ui->rotate_spinBox_x->value() < 360) {
    ui->rotate_spinBox_x->setValue(ui->rotate_spinBox_x->value() + 1.0);
    Multiply();
  }
}

void MainWindow::on_rotate_spinBox_x_editingFinished() { Multiply(); }

void MainWindow::on_rotate_down_y_clicked() {
  if (ui->rotate_spinBox_y->value() > -360) {
    ui->rotate_spinBox_y->setValue(ui->rotate_spinBox_y->value() - 1.0);
    Multiply();
  }
}

void MainWindow::on_rotate_up_y_clicked() {
  if (ui->rotate_spinBox_y->value() < 360) {
    ui->rotate_spinBox_y->setValue(ui->rotate_spinBox_y->value() + 1.0);
    Multiply();
  }
}

void MainWindow::on_rotate_spinBox_y_editingFinished() { Multiply(); }

void MainWindow::on_rotate_down_z_clicked() {
  if (ui->rotate_spinBox_z->value() > -360) {
    ui->rotate_spinBox_z->setValue(ui->rotate_spinBox_z->value() - 1.0);
    Multiply();
  }
}

void MainWindow::on_rotate_up_z_clicked() {
  if (ui->rotate_spinBox_z->value() < 360) {
    ui->rotate_spinBox_z->setValue(ui->rotate_spinBox_z->value() + 1.0);
    Multiply();
  }
}

void MainWindow::on_rotate_spinBox_z_editingFinished() { Multiply(); }

void MainWindow::on_scale_down_x_clicked() {
  if (ui->scale_spinBox_x->value() > 0.01) {
    ui->scale_spinBox_x->setValue(ui->scale_spinBox_x->value() - 0.01);
    Multiply();
  }
}

void MainWindow::on_scale_up_x_clicked() {
  if (ui->scale_spinBox_x->value() < 10.0) {
    ui->scale_spinBox_x->setValue(ui->scale_spinBox_x->value() + 0.01);
    Multiply();
  }
}

void MainWindow::on_scale_spinBox_x_editingFinished() { Multiply(); }

void MainWindow::on_scale_down_y_clicked() {
  if (ui->scale_spinBox_y->value() > 0.01) {
    ui->scale_spinBox_y->setValue(ui->scale_spinBox_y->value() - 0.01);
    Multiply();
  }
}

void MainWindow::on_scale_up_y_clicked() {
  if (ui->scale_spinBox_y->value() < 10.0) {
    ui->scale_spinBox_y->setValue(ui->scale_spinBox_y->value() + 0.01);
    Multiply();
  }
}

void MainWindow::on_scale_spinBox_y_editingFinished() { Multiply(); }

void MainWindow::on_scale_down_z_clicked() {
  if (ui->scale_spinBox_z->value() > 0.01) {
    ui->scale_spinBox_z->setValue(ui->scale_spinBox_z->value() - 0.01);
    Multiply();
  }
}

void MainWindow::on_scale_up_z_clicked() {
  if (ui->scale_spinBox_z->value() < 10.0) {
    ui->scale_spinBox_z->setValue(ui->scale_spinBox_z->value() + 0.01);
    Multiply();
  }
}

void MainWindow::on_scale_spinBox_z_editingFinished() { Multiply(); }

void MainWindow::on_printscreen_button_pressed() {
  QImage screen = this->ui->openGLWidget->grabFramebuffer();
  QString file_path =
      QFileDialog::getSaveFileName(this, "Save image as...", QDir::homePath(),
                                   "BMP-file (*.bmp);;JPEG-file (*.jpeg)");
  if (!file_path.isEmpty() || !file_path.isNull()) screen.save(file_path);
}

void MainWindow::on_gif_button_pressed() { timer_->start(100); }

void MainWindow::MakeGif() {
  if (screenshots_count_ < 50) {
    QImage screen = this->ui->openGLWidget->grabFramebuffer();
    gif_->addFrame(screen, -1);
    screenshots_count_++;
  }
  if (screenshots_count_ == 50) {
    timer_->stop();
    screenshots_count_ = 0;
    QString file_path = QFileDialog::getSaveFileName(
        this, "Save gif as...", QDir::homePath(), "GIF-file (*.gif)");
    if (!file_path.isEmpty() || !file_path.isNull()) gif_->save(file_path);
    delete gif_;
    gif_ = new QGifImage;
  }
}

void MainWindow::on_comboBox_type_of_edges_activated(int index) {
  SettingsData::GetInstance()->SetTypeLines(index);
  ui->openGLWidget->update();
}

void MainWindow::on_comboBox_type_of_vertices_activated(int index) {
  SettingsData::GetInstance()->SetTypeVert(index);
  ui->openGLWidget->update();
}

void MainWindow::on_pushButton_color_of_background_clicked() {
  QColor color = QColorDialog::getColor();
  if (color.isValid()) {
    SettingsData::GetInstance()->SetBgdColor(color);
    ui->openGLWidget->update();
  }
}

void MainWindow::on_pushButton_color_of_edges_clicked() {
  QColor lines_color = QColorDialog::getColor();
  if (lines_color.isValid()) {
    SettingsData::GetInstance()->SetLinesColor(lines_color);
    ui->openGLWidget->update();
  }
}

void MainWindow::on_pushButton_color_of_vertices_clicked() {
  QColor vert_color = QColorDialog::getColor();
  if (vert_color.isValid()) {
    SettingsData::GetInstance()->SetVertColor(vert_color);
    ui->openGLWidget->update();
  }
}

void MainWindow::on_comboBox_projection_activated(int index) {
  SettingsData::GetInstance()->SetFlagProect(index);
  ui->openGLWidget->resizeGL(950, 780);
  ui->openGLWidget->update();
}

void MainWindow::on_comboBox_vertice_size_activated(int index) {
  SettingsData::GetInstance()->SetSizeVert(index);
  ui->openGLWidget->update();
}

void MainWindow::on_comboBox_edges_thickness_activated(int index) {
  SettingsData::GetInstance()->SetThicknessLines(index);
  ui->openGLWidget->update();
}

void MainWindow::on_pushButton_default_clicked() {
  controller_->DeleteCMatrix();
  ResetButtons();
  SettingsData::GetInstance()->DefaultAllSetting();
  RecordInFile();
  InstallSettings();
  ui->openGLWidget->resizeGL(950, 780);
  ui->openGLWidget->update();
}

void MainWindow::Multiply() {
  controller_->DeleteCMatrix();
  controller_->Translate(ui->translate_spinBox_x->value(),
                         ui->translate_spinBox_y->value(),
                         ui->translate_spinBox_z->value());
  controller_->Rotate(ui->rotate_spinBox_x->value(),
                      ui->rotate_spinBox_y->value(),
                      ui->rotate_spinBox_z->value());
  controller_->Scale(ui->scale_spinBox_x->value(), ui->scale_spinBox_y->value(),
                     ui->scale_spinBox_z->value());
  ui->openGLWidget->update();
}
