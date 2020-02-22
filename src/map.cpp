#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include "map.hpp"
#include <unistd.h>
#include <queue>
#include <stack>
#include <thread>

using namespace std;

Noeud::Noeud() {
  this->is_final = false;
  this->letter = ' ';
  for (unsigned int i = 0; i < 27; i++) {
    this->tab[i] = nullptr;
  }
}


Noeud* Noeud:: addNode1(const char & c, const bool & b) {
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
  unsigned short int c;
  Noeud * tmp = this;
  char cstr[size + 1];
  strcpy(cstr, s.c_str());

  for (i = 0; i < size; i++) {
    if (cstr[i] > 'Z' || cstr[i] < 'A')
      c = 'Z' - 'A' + 1;
    else
      c = cstr[i] - 'A';
    if (tmp->tab[c] == nullptr)
      tmp->tab[c] = addNode1(cstr[i],(i == size - 1));

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


vector<string> Noeud::mirror(const string & word ){
  vector<string> table;
  string temp(word);

  stack<char> beginning;
  queue<char> end;
  string result;

  for (unsigned int i = 0; i < temp.size(); i++){
    result = "";
    for (unsigned int j = 0; j <= i; j++){
      beginning.push(temp[j]);
    }
    for(unsigned int j = i + 1; j < temp.size(); j++){
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
    table.push_back(result);
  }
  return table;
}


void Noeud:: addNodePlus(const std::string & s) {
  vector<string> tab(mirror(s));
  addNode(s);
  for(unsigned int i = 0; i < tab.size();i++){
    addNode(tab[i]);
  }
}


/*
void Noeud:: addNodePlus(const std::string & s) {
  vector<string> tab(mirror(s));
  vector<thread> thread_tab;
  thread_tab.push_back(thread(&Noeud::addNode,this,s));
  for(unsigned int i = 0; i < tab.size();i++){
    thread_tab.push_back(thread(&Noeud::addNode,this,tab[i]));
  }
  for(unsigned int i = 0; i < thread_tab.size(); i++) {
    thread_tab[i].join();
  }

}*/


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
    addNodePlus(word);
  }

  file.close();


}
