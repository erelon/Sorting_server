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
  std::hash<std::string> hasher;
  std::mutex mutex;
  while(!mutex.try_lock());
  this->insert(std::to_string(hasher(q)), a);
  mutex.unlock();
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

  std::hash<std::string> hasher;

  std::fstream stream;
  std::string npath(cache_path + std::to_string(cache_num) + std::to_string(hasher(to_search)));
  std::mutex mutex;
  while(!mutex.try_lock());
  //checking if the key was created once:
  FILE *check = fopen(npath.c_str(), "rb");
  mutex.unlock();
  return check != nullptr;
}

std::string FileCacheManager::load(std::string key) {
  std::hash<std::string> hasher;
  //if the key is in the cache- return, else- search in filesystem
  if (hash.find(std::to_string(hasher(key))) != hash.end()) {
    LRU->remove(std::to_string(hasher(key)));
    LRU->push_front(std::to_string(hasher(key)));
    return hash[std::to_string(hasher(key))];
  } else {
    std::fstream stream;
    std::string npath(cache_path + std::to_string(cache_num) + std::to_string(hasher(key)));
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
      t += temp + " ";
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
    hash[std::to_string(hasher(key))] = t;
    LRU->push_front(std::to_string(hasher(key)));
    return hash[std::to_string(hasher(key))];
  }
}