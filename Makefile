

BIN_DIR = bin
OBJ_DIR = obj
SRC_DIR = src

CC = g++
LD = g++

CC_FLAGS = -O2 -Wextra -Werror -std=c++11 -pedantic -c
LD_FLAGS = -O2 -Wextra -Werror -std=c++11 -pedantic

CLEAN_FLAGS = -v -r


all : scrabbleTXT hack


scrabbleTXT: bin/scrabbleTXT

hack : bin/hack


bin/scrabbleTXT : obj/bag.o obj/player.o obj/bonus.o obj/spot.o obj/board.o obj/node.o obj/gaddag.o obj/game.o obj/scrabbleTXT.o obj/main.o
	$(LD) $(LD_FLAGS) $^ -o $@

bin/hack : obj/hack.o obj/bonus.o obj/bag.o obj/player.o obj/gaddag.o obj/node.o obj/spot.o obj/game.o obj/board.o
	$(LD) $(LD_FLAGS) $^ -o $@



obj/bag.o : src/bag.cpp src/bag.hpp
	$(CC) $(CC_FLAGS) $< -o $@

obj/player.o : src/player.cpp src/player.hpp
	$(CC) $(CC_FLAGS) $< -o $@

obj/bonus.o : src/bonus.cpp src/bonus.hpp
	$(CC) $(CC_FLAGS) $< -o $@

obj/spot.o : src/spot.cpp src/spot.hpp src/bonus.hpp
	$(CC) $(CC_FLAGS) $< -o $@

obj/board.o : src/board.cpp src/board.hpp src/spot.hpp
	$(CC) $(CC_FLAGS) $< -o $@

obj/node.o : src/node.cpp src/node.hpp
	$(CC) $(CC_FLAGS) $< -o $@

obj/gaddag.o : src/gaddag.cpp src/gaddag.hpp src/node.hpp
	$(CC) $(CC_FLAGS) $< -o $@

obj/game.o : src/game.cpp src/game.hpp src/gaddag.hpp src/bonus.hpp src/bag.hpp src/player.hpp src/board.hpp src/spot.hpp src/node.hpp
	$(CC) $(CC_FLAGS) $< -o $@

obj/scrabbleTXT.o : src/scrabbleTXT.cpp src/scrabbleTXT.hpp src/game.hpp src/gaddag.hpp src/bonus.hpp src/bag.hpp src/player.hpp src/board.hpp src/spot.hpp src/node.hpp
	$(CC) $(CC_FLAGS) $< -o $@

obj/main.o : src/main.cpp src/scrabbleTXT.hpp
	$(CC) $(CC_FLAGS) $< -o $@

obj/hack.o : src/hack.cpp src/game.hpp
	$(CC) $(CC_FLAGS) $< -o $@




doc : doc/scrabbleTXT.doxy src/*.hpp
	doxygen doc/scrabbleTXT.doxy



clean :
	rm $(CLEAN_FLAGS) $(OBJ_DIR)/*

veryclean :
	rm $(CLEAN_FLAGS) $(OBJ_DIR)/* $(BIN_DIR)/*
