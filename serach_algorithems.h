//
// Created by erelon on 1/20/20.
//

#ifndef SORTING_SERVER__SERACH_ALGORITHEMS_H_
#define SORTING_SERVER__SERACH_ALGORITHEMS_H_
#include <cstdio>
#include <vector>
#include "Matrix.h"

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
  }
  bool operator==(const State<T> &s) const { return to_string(state) == to_string(s.state); }
  T getState() { return this->state; }
  friend std::string to_string(State<T> &t) { return std::to_string(t.getCost()); }
};

template<class T>
struct std::hash<State<T>> {
  size_t
  operator()(const State<T> &obj) const {
    return hash<int>()(obj.getCost());
  }
};

template<class T>
class Searchable {
  State<T> virtual getInitState() = 0;
  bool virtual isGoalState(State<T> is) = 0;
  std::vector<State<T>> virtual getAllPosiblleStates(State<T> now) = 0;
};

template<class T, class S>
class SearchableMatrix : public Searchable<T> {
  Matrix<S> mat;
  State<T> intialState;
  State<T> goalState;
 public:
  SearchableMatrix(Matrix<S> matrix, State<T> startP, State<T> endP) {
    this->mat = matrix;
    this->intialState = State<T>(startP.getState(), mat.costOf(startP), NULL);
    this->goalState = State<T>(endP.getState(), mat.costOf(endP), NULL);

  }
  State<T> getInitState() { return this->intialState; }
  bool isGoalState(State<T> is) { return (this->goalState == is); }
  std::vector<State<T>> getAllPosiblleStates(State<T> now) {
    std::vector<State<T>> ret;
    //maybe ups and lefts are needed
    if (mat.getnumOfRows() - 1 > now.getState().getX() && mat.getnumOfCols() - 1 > now.getState().getY()) {
      Point statePoint(now.getState().getX() + 1, now.getState().getY() + 1);
      ret.push_back(State<T>(statePoint, now.getCost() + this->mat.CostOf(statePoint), &now));
    }
    if (mat.getnumOfRows() - 1 > now.getState().getX()) {
      Point statePoint(now.getState().getX() + 1, now.getState().getY());
      ret.push_back(State<T>(statePoint, now.getCost() + this->mat.CostOf(statePoint), &now));
    }
    if (mat.getnumOfCols() - 1 > now.getState().getY()) {
      Point statePoint(now.getState().getX(), now.getState().getY() + 1);
      ret.push_back(State<T>(statePoint, now.getCost() + this->mat.CostOf(statePoint), &now));
    }
    return ret;
  }
};

template<class T, class Solution>
class Searcher {
 public:
  Solution virtual search(Searchable<T>) = 0;
  int virtual getNumberOfNodesEvaluated() = 0;
};

template<class T, class Solution>
class Genral_Search_Algo : public Searcher<T, Solution> {
 private:
  int evaluatedNodes;
 protected:
  std::priority_queue<State<T>> *openList;
  State<T> popOpenList() {
    evaluatedNodes++;
    auto temp = openList->top();
    openList->pop();
    return temp;
  }
 public:
  Genral_Search_Algo<T, Solution>() {
    this->openList = new std::priority_queue<State<T>>();
    this->evaluatedNodes = 0;
  }
  int OpenListSize() { return openList->size(); };
  int getNumberOfNodesEvaluated() { return evaluatedNodes; }
  Solution virtual search(Searchable<T> searchable) = 0;
};

namespace BFS {
template<class T, class Solution>
class BFS : public Genral_Search_Algo<T, Solution> {
  Solution search(Searchable<T> searchable) {
    this->openList->push(searchable.getInitState());
    std::unordered_set<State<T>> closed = new std::unordered_set<State<T>>();
    while (this->OpenListSize() > 0) {
      State<T> n = this->popOpenList();
      closed.insert(n);
      if (searchable.isGoalState(n))
        return backtrace(closed, closed.size());/////////////////
      std::list<State<T>> succerssors = searchable.getAllPosiblleStates(n);
      for (State<T> s :succerssors) {
        if (closed.find(s) == closed.end() && this->openList.find(s) == this->openList.find(s).end())
          //
          this->openList->push(s);
        else if (n.getCost() < s.getState()) {
          if (closed.find(s) == closed.end())
            this->openList->push(s);
          else this->openList->push(s);//not so sure what to do here

        }
      }
    }
  }
};
}

#endif //SORTING_SERVER__SERACH_ALGORITHEMS_H_
