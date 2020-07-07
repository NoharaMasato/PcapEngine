FROM alpine:latest as build-stage

WORKDIR /usr/src/pcap_app

RUN apk update && apk add gcc make g++ libpcap-dev

COPY . /usr/src/pcap_app
RUN make

# FROM alpine:latest as run-stage
FROM python:3.7-alpine
WORKDIR /usr/src/pcap_app

RUN apk update && apk add --no-cache libstdc++ libpcap-dev py3-numpy
ENV PYTHONPATH /usr/lib/python3.7/site-packages

COPY --from=build-stage /usr/src/pcap_app/pcap .

CMD ["./pcap"]
