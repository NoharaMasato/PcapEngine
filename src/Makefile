CC=/usr/bin/g++
SRCS=packet.cpp ipv4.cpp eth_device.cpp tcp_stream.cpp main.cpp
OBJS=$(SRCS:.cpp=.o)
CPPFLAGS=-c -std=c++17

.PHONY: release
release: CPPFLAGS+=-O0 -DNDEBUG
release: build

.PHONY: dev
dev: CPPFLAGS+=-g -O3 -Wall -W
dev: build

# オブジェクトファイルをリンクする
.PHONY: build
build: $(OBJS)
	$(CC) $(OBJS) -lpcap -o pcap

# .cppから.oに変換する際のルールを指定(コンパイル)
.cpp.o:
	$(CC) $(CPPFLAGS) $<


.PHONY: clean
clean:
	rm *.o && rm pcap