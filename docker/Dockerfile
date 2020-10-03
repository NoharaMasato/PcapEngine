FROM ubuntu:latest as build-stage

WORKDIR /usr/src/pcap_app

RUN apt-get -y update && apt-get -y install libpcap-dev make g++

COPY . /usr/src/pcap_app
RUN make

FROM ubuntu:latest as run-stage
WORKDIR /usr/src/pcap_app

RUN apt-get -y update && apt-get -y install libpcap-dev iproute2

COPY --from=build-stage /usr/src/pcap_app/pcap .

CMD ["./pcap", "eth0"]
