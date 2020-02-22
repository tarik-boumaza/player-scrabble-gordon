#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include "map.hpp"
#include <unistd.h>
#include <queue>
#include <stack>

using namespace std;

Noeud::Noeud() {
  this->is_final = false;
  this->letter = ' ';
  for (unsigned int i = 0; i < 27; i++) {
    this->tab[i] = nullptr;
  }
}


Noeud* Noeud:: addNode(const char & c, const bool & b) {
  Noeud * ptr = new Noeud();
  ptr->letter = c;
  ptr->is_final = b;
  for (unsigned int i = 0 ; i < 27; i++) {
      ptr->tab[i] = nullptr;
  }
  return ptr;
}


void Noeud:: addNode(const std::string & s) {
  unsigned int i = 0, size = s.size();
  short unsigned int c;
  Noeud * tmp = this;
  char cstr[size + 1];
  strcpy(cstr, s.c_str());

  for (i = 0; i < size; i++) {
    c = cstr[i] - 'A';
    if (tmp->tab[c] == nullptr)
      tmp->tab[c] = addNode(cstr[i],(i == size - 1));

    tmp = tmp->tab[c];
  }
}


void Noeud::print_letters(Noeud* node, queue<Noeud*> & fifo){
  string letters ="";

  if(node != nullptr){
    if(!node->is_final){
      fifo.push(node);
    }
    else {
      fifo.push(node);
      queue<Noeud*> newfifo(fifo);
      while(!newfifo.empty()){
        letters = letters +  newfifo.front()->letter;
        newfifo.pop();
      }
      cout << letters << endl;
    }
    for (unsigned int i = 0 ; i < 27; i++) {
      if (node->tab[i] != nullptr) {
          print_letters(node->tab[i],fifo);
      }
    }

  }

  stack<Noeud*> pile1,pile2;
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

void Noeud::print() {
  queue<Noeud*> f;
  print_letters(this,f);

}

void Noeud::addDictionnary(const std::string & filename){

  ifstream file (filename.c_str());

  if(!file.is_open())
  {
    cout << "Erreur lors de la lecture du fichier \nVeuillez vérifier le chemin du fichier" << endl;
  }

  string word;

  while(!file.eof())
  {
    file >> word;
    addNode(word);
  }

  file.close();


}
