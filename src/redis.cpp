#include "redis.hpp"

acl::redis_client* conn;

void redis_init() {
  const char* redis_addr;
  if (getenv("REDIS_HOST") == NULL)
    redis_addr = "127.0.0.1:6379";
  else
    redis_addr = getenv("REDIS_HOST");
  const int conn_timeout = 10, rw_timeout = 10;
  acl::redis_client tmp_conn(redis_addr, conn_timeout, rw_timeout);
  conn = &tmp_conn;
}

void insert_string(std::string key, std::string value) {
  acl::redis_string cmd(conn);
  if (cmd.set(key.c_str(), value.c_str()) == false) {
    std::cerr << "redis set error" << std::endl;
    exit(1);
  }
  value.clear();
  cmd.clear();
}

std::string select_string(std::string key) {
  acl::redis_string cmd(conn);
  acl::string value;
  if (cmd.get(key.c_str(), value) == false) {
    std::cerr << "redis get key error" << std::endl;
    exit(1);
  }
  return value.c_str();
}
