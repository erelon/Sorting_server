//
// Created by erelon on 1/14/20.
//

#include "Solve_problems.h"
#include "Adapter_Solver_Searcher.h"

std::string ReversSolver::solve(std::string str) {
  std::string ret_str;
  std::reverse(str.begin(), str.end());
  ret_str = str;
  std::reverse(str.begin(), str.end());
  return ret_str;
}
ReversSolver::ReversSolver() {}
MatrixSolver::MatrixSolver(Point s, Point e) {
  this->start = s;
  this->end = e;
}

std::string MatrixSolver::solve(Matrix<double> mat) {
  std::string ret_str;
  ret_str = adapt<double, std::string>(mat, this->start, this->end);
  return ret_str;
}
void MatrixSolver::set_start_end(Point s, Point e) {
  this->start = s;
  this->end = e;
}
