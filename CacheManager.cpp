//
// Created by erelon on 1/14/20.
//

#include "CacheManager.h"

//number of cache created
int CACHE_NUM = 0;

FileCacheManager::FileCacheManager(int cap) {
  this->capacity = cap;
  LRU = new std::list<std::string>;
  this->cache_num = CACHE_NUM++;
  cache_path = "./";
}
FileCacheManager::~FileCacheManager() {
  delete LRU;
}

void FileCacheManager::save(std::string q, std::string a) {
  std::string key;
  //craete a smart key for the object
  this->insert(q, a);
}

void FileCacheManager::insert(std::string key, std::string obj) {
  auto got = hash.find(key);
  if (got != hash.end()) {
    //we need to do replacment
    std::string npath(cache_path + std::to_string(cache_num) + key);
    remove(npath.c_str());
  } else {
    if (capacity > 0) {
      capacity--;
    } else {
      //we need to remove one old hash item
      hash.erase(LRU->back());
      LRU->pop_back();
    }
  }
  hash[key] = obj;
  std::fstream stream;
  std::string npath(cache_path + std::to_string(cache_num) + key);
  stream.open(npath.c_str(), std::ios::app);
  if (!stream) {
    throw "file error";
  }
  auto itr = hash.find(key);
  stream << itr->second << std::endl;
  stream.close();
  LRU->remove(key);
  LRU->push_front(key);
}

bool FileCacheManager::is_in_cache(std::string to_search) {
  if (hash.find(to_search) != hash.end())
    return true;

  std::fstream stream;
  std::string npath(cache_path + std::to_string(cache_num) + to_search);
  //checking if the key was created once:
  FILE *check = fopen(npath.c_str(), "rb");
  if (check == nullptr) {
    //fclose(check);
    return false;
  }
  return true;
}

std::string FileCacheManager::load(std::string key) {
  //if the key is in the cache- return, else- search in filesystem
  if (hash.find(key) != hash.end()) {
    LRU->remove(key);
    LRU->push_front(key);
    return hash[key];
  } else {
    std::fstream stream;
    std::string npath(cache_path + std::to_string(cache_num) + key);
    //checking if the key was created once:
    FILE *check = fopen(npath.c_str(), "rb");
    if (check == nullptr)
      throw "en  error";
    fclose(check);
    stream.open(npath.c_str(), std::ios::in);
    //error control
    if (!stream || stream.eof())
      throw "file error";
    std::string t = "", temp;
    stream >> temp;
    while (stream) {
      t += temp +" ";
      stream >> temp;
    }
    t.pop_back();
    stream.close();
    if (capacity > 0) {
      capacity--;
    } else {
      //we need to remove one old hash item
      hash.erase(LRU->back());
      LRU->pop_back();
    }
    hash[key] = t;
    LRU->push_front(key);
    return hash[key];
  }
}