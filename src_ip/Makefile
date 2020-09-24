main: ipv4.o main.o
	g++ -Wall main.o ipv4.o -o main 
 
ipv4.o: ipv4.cpp
	g++ ipv4.cpp -c

clean:
	rm *.o && rm main