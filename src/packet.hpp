#ifndef PACKET_H_
#define PACKET_H_

#include <arpa/inet.h>
#include <net/ethernet.h>
#include <netinet/ether.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>

#include <iostream>
#include <string>

const int ETHERNET_HEADER_SIZE = 10, IP_HEADER_SIZE = 20, UDP_HEADER_SIZE = 8;

struct five_tuple {
  in_addr src_ip, dst_ip;
  u_char ip_version;
  unsigned short src_port, dst_port;
  bool operator==(const five_tuple &other) const {
    return (src_ip.s_addr == other.src_ip.s_addr &&
            dst_ip.s_addr == other.dst_ip.s_addr &&
            src_port == other.src_port && dst_port == other.dst_port &&
            ip_version == other.ip_version);
  }
};

template <>
struct std::hash<five_tuple> {
  std::size_t operator()(const five_tuple &k) const {
    // return (size_t)((k.src_ip.s_addr | (k.dst_ip.s_addr << 32) |
    //                (k.src_port << 64) | (k.dst_port << 70)));
    return (size_t)(k.src_ip.s_addr ^ k.dst_ip.s_addr ^ k.src_port ^
                    k.dst_port);
  }
};

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

  // app layer
  const u_char *l7_content();

  // return five tuple
  five_tuple to_five_tuple();

  // print packet
  void print_meta_data();
  void print_row_data();
};

#endif
