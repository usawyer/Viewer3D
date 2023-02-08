#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "model.h"


class Controller {
 public:
  const int GetNumberOfFacets();
  const int GetNumberOfVertexes();

  std::vector<double> &GetArrVertexes();
  std::vector<int> &GetArrFacets();

  void ParsingFile(const std::string &file_path);
  explicit Controller(Model *m) : model_(m) {}
  ~Controller() {
    if (model_) {
      delete model_;
    }
  }
  Controller() = default;

  void DeleteCMatrix() { return model_->DeleteMMatrix(); }
  float *MatrixCToMass() { return model_->MatrixMToMass(); }
  std::vector<double> &GetDrawVector() { return model_->GetDrawVector(); }

  void Translate(double x, double y, double z);
  void Scale(double x, double y, double z);
  void Rotate(double x, double y, double z);

 private:
  Model *model_ = nullptr;
};


#endif  // CONTROLLER_H_
