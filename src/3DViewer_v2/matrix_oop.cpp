#include "matrix_oop.h"

// Basic constructor
Matrix::Matrix() {
  _rows = 0;
  _cols = 0;
  _matrix = NULL;
}

// Parametrized constructor
Matrix::Matrix(int rows, int cols) : _rows(rows), _cols(cols) {
  if (_rows < 1 || _cols < 1)
    throw std::out_of_range("Incorrect matrix size value");
  create_matrix();
}

// Copy constructor
Matrix::Matrix(const Matrix& other) : _rows(other._rows), _cols(other._cols) {
  create_matrix();

  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < _cols; j++) {
      _matrix[i][j] = other._matrix[i][j];
    }
  }
}

// Move constructor
Matrix::Matrix(Matrix&& other)
    : _rows(other._rows), _cols(other._cols), _matrix(other._matrix) {
  other._cols = other._rows = 0;
  other._matrix = nullptr;
}

Matrix::Matrix(int rows, int cols,
               std::initializer_list<std::initializer_list<double>> list)
    : Matrix(rows, cols) {
  int i = 0, j = 0;
  for (const auto& r : list) {
    for (const auto& c : r) {
      _matrix[i][j] = c;
      ++j;
    }
    j = 0;
    ++i;
  }
}

// Destructor
Matrix::~Matrix() {
  if (_matrix) {
    delete_matrix();
  }
  _rows = 0;
  _cols = 0;
}

// Accessor
int Matrix::get_rows() { return _rows; }
const int Matrix::get_rows() const { return _rows; }

int Matrix::get_cols() { return _cols; }
const int Matrix::get_cols() const { return _cols; }

// Mutator
void Matrix::set_rows(int n_rows) {
  if (n_rows < 1) throw std::out_of_range("Incorrect matrix size value");

  if (n_rows != _rows) {
    delete_matrix();
    _rows = n_rows;
    create_matrix();
  }
}

void Matrix::set_cols(int n_cols) {
  if (n_cols < 1) throw std::out_of_range("Incorrect matrix size value");

  if (n_cols != _cols) {
    delete_matrix();
    _cols = n_cols;
    create_matrix();
  }
}

void Matrix::create_matrix() {
  _matrix = new double*[_rows];
  for (int i = 0; i < _rows; i++) {
    _matrix[i] = new double[_cols];
  }
  inicialization();
}

void Matrix::inicialization() {
  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < _cols; j++) {
      _matrix[i][j] = 0.0;
    }
  }
}

void Matrix::delete_matrix() {
  for (int i = 0; i < _rows; i++) {
    delete[] _matrix[i];
  }
  delete[] _matrix;
}

// Matrix operations
bool Matrix::eq_matrix(const Matrix& other) {
  bool result = true;
  if (_cols != other._cols || _rows != other._rows) {
    result = false;
  } else {
    if (eq_loop(other) != _cols * _rows) {
      result = false;
    }
  }
  return result;
}

int Matrix::eq_loop(const Matrix& other) {
  int match = 0;
  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < _cols; j++) {
      if (fabs(_matrix[i][j] - other._matrix[i][j]) < E) {
        match++;
      }
    }
  }
  return match;
}

void Matrix::sum_matrix(const Matrix& other) {
  if (_cols != other._cols || _rows != other._rows)
    throw std::out_of_range("Different matrix dimensions!");
  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < _cols; j++) {
      _matrix[i][j] += other._matrix[i][j];
    }
  }
}

void Matrix::sub_matrix(const Matrix& other) {
  if (_cols != other._cols || _rows != other._rows)
    throw std::out_of_range("Different matrix dimensions!");
  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < _cols; j++) {
      _matrix[i][j] -= other._matrix[i][j];
    }
  }
}

void Matrix::mul_number(const double num) {
  if (std::isnan(num) || std::isinf(num))
    throw std::out_of_range("Invalid number!");
  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < _cols; j++) {
      _matrix[i][j] *= num;
    }
  }
}

void Matrix::mul_matrix(const Matrix& other) {
  if (_cols != other._rows)
    throw std::out_of_range("Incorrect matrices for multiplication!");
  Matrix result(_rows, other._cols);
  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < other._cols; j++) {
      for (int k = 0; k < other._rows; k++) {
        result._matrix[i][j] += _matrix[i][k] * other._matrix[k][j];
      }
    }
  }
  *this = result;
}

Matrix Matrix::transpose() {
  Matrix result(_cols, _rows);
  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < _cols; j++) {
      result._matrix[j][i] = _matrix[i][j];
    }
  }
  return result;
}

Matrix Matrix::calc_complements() {
  if (_cols != _rows) throw std::out_of_range("The matrix is not square!");
  if (_cols < 1) throw std::out_of_range("Incorrect matrix size!");
  Matrix result(_rows, _cols);
  if (_rows == 1) {
    result._matrix[0][0] = 1.0;
  } else {
    for (int i = 0; i < _rows; i++) {
      for (int j = 0; j < _cols; j++) {
        Matrix matrix_temp = reduced_matrix(i, j);
        result._matrix[i][j] = pow(-1, i + j) * matrix_temp.determinant();
      }
    }
  }
  return result;
}

double Matrix::determinant() {
  double det = 0.0;
  int sign = 1;
  if (_rows != _cols) {
    det = NAN;
  } else if (_rows == 1) {
    det = _matrix[0][0];
  } else if (_rows == 2) {
    det = _matrix[0][0] * _matrix[1][1] - _matrix[1][0] * _matrix[0][1];
  } else {
    for (int k = 0; k < _cols; k++) {
      Matrix matrix_temp = reduced_matrix(0, k);
      det += sign * _matrix[0][k] * matrix_temp.determinant();
      sign = -sign;
    }
  }
  return det;
}

Matrix Matrix::reduced_matrix(int row, int column) {
  Matrix result(_cols - 1, _rows - 1);
  int m = 0;
  for (int i = 0; i < _rows; i++) {
    if (i == row) continue;
    int n = 0;
    for (int j = 0; j < _cols; j++) {
      if (j == column) continue;
      result._matrix[m][n] = _matrix[i][j];
      n++;
    }
    m++;
  }
  return result;
}

Matrix Matrix::inverse_matrix() {
  double det = determinant();
  if (std::isnan(det)) throw std::out_of_range("The matrix is not square!");
  if (fabs(det) < E) throw std::out_of_range("Matrix determinant is 0!");

  Matrix calc_result = calc_complements();
  Matrix transpose_result = calc_result.transpose();
  transpose_result.mul_number(1.0 / det);

  return transpose_result;
}

// Operator overloading
Matrix Matrix::operator+(const Matrix& other) {
  Matrix result = *this;
  result.sum_matrix(other);
  return result;
}

Matrix Matrix::operator-(const Matrix& other) {
  Matrix result = *this;
  result.sub_matrix(other);
  return result;
}

Matrix Matrix::operator*(const Matrix& other) {
  Matrix result = *this;
  result.mul_matrix(other);
  return result;
}

Matrix Matrix::operator*(const double num) {
  Matrix result = *this;
  result.mul_number(num);
  return result;
}

bool Matrix::operator==(const Matrix& other) { return eq_matrix(other); }

Matrix& Matrix::operator=(const Matrix& other) {
  delete_matrix();
  _rows = other._rows;
  _cols = other._cols;
  create_matrix();

  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < _cols; j++) {
      _matrix[i][j] = other._matrix[i][j];
    }
  }
  return *this;
}

void Matrix::operator+=(const Matrix& other) { return sum_matrix(other); }
void Matrix::operator-=(const Matrix& other) { return sub_matrix(other); }
void Matrix::operator*=(const Matrix& other) { return mul_matrix(other); }
void Matrix::operator*=(const double num) { return mul_number(num); }

double& Matrix::operator()(int rows, int cols) {
  if (_rows <= rows || _cols <= cols || rows < 0 || cols < 0) {
    throw std::out_of_range("Incorrect matrix indices!");
  }
  return _matrix[rows][cols];
}

float* Matrix::GetMass() {
  float* mass = new float[_rows * _cols]();
  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < _cols; j++) {
      mass[i * _rows + j] = _matrix[j][i];
    }
  }
  return mass;
}
