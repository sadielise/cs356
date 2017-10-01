FILES = main.cpp BlockCipher.cpp StreamCipher.cpp
CC = g++
CFLAGS = -Wall

pa1: BlockCipher.o StreamCipher.o main.o
	$(CC) $(CFLAGS) -g -I. $(FILES) -o pa1

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

BlockCipher.o: BlockCipher.cpp BlockCipher.h
	$(CC) $(CFLAGS) -c BlockCipher.cpp

StreamCipher.o: StreamCipher.cpp StreamCipher.h
	$(CC) $(CFLAGS) -c StreamCipher.cpp

clean:
	-rm -f pa1 *.o
