#ifndef TCP_STREAM_H
#define TCP_STREAM_H

#include <netinet/in.h>

#include <vector>

#include "packet.hpp"

class tcp_stream {
  std::vector<const u_char *> contents;

 public:
  void add_packet_to_stream(Packet *pkt);
  void print_stream();
};

#endif