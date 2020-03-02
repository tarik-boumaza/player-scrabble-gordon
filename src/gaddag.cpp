#include <stack>
#include <cstring>
#include <iostream>
#include <fstream>

#include "gaddag.hpp"

using namespace std;


Gaddag::Gaddag() {
  this->first = new Node();
  for (unsigned int i = 0; i < 27; i++) {
    this->first->tab[i] = nullptr;
  }
}


Gaddag::~Gaddag() {
  std::stack<Node*> stack({first});
  Node * current;
  unsigned int i;
  do {
    current = stack.top();
    stack.pop();

    for(i = 0; i < 27; i++) {
      if (current->tab[i] != nullptr) {
        stack.push(current->tab[i]);
      }
    }
    delete current;
  } while (!stack.empty());
}


char Gaddag::getLetter(const unsigned short int & n) const {
  if (n < 26)
    return ('A' + n);
  return ('+');
}





vector<string> Gaddag::mirror(const string & word ){
  vector<string> table;
  string temp(word);
  unsigned int i,j;
  stack<char> beginning;
  queue<char> end;
  string result;

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
    table.push_back(result);
  }
  return table;
}


void Gaddag::addNodePlus(const std::string & s) {
  vector<string> tab(mirror(s));
  for(unsigned int i = 0; i < tab.size();i++){
    first->addNode(tab[i]);
  }
}


void Gaddag::addDictionnary(const std::string & filename){
  ifstream file (filename.c_str());
  if(!file.is_open()) {
    cerr << "Erreur lors de la lecture du fichier" << filename <<
            "\nVeuillez vérifier le chemin du fichier" << endl;
    exit(EXIT_FAILURE);
  }

  string word;
  while(!file.eof()) {
    file >> word;
    addNodePlus(word);
  }

  file.close();
}


void Gaddag::print_letters(Node* node,
                          queue<pair<char,Node*>> & fifo,
                          const char & c) {
  string letters ="";
  pair<char,Node*> p(c,node);
  if(node != nullptr){
    fifo.push(p);
    if(node->is_final){
      queue<pair<char,Node*>> newfifo(fifo);
      while(!newfifo.empty()){
        letters = letters +  newfifo.front().first;
        newfifo.pop();
      }
      cout << letters << endl;
    }
    for (unsigned short int i = 0 ; i < 27; i++) {
      if (node->tab[i] != nullptr) {
          print_letters(node->tab[i],fifo,getLetter(static_cast<char>(i)));
      }
    }

  }

  stack<pair<char,Node*>> pile1,pile2;
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
  queue<pair<char,Node*>> f;
  print_letters(this->first,f,' ');
}
