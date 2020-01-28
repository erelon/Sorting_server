//
// Created by erelon on 1/14/20.
//

#include <thread>
#include <sstream>
#include "Server_side.h"

int open_server(int port, sockaddr_in *p_in) {
  //create socket
  int socketfd = socket(AF_INET, SOCK_STREAM, 0);
  if (socketfd == -1) {
    //error
    std::cerr << "Could not create a socket" << std::endl;
    return -1;
  }

  //bind socket to IP address
  // we first need to create the sockaddr obj.
  //in means IP4
  (*p_in).sin_family = AF_INET;
  (*p_in).sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
  (*p_in).sin_port = htons(port);
  //we need to convert our number
  // to a number that the network understands.

  //the actual bind command
  if (bind(socketfd, (struct sockaddr *) p_in, sizeof(*p_in)) == -1) {
    std::cerr << "Could not bind the socket to an IP" << std::endl;
    return -2;
  }

  //making socket listen to the port
  if (listen(socketfd, 10) == -1) { //can also set to SOMAXCON (max connections)
    std::cerr << "Error during listening command" << std::endl;
    return -3;
  } else {
    std::cout << "Server is now listening ..." << std::endl;
  }

  return socketfd;
}

int accept_client(int socketfd, sockaddr_in address) {
  // accepting a client
  socklen_t clientAddrLen = sizeof(address);

  struct timeval tv;
  tv.tv_sec = 10;
  tv.tv_usec = 0;
  setsockopt(socketfd, SOL_SOCKET, SO_RCVTIMEO, (const char *) &tv, sizeof tv);
  int client_socket = accept(socketfd, (struct sockaddr *) &address,
                             &clientAddrLen);

  if (client_socket == -1) {
    //std::cerr << strerror(errno) << std::endl;
    //timeout
    return -1;
  }
}

namespace server_side {

class MyParalelServer : public Server {
 private:
  ClientHandler *client_handler;
  sockaddr_in address;
  bool to_run = false;
 public:
  MyParalelServer(ClientHandler *cl);
  int run(int socketfd);
  int open(int port, ClientHandler *c);
  int stop();
  bool is_running();
  void run_adapter(std::string Data, int client);
};

bool MyParalelServer::is_running() {
  return to_run;
}

MyParalelServer::MyParalelServer(ClientHandler *cl) {
  this->client_handler = cl;
}

int MyParalelServer::open(int port, ClientHandler *c) {
  this->to_run = true;
  int socketfd = open_server(port, &address);
  run(socketfd);
}

int MyParalelServer::run(int socketfd) {
  int numOfClient = 0;
  while (to_run) {
    int client = accept_client(socketfd, address);
    numOfClient++;
    if (client == -1) {
      this->stop();
      continue;
    }

    char buffer[2048] = {0};
    read(client, buffer, 1024);
    std::string Data(buffer);
    std::thread take_client(&MyParalelServer::run_adapter, this, Data, client);
    take_client.detach();
  }
  close(socketfd);
}

void MyParalelServer::run_adapter(std::string Data, int client) {
  this->client_handler->handleClient(Data, client);
}

int MyParalelServer::stop() {
  this->to_run = false;
}

class MySerialServer : Server {
 private:
  ClientHandler *client_handler;
  sockaddr_in address;
  bool to_run = false;
 public:
  MySerialServer(ClientHandler *cl);
  int run(int socketfd);
  int open(int port, ClientHandler *c);
  int stop();
};

int MySerialServer::open(int port, ClientHandler *c) {
  this->to_run = true;
  int socketfd = open_server(port, &address);
  std::thread server(&MySerialServer::run, this, socketfd);
  server.detach();
}

int MySerialServer::run(int socketfd) {
  while (to_run) {
    int client = accept_client(socketfd, address);
    if (client == -1) {
      //add timeout
      sleep(2);
      continue;
    }

    char buffer[2048] = {0};
    read(client, buffer, 1024);
    std::string Data(buffer);

    (this->client_handler)->handleClient(Data, client);
  }
  close(socketfd);
}

int MySerialServer::stop() {
  this->to_run = false;
}
MySerialServer::MySerialServer(ClientHandler *cl) {
  this->client_handler = cl;
}

class MyTestClientHandler : public ClientHandler {
 private:
  Solver<std::string, std::string> *s;
  CacheManager<std::string, std::string> *cache_manager;
 public:
  MyTestClientHandler(Solver<std::string, std::string> *sol, CacheManager<std::string, std::string> *manger);
  void handleClient(std::string in, int out);
};

MyTestClientHandler::MyTestClientHandler(Solver<std::string, std::string> *sol,
                                         CacheManager<std::string, std::string> *manger) {
  this->cache_manager = manger;
  this->s = sol;
}

void MyTestClientHandler::handleClient(std::string in, int out) {
  while (in.compare("end")) {

    std::string answer;
    if (this->cache_manager->is_in_cache(in)) {
      answer = cache_manager->load(in);
      write(out, answer.c_str(), answer.length());
    }
    answer = s->solve(in);
    this->cache_manager->save(in, answer);
    write(out, answer.c_str(), answer.length());
    char buffer[2048] = {0};
    read(out, buffer, 1024);
    in = buffer;
  }
}

class MyClientHandler : public ClientHandler {
 private:
  MatrixSolver *s;
  CacheManager<std::string, std::string> *cache_manager;
 public:
  MyClientHandler(MatrixSolver *sol, CacheManager<std::string, std::string> *manger);
  void handleClient(std::string in, int out);
};

MyClientHandler::MyClientHandler(MatrixSolver *sol, CacheManager<std::string, std::string> *manger) {
  this->cache_manager = manger;
  this->s = sol;
}
void MyClientHandler::handleClient(std::string in, int out) {
  std::vector<double> input;
  int count_colms = 0, count_rows = 0;
  std::string answer;
  bool first_raw = true;

  if (in.find("end") == std::string::npos) {
    //this is a long string with end in the end
    char *dup = strdup(in.c_str());
    char **save_big = new char *;
    char **save = new char *;
    char *big_token = strtok_r(dup, "\r\n", save_big);

    while (big_token == NULL || strcmp(big_token, "end") != 0) {
      if (big_token == NULL) {
        char buffer[2048] = {0};
        read(out, buffer, 2048);
        in = buffer;
        dup = strdup(in.c_str());
        big_token = strtok_r(dup, "\r\n", save_big);
      }

      char *token = strtok_r(big_token, ",", save);
      while (token != NULL) {
        if (first_raw) { count_colms++; }

        input.push_back(atoi(token));
        token = strtok_r(NULL, " ,", save);
      }
      first_raw = false;
      count_rows++;
      big_token = strtok_r(NULL, "\r\n", save_big);
    }
    count_rows -= 2;
    delete save_big;
    delete save;
  } else {
    //this is a short string send again and again till end
    while (in.find("end") == std::string::npos) {
      count_rows++;
      char *dup = strdup(in.c_str());
      char **save = new char *;
      char *token = strtok_r(dup, ", \r\n", save);
      while (token != NULL) {
        if (first_raw) { count_colms++; }

        input.push_back(atoi(token));
        token = strtok_r(NULL, " ,\r\n", save);
      }
      free(dup);
      first_raw = false;
      char buffer[2048] = {0};
      read(out, buffer, 2048);
      in = buffer;
    }
  }//end of else
  count_rows -= 2;
  auto y = input.back();
  input.pop_back();
  auto x = input.back();

  input.pop_back();
  Point end(x, y);

  y = input.back();
  input.pop_back();
  x = input.back();
  input.pop_back();
  Point start(x, y);

  s->set_start_end(start, end);
  Matrix<double> mat(count_rows, count_colms, input);
  std::string string_Mat = to_string(mat);
  string_Mat += to_string(start) + to_string(end);

  std::mutex mute;
  //while (!mute.try_lock());
  if (this->cache_manager->is_in_cache(string_Mat)) {
    answer = cache_manager->load(string_Mat);
    mute.unlock();
    write(out, answer.c_str(), answer.length());
    return;
  }
  //mute.unlock();

  answer = s->solve(mat);
  //bool check = mute.try_lock();
  //while (check == false) {
  // check = mute.try_lock();
  //}
  this->cache_manager->save(string_Mat, answer);
  //mute.unlock();
  write(out, answer.c_str(), answer.length());
}
}
int boot::Main::main(int argc, char *argv[]) {
  FileCacheManager cache_manager(5);
  MatrixSolver *solver = new MatrixSolver();

  //ReversSolver solver;
  //server_side::MyTestClientHandler client_handler(&solver, &cache_manager);

  server_side::MyClientHandler client_handler(solver, &cache_manager);
  server_side::MyParalelServer server(&client_handler);

  server.open(5600, &client_handler);
  while (server.is_running()) {
    sleep(2);
  }
  delete solver;
}
