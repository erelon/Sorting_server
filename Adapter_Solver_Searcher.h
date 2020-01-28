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
std::string adapt(Matrix<T> sr, Point start, Point end) {

  Searchable_Matrix<int, Point> sm(&sr, start, end);
  A_Star<Solution> work;

  return work.search(sm);

/*
 * code for checking what algorithm is the best:
 * std::string a = "The matrix is:\n";
 * a += sr.to_String();
 * a += work.search(sm);
 * a += +"\nNum of nodes evaluated:" + std::to_string(work.get_Number_Of_Nodes_Evaluated());
 * return a;
 *
 */

}

#endif //SORTING_SERVER__ADAPTER_SOLVER_SEARCHER_H_
