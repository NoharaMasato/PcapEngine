#ifndef TCP_STREAM_H
#define TCP_STREAM_H

#include <netinet/in.h>

#include <vector>

struct five_tuple {
  in_addr src_ip, dst_ip;
  u_char ip_version;
  unsigned short src_port, dst_port;
};

class tcp_stream {
  five_tuple key;
  std::vector<u_char*> contents;

 public:
  void add_packet_to_stream();
  void print_stream();
};

#endif