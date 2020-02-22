#include <iostream>
#include "game.hpp"

int main() {
  Noeud * n = new Noeud();
  n->addNode("etudiant");
  n->addNode("etudiante");
  n->addNode("etrangere");
  n->addNode("scrabble");
  n->addNode("bonsoir");
  n->addNode("scrabb");
  n->print();
}
