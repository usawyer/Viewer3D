#include "affine_transformation.h"

TransformMatrix::TransformMatrix() {
  if (!transform_matrix_.empty()) transform_matrix_.delete_matrix();
  transform_matrix_ = Matrix(4, 4,
                             {{1.0, 0.0, 0.0, 0.0},
                              {0.0, 1.0, 0.0, 0.0},
                              {0.0, 0.0, 1.0, 0.0},
                              {0.0, 0.0, 0.0, 1.0}});
}

void TransformMatrix::Translate(double x, double y, double z) {
  Matrix result(4, 4,
                {{1.0, 0.0, 0.0, x},
                 {0.0, 1.0, 0.0, y},
                 {0.0, 0.0, 1.0, z},
                 {0.0, 0.0, 0.0, 1.0}});
  transform_matrix_.mul_matrix(result);
}

void TransformMatrix::Scale(double x, double y, double z) {
  Matrix result(4, 4,
                {{x, 0.0, 0.0, 0.0},
                 {0.0, y, 0.0, 0.0},
                 {0.0, 0.0, z, 0.0},
                 {0.0, 0.0, 0.0, 1.0}});
  transform_matrix_.mul_matrix(result);
}

void TransformMatrix::Rotate(double x, double y, double z) {
  x *= M_PI / 180;
  y *= M_PI / 180;
  z *= M_PI / 180;

  Matrix result(
      4, 4,
      {{cos(y) * cos(z), -cos(y) * sin(z), -sin(y), 0.0},
       {-sin(x) * sin(y) * cos(z) + cos(x) * sin(z),
        sin(x) * sin(y) * sin(z) + cos(x) * cos(z), -sin(x) * cos(y), 0.0},
       {cos(x) * sin(y) * cos(z) + sin(x) * sin(z),
        -cos(x) * sin(y) * sin(z) + sin(x) * cos(z), cos(x) * cos(y), 0.0},
       {0.0, 0.0, 0.0, 1.0}});
  transform_matrix_.mul_matrix(result);
}
