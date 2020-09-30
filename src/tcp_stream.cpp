#include "tcp_stream.hpp"

#include <iostream>

#include "packet.hpp"

void tcp_stream::add_packet_to_stream(Packet *pkt) {
  contents.push_back(pkt->l7_content());
}

void tcp_stream::print_stream() {
  int packet_cnt = int(contents.size());
  for (int i(0); i < packet_cnt; i++) {
    std::cout << contents[i] << " ";
  }
  std::cout << std::endl;
}
