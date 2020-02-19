#include <iostream>
#include <cstring>
#include <string>
#include "map.hpp"

using mapit = std::unordered_map<char,Noeud*>::const_iterator;

Noeud::Noeud() {
  is_final = false;
  this->node = std::unordered_map<char,Noeud*> {{'0',nullptr}};
}


void Noeud:: addNode(const char & c, const bool & b) {
  this->node.insert({c,nullptr});
  node[c]->is_final = b;
}


void Noeud:: addNode(const std::string & s) {
  unsigned int i = 0;
  unsigned int size = s.size();
  Noeud * temp = this;

  char cstr[size + 1];
  strcpy(cstr, s.c_str());

  std::unordered_map<char, Noeud*> :: const_iterator got ;
  while (i < size) {
    got = temp->node.find(cstr[i]);
    if (got == temp->node.end()) {
      temp->addNode(cstr[i], (i == size - 1));
    }
    temp = temp->node[cstr[i]];
    i++;
  }
}

//void Noeud::print_hashmap(const std::unordered_map<char,Noeud*> & m) const {}


void Noeud::print() const {
  std::cout << "Affichage de l'arbre..." << std::endl;
  for(mapit it = this->node.begin(); it != this->node.end(); ++it){
    std::cout << it->first;
  }
}
