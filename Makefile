CC=g++
CFLAGS=-Wall -std=c++11
override HEADERS+=-lncurses
GAME=incarnate

SRCS=$(wildcard src/*.cpp)
INCL=$(wildcard include/*.h)
OBJS=$(patsubst src/%.cpp,build/%.o,$(SRCS))

.PHONY: all clean default
default: setup $(GAME)
all: default

setup:	
	mkdir -p build

build/%.o: src/%.cpp $(INCL)
	$(CC) $(CFLAGS) -I include -c $< -o $@ 

$(GAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(GAME) $(HEADERS)

clean:
	@rm -f build/*.o
	@rm -f $(GAME)
