//
// Created by erelon on 1/21/20.
//

#ifndef SORTING_SERVER_SEARCH_ALGORITHEMS_SEARCHER_H_
#define SORTING_SERVER_SEARCH_ALGORITHEMS_SEARCHER_H_
#include "Searchable.h"

template<class T, class Solution>
class Searcher {
 public:
  Solution virtual search(Searchable<T>) = 0;
  int virtual get_Number_Of_Nodes_Evaluated() = 0;
};

#endif //SORTING_SERVER_SEARCH_ALGORITHEMS_SEARCHER_H_
