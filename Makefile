CC=/usr/bin/g++

SRC_DIR=src
OBJ_DIR=obj

SRCS=$(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

CPPFLAGS=-c -std=c++17

# デフォルトのターゲット指定
.DEFAULT_GOAL := dev

.PHONY: release
release: clean #はじめに全て消す
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
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CPPFLAGS) $< -o $@

.PHONY: clean
clean:
	rm $(OBJ_DIR)/*.o && rm pcap

# 依存関係(gcc -MM *.cppで出力)
obj/ipv4.o: src/ipv4.cpp src/ipv4.hpp
obj/main.o: src/main.cpp src/config.hpp src/eth_device.hpp src/packet.hpp src/tcp_stream.hpp
obj/packet.o: src/packet.cpp src/packet.hpp
obj/tcp_stream.o: src/tcp_stream.cpp src/tcp_stream.hpp src/packet.hpp
