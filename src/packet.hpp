#ifndef PACKET_H_
#define PACKET_H_

#include <netinet/in.h>

const int IP_HEADER_SIZE = 20;
const int UDP_HEADER_SIZE = 8;

class Packet {
  int pkt_len;
  const u_char *data_buffer, *payload;

  struct ether_header *ethernet_header;
  struct ip *ip_header;
  struct tcphdr *tcp_header;
  struct udphdr *udp_header;

 public:
  // constractor
  Packet(const u_char *packet, int len, int ip_hdr_start);

  // data link layer
  struct ether_addr *src_ether_addr(), *dst_ether_addr();

  // ip layer
  u_char ip_version();
  in_addr src_ip_addr(), dst_ip_addr();

  // transport layer
  unsigned short src_port(), dst_port();

  // print packet
  void print_meta_data();
  void print_row_data();
};

#endif