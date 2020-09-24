#include "eth_device.hpp"

#include <iostream>

eth_device::eth_device(std::string name) {
  device_name = name;
  if (name.substr(0, 3) == "eth" || name.substr(0, 3) == "enp") {
    device_type = ETHERNET;
  } else if (name.substr(0, 2) == "lo") {
    device_type = LOOPBACK;
  } else {
    device_type = NONE;
  }
}

bool eth_device::is_ethernet_device() { return device_type == ETHERNET; }

std::string eth_device::get_device_name(){
  return device_name;
}

std::ostream& operator<<(std::ostream& os, const eth_device& a) {
  os << "device name [" << a.device_name << "]" << std::endl;
  return os;
}
