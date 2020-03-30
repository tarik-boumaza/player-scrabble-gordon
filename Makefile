

BIN_DIR = bin
OBJ_DIR = obj
SRC_DIR = src

CC = g++
LD = g++

CC_FLAGS = -g -Werror -Wextra -std=c++11 -pedantic -c
LD_FLAGS = -g -Werror -Wextra -std=c++11 -pedantic

CLEAN_FLAGS = -v -r -f

all : main


main: bin/main

test_board : bin/test_board


bin/main : obj/main.o obj/bonus.o obj/spot.o obj/board.o obj/bag.o obj/player.o obj/map.o obj/gaddag.o obj/game.o obj/scrabbleTXT.o
	$(LD) $(LD_FLAGS) $^ -o $@

bin/test_board : obj/test_board.o obj/bonus.o obj/bag.o obj/player.o obj/gaddag.o obj/map.o obj/spot.o obj/game.o obj/board.o
	$(LD) $(LD_FLAGS) $^ -o $@


obj/main.o : src/main.cpp src/scrabbleTXT.hpp
	$(CC) $(CC_FLAGS) $< -o $@

obj/test_board.o : src/test_board.cpp src/game.hpp
	$(CC) $(CC_FLAGS) $< -o $@

obj/scrabbleTXT.o : src/scrabbleTXT.cpp src/scrabbleTXT.hpp src/game.hpp src/gaddag.hpp src/bonus.hpp src/bag.hpp src/player.hpp src/board.hpp src/spot.hpp src/map.hpp
	$(CC) $(CC_FLAGS) $< -o $@

obj/game.o : src/game.cpp src/game.hpp src/gaddag.hpp src/bonus.hpp src/bag.hpp src/player.hpp src/board.hpp src/spot.hpp src/map.hpp
	$(CC) $(CC_FLAGS) $< -o $@

obj/bag.o : src/bag.cpp src/bag.hpp
	$(CC) $(CC_FLAGS) $< -o $@

obj/player.o : src/player.cpp src/player.hpp
	$(CC) $(CC_FLAGS) $< -o $@

obj/board.o : src/board.cpp src/board.hpp src/spot.hpp
	$(CC) $(CC_FLAGS) $< -o $@

obj/spot.o : src/spot.cpp src/spot.hpp src/bonus.hpp
	$(CC) $(CC_FLAGS) $< -o $@

obj/bonus.o : src/bonus.cpp src/bonus.hpp
	$(CC) $(CC_FLAGS) $< -o $@

obj/gaddag.o : src/gaddag.cpp src/gaddag.hpp src/map.hpp
	$(CC) $(CC_FLAGS) $< -o $@

obj/map.o : src/map.cpp src/map.hpp
	$(CC) $(CC_FLAGS) $< -o $@






clean:
	rm $(CLEAN_FLAGS) $(OBJ_DIR)/*
