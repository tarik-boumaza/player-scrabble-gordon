#include <iostream>
#include <cstring>
#include <string>
#include "map.hpp"
#include <unistd.h>

using namespace std;

Noeud::Noeud() {
  for (unsigned int i = 0; i < 27; i++) {
    this->tab[i] = nullptr;
  };
  this->is_final = false;
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
  bool f;

  for (i = 0; i < size; i++) {
    f = (i == size - 1);
    c = cstr[i] - 'a';
    if (tmp->tab[c] == nullptr)
      tmp->tab[c] = addNode(cstr[i],f);

    tmp = tmp->tab[c];
  }
  if (tmp->tab[c] != nullptr)
    tmp->tab[c]->is_final = true;
}

void Noeud::print() const {
  char c;
  for (unsigned int i = 0 ; i < 27; i++) {
    if (tab[i] != nullptr) {
      c = 'a' + i;
      cout << c << " ";
      if (tab[i]->is_final)
        cout << "F ";
      tab[i]->print();
    }

  }
  cout << endl;
}
