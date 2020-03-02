#include <stack>
#include <string>
#include <iostream>
#include <fstream>

#include "gaddag.hpp"


Gaddag::Gaddag() {
  this->first = new Node();
  for (unsigned int i = 0; i < 27; i++) {
    this->first->tab[i] = nullptr;
  }
}


Gaddag::~Gaddag() {
  std::stack<Node*> s({first});
  Node * current;
  unsigned int i;
  do {
    current = s.top();
    s.pop();

    for(i = 0; i < 27; i++) {
      if (current->tab[i] != nullptr) {
        s.push(current->tab[i]);
      }
    }
    delete current;
  } while (!s.empty());
}


char Gaddag::getLetter(const unsigned short int & n) const {
  if (n < 26)
    return ('A' + n);
  return ('+');
}





std::list<std::string> Gaddag::mirror(const std::string & word ){
  std::list<std::string> l;
  std::string temp(word);
  unsigned int i,j;
  std::stack<char> beginning;
  std::queue<char> end;
  std::string result;

  for (i = 0; i < temp.size(); i++){
    result = "";
    for (j = 0; j <= i; j++){
      beginning.push(temp[j]);
    }
    for(j = i + 1; j < temp.size(); j++){
      end.push(temp[j]);
    }
    while(!beginning.empty()){
      result += beginning.top();
      beginning.pop();
    }
    result += "+";
    while(!end.empty()){
      result += end.front();
      end.pop();
    }
    l.push_back(result);
  }
  return l;
}


void Gaddag::addNodePlus(const std::string & s) {
  std::list<std::string> l(mirror(s));
  while(!l.empty()){
    first->addNode(l.back());
    l.pop_back();
  }
}


void Gaddag::addDictionnary(const std::string & filename){
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


void Gaddag::print_letters(Node* node,
                          std::queue<std::pair<char,Node*>> & fifo,
                          const char & c) {
  std::string letters ="";
  std::pair<char,Node*> p(c,node);
  if(node != nullptr){
    fifo.push(p);
    if(node->is_final){
      std::queue<std::pair<char,Node*>> newfifo(fifo);
      while(!newfifo.empty()){
        letters = letters +  newfifo.front().first;
        newfifo.pop();
      }
      std::cout << letters << std::endl;
    }
    for (unsigned short int i = 0 ; i < 27; i++) {
      if (node->tab[i] != nullptr) {
          print_letters(node->tab[i],fifo,getLetter(static_cast<char>(i)));
      }
    }

  }

  std::stack<std::pair<char,Node*>> pile1,pile2;
  while(!fifo.empty()){
    pile1.push(fifo.front());
    fifo.pop();
  }
  pile1.pop();
  while(!pile1.empty()){
    pile2.push(pile1.top());
    pile1.pop();
  }
  while(!pile2.empty()){
    fifo.push(pile2.top());
    pile2.pop();
  }
}


void Gaddag::print() {
  std::queue<std::pair<char,Node*>> f;
  print_letters(this->first,f,' ');
}
