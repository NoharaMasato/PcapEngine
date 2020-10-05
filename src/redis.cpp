#include "redis.hpp"

void insert_string(std::string key, std::string value) {
  acl::redis_string cmd(&conn);
  if (cmd.set(key.c_str(), value.c_str()) == false) {
    std::cerr << "redis set error" << std::endl;
    exit(1);
  }
  value.clear();
  cmd.clear();
}

std::string select_string(std::string key) { return ""; }