//
// Created by erelon on 1/14/20.
//

#ifndef SORTING_SERVER__SOLVE_PROBLEMS_H_
#define SORTING_SERVER__SOLVE_PROBLEMS_H_
#include <bits/stdc++.h>
#include <string>
#include <cstdio>

template<class Problem, class Solution>
class Solver {
 public:
  Solution virtual solve(Problem) = 0;
  //void virtual parse(std::string p)=0;
};

class ReversSolver : public Solver<std::string, std::string> {
 private:
  std::string string_to_revers;
 public:
  ReversSolver();
  std::string solve(std::string str);
};

#endif //SORTING_SERVER__SOLVE_PROBLEMS_H_
