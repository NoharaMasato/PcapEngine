#include "packet.hpp"

#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>

#include <iostream>

Packet::Packet(const u_char *packet, int len, int ip_hdr_start) {
  struct ip *ip_header;
  struct tcphdr *tcp_header;
  struct udphdr *udp_header;

  data_buffer = packet;
  pkt_len = len;

  ip_header_start = ip_hdr_start;
  tcp_header_start = ip_header_start + 20;

  // parse ip header
  ip_header = (struct ip *)(packet + ip_header_start);
  srcip = ip_header->ip_src;
  dstip = ip_header->ip_dst;
  tcp_proto = ip_header->ip_p;
  ip_version = ip_header->ip_v;

  // parse tcp header
  if (tcp_proto == IPPROTO_TCP) {
    tcp_header = (struct tcphdr *)(packet + tcp_header_start);
    srcport = tcp_header->th_sport;
    dstport = tcp_header->th_dport;
  } else if (tcp_proto == IPPROTO_UDP) {
    udp_header = (struct udphdr *)(packet + tcp_header_start);
    srcport = udp_header->uh_sport;
    dstport = udp_header->uh_dport;
  }
}

void Packet::print_packet() {
  if (tcp_proto == IPPROTO_TCP) {
    std::cout << "packet length:" << pkt_len << std::endl;
    for (int i(0); i < pkt_len;) {
      printf("%02x ", (int)(data_buffer[i]));
      i++;
      if (i % 16 == 0)
        std::cout << std::endl;
      else if (i % 8 == 0)
        std::cout << " ";
    }
    std::cout << "\n";
    std::cout << "src ip:" << inet_ntoa(srcip) << ","
              << "dst ip:" << inet_ntoa(dstip) << std::endl;
    std::cout << "src port:" << ntohs(srcport) << ","
              << "dst port:" << ntohs(dstport) << std::endl;
    std::cout << std::endl;
  }
}

void Packet::print_row_data() {
  for (int i(0); i < pkt_len;) {
    printf("%02x ", (int)(data_buffer[i]));
    i++;
    if (i % 16 == 0)
      std::cout << std::endl;
    else if (i % 8 == 0)
      std::cout << " ";
  }
  std::cout << "\n\n";
}
