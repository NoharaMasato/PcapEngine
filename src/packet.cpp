#include "packet.hpp"

bool five_tuple::operator==(const five_tuple &other) const {
  return (src_ip.s_addr == other.src_ip.s_addr &&
          dst_ip.s_addr == other.dst_ip.s_addr && src_port == other.src_port &&
          dst_port == other.dst_port && ip_version == other.ip_version);
}

std::string five_tuple::to_string() {
  std::string ret_val;
  return std::to_string(src_ip.s_addr) + std::to_string(dst_ip.s_addr) +
         std::to_string(src_port) + std::to_string(dst_port) + std::to_string(ip_version);
}

Packet::Packet(const u_char *packet, int len, int ip_hdr_start) {
  data_buffer = packet;
  pkt_len = len;

  // parse ethernet header
  ethernet_header = (struct ether_header *)packet;

  // parse ip header
  ip_header = (struct ip *)(packet + ip_hdr_start);

  // parse tcp header
  int tcp_header_start = ip_hdr_start + IP_HEADER_SIZE;
  if (ip_header->ip_p == IPPROTO_TCP) {
    tcp_header = (struct tcphdr *)(packet + tcp_header_start);
    payload =
        (const u_char *)((unsigned char *)tcp_header + (tcp_header->doff * 4));
  } else if (ip_header->ip_p == IPPROTO_UDP) {
    udp_header = (struct udphdr *)(packet + tcp_header_start);
    payload = (const u_char *)((unsigned char *)udp_header + UDP_HEADER_SIZE);
  }
}

struct ether_addr *Packet::src_ether_addr() {
  return (struct ether_addr *)&(ethernet_header->ether_shost);
}
struct ether_addr *Packet::dst_ether_addr() {
  return (struct ether_addr *)&(ethernet_header->ether_dhost);
}

in_addr Packet::src_ip_addr() { return ip_header->ip_src; }
in_addr Packet::dst_ip_addr() { return ip_header->ip_dst; }

unsigned int Packet::ip_version() { return ip_header->ip_v; }

unsigned short Packet::src_port() {
  if (ip_header->ip_p == IPPROTO_TCP)
    return tcp_header->th_sport;
  else if (ip_header->ip_p == IPPROTO_UDP)
    return udp_header->uh_sport;
  else
    return 0;
}

unsigned short Packet::dst_port() {
  if (ip_header->ip_p == IPPROTO_TCP)
    return tcp_header->th_dport;
  else if (ip_header->ip_p == IPPROTO_UDP)
    return udp_header->uh_dport;
  else
    return 0;
}

const u_char *Packet::l7_content() { return payload; }

five_tuple Packet::to_five_tuple() {
  return five_tuple{src_ip_addr(), dst_ip_addr(), ip_version(), src_port(),
                    dst_port()};
}

void Packet::print_meta_data() {
  if (ip_header->ip_p == IPPROTO_TCP) {
    std::cout << "\n\n=====packet start=====\n";
    std::cout << "packet length " << pkt_len << "\n"
              << "src mac       " << ether_ntoa(src_ether_addr()) << "\n"
              << "dst mac       " << ether_ntoa(dst_ether_addr()) << "\n"
              << "src ip        " << inet_ntoa(src_ip_addr()) << "\n"
              << "dst ip        " << inet_ntoa(dst_ip_addr()) << "\n"
              << "src port      " << ntohs(src_port()) << "\n"
              << "dst port      " << ntohs(dst_port()) << "\n"
              << "content       " << payload << "\n"
              << "=====packet end=======\n";
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
