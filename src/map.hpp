#pragma once

#include <string>

class Noeud {

public:

  char letter;
  Noeud * tab[27];
  bool is_final;


public:

  Noeud();

  Noeud* addNode(const char & c, const bool & b);

  void addNode(const std::string & s);

  void print() const;


};
