#include <bits/stdc++.h>
#include <iomanip>
#include <pcap.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/if_ether.h> /* includes net/ethernet.h */
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <netinet/tcp.h>

using namespace std;
char* device;

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
  
  Packet(const u_char* packet,int len,int ip_hdr_start){
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
    if(tcp_proto == IPPROTO_TCP){
      tcp_header = (struct tcphdr *)(packet + tcp_header_start);
      srcport = tcp_header->th_sport;
      dstport = tcp_header->th_dport;
    }else if(tcp_proto == IPPROTO_UDP){
      udp_header = (struct udphdr *)(packet + tcp_header_start);
      srcport = udp_header->uh_sport;
      dstport = udp_header->uh_dport;
    }
  }

  void print_packet(){
    if(tcp_proto == IPPROTO_TCP){
      cout << "packet length:" << pkt_len << endl;
      for(int i(0);i<pkt_len;){
        printf("%02x ",(int)(data_buffer[i]));
        i++;
        if(i%16==0) cout << endl;
        else if(i%8==0) cout << " ";
      }
      cout << "\n";
      cout << "src ip:" << inet_ntoa(srcip) << "," << "dst ip:" << inet_ntoa(dstip) << endl;
      cout << "src port:" << ntohs(srcport) << "," << "dst port:" << ntohs(dstport) << endl;
      cout << endl;
    }
  }
};

void print_row_data(const u_char* data_buffer, int pkt_len){
  for(int i(0);i<pkt_len;){
    printf("%02x ",(int)(data_buffer[i]));
    i++;
    if(i%16==0) cout << endl;
    else if(i%8==0) cout << " ";
  }
  cout << "\n\n";
}

void my_callback(u_char *useless,const struct pcap_pkthdr* pkthdr,const u_char* packet){
  int ip_header_start = 4;
  if(((string)(device)).substr(0,3) == "eth") ip_header_start += 10;
  cout << (packet[ip_header_start]>>4) << endl;
  // print_packet(packet,pkthdr->len);
  // print_row_data(packet,pkthdr->len);
  if((packet[ip_header_start]>>4) == 4){
    Packet pkt(packet,pkthdr->len,ip_header_start);
    pkt.print_packet();
  }else{
    cout << "not ip v4 packet" << endl;
  }
}

int main(int argc,char *argv[]){
  cout << "[pcap engine start]" << endl;

  char errbuf[PCAP_ERRBUF_SIZE];
  pcap_t *pcap_handle;
  const u_char *packet;
  if(argc == 2){
    device = argv[1];
  }else{
    pcap_if_t *interfaces,*temp;
    if(pcap_findalldevs(&interfaces,errbuf)==-1){
      printf("\nerror in pcap findall devs");
      return -1;   
    }
    for(temp=interfaces;temp;temp=temp->next){
      cout << temp->name << endl;
      if(((string)(temp->name)).substr(0,3) == "eth"){
        device = temp->name;
      }
    }
    if(device == NULL){
      cout << "no ethernet network interface\n";
      return 1;
    }
    //return 0;
    // device = pcap_lookupdev(errbuf);
  }
  cout << "device:" << device << endl;

  pcap_handle = pcap_open_live(device, 4096, 1, 10, errbuf); // device, snapshot length, promiscas or not, errbuf

  if(pcap_handle == NULL) {
      printf("pcap_open_live(): %s\n",errbuf);
      exit(1);
  }

  pcap_loop(pcap_handle,100,my_callback,NULL);

  pcap_close(pcap_handle);
  return 0;
}

