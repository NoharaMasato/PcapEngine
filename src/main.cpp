#include "packet.hpp"

#include <pcap.h>

#include <iostream>
#include <string>

char *device;

void my_callback(u_char *useless, const struct pcap_pkthdr *pkthdr,
                 const u_char *packet) {
  int ip_header_start = 4;
  if (((std::string)(device)).substr(0, 3) == "eth") ip_header_start += 10;
  std::cout << (packet[ip_header_start] >> 4) << std::endl;

  if ((packet[ip_header_start] >> 4) == 4) {
    Packet pkt(packet, pkthdr->len, ip_header_start);
    pkt.print_packet();
  } else {
    std::cout << "not ip v4 packet" << std::endl;
  }
}

int main(int argc, char *argv[]) {
  std::cout << "[pcap engine start]" << std::endl;

  char errbuf[PCAP_ERRBUF_SIZE];
  pcap_t *pcap_handle;

  if (argc == 2) {
    device = argv[1];
  } else {
    pcap_if_t *interfaces, *temp;
    if (pcap_findalldevs(&interfaces, errbuf) == -1) {
      printf("\nerror in pcap findall devs");
      return -1;
    }
    for (temp = interfaces; temp; temp = temp->next) {
      std::cout << temp->name << std::endl;
      if (((std::string)(temp->name)).substr(0, 3) == "eth") {
        device = temp->name;
      }
    }
    if (device == NULL) {
      std::cout << "no ethernet network interface\n";
      return 1;
    }
  }
  std::cout << "device:" << device << std::endl;

  pcap_handle = pcap_open_live(
      device, 4096, 1, 10,
      errbuf);  // device, snapshot length, promiscas or not, errbuf

  if (pcap_handle == NULL) {
    printf("pcap_open_live(): %s\n", errbuf);
    exit(1);
  }

  pcap_loop(pcap_handle, 1000, my_callback, NULL);

  pcap_close(pcap_handle);
  return 0;
}
