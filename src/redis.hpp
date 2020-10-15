#ifndef REDIS_H_
#define REDIS_H_

#include <acl_cpp/lib_acl.hpp>
#include <cstdlib>
#include <iostream>
#include <string>

#include "config.hpp"

void redis_init();
void insert_string(std::string key, std::string value);
std::string select_string(std::string key);

#endif
