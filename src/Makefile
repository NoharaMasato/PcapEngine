main: packet.o main.o
	g++ -Wall main.o packet.o -lpcap -o pcap

main.o:
	g++ -Wall main.cpp -c

packet.o: 
	g++ -Wall packet.cpp -c

clean:
	rm *.o && rm pcap