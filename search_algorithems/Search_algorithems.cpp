//
// Created by erelon on 1/20/20.
//

#include "Search_algorithems.h"

template<class T, class Solution>
State<T> General_Search_Algo<T, Solution>::pop_Open_List() {
  evaluated_Nodes++;
  auto temp = open_List->top();
  open_List->pop();
  return temp;
}
template<class T, class Solution>
General_Search_Algo<T, Solution>::General_Search_Algo() {
  this->open_List = new std::priority_queue<State<T>>();
  this->evaluated_Nodes = 0;
}

template<class T, class Solution>
Solution BFS<T, Solution>::search(Searchable<T> searchable) {
  this->open_List->push(searchable.get_Init_State());
  std::unordered_set<State<T>> closed = new std::unordered_set<State<T>>();
  while (this->Open_List_Size() > 0) {
    State<T> n = this->pop_Open_List();
    closed.insert(n);
    if (searchable.is_Goal_State(n))
      return backtrace(closed, closed.size());/////////////////
    std::list<State<T>> succerssors = searchable.get_All_Possible_States(n);
    for (State<T> s :succerssors) {
      if (closed.find(s) == closed.end() && this->open_List.find(s) == this->open_List.find(s).end())
        //
        this->open_List->push(s);
      else if (n.get_Cost() < s.get_State()) {
        if (closed.find(s) == closed.end())
          this->open_List->push(s);
        else this->open_List->push(s);//not so sure what to do here

      }
    }
  }
}