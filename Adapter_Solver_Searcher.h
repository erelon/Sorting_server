//
// Created by erelon on 1/22/20.
//

#ifndef SORTING_SERVER__ADAPTER_SOLVER_SEARCHER_H_
#define SORTING_SERVER__ADAPTER_SOLVER_SEARCHER_H_

#include <string>
#include "Matrix.h"
#include "search_algorithems/Searchable_Matrix.h"
#include "search_algorithems/Search_algorithems.h"

template<class T, class Solution>
Solution adapt(Matrix<T> sr, Point start, Point end) {

  Searchable_Matrix<double, Point> sm(&sr, start, end);
  BFS<Solution> work;

  return work.search(sm);
}

#endif //SORTING_SERVER__ADAPTER_SOLVER_SEARCHER_H_
