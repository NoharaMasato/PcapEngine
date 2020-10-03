CC=/usr/bin/g++
SRCS=packet.cpp ipv4.cpp eth_device.cpp tcp_stream.cpp main.cpp
OBJS=$(SRCS:.cpp=.o)
CPPFLAGS=-c -std=c++17

# デフォルトのターゲット指定
.DEFAULT_GOAL := dev

.PHONY: release
release: CPPFLAGS+=-O0 -DNDEBUG
release: EXE_FILE_NAME=release
release: build

.PHONY: dev
dev: CPPFLAGS+=-g -O3 -Wall -W
dev: EXE_FILE_NAME=pcap
dev: build

# オブジェクトファイルをリンクする
.PHONY: build
build: $(OBJS)
	$(CC) $(OBJS) -lpcap -o $(EXE_FILE_NAME)

# .cppから.oに変換する際のルールを指定(コンパイル)
# $<は依存するファイルの最初のもの
.cpp.o:
	$(CC) $(CPPFLAGS) $<

.PHONY: clean
clean:
	rm *.o && rm pcap

# 依存関係(gcc -MM *.cppで出力)
ipv4.o: ipv4.cpp ipv4.hpp
main.o: main.cpp config.hpp eth_device.hpp packet.hpp tcp_stream.hpp
packet.o: packet.cpp packet.hpp
tcp_stream.o: tcp_stream.cpp tcp_stream.hpp packet.hpp
