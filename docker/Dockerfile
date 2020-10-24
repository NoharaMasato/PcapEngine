FROM ubuntu:latest as build-stage

WORKDIR /usr/src/pcap_app

RUN apt-get -y update && apt-get -y install libpcap-dev make g++ git zlib1g-dev
RUN mkdir -p ~/lib/acl && git clone https://github.com/acl-dev/acl.git ~/lib/acl/
RUN cd ~/lib/acl/lib_acl && make && \
  cd ~/lib/acl/lib_protocol && make && \
  cd ~/lib/acl/lib_acl_cpp && make

COPY . /usr/src/pcap_app
RUN make

FROM ubuntu:latest as run-stage
WORKDIR /usr/src/pcap_app

RUN apt-get -y update && apt-get -y install libpcap-dev iproute2 iputils-ping netcat tcpdump

# packet転送, routingの設定
# RUN /sbin/route add -host 192.168.0.2 eth0
# RUN /sbin/route add -host 192.168.1.2 eth1

COPY --from=build-stage /usr/src/pcap_app/pcap .

# CMD ["./pcap", "eth0"]
CMD ["nc","-l","8080"]
