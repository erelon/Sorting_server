//
// Created by erelon on 1/21/20.
//

#ifndef SORTING_SERVER_SEARCH_ALGORITHEMS_SEARCHABLE_H_
#define SORTING_SERVER_SEARCH_ALGORITHEMS_SEARCHABLE_H_

#include "State.h"
#include "../Matrix.h"

template<class T>
class Searchable {
  State<T> virtual get_Init_State() = 0;
  bool virtual is_Goal_State(State<T> is) = 0;
  std::vector<State<T>> virtual get_All_Possible_States(State<T> now) = 0;
};

template<class T, class S>
class Searchable_Matrix : public Searchable<T> {
  Matrix<S> mat;
  Point start_Point;
  Point end_Point;
 public:
  Searchable_Matrix(Matrix<S> matrix, Point startP, Point endP);
  State<T> get_Init_State();
  bool is_Goal_State(State<T> is);
  std::vector<State<T>> get_All_Possible_States(State<T> now);
  bool in_Metrix_Bounds (Point p);
};

#endif //SORTING_SERVER_SEARCH_ALGORITHEMS_SEARCHABLE_H_
