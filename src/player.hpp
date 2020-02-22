#pragma once


class Player {

private:
  unsigned short int id;
  char hand[7];

public:

  Player(const unsigned short int & _id);

  Player(const unsigned short int & _id, const char h[7]);

  unsigned short int getId() const;

  void setId(const unsigned short int & _id);

  char getLetter(const unsigned short int & _n) const;

  void setLetter(const unsigned short int & n, const char & c);

};
