#include <QApplication>
#include <QLabel>
#include <QSurfaceFormat>

#include "mainwindow.h"

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);
  IModelFactory* model_factory = new ModelFactory();
  Controller controller(model_factory->CreateModel());
  MainWindow w(&controller);
  w.show();
  return app.exec();
}
