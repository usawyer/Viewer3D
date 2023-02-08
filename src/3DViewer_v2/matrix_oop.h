#ifndef SRC_MATRIX_OOP_H_
#define SRC_MATRIX_OOP_H_

#include <cmath>
#include <iostream>

#define E 1e-6

class Matrix {
 private:
  int _rows, _cols;
  double** _matrix;

 private:
  void create_matrix();
  void inicialization();
  int eq_loop(const Matrix& other);
  Matrix reduced_matrix(int row, int column);

 public:
  Matrix();
  Matrix(int rows, int cols);
  Matrix(int rows, int cols,
         std::initializer_list<std::initializer_list<double>> list);
  Matrix(const Matrix& other);
  Matrix(Matrix&& other);
  ~Matrix();

  void set_rows(int n_rows);
  void set_cols(int n_cols);

  int get_rows();
  int get_cols();
  const int get_rows() const;
  const int get_cols() const;
  bool empty() { return _matrix ? 1 : 0; }
  void delete_matrix();

  bool eq_matrix(const Matrix& other);
  void sum_matrix(const Matrix& other);
  void sub_matrix(const Matrix& other);
  void mul_number(const double num);
  void mul_matrix(const Matrix& other);
  Matrix transpose();
  Matrix calc_complements();
  double determinant();
  Matrix inverse_matrix();

  Matrix operator+(const Matrix& other);
  Matrix operator-(const Matrix& other);
  Matrix operator*(const Matrix& other);
  Matrix operator*(const double num);

  bool operator==(const Matrix& other);
  Matrix& operator=(const Matrix& other);
  void operator+=(const Matrix& other);
  void operator-=(const Matrix& other);
  void operator*=(const Matrix& other);
  void operator*=(const double num);
  double& operator()(int rows, int cols);

  float* GetMass();
};

#endif  // SRC_MATRIX_OOP_H_
