//
// Created by erelon on 1/14/20.
//

#include "Solve_problems.h"

std::string ReversSolver::solve(std::string str) {
  std::string ret_str;
  std::reverse(str.begin(), str.end());
  ret_str = str;
  std::reverse(str.begin(), str.end());
  return ret_str;
}
ReversSolver::ReversSolver() {}