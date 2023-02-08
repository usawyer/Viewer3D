#ifndef SRC_PROJECT_MAINWIDGET_H_
#define SRC_PROJECT_MAINWIDGET_H_

#include <QColor>
#include <QMatrix4x4>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLWidget>

#include "controller.h"
#include "qgifimage.h"
#include "settings_data.h"

class MainWidget : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT

 public:
  using QOpenGLWidget::QOpenGLWidget;
  ~MainWidget();
  void paintGL() override;
  void resizeGL(int w, int h) override;
  void SetController(Controller *contr) { conroller_wg_ = contr; }

 protected:
  void initializeGL() override;
  void initShaders();

 private:
  QOpenGLShaderProgram program_;
  QMatrix4x4 projection_, view_;
  Controller *conroller_wg_;

  void DrawPoints();
  void DrawLines();
};

#endif  // SRC_PROJECT_MAINWIDGET_H_
