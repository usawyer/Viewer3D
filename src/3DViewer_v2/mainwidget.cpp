#include "mainwidget.h"

MainWidget::~MainWidget() {
  makeCurrent();
  doneCurrent();
}

void MainWidget::initializeGL() {
  initializeOpenGLFunctions();
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  initShaders();
}

void MainWidget::initShaders() {
  if (!program_.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                        ":/vshader.glsl"))
    close();

  if (!program_.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                        ":/fshader.glsl"))
    close();

  if (!program_.link()) close();
  if (!program_.bind()) close();
}

void MainWidget::resizeGL(int w, int h) {
  qreal aspect = qreal(w) / qreal(h ? h : 1);
  const qreal zNear = 0.1, zFar = 10000.0;
  projection_.setToIdentity();
  if (!SettingsData::GetInstance()->GetFlagProect()) {
    projection_.perspective(45.0, width() / height(), zNear, zFar);
  } else {
    projection_.ortho(-aspect, aspect, -1.0, 1.0, zNear, zFar);
  }
}

void MainWidget::paintGL() {
  glClearColor(SettingsData::GetInstance()->GetBgdColor().redF(),
               SettingsData::GetInstance()->GetBgdColor().greenF(),
               SettingsData::GetInstance()->GetBgdColor().blueF(),
               SettingsData::GetInstance()->GetBgdColor().alphaF());
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  int vertexLocation = program_.attributeLocation("a_position");
  glVertexAttribPointer(vertexLocation, 3, GL_DOUBLE, GL_FALSE, 0,
                        conroller_wg_->GetDrawVector().data());
  glEnableVertexAttribArray(vertexLocation);

  view_.setToIdentity();
  view_.lookAt(QVector3D(0.0, 0.0, 10.0), QVector3D(0.0, 0.0, 0.0),
               QVector3D(0.0, 1.0, 0.0));

  float *mass = conroller_wg_->MatrixCToMass();
  program_.setUniformValue("mvp_matrix",
                           projection_ * view_ * QMatrix4x4(mass, 4, 4));
  if (mass) delete mass;

  DrawPoints();
  DrawLines();

  glDisableVertexAttribArray(vertexLocation);
}

void MainWidget::DrawPoints() {
  if (SettingsData::GetInstance()->GetTypeVert()) {
    if (SettingsData::GetInstance()->GetTypeVert() == 1) {
      glEnable(GL_POINT_SMOOTH);
    }

    glPointSize(SettingsData::GetInstance()->GetSizeVert());
    QColor color = SettingsData::GetInstance()->GetVertColor();
    program_.setUniformValue("colorl", color);
    glDrawArrays(GL_POINTS, 0, conroller_wg_->GetDrawVector().size() / 3);
    glDisable(GL_POINT_SMOOTH);
  }
}

void MainWidget::DrawLines() {
  QColor color = SettingsData::GetInstance()->GetLinesColor();
  program_.setUniformValue("colorl", color);
  glLineWidth(SettingsData::GetInstance()->GetThicknessLines());
  if (SettingsData::GetInstance()->GetTypeLines() == 1) {
    glLineStipple(5, 0x00FF);
    glEnable(GL_LINE_STIPPLE);
  }
  glDrawArrays(GL_LINES, 0, conroller_wg_->GetDrawVector().size() / 3);
  glDisable(GL_LINE_STIPPLE);
}
