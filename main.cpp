//
// Created by erelon on 1/19/20.
//
#include "search_algorithems/Searchable.h"
#include "Server_side.h"
#include "Matrix.h"
#include "search_algorithems/Search_algorithems.h"
#include "search_algorithems/Searchable_Matrix.h"

int main(int argc, char *argv[]) {
  boot::Main main1;
  main1.main(argc, argv);

/*
  Point start(0, 0);
  Point end(5, 5);

  std::vector<double> test;
  for (int i = 0; i < 36; i++) {
    test.push_back(i);
  }

  Matrix<double> mat(6, 6, test);
  std::cout << to_string(mat) << std::endl;

  Searchable_Matrix<double, Point> sm(&mat, start, end);

  BFS< std::string> work1;
  std::string way1 = work1.search(sm);

  A_Star<std::string> work2;
  std::string way2 =work2.search(sm);

  std::cout<<"BFS: "<<work1.get_Number_Of_Nodes_Evaluated()<<"\n"<<way1<<std::endl;
  std::cout<<"A Star: "<<work2.get_Number_Of_Nodes_Evaluated()<<"\n"<<way2<<std::endl;
*/
  return 0;
}