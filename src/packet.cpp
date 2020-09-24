#include "packet.hpp"

#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>

#include <iostream>

Packet::Packet(const u_char *packet, int len, int ip_hdr_start) {
  data_buffer = packet;
  pkt_len = len;

  int tcp_header_start = ip_hdr_start + 20;

  // parse ip header
  ip_header = (struct ip *)(packet + ip_hdr_start);

  // parse tcp header
  if (ip_header->ip_p == IPPROTO_TCP) {
    tcp_header = (struct tcphdr *)(packet + tcp_header_start);
  } else if (ip_header->ip_p == IPPROTO_UDP) {
    udp_header = (struct udphdr *)(packet + tcp_header_start);
  }
}

in_addr Packet::src_ip_addr() { return ip_header->ip_src; }

in_addr Packet::dst_ip_addr() { return ip_header->ip_dst; }

u_char Packet::ip_version() { return ip_header->ip_v; }

unsigned short Packet::src_port() {
  if (ip_header->ip_p == IPPROTO_TCP)
    return tcp_header->th_sport;
  else if (ip_header->ip_p == IPPROTO_UDP)
    return udp_header->uh_sport;
}

unsigned short Packet::dst_port() {
  if (ip_header->ip_p == IPPROTO_TCP)
    return tcp_header->th_dport;
  else if (ip_header->ip_p == IPPROTO_UDP)
    return udp_header->uh_dport;
}

void Packet::print_packet() {
  if (ip_header->ip_p == IPPROTO_TCP) {
    std::cout << "\n\n=====packet start=====";
    std::cout << "packet length:" << pkt_len << std::endl;
    std::cout << "src ip:" << inet_ntoa(src_ip_addr()) << ","
              << "dst ip:" << inet_ntoa(dst_ip_addr()) << std::endl;
    std::cout << "src port:" << ntohs(src_port()) << ","
              << "dst port:" << ntohs(dst_port()) << std::endl;
    std::cout << "====packet end====";
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
