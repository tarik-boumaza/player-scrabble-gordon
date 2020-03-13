#include <cstring>
#include "map.hpp"


Node::Node() {
  this->is_final = false;
  for (unsigned int i = 0; i < 27; i++) {
    this->tab[i] = nullptr;
  }
}


Node* Node::getNode(const unsigned short int & i)const{
  return tab[i];
}


bool Node::isFinal() const {
  return is_final;
}



Node* Node::addNode(const bool & b) {
  Node * ptr = new Node();
  ptr->is_final = b;
  for (unsigned int i = 0 ; i < 27; i++) {
      ptr->tab[i] = nullptr;
  }
  return ptr;
}


void Node::addNode(const std::string & s) {
  unsigned int i = 0, size = s.size();
  unsigned short int c;
  Node * tmp = this;

  for (i = 0; i < size; i++) {
    if (s[i] > 'Z' || s[i] < 'A')
      c = 'Z' - 'A' + 1;
    else
      c = s[i] - 'A';
    if (tmp->tab[c] == nullptr)
      tmp->tab[c] = addNode( (i == size - 1) );

    tmp = tmp->tab[c];
  }
}
