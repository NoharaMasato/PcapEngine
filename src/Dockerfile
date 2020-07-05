FROM alpine:latest as build-stage

WORKDIR /usr/src/pcap_app

RUN apk update && apk add --no-cache gcc make g++ libpcap-dev

COPY . /usr/src/pcap_app
RUN make

FROM alpine:latest as run-stage

WORKDIR /usr/src/pcap_app
RUN apk update && apk add --no-cache libstdc++ libpcap-dev

COPY --from=build-stage /usr/src/pcap_app/pcap .

CMD ["./pcap lo"]
