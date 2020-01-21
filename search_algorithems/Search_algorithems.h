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

template<class Solution>
class General_Search_Algo : public Searcher<Solution> {
 private:
  int evaluated_Nodes;
 protected:
  std::priority_queue<State<Point>> *open_List;
  State<Point> pop_Open_List(){
    evaluated_Nodes++;
    auto temp = open_List->top();
    open_List->pop();
    return temp;
  }
 public:
  General_Search_Algo<Solution>(){
    this->open_List = new std::priority_queue<State<Point>>();
    this->evaluated_Nodes = 0;
  }
  int Open_List_Size() { return open_List->size(); };
  int get_Number_Of_Nodes_Evaluated() { return evaluated_Nodes; }
  Solution virtual search(Searchable<Point> &searchable) = 0;
};

template<class Solution>
class BFS : public General_Search_Algo<Solution> {
 public:
  Solution backtrace(State<Point> &u) {
    Solution s;
    s += to_string(u.get_State());
    while (u.came_from() != nullptr) {
      u = *u.came_from();
      s += to_string(u.get_State());
    }
    return s;
  }

  Solution search(Searchable<Point> &searchable) {
    this->open_List->push(searchable.get_Init_State());
    while (!this->open_List->empty()) {
      auto u = this->pop_Open_List();
      if (searchable.is_Goal_State(u))
        return backtrace(u);
      else {
        for (auto v : searchable.get_All_Possible_States(u)) {
          if (true) {//check if v was visited{
            //v was visited
            this->open_List->push(v);
          }
          //mark u as done
        }
      }

    }
  }
};

#endif //SORTING_SERVER__SERACH_ALGORITHEMS_H_
