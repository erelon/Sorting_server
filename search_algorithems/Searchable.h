//
// Created by erelon on 1/21/20.
//

#ifndef SORTING_SERVER_SEARCH_ALGORITHEMS_SEARCHABLE_H_
#define SORTING_SERVER_SEARCH_ALGORITHEMS_SEARCHABLE_H_
#include <vector>
#include "State.h"
#include "../Matrix.h"

template<class T>
class Searchable {
  State<T> virtual getInitState() = 0;
  bool virtual isGoalState(State<T> is) = 0;
  std::vector<State<T>> virtual getAllPosiblleStates(State<T> now) = 0;
};

template<class T, class S>
class SearchableMatrix : public Searchable<T> {
  Matrix<S> mat;
  Point startPoint;
  Point endPoint;
 public:
  SearchableMatrix(Matrix<S> matrix, Point startP, Point endP);
  State<T> getInitState() { return State<T>(this->startPoint, 0, NULL); }
  bool isGoalState(State<T> is) { return (this->endPoint == is.getState()); }
  std::vector<State<T>> getAllPosiblleStates(State<T> now);
};

#endif //SORTING_SERVER_SEARCH_ALGORITHEMS_SEARCHABLE_H_
