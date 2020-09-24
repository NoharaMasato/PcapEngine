#include <pcap.h>

#include <iostream>
#include <string>

#include "eth_device.hpp"
#include "packet.hpp"

eth_device *DEVICE;

void my_callback(u_char *useless, const struct pcap_pkthdr *pkthdr,
                 const u_char *packet) {
  int ip_header_start = 4;
  if (DEVICE->is_ethernet_device()) ip_header_start += 10;
  // std::cout << (packet[ip_header_start] >> 4) << std::endl;

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
    eth_device dev = (std::string)argv[1];
    DEVICE = &dev;
  } else {
    pcap_if_t *interfaces, *temp;
    if (pcap_findalldevs(&interfaces, errbuf) == -1) {
      printf("\nerror in pcap findall devs");
      return -1;
    }
    for (temp = interfaces; temp; temp = temp->next) {
      eth_device dev = (std::string)(temp->name);
      if (dev.is_ethernet_device()) {
        DEVICE = &dev;
      }
    }
    if (DEVICE == NULL) {
      std::cout << "no ethernet network interface\n";
      return 1;
    }
  }
  std::cout << "device:" << *DEVICE << std::endl;

  pcap_handle = pcap_open_live(
      (DEVICE->get_device_name()).c_str(), 4096, 1, 10,
      errbuf);  // device, snapshot length, promiscas or not, errbuf

  if (pcap_handle == NULL) {
    printf("pcap_open_live(): %s\n", errbuf);
    exit(1);
  }

  pcap_loop(pcap_handle, 1000, my_callback, NULL);

  pcap_close(pcap_handle);
  return 0;
}
