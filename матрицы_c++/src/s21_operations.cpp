#include "s21_matrix_oop.h"
using namespace std;

// геттеры
int S21Matrix::GetRows() const { return rows_; }

int S21Matrix::GetCols() const { return cols_; }

// сеттеры
void S21Matrix::SetRows(int rows) {
  if (rows <= 0) {
    throw std::invalid_argument("Rows must be positive");
  }

  // Если размер не меняется, ничего не делаем
  if (rows_ == rows) return;

  // создание новой матрицы
  double** new_matrix = new double*[rows];
  if (new_matrix == nullptr) {
    throw bad_alloc();
  }
  for (int i = 0; i < rows; i++) {
    new_matrix[i] = new double[cols_];
    if (new_matrix[i] == nullptr) {
      throw bad_alloc();
    }
    // заполнение нулями
    for (int j = 0; j < cols_; j++) {
      new_matrix[i][j] = 0.0;
    }

    // Копируем существующие данные
    if (i < rows_) {
      for (int j = 0; j < cols_; j++) {
        new_matrix[i][j] = matrix_[i][j];
      }
    }
  }

  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
    matrix_[i] = nullptr;
  }
  delete[] matrix_;
  matrix_ = nullptr;

  matrix_ = new_matrix;
  rows_ = rows;
}

void S21Matrix::SetCols(int cols) {
  if (cols <= 0) {
    throw invalid_argument("Cols must be positive");
  }

  // Если размер не меняется, ничего не делаем
  if (cols_ == cols) return;

  double** new_matrix = new double*[rows_];
  if (new_matrix == nullptr) {
    throw bad_alloc();
  }
  for (int i = 0; i < rows_; i++) {
    new_matrix[i] = new double[cols];
    if (new_matrix[i] == nullptr) {
      throw bad_alloc();
    }
    // заполнение нулями
    for (int j = 0; j < cols; j++) {
      new_matrix[i][j] = 0.0;
    }
    // копирование существующих данных
    for (int j = 0; j < (cols < cols_ ? cols : cols_); j++) {
      new_matrix[i][j] = matrix_[i][j];
    }
  }

  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
    matrix_[i] = nullptr;
  }
  delete[] matrix_;
  matrix_ = nullptr;

  matrix_ = new_matrix;
  cols_ = cols;
}

bool S21Matrix::EqMatrix(const S21Matrix& other) {
  if (!check_matrix() || !other.check_matrix()) {
    throw invalid_argument("Matrix is not valid");
  }

  bool result = true;

  if (rows_ != other.rows_ || cols_ != other.cols_) {
    result = false;
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (fabs(matrix_[i][j] - other.matrix_[i][j]) >= 1e-7) {
        result = false;
      }
    }
  }

  return result;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (!check_matrix() || !other.check_matrix()) {
    throw invalid_argument("Matrix is not valid");
  }

  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw invalid_argument("Matrix dimensions must match");
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (!check_matrix() || !other.check_matrix()) {
    throw invalid_argument("Matrix is not valid");
  }

  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw invalid_argument("Matrix dimensions must match");
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  if (!check_matrix()) {
    throw invalid_argument("Matrix is not valid");
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (!check_matrix() || !other.check_matrix()) {
    throw invalid_argument("Matrix is not valid");
  }

  if (cols_ != other.rows_) {
    throw invalid_argument("Matrix dimensions must match");
  }

  S21Matrix result(rows_, other.cols_);

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      result.matrix_[i][j] = 0;
      for (int k = 0; k < cols_; k++) {
        double temp = matrix_[i][k] * other.matrix_[k][j];
        result.matrix_[i][j] += temp;
      }
    }
  }

  *this = result;
}

S21Matrix S21Matrix::Transpose() {
  if (!check_matrix()) {
    throw invalid_argument("Matrix is not valid");
  }

  S21Matrix result(cols_, rows_);

  for (int i = 0; i < cols_; i++) {
    for (int j = 0; j < rows_; j++) {
      result.matrix_[i][j] = matrix_[j][i];
    }
  }

  return result;
}

S21Matrix S21Matrix::minor(int k, int z) {
  if (!check_matrix()) {
    throw invalid_argument("Matrix is not valid");
  }

  if (rows_ - 1 <= 0 || cols_ - 1 <= 0) {
    throw invalid_argument("Matrix dimensions must be positive");
  }
  S21Matrix result(rows_ - 1, cols_ - 1);
  int y = 0;
  for (int i = 0; i < rows_; i++) {
    if (i != k) {
      int x = 0;
      for (int j = 0; j < cols_; j++) {
        if (j != z) {
          result.matrix_[y][x] = matrix_[i][j];
          x++;
        }
      }
      y++;
    }
  }

  return result;
}

double S21Matrix::Determinant() {
  if (!check_matrix()) {
    throw invalid_argument("Matrix is not valid");
  }

  if (rows_ != cols_) {
    throw invalid_argument("Matrix must be square");
  }

  double det = 0;

  if (rows_ == 1) {
    det = matrix_[0][0];
  } else if (rows_ == 2) {
    det = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  } else {
    // вычисление определителя через разложение по первой строке
    for (int i = 0; i < cols_; i++) {
      S21Matrix minor_matrix = minor(0, i);
      double minor_det = minor_matrix.Determinant();
      det += matrix_[0][i] * minor_det * pow(-1, i);
    }
  }

  return det;
}

S21Matrix S21Matrix::CalcComplements() {
  if (!check_matrix()) {
    throw invalid_argument("Matrix is not valid");
  }

  if (rows_ != cols_) {
    throw invalid_argument("Matrix must be square");
  }

  S21Matrix result(rows_, cols_);

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      S21Matrix temp = minor(i, j);
      double temp_det = temp.Determinant();
      result.matrix_[i][j] = pow(-1, i + j) * temp_det;
    }
  }

  return result;
}

S21Matrix S21Matrix::InverseMatrix() {
  if (!check_matrix()) {
    throw invalid_argument("Matrix is not valid");
  }

  double det = Determinant();
  if (det == 0) {
    throw invalid_argument("Matrix is singular");
  }

  S21Matrix temp = CalcComplements();
  S21Matrix result(rows_, cols_);
  result = temp.Transpose();
  result.MulNumber(1 / det);

  return result;
}

bool S21Matrix::check_matrix() const {
  bool result = true;
  if (rows_ <= 0 || cols_ <= 0) {
    result = false;
  }

  if (matrix_ == nullptr) {
    result = false;
  }

  for (int i = 0; i < rows_; i++) {
    if (matrix_[i] == nullptr) {
      result = false;
    }
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (isnan(matrix_[i][j]) || isinf(matrix_[i][j])) {
        result = false;
      }
    }
  }

  return result;
}