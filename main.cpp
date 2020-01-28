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
  Point end(2, 2);

  std::vector<double> test;
  //for (int i = 0; i < 36; i++) {
//    test.push_back(i);
  //}

  test.push_back(1);
  test.push_back(1);
  test.push_back(10);
  test.push_back(7);
  test.push_back(20);
  test.push_back(4);
  test.push_back(7);
  test.push_back(1);
  test.push_back(1);
  test.push_back(0);
  test.push_back(0);
  test.push_back(2);
  test.push_back(2);

  Matrix<double> mat(3, 3, test);
  std::cout << to_string(mat) << std::endl;

  Searchable_Matrix<double, Point> sm(&mat, start, end);

  BFS< std::string> work1;
  std::string way1 = work1.search(sm);

  A_Star<std::string> work2;
  std::string way2 =work2.search(sm);

  DFS<std::string> work3;
  std::string way3 =work3.search(sm);


  std::cout<<"BFS: "<<work1.get_Number_Of_Nodes_Evaluated()<<"\n"<<way1<<std::endl;
  std::cout<<"A Star: "<<work2.get_Number_Of_Nodes_Evaluated()<<"\n"<<way2<<std::endl;
  std::cout<<"DSF: "<<work3.get_Number_Of_Nodes_Evaluated()<<"\n"<<way3<<std::endl;
*/
  return 0;
}