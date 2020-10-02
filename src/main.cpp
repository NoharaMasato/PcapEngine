#include <pcap.h>
#include <unistd.h>

#include <chrono>
#include <iostream>
#include <string>
#include <unordered_map>

#include "config.hpp"
#include "eth_device.hpp"
#include "packet.hpp"
#include "tcp_stream.hpp"

eth_device *DEVICE;
std::unordered_map<five_tuple, tcp_stream> tcp_streams;  // hash table
long long int total_packet_size(0);

void my_callback(u_char *useless, const struct pcap_pkthdr *pkthdr,
                 const u_char *packet) {
#ifdef PRINT_DEBUG
  int ip_header_start = 4;
  if (DEVICE->is_ethernet_device()) ip_header_start += ETHERNET_HEADER_SIZE;

  if ((packet[ip_header_start] >> 4) == 4) {
    Packet pkt(packet, pkthdr->len, ip_header_start);
    pkt.print_meta_data();
    tcp_streams[pkt.to_five_tuple()].add_packet_to_stream(&pkt);
    tcp_streams[pkt.to_five_tuple()].print_stream();
  } else {
    std::cout << "not ip v4 packet" << std::endl;
  }
#endif

  total_packet_size += pkthdr->len;
}

int main(int argc, char *argv[]) {
  char errbuf[PCAP_ERRBUF_SIZE];
  pcap_t *pcap_handle;
  pcap_if_t *interfaces, *temp;
  struct pcap_stat stat;

  std::cout << "[pcap engine start]" << std::endl;
  if (argc == 2) {
    eth_device dev = (std::string)argv[1];
    DEVICE = &dev;
  } else {
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

  std::chrono::system_clock::time_point start, end;
  start = std::chrono::system_clock::now();

  pcap_loop(pcap_handle, (int)1e7, my_callback, NULL);

  //ここまでに受け取ったパケットの統計情報をstatに入れる
  pcap_stats(pcap_handle, &stat);

  end = std::chrono::system_clock::now();
  double time = static_cast<double>(
      std::chrono::duration_cast<std::chrono::microseconds>(end - start)
          .count() /
      1000.0);

  std::cout << "=====report====="
            << "\n"
            << "パケット処理量:" << total_packet_size / 1e9 << "[GB]\n"
            << "処理時間" << time << " [ms]\n"
            << "スループット" << total_packet_size / time / 1e6 << " [Gbps]\n"
            << "受け取ったパケット数" << stat.ps_recv << "\n"
            << "dropしたパケット数" << stat.ps_drop << "\n"
            << "ネットワークでdropしたパケット数" << stat.ps_ifdrop << "\n"
            << "================"
            << "\n";
  pcap_close(pcap_handle);
  return 0;
}
