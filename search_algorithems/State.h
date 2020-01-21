//
// Created by erelon on 1/21/20.
//

#ifndef SORTING_SERVER_SEARCH_ALGORITHEMS_STATE_H_
#define SORTING_SERVER_SEARCH_ALGORITHEMS_STATE_H_
#include <string>

template<class T>
class State {
 private:
  T state;
  double cost;
  State<T> *cameFrom;
 public:
  double getCost() { return cost; }
  State<T>() { this->cameFrom = NULL; }
  State(T state, double cost, State<T> *cameFrom) {
    this->state = state;
    this->cost = cost;
    this->cameFrom = cameFrom;
    //add the new State
  }
  bool operator==(const State<T> &s) const { return to_string(state) == to_string(s.state); }
  T getState() { return this->state; }
  friend std::string to_string(State<T> &t) { return std::to_string(t.getCost()); }
};

template<class T>
struct std::hash<State<T>> {
  size_t operator()(const State<T> &obj) const {
    return hash<int>()(obj.getCost());
  }
};

#endif //SORTING_SERVER_SEARCH_ALGORITHEMS_STATE_H_
