#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <unistd.h>
#include <queue>
#include <utility>
#include <stack>

#include "map.hpp"

using namespace std;

Node::Node() {
  this->is_final = false;
  for (unsigned int i = 0; i < 27; i++) {
    this->tab[i] = nullptr;
  }
}


char Node::getLetter(const unsigned short int & n) const {
  if (n < 26)
    return ('A' + n);
  return ('+');
}


Node* Node:: addNode(const bool & b) {
  Node * ptr = new Node();
  ptr->is_final = b;
  for (unsigned int i = 0 ; i < 27; i++) {
      ptr->tab[i] = nullptr;
  }
  return ptr;
}


void Node:: addNode(const std::string & s) {
  unsigned int i = 0, size = s.size();
  unsigned short int c;
  Node * tmp = this;
  char cstr[size + 1];
  strcpy(cstr, s.c_str());

  for (i = 0; i < size; i++) {
    if (cstr[i] > 'Z' || cstr[i] < 'A')
      c = 'Z' - 'A' + 1;
    else
      c = cstr[i] - 'A';
    if (tmp->tab[c] == nullptr)
      tmp->tab[c] = addNode( (i == size - 1) );

    tmp = tmp->tab[c];
  }
}


void Node::print_letters(Node* node,
                          queue<pair<char,Node*>> & fifo,
                          const char & c){
  string letters ="";
  pair<char,Node*> p(c,node);
  if(node != nullptr){
    fifo.push(p);
    if(node->is_final){
      queue<pair<char,Node*>> newfifo(fifo);
      while(!newfifo.empty()){
        letters = letters +  newfifo.front().first;
        //cout << atoi(&newfifo.front().first) << endl;
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

void Node::print() {
  queue<pair<char,Node*>> f;
  print_letters(this,f,' ');
}


vector<string> Node::mirror(const string & word ){
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


void Node:: addNodePlus(const std::string & s) {
  vector<string> tab(mirror(s));
  for(unsigned int i = 0; i < tab.size();i++){
    addNode(tab[i]);
  }
}


void Node::addDictionnary(const std::string & filename){

  ifstream file (filename.c_str());

  if(!file.is_open())
  {
    cerr << "Erreur lors de la lecture du fichier \nVeuillez vérifier le chemin du fichier" << endl;
  }

  string word;

  while(!file.eof())
  {
    file >> word;
    addNodePlus(word);
  }

  file.close();
}


const bool Node::exist(const string & s) const {
  bool res = false;


  return res;
}
