#ifndef PACKET_H_
#define PACKET_H_

#include <netinet/in.h>

class Packet {
  int pkt_len;
  const u_char *data_buffer;

  struct ip *ip_header;
  struct tcphdr *tcp_header;
  struct udphdr *udp_header;

 public:
  Packet(const u_char *packet, int len, int ip_hdr_start);

  u_char ip_version();

  void print_packet();
  void print_row_data();

  in_addr src_ip_addr();
  in_addr dst_ip_addr();

  unsigned short src_port(), dst_port();
};

#endif