//
// Created by erelon on 1/20/20.
//

#ifndef SORTING_SERVER__MATRIX_H_
#define SORTING_SERVER__MATRIX_H_
#include <vector>
#include <string>
#include <mutex>

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
  int getX() const { return x; }
  int getY() const { return y; }
  Point operator=(const Point &p) {
    this->x = p.getX();
    this->y = p.getY();
    return *this;
  }
  bool operator<(const Point &p2) {
    if (this->getX() > p2.getX()) {
      return this->getX() > p2.getX();
    }
    return this->getY() > p2.getY();
  }
  bool operator==(const Point &obj) {
    if (this->x == obj.x && this->y == obj.y)
      return true;
    else return false;
  }
  std::string to_string() {
    return std::to_string(this->getX()) + " " + std::to_string(this->getY());
  }
  friend std::string to_string(Point const &self) { return std::to_string(self.x) + " " + std::to_string(self.y); }
};

template<>
struct std::hash<Point> {
  size_t operator()(const Point &obj) const {
    return hash<int>()(atoi(to_string(obj).c_str()));
  }
};

//T must have a cost with get_Cost() func
template<class T>
class Matrix {
 private:
  T **Mat;
  int numOfColms{};
  int numOfRows{};
 public:
  Matrix<T>(int rows, int colms, std::vector<T> data);
  Matrix<T>() {
    this->Mat = nullptr;
    numOfColms = 0;
    numOfRows = 0;
  }
  ~Matrix<T>();
  int getnumOfRows() { return numOfRows; }
  int getnumOfCols() { return numOfColms; }
  int costOf(Point p) { return this->Mat[p.getX()][p.getY()]; }
  friend std::string to_string(Matrix &self) { return self.to_String(); }
  std::string to_String();
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
  for (int i = numOfRows - 1; i >= 0; i--) {
    //delete Mat[i];
  }
  //delete Mat;
}

template<class T>
std::string Matrix<T>::to_String() {
  std::string out;
  std::mutex mutex;
  while (!mutex.try_lock());
  for (int i = 0; i < numOfRows; i++) {
    for (int j = 0; j < numOfColms; j++) {
      out += std::to_string(Mat[i][j]) + " ";
    }
    out += "\n";
  }
  mutex.unlock();
  return out;
}

template<class T>
std::string to_string(T &t) { return t.to_string(); }

#endif //SORTING_SERVER__MATRIX_H_
