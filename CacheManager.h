//
// Created by erelon on 1/14/20.
//

#ifndef SORTING_SERVER__CACHEMANAGER_H_
#define SORTING_SERVER__CACHEMANAGER_H_
#include "server_side.h"

template<class Problem, class Solution>
class CacheManager {
 public:
  bool virtual is_in_cache(Problem) = 0;
  Solution virtual load(Problem) = 0;
  void virtual save(Problem, Solution) = 0;
};

class FileCacheManager : public CacheManager<std::string, std::string> {
 private:
  std::string cache_path;
  std::unordered_map<std::string, std::string> hash;
  std::list<std::string> *LRU;
  int capacity;
  int cache_num;

  void save(std::string q, std::string a);
  std::string load(std::string key);
 public:
  FileCacheManager(int cap);
  ~FileCacheManager();
  void insert(std::string key, std::string obj);
  bool is_in_cache(std::string to_search);
};
#endif //SORTING_SERVER__CACHEMANAGER_H_
