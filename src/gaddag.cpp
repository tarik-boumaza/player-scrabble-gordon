/**
 * @file gaddag.cpp
*/


#include <stack>
#include <string>
#include <iostream>
#include <fstream>
#include "map.hpp"
#include "gaddag.hpp"


Gaddag::Gaddag() {
  this->first = new Node();
}


Gaddag::~Gaddag() {
  delete first;
}


Node* Gaddag::getFirst(){
  return first;
}


char Gaddag::getLetter(const unsigned short int & n) const {
  if (n < 26)
    return ('A' + n);
  return ('+');
}


static std::list<std::string> mirror(const std::string & word ){
  std::list<std::string> result;
  std::string temp;
  int i, j, z;
  int size = word.size();

  for (i = size ; i > 0; i--) {
    temp.clear();
    for (j = size - 1; j >= i; j--) {
      temp = word[j] + temp;
    }
    temp =  "+" + temp;
    z  = 0;
    while(z < i){
      temp = word[z] + temp;
      z++;
    }
    result.push_back(temp);
  }
  return result;
}


void Gaddag::addNodePlus(const std::string & s) {
  std::list<std::string> l(mirror(s));
  while(!l.empty()){
    first->addNode(l.back());
    l.pop_back();
  }
}


void Gaddag::addDictionnary() {
  std::string filename = "./data/dico.txt";
  std::ifstream file (filename.c_str());
  if(!file.is_open()) {
    std::cerr << "Erreur lors de la lecture du fichier" << filename <<
            "\nVeuillez vérifier le chemin du fichier" << std::endl;
    exit(EXIT_FAILURE);
  }

  std::string word;
  while(!file.eof()) {
    file >> word;
    addNodePlus(word);
  }

  file.close();
}


void Gaddag::print() {
  std::list<std::pair<char,Node*>> f;
  print_letters(this->first,f,' ');
}


void Gaddag::print_letters(Node* node,
                          std::list<std::pair<char,Node*>> & l,
                          const char & c) {
  std::string letters ="";
  std::pair<char,Node*> p(c,node);
  if(node != nullptr){
    l.push_back(p);
    if(node->isFinal()){
      std::list<std::pair<char,Node*>> newlist(l);
      while(!newlist.empty()){
        letters = letters +  newlist.front().first;
        newlist.pop_front();
      }
      std::cout << letters << std::endl;
    }
    for (unsigned short int i = 0 ; i < 27; i++) {
      if (node->getNode(i) != nullptr) {
          print_letters(node->getNode(i),l,getLetter(static_cast<char>(i)));
      }
    }

  }
  l.pop_back();
}