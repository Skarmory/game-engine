CC=g++
CFLAGS=-Wall -std=c++11 -pthread -Iinclude -ISFML/include
override LIBS=-LSFML/lib -libsfml-graphics -libsfml-system -libsfml-window -Wl,-rpath=SFML/lib
GAME=incarnate

SRCS=$(wildcard src/*.cpp)
INCL=$(wildcard include/*.h)
OBJS=$(patsubst src/%.cpp,build/%.o,$(SRCS))
BITS=$(shell getconf LONG_BIT)

.PHONY: all clean default setup
default: $(GAME)
all: setup $(GAME)

setup:	
	mkdir -p build;\

build/%.o: src/%.cpp $(INCL)
	$(CC) $(CFLAGS) -c $< -o $@ 

$(GAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(GAME) $(LIBS)

clean:
	@rm -f build/*.o
	@rm -f $(GAME)
