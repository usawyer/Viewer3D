#ifndef AFFINE_TRANSFORMATION_H_
#define AFFINE_TRANSFORMATION_H_

#include "matrix_oop.h"

class TransformMatrix {
 public:
  TransformMatrix();

  void Translate(double x, double y, double z);
  void Scale(double x, double y, double z);
  void Rotate(double x, double y, double z);

  void DeleteMatrix() {
    TransformMatrix tmp;
    transform_matrix_ = tmp.transform_matrix_;
  }

  float* MatrixToMass() { return transform_matrix_.GetMass(); }
  Matrix GetTransform() { return transform_matrix_; }

 private:
  Matrix transform_matrix_;
};

#endif  // AFFINE_TRANSFORMATION_H_
