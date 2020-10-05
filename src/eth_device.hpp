#ifndef ETH_DEVICE_H_
#define ETH_DEVICE_H_

#include <iostream>
#include <string>

enum ETHER_DEVICE_TYPE { LOOPBACK, ETHERNET, NONE };

class eth_device {
  std::string device_name;
  ETHER_DEVICE_TYPE device_type;

 public:
  eth_device(std::string name);
  bool is_ethernet_device();
  std::string get_device_name();
  friend std::ostream& operator<<(std::ostream& os, const eth_device& a);
};

#endif