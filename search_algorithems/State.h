//
// Created by erelon on 1/21/20.
//

#ifndef SORTING_SERVER_SEARCH_ALGORITHEMS_STATE_H_
#define SORTING_SERVER_SEARCH_ALGORITHEMS_STATE_H_
#include <string>
//////
#include "../Matrix.h"
//////
template<class T>
class State {
 private:
  T state;
  double cost;
  State<T> *came_From = nullptr;
 public:
  State<T> *came_from() { return came_From; }
  double const get_Cost() const { return cost; }
  State<T>() { this->came_From = NULL; }
  State(T state, double cost, State<T> *came_From) {
    this->state = state;
    this->cost = cost;
    this->came_From = came_From;
    //add the new State
  }
  bool operator==(const State<T> &s) const { return to_string(state) == to_string(s.state); }
  bool operator<(const State<T> &s) const { return cost < s.get_Cost(); }
  T get_State() { return this->state; }
  friend std::string to_string(State<T> &t) { return std::to_string(t.get_Cost()); }
};

template<>
struct std::hash<State<Point>> {
  size_t operator()(const State<Point> &obj) const {
    return hash<int>()(obj.get_Cost());
  }
};

#endif //SORTING_SERVER_SEARCH_ALGORITHEMS_STATE_H_
