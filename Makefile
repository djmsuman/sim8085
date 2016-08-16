OBJS = ram.o cpu.o hexcode_parser.o reploop.o main.o
CC = g++
DEBUG = -g -Wno-unused-parameter
CFLAGS = -Os $(DEBUG) -W -Wall -std=c++11 -c
LFLAGS = -Wall -Os
TARGET = -o sim8085
BOOKMARKEDFLAGS =  -Wpointer-arith -Wno-unused-parameter -Werror 

default:	build copybin

clean:
	rm -f *.o sim8085
	cd tests && make -f Makefile clean
	

build: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) $(TARGET)

copybin: build
	cp sim8085 ../bin/sim8085

cpu.o: cpu.cpp ram.cpp core.h datatypes.h
	$(CC) $(CFLAGS) cpu.cpp

ram.o: ram.cpp core.h datatypes.h
	$(CC) $(CFLAGS) ram.cpp

reploop.o: reploop.cpp cpu.cpp ram.cpp core.h datatypes.h
	$(CC) $(CFLAGS) reploop.cpp

hexcode_parser.o: hexcode_parser.cpp cpu.cpp ram.cpp core.h datatypes.h
	$(CC) $(CFLAGS) hexcode_parser.cpp

main.o: *.cpp *.h
	$(CC) $(CFLAGS) main.cpp

test: 
	cd tests && make -f Makefile
	cd tests && echo "Running tests"
	cd tests && ./test
