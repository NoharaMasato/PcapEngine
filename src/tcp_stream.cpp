#include "tcp_stream.hpp"

void tcp_stream::add_packet_to_stream(Packet *pkt) {
  contents.push_back(pkt->l7_content());
}

void tcp_stream::print_stream() {
  int packet_cnt = int(contents.size());
  std::cout << "\n\n==stream content start==\n";
  for (int i(0); i < packet_cnt; i++) {
    std::cout << contents[i] << " ";
  }
  std::cout << "\n\n==stream content end==\n";
  std::cout << std::endl;
}
