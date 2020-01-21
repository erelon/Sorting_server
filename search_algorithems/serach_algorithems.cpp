//
// Created by erelon on 1/20/20.
//

#include <queue>
#include <unordered_set>
#include <list>
#include <execinfo.h>
#include "serach_algorithems.h"

template<class T, class Solution>
State<T> Genral_Search_Algo<T, Solution>::popOpenList() {
  evaluatedNodes++;
  auto temp = openList->top();
  openList->pop();
  return temp;
}

template<class T, class Solution>
Solution BFS<T, Solution>::search(Searchable<T> searchable) {
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