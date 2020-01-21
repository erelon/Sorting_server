//
// Created by erelon on 1/21/20.
//

#include "Searchable.h"

template<class T, class S>
SearchableMatrix<T, S>::SearchableMatrix(Matrix<S> matrix, Point startP, Point endP) {
  this->mat = matrix;
  this->startPoint = startP;
  this->endPoint = endP;
}

template<class T, class S>
std::vector<State<T>> SearchableMatrix<T, S>::getAllPosiblleStates(State<T> now) {
  std::vector<State<T>> ret;
  //maybe ups and lefts are needed
  if (mat.getnumOfRows() - 1 > now.getState().getX()) {
    Point statePoint(now.getState().getX() + 1, now.getState().getY());
    ret.push_back(State<T>(statePoint, now.getCost() + this->mat.costOf(statePoint), &now));
  }
  if (mat.getnumOfCols() - 1 > now.getState().getY()) {
    Point statePoint(now.getState().getX(), now.getState().getY() + 1);
    ret.push_back(State<T>(statePoint, now.getCost() + this->mat.costOf(statePoint), &now));
  }
  return ret;
}