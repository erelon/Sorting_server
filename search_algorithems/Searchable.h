//
// Created by erelon on 1/21/20.
//

#ifndef SORTING_SERVER_SEARCH_ALGORITHEMS_SEARCHABLE_H_
#define SORTING_SERVER_SEARCH_ALGORITHEMS_SEARCHABLE_H_

#include <vector>
#include "State.h"

template<class S>
class Searchable {
 public:
  State<S> virtual get_Init_State() = 0;
  bool virtual is_Goal_State(State<S> is) = 0;
  std::vector<State<S>> virtual get_All_Possible_States(State<S> now) = 0;
};

#endif //SORTING_SERVER_SEARCH_ALGORITHEMS_SEARCHABLE_H_
