//
// Created by erelon on 1/19/20.
//
#include "search_algorithems/Searchable.h"
#include "Server_side.h"
#include "Matrix.h"
#include "search_algorithems/Search_algorithems.h"
#include "search_algorithems/Searchable_Matrix.h"

int main(int argc, char *argv[]) {
  //boot::Main main1;
  //main1.main(argc, argv);

  Point start(0, 0);
  Point end(4, 4);

  std::vector<double> test;
  for (int i = 0; i < 25; i++) {
    test.push_back(i);
  }

  Matrix<double> mat(5, 5, test);
  std::cout << to_string(mat) << std::endl;

  Searchable_Matrix<double, Point> sm(&mat, start, end);

  BFS< std::string> work;
  work.search(sm);
  return 0;
}