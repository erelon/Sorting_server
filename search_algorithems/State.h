//
// Created by erelon on 1/21/20.
//

#ifndef SORTING_SERVER_SEARCH_ALGORITHEMS_STATE_H_
#define SORTING_SERVER_SEARCH_ALGORITHEMS_STATE_H_
#include <string>
#include "../Matrix.h"

template<class T>
class State {
 private:
  T state;
  int cost;
  State<T> *came_From;
 public:
  State<Point> *came_from() const { return came_From; }
  int const get_Cost() const { return cost; }
  State<T>() {
    this->came_From = nullptr;
    cost = 0;
  }
  State<T>(State<T> const &copy) {
    this->state = copy.get_State();
    this->cost = copy.get_Cost();
    this->came_From = copy.came_from();
  }
  State(T state, int cost, State<T> *came_From1) {
    this->state = state;
    this->cost = cost;
    this->came_From = came_From1;
    //add the new State
  }
  ~State<T>() {}
  bool operator==(const State<T> &s) const { return to_string(state) == to_string(s.state); }
  bool operator<(const State<T> &s) const {
    return cost < s.get_Cost();
  }
  /*State<T> &operator=(const State<T> &s) {
    state = s.get_State();
    cost = s.get_Cost();
    came_From = s.came_from();
    return *this;
  }*/
  T get_State() const { return this->state; }
  T get_State() { return this->state; }
  friend std::string to_string(State<T> &t) { return std::to_string(t.get_Cost()); }
};

class StateComparator {
 public:
  int operator()(const State<Point> &p1, const State<Point> &p2) {
    return !(p1.get_Cost() < p2.get_Cost());
  }
};

template<>
struct std::hash<State<Point>> {
  size_t operator()(State<Point> obj) const {
    return hash<int>()(obj.get_Cost());
  }
};

#endif //SORTING_SERVER_SEARCH_ALGORITHEMS_STATE_H_
