//
// Created by erelon on 1/14/20.
//

#ifndef SORTING_SERVER__SERVER_SIDE_H_
#define SORTING_SERVER__SERVER_SIDE_H_
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "Solve_problems.h"
#include "CacheManager.h"

class ClientHandler {
 public:
  void virtual handleClient(std::string in, int out) = 0;
};

class Server {
  int virtual open(int port, ClientHandler *c) = 0;
  int virtual stop() = 0;
};

namespace boot {
class Main {
 public:
  int main(int argc, char *argv[]);
};
}
#endif //SORTING_SERVER__SERVER_SIDE_H_
