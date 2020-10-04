CC := /usr/bin/g++

SRC_DIR := src
OBJ_DIR := obj
DEP_DIR := deps

# :=は即時評価, =は遅延評価
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
HEADERS := $(wildcard $(SRC_DIR)/*.h)
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
DEPS := $(SRCS:$(SRC_DIR)/%.cpp=$(DEP_DIR)/%.d)

CPPFLAGS := -c -std=c++17

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

# 依存関係ファイルの作成(sedにより、一行目の先頭にobj/という文字を追加している)
$(DEP_DIR)/%.d: $(SRC_DIR)/%.cpp $(HEADERS)
	${CC} -MM $< | sed -e 's/^$*/$(OBJ_DIR)\/$*/g' > $(DEP_DIR)/$*.d

# オブジェクトファイルの依存関係を上書きする
-include $(DEP_DIR)/${DEPS}

.PHONY: clean
clean:
	rm $(OBJ_DIR)/*.o $(DEP_DIR)/*.d pcap
