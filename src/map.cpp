#include <iostream>
#include <cstring>
#include <string>
#include "map.hpp"

using mapit = std::unordered_map<char,Noeud*>::const_iterator;

Noeud:: Noeud() {
  is_final = false;
  //this->node = std::unordered_map<char,Noeud*>;
}


void Noeud:: addNode(const char & c, const bool & b) {
  Noeud * nouveau = new Noeud;
  nouveau->is_final = b;
  this->node.insert({c,nouveau});

}


void Noeud:: addNode(const std::string & s) {
  std::cout<<"je dois ajouter "<< s <<std::endl;
  unsigned int i = 0;
  unsigned int size = s.size();
  Noeud * temp = this;

  char cstr[size + 1];
  strcpy(cstr, s.c_str());

  std::unordered_map<char, Noeud*> :: const_iterator got ;
  while (i < size) {
    std::cout<<"je dois ajouter "<< cstr[i] <<std::endl;
    got = temp->node.find(cstr[i]);
    if (got == temp->node.end()) {
      std::cout<<" le "<<cstr[i] <<" n existe pas je le créé "<<std::endl;
      temp->addNode(cstr[i], (i == size - 1));
    }
    temp = temp->node[cstr[i]];
    std::cout<<"j avance "<<std::endl;
    i++;
  }
}


void Noeud::print_hashmap() const {
  for (mapit it = this->node.begin(); it != this->node.end(); ++it){
      std::cout<< it->first + " ";
      it->second->print_hashmap();
  }

}


void Noeud::print() const {
  std::cout << "Affichage de l'arbre..." << std::endl;
  for(mapit it = this->node.begin(); it != this->node.end(); ++it){
    std::cout << it->first << " ";
    it->second->print();
  }

}
