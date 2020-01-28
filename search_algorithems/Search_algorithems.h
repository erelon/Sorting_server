//
// Created by erelon on 1/20/20.
//

#ifndef SORTING_SERVER__SERACH_ALGORITHEMS_H_
#define SORTING_SERVER__SERACH_ALGORITHEMS_H_

#include <vector>
#include <unordered_set>
#include <list>
#include <queue>
#include <algorithm>
#include "Searcher.h"
#include "../Matrix.h"

template<class Solution>
class General_Search_Algo : public Searcher<Solution> {
 private:
  int evaluated_Nodes;
 protected:
  std::priority_queue<State<Point>, std::vector<State<Point>>, StateComparator> *open_List;
  State<Point> *pop_Open_List() {
    evaluated_Nodes++;
    State<Point> *temp = new State<Point>(open_List->top());
    open_List->pop();
    return temp;
  }

 public:
  General_Search_Algo<Solution>() {
    this->open_List = new std::priority_queue<State<Point>, std::vector<State<Point>>, StateComparator>();
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

    if (path.back().get_Cost() == -1)
      return "no path found";

    std::string s;
    path.reverse();
    Point last;
    bool first_time(true);
    for (auto iter = path.begin(); iter != path.end(); iter++) {
      if (!first_time) {
        if (iter->get_State().getX() > last.getX())
          s = s + "DOWN: ";
        if (iter->get_State().getX() < last.getX())
          s = s + "UP: ";
        if (iter->get_State().getY() > last.getY())
          s = s + "RIGHT: ";
        if (iter->get_State().getY() < last.getY())
          s = s + "Left: ";
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

//&& visited.find(*all_Possible_States[i]) == visited.end()


template<class Solution>
class BFS : public General_Search_Algo<Solution> {
 public:
  Solution search(Searchable<Point> &searchable) {
    std::vector<Point> done;
    State<Point> *u;
    this->open_List->push(*searchable.get_Init_State());
    //std::unordered_set<State<Point>> visited;

    while (!this->open_List->empty()) {
      u = (this->pop_Open_List());
      if (std::find(done.begin(), done.end(), u->get_State()) != done.end()) {
        //this u was checked already
        continue;
      }
      if (searchable.is_Goal_State(*u))
        return this->backtrace(*u);
      else {
        State<Point> **all_Possible_States = searchable.get_All_Possible_States(*u);
        for (int i = 0; i < 4; i++) {
          if (all_Possible_States[i] != nullptr
              && std::find(done.begin(), done.end(), all_Possible_States[i]->get_State()) == done.end()) {
            //visited.insert(*all_Possible_States[i]);
            this->open_List->push(*all_Possible_States[i]);
          }
        }
        done.push_back(u->get_State());
      }
    }
    return "no path found";
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

class A_Star_Node_Compare {
 public:
  int operator()(A_Star_Node<Point> *p1, A_Star_Node<Point> *p2) {
    return !(p1->getF() < p2->getF());
  }
};

template<class Solution>
class A_Star : public General_Search_Algo<Solution> {
 public:
  Solution search(Searchable<Point> &searchable) {
    auto
        open_List_alloc =
        new std::priority_queue<A_Star_Node<Point> *, std::vector<A_Star_Node<Point> *>, A_Star_Node_Compare>();
    std::list<A_Star_Node<Point> *> all_Nodes;
    std::list<A_Star_Node<Point> *> close_List;
    auto iter = new A_Star_Node<Point>(searchable.get_Init_State(), 0);
    open_List_alloc->push(iter);
    all_Nodes.push_back(iter);
    this->open_List->push(*iter->get_State());
    while (!open_List_alloc->empty()) {
      this->pop_Open_List();
      A_Star_Node<Point> *q = open_List_alloc->top();
      open_List_alloc->pop();
      all_Nodes.remove(q);

      State<Point> **suc = searchable.get_All_Possible_States(*q->get_State());
      for (int i = 0; i < 4; i++) {
        if (*(suc + i) == nullptr)
          continue;
        if (searchable.is_Goal_State(*suc[i])) {
          return this->backtrace(*suc[i]);
        }
        bool seen = false;
        for (auto item = close_List.begin(); item != close_List.end(); item++) {
          if ((*item)->get_State()->get_State() == suc[i]->get_State()) {
            seen = true;
            break;
            //we have finished with this node
          }
        }
        if(seen) continue;
        A_Star_Node<Point> *suc_A = new A_Star_Node<Point>
            (new State<Point>(suc[i]->get_State(), suc[i]->get_Cost(), suc[i]->came_from()),
             abs(suc[i]->get_State().getX() - searchable.get_Goal_State().get_State().getX())
                 + abs(suc[i]->get_State().getY() - searchable.get_Goal_State().get_State().getY()));
        bool is_lower = true;
        for (auto item:all_Nodes) {
          if (suc_A->get_State()->get_State() == item->get_State()->get_State()) {
            if (item->getF() < suc_A->getF())
              is_lower = false;
          }
        }

        for (auto item:close_List) {
          if (suc_A->get_State()->get_State() == item->get_State()->get_State()) {
            if (item->getF() < suc_A->getF())
              is_lower = false;
          }
        }
        if (is_lower) {
          open_List_alloc->push(suc_A);
          all_Nodes.push_back(suc_A);
          this->open_List->push(*suc_A->get_State());
        }
      }
      close_List.push_back(q);
    }
    return "no path found";
  }
};

template<class Solution>
class DFS : public General_Search_Algo<Solution> {
 public:
  Solution search(Searchable<Point> &searchable) {
    State<Point> *u;;
    std::vector<Point> visited;
    std::stack<State<Point> *> open_stack;
    this->open_List->push(*searchable.get_Init_State());
    open_stack.push(searchable.get_Init_State());

    while (!open_stack.empty()) {
      u = open_stack.top();
      open_stack.pop();
      this->pop_Open_List();
      if (searchable.is_Goal_State(*u))
        return this->backtrace(*u);
      auto child = searchable.get_All_Possible_States(*u);
      for (int i = 0; i < 4; i++) {
        if (child[i] == nullptr)
          continue;
        if (std::find(visited.begin(), visited.end(), child[i]->get_State()) == visited.end()) {
          visited.push_back(child[i]->get_State());
          open_stack.push(child[i]);
          this->open_List->push(*child[i]);
        }
      }
    }
  }
};

#endif //SORTING_SERVER__SERACH_ALGORITHEMS_H_
