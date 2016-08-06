CC=g++
override CFLAGS+=-Wall -std=c++11 -lncurses
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
	$(CC) $(CFLAGS) $(OBJS) -o $(GAME)

clean:
	@rm -f build/*.o
	@rm -f $(GAME)
