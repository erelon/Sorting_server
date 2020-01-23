//
// Created by erelon on 1/21/20.
//

#ifndef SORTING_SERVER_SEARCH_ALGORITHEMS_SEARCHABLE_MATRIX_H_
#define SORTING_SERVER_SEARCH_ALGORITHEMS_SEARCHABLE_MATRIX_H_
#include "../Matrix.h"
#include "Searchable.h"

template<class T, class S>
class Searchable_Matrix : public Searchable<S> {
  Matrix<T> *mat;
  Point start_Point;
  Point end_Point;
 public:
  Searchable_Matrix(Matrix<T> *matrix, Point startP, Point endP) {
    this->mat = matrix;
    this->start_Point = startP;
    this->end_Point = endP;
  }
  State<S> *get_Init_State() { return new State<S>(this->start_Point, 0, nullptr); }
  State<S> get_Goal_State() { return State<S>(this->end_Point, 0, nullptr); }
  bool is_Goal_State(State<S> is) { return (this->end_Point == is.get_State()); }
  State<S> **get_All_Possible_States(State<S> &current_State) {
    State<S> **ret = new State<S> *[4];

    std::list<Point> offsets;
    offsets.emplace_back(1, 0); // Down
    offsets.emplace_back(-1, 0); // Up
    offsets.emplace_back(0, 1); // Right
    offsets.emplace_back(0, -1); // Left

    int i = 0;
    for (auto iter : offsets) {
      Point nextPoint(current_State.get_State().getX() + iter.getX(), current_State.get_State().getY() + iter.getY());
      if (in_Metrix_Bounds(nextPoint) && this->mat->costOf(nextPoint) != -1) {
        ret[i++] = new State<Point>(nextPoint,
                                    current_State.get_Cost() + this->mat->costOf(nextPoint),
                                    &current_State);
      } else ret[i++] = nullptr;
    }
    return ret;
  }
  bool in_Metrix_Bounds(Point p) {
    return (p.getX() >= 0 && p.getY() >= 0 && p.getX() < mat->getnumOfRows() && p.getY() < mat->getnumOfCols());
  }
};

#endif //SORTING_SERVER_SEARCH_ALGORITHEMS_SEARCHABLE_MATRIX_H_
