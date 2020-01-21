//
// Created by erelon on 1/20/20.
//

#ifndef SORTING_SERVER__SERACH_ALGORITHEMS_H_
#define SORTING_SERVER__SERACH_ALGORITHEMS_H_

#include <vector>
#include <unordered_set>
#include <list>
#include <queue>
#include "Searcher.h"
#include "../Matrix.h"

template<class T, class Solution>
class General_Search_Algo : public Searcher<T, Solution> {
 private:
  int evaluated_Nodes;
 protected:
  std::priority_queue<State<T>> *open_List;
  State<T> pop_Open_List();
 public:
  General_Search_Algo<T, Solution>();
  int Open_List_Size() { return open_List->size(); };
  int get_Number_Of_Nodes_Evaluated() { return evaluated_Nodes; }
  Solution virtual search(Searchable<T> searchable) = 0;
};

template<class T, class Solution>
class BFS : public General_Search_Algo<T, Solution> {
 public:
  Solution search(Searchable<T> searchable);
};

#endif //SORTING_SERVER__SERACH_ALGORITHEMS_H_
