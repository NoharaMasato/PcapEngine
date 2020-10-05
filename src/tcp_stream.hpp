#ifndef TCP_STREAM_H_
#define TCP_STREAM_H_

#include <netinet/in.h>

#include <iostream>
#include <vector>

#include "packet.hpp"

class tcp_stream {
  std::vector<const u_char *> contents;

 public:
  void add_packet_to_stream(Packet *pkt);
  void print_stream();
};

#endif
