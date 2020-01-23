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
  State<Point> *pop_Open_List() {
    evaluated_Nodes++;
    State<Point> *temp = new State<Point>(open_List->top());
    open_List->pop();
    return temp;
  }

 public:
  General_Search_Algo<Solution>() {
    this->open_List = new std::priority_queue<State<Point>>();
    this->evaluated_Nodes = 0;
  }
  int Open_List_Size() { return open_List->size(); };
  int get_Number_Of_Nodes_Evaluated() { return evaluated_Nodes; }
  Solution virtual search(Searchable<Point> &searchable) = 0;
  Solution backtrace(State<Point> &u) {
    std::list<State<Point>> path;
    State<Point> const *step;
    path.push_back(u);
    step = u.came_from();
    while (step != nullptr) {
      path.push_back(*step);
      step = step->came_from();
    }
    std::string s;
    path.reverse();
    Point last;
    bool first_time(true);
    for (auto iter = path.begin(); iter != path.end(); iter++) {
      if (!first_time) {
        if (iter->get_State().getX() > last.getX())
          s = s + "RIGHT: ";
        if (iter->get_State().getX() < last.getX())
          s = s + "Left: ";
        if (iter->get_State().getY() > last.getY())
          s = s + "DOWN: ";
        if (iter->get_State().getY() < last.getY())
          s = s + "UP: ";
        s = s + std::to_string(iter->get_Cost()) + ", ";
      }
      last = iter->get_State();
      first_time = false;
    }
    s.pop_back();
    s.pop_back();
    return s;
  }
};

template<class Solution>
class BFS : public General_Search_Algo<Solution> {
 public:
  Solution search(Searchable<Point> &searchable) {
    std::unordered_set<State<Point>> done;
    State<Point> *u;
    this->open_List->push(*searchable.get_Init_State());
    std::unordered_set<State<Point>> visited;

    while (!this->open_List->empty()) {
      u = (this->pop_Open_List());
      if (done.find(*u) != done.end()) {
        //this u was checked already
        continue;
      }
      if (searchable.is_Goal_State(*u))
        return this->backtrace(*u);
      else {
        visited.insert(*u);
        State<Point> **all_Possible_States = searchable.get_All_Possible_States(*u);
        for (int i = 0; i < 4; i++) {
          if (*(all_Possible_States + i) != nullptr) {
            if (visited.find(*all_Possible_States[i]) == visited.end()) {//check if v was not visited yet
              visited.insert(*all_Possible_States[i]);
              this->open_List->push(*all_Possible_States[i]);
            }
          }
        }
      }
      done.insert(*u);
    }
  }
};

template<class T>
class A_Star_Node {
  State<T> *t;
  int f;
  int hurisic;
 public:
  A_Star_Node(State<T> *state, int h) {
    t = state;
    hurisic = h;
    f = t->get_Cost() + h;
  }
  int getH() { return hurisic; }
  int getF() { return f; }
  State<T> *get_State() { return t; }
  ~A_Star_Node() {}
  bool operator<(const A_Star_Node<T> &ASN) const { return (this->f < ASN.f); }
  bool operator==(const A_Star_Node<T> &ASN) const { return (t == ASN.t && hurisic == ASN.hurisic); }
};

template<class Solution>
class A_Star : public General_Search_Algo<Solution> {
 public:
  Solution search(Searchable<Point> &searchable) {
    std::priority_queue<A_Star_Node<Point>> *open_List = new std::priority_queue<A_Star_Node<Point>>();
    std::list<A_Star_Node<Point>> all_Nodes;
    std::list<A_Star_Node<Point>> close_List;
    auto iter = new A_Star_Node<Point>(searchable.get_Init_State(), 0);
    open_List->push(*iter);
    all_Nodes.push_back(*iter);
    this->open_List->push(*iter->get_State());
    while (!open_List->empty()) {
      this->pop_Open_List();
      A_Star_Node<Point> q = open_List->top();
      open_List->pop();
      all_Nodes.remove(q);

      State<Point> **suc = searchable.get_All_Possible_States(*q.get_State());
      for (int i = 0; i < 4; i++) {
        if (*(suc + i) == nullptr)
          continue;
        if (searchable.is_Goal_State(*suc[i])) {
          return this->backtrace(*suc[i]);
        }
        A_Star_Node<Point> suc_A
            (new State<Point>(suc[i]->get_State(), q.get_State()->get_Cost() + suc[i]->get_Cost(), suc[i]->came_from()),
             abs(suc[i]->get_State().getX() - searchable.get_Goal_State().get_State().getX())
                 + abs(suc[i]->get_State().getY() - searchable.get_Goal_State().get_State().getY()));
        bool is_lower = true;
        for (auto item:all_Nodes) {
          if (suc_A.get_State()->get_State() == item.get_State()->get_State()) {
            if (item.getF() < suc_A.getF())
              is_lower = false;
          }
        }

        for (auto item:close_List) {
          if (suc_A.get_State()->get_State() == item.get_State()->get_State()) {
            if (item.getF() < suc_A.getF())
              is_lower = false;
          }
        }
        if (is_lower) {
          open_List->push(suc_A);
          all_Nodes.push_back(suc_A);
          this->open_List->push(*suc_A.get_State());
        }
      }
      close_List.push_back(q);
    }
  }
};

template<class Solution>
class DFS : public General_Search_Algo<Solution> {
 public:
  Solution search(Searchable<Point> &searchable) {

  }
};

#endif //SORTING_SERVER__SERACH_ALGORITHEMS_H_
