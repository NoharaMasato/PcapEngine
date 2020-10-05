#ifndef REDIS_H_
#define REDIS_H_

#include <acl_cpp/lib_acl.hpp>
#include <iostream>
#include <string>

#include "config.hpp"

const char* redis_addr = "127.0.0.1:6379";
const int conn_timeout = 10, rw_timeout = 10;

acl::redis_client conn(redis_addr, conn_timeout, rw_timeout);

void insert_string(std::string key, std::string value);

std::string select_string(std::string key);

#endif