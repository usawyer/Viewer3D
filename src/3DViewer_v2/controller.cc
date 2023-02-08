#include "controller.h"

const int Controller::GetNumberOfFacets() {
  return model_->GetNumberOfFacets();
}

const int Controller::GetNumberOfVertexes() {
  return model_->GetNumberOfVertexes();
}

std::vector<double> &Controller::GetArrVertexes() {
  return model_->GetArrVertexes();
}

std::vector<int> &Controller::GetArrFacets() {
  return model_->GetArrFacets();
}

void Controller::ParsingFile(const std::string &file_path) {
  model_->ParsingFile(file_path);
}

void Controller::Translate(double x, double y, double z) {
  model_->MTranslate(x, y, z);
}

void Controller::Scale(double x, double y, double z) {
  model_->MScale(x, y, z);
}

void Controller::Rotate(double x, double y, double z) {
  model_->MRotate(x, y, z);
}
