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
  State<Point> pop_Open_List() {
    evaluated_Nodes++;
    State<Point> *temp = new State<Point>();
    (*temp).operator=(open_List->top());
    open_List->pop();
    return *temp;
  }
 public:
  General_Search_Algo<Solution>() {
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
    State<Point> const *step;
    s += to_string(u.get_State()) + ", ";https://github.com/erelon/Sorting_server.git
    while (u.came_from() != nullptr) {
      step = u.came_from();
      s += to_string(step->get_State()) + ", ";
    }
    return s;
  }

  Solution search(Searchable<Point> &searchable) {
    std::unordered_set<State<Point>> done;
    this->open_List->push(searchable.get_Init_State());
    while (!this->open_List->empty()) {
      auto u = this->pop_Open_List();
      if (done.find(u) != done.end()) {
        //this u was checked already
        continue;
      }
      if (searchable.is_Goal_State(u))
        return backtrace(u);
      else {
        std::unordered_set<State<Point>> visited;
        State<Point> *all_Possible_States = searchable.get_All_Possible_States(u);
        for (int i = 0; i < 4; i++) {
          if ((all_Possible_States + i)->came_from() != nullptr) {
            if (visited.find(all_Possible_States[i]) == visited.end()) {//check if v was not visited yet
              visited.insert(all_Possible_States[i]);
              this->open_List->push(all_Possible_States[i]);
            }
          }
        }
      }
      done.insert(u);
    }
  }
};

#endif //SORTING_SERVER__SERACH_ALGORITHEMS_H_
