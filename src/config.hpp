#ifndef CONFIG_H_
#define CONFIG_H_

// statistics
#define PRINT_DEBUG
#define MESURE_TIME

// redis
#define REDIS
// #define PRINT_STREAM

// 処理するパケットの個数(0は無限に処理する)
const int PACKET_CNT = (int)1e5;

#endif
