CC = g++
DEBUG = -g
CFLAGS = -W -Wall -Wpointer-arith -Wno-unused-parameter -Werror -std=c++11 -c
LFLAGS = -Wall
TARGET = -o test
OBJS = unions.o dssize.o test.o

default:	$(OBJS)
	$(CC) $(OBJS) $(TARGET)

clean:
	rm -f *.o test

unions.o:	unions.cpp ../core.h
	$(CC) $(CFLAGS) unions.cpp

dssize.o:	dssize.cpp ../*.h
	$(CC) $(CFLAGS) dssize.cpp

test.o:	test.cpp
	$(CC) $(CFLAGS) test.cpp
