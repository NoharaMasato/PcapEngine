#ifndef PACKET_H_
#define PACKET_H_

#include <netinet/in.h>

class Packet{
public:
  // packet general
  int pkt_len;
  const u_char* data_buffer;
  int eth_header_start,ip_header_start,tcp_header_start;

  // ip attr
  struct in_addr srcip,dstip;
  u_char tcp_proto, ip_version;

  // tcp attr
  unsigned short srcport,dstport;
  
  Packet(const u_char* packet,int len,int ip_hdr_start);
  void print_packet();

  void print_row_data();
};

#endif 