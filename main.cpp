//
// Created by erelon on 1/19/20.
//
#include "server_side.h"
#include "Matrix.h"
#include "serach_algorithems.h"

int main(int argc, char *argv[]) {
  //boot::Main main1;
  //main1.main(argc, argv);

  State<Point> start(Point(0, 0), 0, NULL);
  State<Point> end(Point(4, 4), 0, NULL);

  std::vector<State<double>> test;
  for (int i = 0; i < 25; i++) {
    test.push_back(State<double>(i, i, NULL));
  }

  Matrix<State<double>> mat(5, 5, test);
  std::cout << to_string(mat) << std::endl;

  SearchableMatrix<double, State<double >> sm(mat, start, end);
  //BFS::search(sm);

  return 0;
}