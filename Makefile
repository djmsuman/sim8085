OBJS = ram.o cpu.o hexcode_parser.o reploop.o main.o
OBJSFROMDIR = $(OBJTARGETDIR)ram.o $(OBJTARGETDIR)cpu.o $(OBJTARGETDIR)hexcode_parser.o $(OBJTARGETDIR)reploop.o $(OBJTARGETDIR)main.o
OBJSTODIR = -o $(OBJTARGETDIR)
CC = g++
DEBUG = -g -Wno-unused-parameter
CFLAGS = -Os $(DEBUG) -W -Wall -std=c++11 -c
LFLAGS = -Wall -Os
TARGET = -o ./build/bin/sim8085
OBJTARGETDIR = ./build/obj/
BOOKMARKEDFLAGS =  -Wpointer-arith -Wno-unused-parameter -Werror 

default: clean mkbuilddir build

mkbuilddir:
	mkdir -p build/obj build/bin

clean:
	rm -rf ./build/
	cd tests && make -f Makefile clean

build: $(OBJS)
	$(CC) $(LFLAGS) $(OBJSFROMDIR) $(TARGET)

cleanobj:
	rm -f build/obj/* && && make -f Makefile cleanobj

exec:
	./build/bin/sim8085

cpu.o: src/devices/cpu.cpp src/devices/ram.cpp src/libs/core.h src/libs/datatypes.h
	$(CC) $(CFLAGS) src/devices/cpu.cpp $(OBJSTODIR)cpu.o

ram.o: src/devices/ram.cpp src/libs/core.h src/libs/datatypes.h
	$(CC) $(CFLAGS) src/devices/ram.cpp $(OBJSTODIR)ram.o

reploop.o: src/reploop.cpp src/devices/cpu.cpp src/devices/ram.cpp src/libs/core.h src/libs/datatypes.h
	$(CC) $(CFLAGS) src/reploop.cpp $(OBJSTODIR)reploop.o

hexcode_parser.o: src/hexcode_parser.cpp src/devices/cpu.cpp src/devices/ram.cpp src/libs/core.h src/libs/datatypes.h
	$(CC) $(CFLAGS) src/hexcode_parser.cpp $(OBJSTODIR)hexcode_parser.o

main.o: src/*.cpp src/devices/*.cpp src/libs/*.h
	$(CC) $(CFLAGS) src/main.cpp $(OBJSTODIR)main.o

test: 
	cd tests && make -f Makefile
	cd tests && echo "Running tests"
	cd tests && ./build/bin/test
