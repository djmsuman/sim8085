CC = g++
DEBUG = -g
CFLAGS = -W -Wall -Wpointer-arith -Wno-unused-parameter -Werror -std=c++11 -c
LFLAGS = -Wall
TARGET = -o ./build/bin/test
OBJTARGETDIR = ./build/obj/
OBJSTODIR = -o $(OBJTARGETDIR)
OBJSFROMDIR = $(OBJTARGETDIR)unions.o $(OBJTARGETDIR)dssize.o $(OBJTARGETDIR)test.o
OBJS = unions.o dssize.o test.o

deafult: mkbuilddir testbuild

testbuild: $(OBJS)
	$(CC) $(OBJSFROMDIR) $(TARGET)

mkbuilddir:
	mkdir -p build/obj build/bin

cleanobj:
	rm -f build/obj/*

unions.o: ./cases/unions.cpp ../src/libs/core.h
	$(CC) $(CFLAGS) ./cases/unions.cpp $(OBJSTODIR)unions.o

dssize.o: ./cases/dssize.cpp ../src/libs/*.h
	$(CC) $(CFLAGS) ./cases/dssize.cpp $(OBJSTODIR)dssize.o

test.o:	test.cpp
	$(CC) $(CFLAGS) test.cpp $(OBJSTODIR)test.o

clean:
	rm -rf ./build
