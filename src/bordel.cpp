#include "board.hpp"
#include "bag.hpp"
#include "game.hpp"
#include "gaddag.hpp"
#include "player.hpp"

#include <iostream>
#include <sstream>

#include <list>


int main() {
    Game * g = new Game();
    char rack[7];
    rack[0] = 'I';
    rack[1] = 'I';
    rack[2] = 'I';
    rack[3] = 'S';
    rack[4] = 'S';
    rack[5] = '/';
    rack[6] = '/';
    float gr = g->grade(rack);
    std::cout << "'ISSIS' grade = " << gr << std::endl; 
}