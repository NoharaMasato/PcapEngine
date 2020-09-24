#include <iostream>
#include "ipv4.hpp"

int main(){
  ipv4 address(192,168,0,1);
  std::cout << address.to_string() << std::endl;
  std::cout << address << std::endl;
}