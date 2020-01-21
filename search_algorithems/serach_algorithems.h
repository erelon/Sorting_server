//
// Created by erelon on 1/20/20.
//

#ifndef SORTING_SERVER__SERACH_ALGORITHEMS_H_
#define SORTING_SERVER__SERACH_ALGORITHEMS_H_
#include <cstdio>
#include <vector>
#include "searcher.h"
#include "../Matrix.h"

template<class T, class Solution>
class Genral_Search_Algo : public Searcher<T, Solution> {
 private:
  int evaluatedNodes;
 protected:
  std::priority_queue<State<T>> *openList;
  State<T> popOpenList();
 public:
  Genral_Search_Algo<T, Solution>() {
    this->openList = new std::priority_queue<State<T>>();
    this->evaluatedNodes = 0;
  }
  int OpenListSize() { return openList->size(); };
  int getNumberOfNodesEvaluated() { return evaluatedNodes; }
  Solution virtual search(Searchable<T> searchable) = 0;
};

template<class T, class Solution>
class BFS : public Genral_Search_Algo<T, Solution> {
 public:
  Solution search(Searchable<T> searchable);
};

#endif //SORTING_SERVER__SERACH_ALGORITHEMS_H_
