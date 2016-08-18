CC=g++
CFLAGS=-Wall -std=c++11 -Iinclude -Ilibtcod-1.5.1/include
override LIBS=-Llibtcod-1.5.1 -ltcod -ltcodxx -Wl,-rpath=libtcod-1.5.1
GAME=incarnate

SRCS=$(wildcard src/*.cpp)
INCL=$(wildcard include/*.h)
OBJS=$(patsubst src/%.cpp,build/%.o,$(SRCS))
BITS=$(shell getconf LONG_BIT)

.PHONY: all clean default
default: setup $(GAME)
all: default

setup:	
	mkdir -p build;
	if [ ! -d libtcod-1.5.1 ]; then\
		if [ -f libtcod-1.5.1.tar.gz ]; then gunzip libtcod-1.5.1.tar.gz; fi;\
		tar xf libtcod-1.5.1.tar;\
		cd libtcod-1.5.1 &&\
		if [ $(BITS) -eq 64 ]; then echo "Making 64 bit" && make -f makefiles/makefile-linux64 clean all; else echo "Making 32 bit" && make -f makefiles/makefile-linux clean all; fi;\
		cd ..;\
		if [ ! -f terminal.png ]; then cp libtcod-1.5.1/terminal.png terminal.png; fi;\
	fi

build/%.o: src/%.cpp $(INCL)
	$(CC) $(CFLAGS) -c $< -o $@ 

$(GAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(GAME) $(LIBS)

clean:
	@rm -f build/*.o
	@rm -f $(GAME)
