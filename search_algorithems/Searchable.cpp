//
// Created by erelon on 1/21/20.
//

#include "Searchable.h"

template<class T, class S>
Searchable_Matrix<T, S>::Searchable_Matrix(Matrix<S> matrix, Point startP, Point endP) {
  this->mat = matrix;
  this->start_Point = startP;
  this->end_Point = endP;
}

template<class T, class S>
std::vector<State<T>> Searchable_Matrix<T, S>::get_All_Possible_States(State<T> now) {
  std::vector<State<T>> ret;
  //maybe ups and lefts are needed
  if (mat.getnumOfRows() - 1 > now.get_State().getX()) {
    Point state_Point(now.get_State().getX() + 1, now.get_State().getY());
    ret.push_back(State<T>(state_Point, now.get_Cost() + this->mat.costOf(state_Point), &now));
  }
  if (mat.getnumOfCols() - 1 > now.get_State().getY()) {
    Point state_Point(now.get_State().getX(), now.get_State().getY() + 1);
    ret.push_back(State<T>(state_Point, now.get_Cost() + this->mat.costOf(state_Point), &now));
  }
  return ret;
}