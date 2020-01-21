//
// Created by erelon on 1/21/20.
//

#ifndef SORTING_SERVER_SEARCH_ALGORITHEMS_SEARCHER_H_
#define SORTING_SERVER_SEARCH_ALGORITHEMS_SEARCHER_H_
#include "Searchable.h"
#include "../Matrix.h"

template<class Solution>
class Searcher {
 public:
  Solution virtual search(Searchable<Point> &searchable) = 0;
  int virtual get_Number_Of_Nodes_Evaluated() = 0;
};

#endif //SORTING_SERVER_SEARCH_ALGORITHEMS_SEARCHER_H_
