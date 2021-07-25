# PcapEngine

## dependencies
libpcap
redis-server
redis-client(https://github.com/acl-dev/acl/tree/master/lib_acl_cpp/samples/redis)

## build
```bash
make
```

## run with docker
```
docker-compose up -d
```

## 注意点
- redisを使うとSegmentation Faultが起きがち
- pcap-engineのソースコードを変更すると、dockerの立ち上げ直しだけではなく、buildも必要(docker-compose build packet-capture-engin)
- port番号やipヘッダーの長さを正しく読み取るにはntohs()関数を通すことによってhost側の表現に直さないといけない
