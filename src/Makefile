CC=g++
CFLAGS=-std=c++14 -g -Wall -pedantic

client: main.cpp
	$(CC) $(CFLAGS)  client.cpp crc.cpp getopt.cpp errors.cpp main.cpp -o client
clean:
	rm -f *.o *.out client
