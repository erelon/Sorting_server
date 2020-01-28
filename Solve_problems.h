//
// Created by erelon on 1/14/20.
//

#ifndef SORTING_SERVER__SOLVE_PROBLEMS_H_
#define SORTING_SERVER__SOLVE_PROBLEMS_H_
#include <bits/stdc++.h>
#include <string>
#include <cstdio>
#include "Matrix.h"

template<class Problem, class Solution>
class Solver {
 public:
  Solution virtual solve(Problem) = 0;
};

class ReversSolver : public Solver<std::string, std::string> {
 private:
  std::string string_to_revers;
 public:
  ReversSolver();
  std::string solve(std::string str);
};

class MatrixSolver : public Solver<Matrix<int> , std::string>{
  Matrix<int> matrix_to_solve;
  Point start;
  Point end;
 public:
  MatrixSolver(){}
  MatrixSolver(Point s, Point e);
  void set_start_end(Point s, Point e);
  std::string solve(Matrix<int> mat);
};

#endif //SORTING_SERVER__SOLVE_PROBLEMS_H_
