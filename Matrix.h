//
// Created by erelon on 1/20/20.
//

#ifndef SORTING_SERVER__MATRIX_H_
#define SORTING_SERVER__MATRIX_H_
#include <vector>
#include <string>

class Point {
  int x, y;
 public:
  Point() {
    x = 0;
    y = 0;
  }
  Point(int x, int y) {
    this->x = x;
    this->y = y;
  }
  int getX() { return x; }
  int getY() { return y; }
  bool operator==(Point obj) {
    if (this->x == obj.x && this->y == obj.y)
      return true;
    else return false;
  }
  friend std::string to_string(Point const &self) {
    std::string out = "";
    out += std::to_string(self.x);
    out += std::to_string(self.y);
    return out;
  }
};

//T must have a cost with getCost() func
template<class T>
class Matrix {
 private:
  T **Mat;
  int numOfColms;
  int numOfRows;
 public:
  Matrix<T>(int rows, int colms, std::vector<T> data);
  Matrix<T>() { this->Mat = NULL; }
  ~Matrix<T>();
  int getnumOfRows() { return numOfRows; }
  int getnumOfCols() { return numOfColms; }
  double costOf(Point p) { return this->Mat[p.getX()][p.getY()]; }
  std::string to_String();
  friend std::string to_string(Matrix &self) {
    return self.to_String();
  }
};

template<class T>
Matrix<T>::Matrix(int rows, int colms, std::vector<T> data) {
  this->numOfRows = rows;
  this->numOfColms = colms;
  Mat = new T *[numOfRows];

  for (int i = 0; i < numOfRows; i++) {
    Mat[i] = new T[numOfColms];
  }

  auto iterData = data.begin();
  for (int i = 0; i < numOfRows; i++)
    for (int j = 0; j < numOfColms; j++) {
      Mat[i][j] = *iterData;
      iterData++;
    }
}

template<class T>
Matrix<T>::~Matrix<T>() {
  for (int i = 0; i < numOfRows; i++) {
    delete Mat[i];
  }
  delete Mat;
}

template<class T>
std::string Matrix<T>::to_String() {
  std::string out = "";
  for (int i = 0; i < numOfRows; i++) {
    for (int j = 0; j < numOfColms; j++) {
      out += std::to_string(Mat[i][j]) + " ";
    }
    out += "\n";
  }
  return out;
}

template<class T>
std::string to_string(T &t) { return std::to_string(t.getCost()); }

#endif //SORTING_SERVER__MATRIX_H_
