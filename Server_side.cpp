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
  int client_socket = accept(socketfd, (struct sockaddr *) &address,
                             &clientAddrLen);

  if (client_socket == -1) {
    std::cerr << strerror(errno) << std::endl;
    return -1;
  }
}

namespace server_side {

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
  CacheManager<std::string,std::string> *cache_manager;
 public:
  MyTestClientHandler(Solver<std::string, std::string> *sol, CacheManager<std::string,std::string> *manger);
  void handleClient(std::string in, int out);
};

MyTestClientHandler::MyTestClientHandler(Solver<std::string, std::string> *sol, CacheManager<std::string,std::string> *manger) {
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
}

int boot::Main::main(int argc, char *argv[]) {
  FileCacheManager cache_manager(5);
  ReversSolver solver;
  server_side::MyTestClientHandler client_handler(&solver, &cache_manager);

  server_side::MySerialServer server(&client_handler);
  server.open(5600, &client_handler);
  while (true);
}
