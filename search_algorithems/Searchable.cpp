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
std::vector<State<T>> Searchable_Matrix<T, S>::get_All_Possible_States(State<T> current_State) {
  std::vector<State<T>> ret;

  std::vector<Point> offsets;
  offsets.emplace_back(-1, 0); // Up
  offsets.emplace_back(1, 0); // Down
  offsets.emplace_back(0, -1); // Left
  offsets.emplace_back(0, 1); // Right

  for (auto iter : offsets) {
    std::pair<int, int> nextPoint =
        make_pair(current_State.getState().first + iter.getX(), current_State.getState().second + iter.getY());
    if (in_Metrix_Bounds(nextPoint)) {
      ret.push_back(State<std::pair<int, int>>(nextPoint,
                                               current_State.getCost() + this->mat.CostOf(nextPoint),
                                               &current_State));
    }
  }
  return ret;
}

template<class T, class S>
bool Searchable_Matrix<T, S>::in_Metrix_Bounds(Point p) {
  return (p.getX() >= 0 && p.getY() >= 0 && p.getX() < mat.getnumOfRows() && p.getY() < mat.getnumOfCols());
}
template<class T, class S>
State<T> Searchable_Matrix<T, S>::get_Init_State() { return State<T>(this->start_Point, 0, NULL); }

template<class T, class S>
bool Searchable_Matrix<T, S>::is_Goal_State(State<T> is) { return (this->end_Point == is.get_State()); }

