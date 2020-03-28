#include <iostream>
#include "map.hpp"
#include "board.hpp"
#include "player.hpp"
#include "bag.hpp"
#include "gaddag.hpp"
#include "game.hpp"
#include <stack>



Game::Game() {
  bag = new Bag("./data/letters.txt","./data/points.txt");
  player = new Player;
  gad = new Gaddag;
  board = new Board;
}


Game::Game(const Board& b){
  bag = new Bag("./data/letters.txt","./data/points.txt");
  player = new Player;
  gad = new Gaddag;
  board = new Board(b);
}


Game::~Game() {
  delete board;
  delete player;
  delete bag;
  delete gad;
}


void Game::draw(const unsigned short int & n) {
  unsigned int i = 0;
  while (i < n && !isFinished() ) {
    player->setLetter(bag->randomDraw());
    i++;
  }
}


void Game::init() {
  draw(7);
  gad->addDictionnary();
}


void Game::printDico() {
  gad->print();
}


void Game::printHand() const {
  player->printHand();
}


void Game::printBag() const {
  bag->printLetters();
}


bool Game::isFinished() const {
  return bag->isEmpty();
}


void Game::useLetter(const char & c) {
  player->removeLetter(c);
}


//c.first représente la case du plateau
//c.second représente la lettre jouée sur la case
couple Game::score (const couple & c) const {
  unsigned short int res = bag->getPoints(c.second);
  res *= static_cast<unsigned short int>(board->getLetterFactor(c.first));
  couple p (res,static_cast<unsigned short int>(board->getWordFactor(c.first)));
  return p;
  //p.first est le score que donne la lettre multiplié par le letter_factor
  //p.second est le word_factor
}


//couple.first représente la case du plateau
//couple.second représente la lettre jouée sur la case
//l contient ainsi l'ensemble des lettres jouées ainsi que leurs positions
unsigned short int Game::score(const std::list<couple> & l) const {
  unsigned short int res = 0;
  unsigned short int wf = 1;
  std::list<couple> copy (l);
  couple temp;
  while(!copy.empty()) {
    temp = score(copy.back()); //temp.first est le score, temp.second est le word_factor
    //std::cout << "Lettre " << static_cast<int>((copy.back().first))
    //                        << " : + " << static_cast<char>(copy.back().second) << " pts" << std::endl;
    res += temp.first;
    if (temp.second > wf)
      wf = temp.second;
    copy.pop_back();
  }
  return (wf * res);
}


unsigned short int Game::score (const Board * b, const int & pos,
                                const char & direction) const {

  int i = pos;
  std::list<couple> l;
  couple temp;


  temp = couple(i,b->getLetter(i));
  l.push_back(temp);

  if (direction == 'H') {
    i -= 15;
    while (i >= 0 && b->getLetter(i) != 0) {
      temp = couple(i,b->getLetter(i));
      l.push_back(temp);
      i -=15 ;
    }
    return score(l);
  }

  if (direction == 'B') {
    i += 15;
    while (i / 15 < 15 && b->getLetter(i) != 0) {
      temp = couple(i,b->getLetter(i));
      l.push_back(temp);
      i +=15 ;
    }
    return score(l);
  }

  if (direction == 'G') {
    i -= 1;
    while ( pos / 15 == (i * (-1)) / 15 && b->getLetter(i) != 0) {
      temp = couple(i,b->getLetter(i));
      l.push_back(temp);
      i -= 1 ;
    }
    return score(l);
  }

  i += 1;
  while ( pos / 15 == i / 15  && b->getLetter(i) != 0) {
    temp = couple(i,b->getLetter(i));
    l.push_back(temp);
    i += 1;
  }
  return score(l);



}




unsigned short int Game::score (const Move & m) const {

  std::string word = m.word;
  unsigned int pos = static_cast<unsigned int> (m.first_square);

  unsigned short int points = 0;
  unsigned int board_pos = pos;
  couple temp_couple;
  unsigned int temp_pos = 0;
  std::list<couple> move;

  if (m.direction == 'H') {               //On joue vers le HAUT

    int word_pos = static_cast<int>(word.size() - 1);

    while ( word_pos >= 0
            && board_pos < 225) {

      if (board->getLetter(board_pos) == 0) {

          if ( (board_pos % 15) > 0
                &&  board->getLetter(board_pos - 1) != 0) { //lettre à gauche
            temp_pos = board_pos;
            while ( (temp_pos % 15) < 14
                    && board->getLetter(temp_pos + 1) != 0 ) { //tant que lettre à droite
              temp_pos++;
            }
            Board * b_copy = new Board(*board);
            b_copy->setLetter(temp_pos,word[word_pos]);
            points += score(b_copy,temp_pos,'G');
          }

          else if ( (board_pos % 15) < 14 && board->getLetter(board_pos + 1) != 0) {   //lettre à droite uniquement
            Board * b_copy = new Board(*board);
            b_copy->setLetter(board_pos,word[word_pos]);
            points += score(b_copy,board_pos,'D');
          }

      }
      temp_couple = couple (board_pos,word[word_pos]);
      move.push_back(temp_couple);
      board_pos -= 15;
      word_pos--;

    }

    points += score(move);
    return points;
  }

  else if (m.direction == 'B')  {        //On joue vers le BAS

    unsigned int word_pos = 0;

    while ( word_pos < word.size()
            && board_pos < 225) {

      if (board->getLetter(board_pos) == 0) {

          if ( (board_pos % 15) > 0
              &&  board->getLetter(board_pos - 1) != 0) { //lettre à gauche

            temp_pos = board_pos;
            while ( (temp_pos % 15) < 14
                    && board->getLetter(temp_pos + 1) != 0 ) { //tant que lettre à droite
            temp_pos++;
          }

          Board * b_copy = new Board(*board);
          b_copy->setLetter(temp_pos,word[word_pos]);
          points += score(b_copy,temp_pos,'G');
        }

        else if ( (board_pos % 15) < 14
                  && board->getLetter(board_pos + 1) != 0) {   //lettre à droite uniquement
          Board * b_copy = new Board(*board);
          b_copy->setLetter(board_pos,word[word_pos]);
          points += score(b_copy,board_pos,'D');
        }

      }
      temp_couple = couple (board_pos,word[word_pos]);
      move.push_back(temp_couple);
      board_pos += 15;
      word_pos++;
    }

    points += score(move);
    return points;

  }

  else if (m.direction =='G') {          //On joue vers la GAUCHE

    int word_pos = static_cast<int>(word.size() - 1);

    while ( word_pos >= 0
            && board->getIndice(board_pos).first == board->getIndice(pos).first ) {

      if (board->getLetter(board_pos) == 0) {

          if ( board_pos > 14
              &&  board->getLetter(board_pos - 15) != 0) {   //lettre en haut

            temp_pos = board_pos;
            while ( temp_pos < 210
                    && board->getLetter(temp_pos + 15) != 0 ) {   //tant que lettre en bas
              temp_pos += 15;
            }

          Board * b_copy = new Board(*board);
          b_copy->setLetter(temp_pos,word[word_pos]);
          points += score(b_copy,temp_pos,'H');
        }

        else if ( board_pos < 210
                && board->getLetter(board_pos + 15) != 0) {   //lettre  en bas uniquement
          Board * b_copy = new Board(*board);
          b_copy->setLetter(board_pos,word[word_pos]);
          points += score(b_copy,board_pos,'B');
        }

      }
      temp_couple = couple (board_pos,word[word_pos]);
      move.push_back(temp_couple);
      board_pos--;
      word_pos--;
    }
    points += score(move);
    return points;

  }

  else {                           //On joue vers la DROITE

    unsigned int word_pos = 0;
    unsigned int line = (pos / 15);

    while ( word_pos < word.size()
            && board_pos / 15 == line) {

      if (board->getLetter(board_pos) == 0) {
          if ( board_pos > 14
              &&  board->getLetter(board_pos - 15) != 0) {   //lettre en haut

            temp_pos = board_pos;
            while ( temp_pos < 210
                    && board->getLetter(temp_pos + 15) != 0 ) {   //tant que lettre en bas
              temp_pos += 15;
            }

          Board * b_copy = new Board(*board);
          b_copy->setLetter(temp_pos,word[word_pos]);
          points += score(b_copy,temp_pos,'H');
        }
        else if ( board_pos < 210
                  && board->getLetter(board_pos + 15) != 0) { //lettre  en bas uniquement
          Board * b_copy = new Board(*board);
          b_copy->setLetter(board_pos,word[word_pos]);
          points += score(b_copy,board_pos,'B');
        }
        std::cout << std::endl;

      }
      temp_couple = couple (board_pos,word[word_pos]);
      move.push_back(temp_couple);
      board_pos++;
      word_pos++;
    }

    points += score(move);

  }

  return points;

}


void Game::getCrossSetsHorizontal(const unsigned char & square,
                                  char tab_horizontal[], bool final) const {
  unsigned char x = (board->getIndice(square)).first;
  unsigned char y = (board->getIndice(square)).second;

  // dans le cas où ma case n'est adjacente qu'à une seule case vide directement
  // à gauche
  if(((board->getSpot(board->getIndice(x,y)))->getLetter() == 0)){
    if( (((y < 14) && ((board->getSpot(board->getIndice(x,y+1)))->getLetter() == 0))
        || (y >= 14))
        && (y > 0)
        && ((board->getSpot(board->getIndice(x,y-1)))->getLetter() != 0)) {

          Spot* parcours = board->getSpot(board->getIndice(x, y-1));
          Node* gad_parcours = gad->getFirst();
          int i = 1;

          while((parcours->getLetter() != 0)
                && (y - i >= 0) ) {
            gad_parcours = gad_parcours->getNode(parcours->getLetter());
            parcours = board->getSpot(board->getIndice(x, y-1-i));
            i++;
          }

          if(gad_parcours != nullptr)
            gad_parcours = gad_parcours->getNode('+');

          for(int i = 0; i < 26; i++) {

            if(gad_parcours->getNode(i) != nullptr){
              if(final){
                if((gad_parcours->getNode(i))->isFinal())
                  tab_horizontal[i] = gad->getLetter(i);
                else
                  tab_horizontal[i] = '/';
              }
              else tab_horizontal[i] = gad->getLetter(i);
            }
            else
            {
              tab_horizontal[i] = '/';
            }
          }

    }

    // dans le cas où ma case n'est adjacente qu'à une seule case vide directement
    // à droite
    else if( (y < 14)
          && ((board->getSpot(board->getIndice(x,y+1)))->getLetter() != 0)
          && (((y > 0)
          && ((board->getSpot(board->getIndice(x,y-1)))->getLetter() == 0))
          || (y <= 0))) {

          std::stack<char> pile;
          Spot* parcours = board->getSpot(board->getIndice(x, y+1));
          Node* gad_parcours = gad->getFirst();
          int i = 1;

          while((parcours->getLetter() != 0)
                && (y + i >= 0) ) {
            pile.push(parcours->getLetter());
            parcours = board->getSpot(board->getIndice(x, y+1+i));
            i++;
          }

          while (!pile.empty()) {
            gad_parcours = gad_parcours->getNode(pile.top());
            pile.pop();
          }

          for(int i = 0; i < 26; i++) {

            if(gad_parcours->getNode(i) != nullptr){
              if(final){
                if((gad_parcours->getNode(i))->isFinal())
                  tab_horizontal[i] = gad->getLetter(i);
                else
                  tab_horizontal[i] = '/';
              }
              else tab_horizontal[i] = gad->getLetter(i);
            }
            else
            {
              tab_horizontal[i] = '/';
            }
          }
    }

    else if ((y < 14)
            && ((board->getSpot(board->getIndice(x,y+1)))->getLetter() != 0)
            && (y > 0)
            && ((board->getSpot(board->getIndice(x,y-1)))->getLetter() != 0)){

          Spot* parcours = board->getSpot(board->getIndice(x, y-1));
          Node* gad_parcours = gad->getFirst();
          int i = 1;

          while((parcours->getLetter() != 0)
                && (y - i >= 0)){
            gad_parcours = gad_parcours->getNode(parcours->getLetter());
            parcours = board->getSpot(board->getIndice(x, y-1-i));
            i++;
          }

          gad_parcours = gad_parcours->getNode('+');
          Node * copy = gad_parcours;

          for (int i = 0; i < 26; i++) {

            copy = gad_parcours;

            if (copy != nullptr && copy->getNode(i) != nullptr) {

              copy = copy->getNode(i);
              Node* gad_coup_possible = copy;
              parcours = board->getSpot(board->getIndice(x,y+1));
              int j = 1;

              while( gad_coup_possible != nullptr
                    && parcours->getLetter() != 0 ) {
                gad_coup_possible = gad_coup_possible->getNode(parcours->getLetter());
                parcours = board->getSpot(board->getIndice(x, y+1+j));
                j++;
              }

              if (gad_coup_possible != nullptr
                  && parcours->getLetter() == 0
                  && gad_coup_possible->isFinal() ) {
                tab_horizontal[i] = gad->getLetter(i);
              }
              else
              {
                tab_horizontal[i] = '/';
              }
            }

            else
            {
                tab_horizontal[i] = '/';
            }
          }
    }
    else
    {
      for(int i = 0; i < 26; i++){
        tab_horizontal[i] = gad->getLetter(i);
      }
    }

  }
  else
  {
    for(int i = 0; i < 26; i++){
      tab_horizontal[i] = '/';
    }
  }

}

void Game::getCrossSetsVertical(const unsigned char & square,
                                  char tab_vertical[], bool final) const {

  unsigned char x = (board->getIndice(square)).first;
  unsigned char y = (board->getIndice(square)).second;
  // dans le cas où ma case n'est adjacente qu'à une seule case vide directement
  // à gauche
  if (((board->getSpot(board->getIndice(x,y)))->getLetter() == 0)){

    if( (((x < 14) && ((board->getSpot(board->getIndice(x+1,y)))->getLetter() == 0))
        || (x >= 14))
        && (x > 0)
        && ((board->getSpot(board->getIndice(x-1,y)))->getLetter() != 0)) {

          Spot* parcours = board->getSpot(board->getIndice(x-1, y));
          Node* gad_parcours = gad->getFirst();
          int i = 1;

          while((parcours->getLetter() != 0)
                && (x - i >= 0) ) {
            gad_parcours = gad_parcours->getNode(parcours->getLetter());
            parcours = board->getSpot(board->getIndice(x-1-i, y));
            i++;
          }

          if(gad_parcours != nullptr)
            gad_parcours = gad_parcours->getNode('+');

          for(int i = 0; i < 26; i++) {

            if(gad_parcours->getNode(i) != nullptr){

              if(final){
                if((gad_parcours->getNode(i))->isFinal())
                  tab_vertical[i] = gad->getLetter(i);
                else
                  tab_vertical[i] = '/';
              }
              else tab_vertical[i] = gad->getLetter(i);

            }
            else
            {
              tab_vertical[i] = '/';
            }
          }
    }
    // dans le cas où ma case n'est adjacente qu'à une seule case vide directement
    // à droite
    else if( (x < 14)
          && ((board->getSpot(board->getIndice(x+1,y)))->getLetter() != 0)
          && (((x > 0)
          && ((board->getSpot(board->getIndice(x-1,y)))->getLetter() == 0))
          || (x <= 0))) {

          std::stack<char> pile;
          Spot* parcours = board->getSpot(board->getIndice(x+1, y));
          Node* gad_parcours = gad->getFirst();
          int i = 1;

          while((parcours->getLetter() != 0)
                && (x + i >= 0) ) {
            pile.push(parcours->getLetter());
            parcours = board->getSpot(board->getIndice(x+1+i, y));
            i++;
          }

          while (!pile.empty()) {
            gad_parcours = gad_parcours->getNode(pile.top());
            pile.pop();
          }

          for(int i = 0; i < 26; i++) {

            if(gad_parcours->getNode(i) != nullptr){

              if(final){
                if((gad_parcours->getNode(i))->isFinal())
                  tab_vertical[i] = gad->getLetter(i);
                else
                  tab_vertical[i] = '/';
              }
              else tab_vertical[i] = gad->getLetter(i);

            }
            else
            {
              tab_vertical[i] = '/';
            }
          }
    }

    else if ((x < 14)
            && ((board->getSpot(board->getIndice(x+1,y)))->getLetter() != 0)
            && (x > 0)
            && ((board->getSpot(board->getIndice(x-1,y)))->getLetter() != 0)){

          Spot* parcours = board->getSpot(board->getIndice(x-1, y));
          Node* gad_parcours = gad->getFirst();
          int i = 1;

          while((parcours->getLetter() != 0)
                && (x - i >= 0)){
            gad_parcours = gad_parcours->getNode(parcours->getLetter());
            parcours = board->getSpot(board->getIndice(x-1-i, y));
            i++;
          }

          gad_parcours = gad_parcours->getNode('+');
          Node * copy = gad_parcours;

          for (int i = 0; i < 26; i++) {

            copy = gad_parcours;

            if (copy != nullptr && copy->getNode(i) != nullptr) {

              copy = copy->getNode(i);
              Node* gad_coup_possible = copy;
              parcours = board->getSpot(board->getIndice(x+1,y));
              int j = 1;

              while( gad_coup_possible != nullptr
                    && parcours->getLetter() != 0 ) {
                gad_coup_possible = gad_coup_possible->getNode(parcours->getLetter());
                parcours = board->getSpot(board->getIndice(x+1+j, y));
                j++;
              }

              if (gad_coup_possible != nullptr
                  && parcours->getLetter() == 0
                  && gad_coup_possible->isFinal() ) {

                tab_vertical[i] = gad->getLetter(i);
              }
              else
              {
                tab_vertical[i] = '/';
              }

            }
            else
            {
                tab_vertical[i] = '/';
            }
          }
    }
    else {
      for(int i = 0; i < 26; i++) {
        tab_vertical[i] = gad->getLetter(i);
      }
    }

  }
  else {
    for(int i = 0; i < 26; i++) {
      tab_vertical[i] = '/';
    }
  }
}


void Game::Gen(unsigned char square, int pos, std::string& word,
         unsigned int rack[], Node* arc, unsigned int direction,
         Board* b,unsigned short int& points, Move& move){

  unsigned char x = (b->getIndice(square)).first;
  unsigned char y = (b->getIndice(square)).second;
  char letter = (b->getSpot(square))->getLetter();

  //std::cout<<"je rentre dans la fontion Gen"<<std::endl;
  // si la case sur laquelle je suis n'est pas vide, j'avance dans le gaddag
  // en lisant la lettre qu'elle contient déja

  if(letter != 0)
  {
    //std::cout<<"la case contient une lettre "<<std::endl;
    Node* next_arc = arc->getNode(letter);
    GoOn(square, pos,letter, word, rack, next_arc, arc, direction, b, points, move);

  }
  else
  {
    char tab_horizontal[26];
    char tab_vertical[26];
    *board = *b;
    //std::cout<<"la case ne contient pas de lettre  "<<std::endl;
    // si direction = 1 -> je me déplace horizontalement, et donc les cross sets
    // verticals doivent être des lettres finales
    if(direction == 1){
      getCrossSetsHorizontal(square,tab_horizontal, false);
      getCrossSetsVertical(square,tab_vertical, true);
      /*std::cout<<"le getCrossSetsHorizontal "<<std::endl;
      for (int i = 0; i < 26; i++){
        std::cout<<tab_horizontal[i]<< " ";
      }
      std::cout<<std::endl;
      std::cout<<"le getCrossSetsVertical "<<std::endl;
      for (int i = 0; i < 26; i++){
        std::cout<<tab_vertical[i]<< " ";
      }
      std::cout<<std::endl;*/
    }
    // sinon je me déplace verticalement et donc les cross sets horizontales
    // doivent être des lettres finales
    else
    {
      getCrossSetsHorizontal(square,tab_horizontal, true);
      getCrossSetsVertical(square,tab_vertical, false);
      /*std::cout<<"le getCrossSetsVertical "<<std::endl;
      for (int i = 0; i < 26; i++){
        std::cout<<tab_vertical[i]<< " ";
      }
      std::cout<<std::endl;
      std::cout<<"le getCrossSetsHorizontal "<<std::endl;
      for (int i = 0; i < 26; i++){
        std::cout<<tab_horizontal[i]<< " ";
      }
      std::cout<<std::endl;*/
    }

    // pour chaque lettre que possède le jour, jouable sur cette case, j'essaye
    // de génerer des mots
    unsigned char square_copy = square;
    int pos_copy = pos;
    std::string word_copy = word;
    Board b_copy(*b);
    Node* arc_copy = arc;
    unsigned int rack_copy[26];
    unsigned short int points_copy = points;


    for (int i = 0; i < 26; i++){
      rack_copy[i] = rack[i];
    }

    for(int i = 0; i < 26; i++){
      /*std::cout<<"je suis à "<< i << "eme case du rack" <<std::endl;
      std::cout<<"le rack contient "<< rack[i]<<std::endl;
      std::cout<<"tab horizontale contitent "<< tab_horizontal[i]<<std::endl;
      std::cout<<"tab_vertical contient  "<< tab_vertical[i]<<std::endl;*/

      square = square_copy;
      pos = pos_copy;
      word = word_copy;
      *b = b_copy;
      arc = arc_copy;


      for (int i = 0; i < 26; i++){
        rack[i] = rack_copy[i];
      }

      if((rack[i] > 0)
        && (tab_horizontal[i] != '/')
        && (tab_vertical[i] != '/')){
          //std::cout<<"je rentre dans le if pour la case "<< i <<std::endl;
          rack[i]--;
          Node* next_arc = arc->getNode(i);
          b->getSpot(square)->setLetter('A'+ i);
          GoOn(square, pos,'A'+ i, word, rack, next_arc, arc, direction, b, points,move);
        }
    }

  }
}


void Game::GoOn(unsigned char  square, int pos, char L,std:: string& word,
          unsigned int rack[],Node* new_arc,
          Node* old_arc,unsigned int direction,
          Board* b,unsigned short int& points, Move& move){

  unsigned char x = (b->getIndice(square)).first;
  unsigned char y = (b->getIndice(square)).second;
  //std::cout<<"je rentre dans la fontion GoOn"<<std::endl;
  if(pos <= 0 ){ // se déplacer à gauche
      //std::cout<<"pos est <= 0 "<<std::endl;
      //std::cout<<"j'ajoute à mon mot la lettre: "<< L << " à gauche"<<std::endl;
      word = L + word;
      //std::cout<<"WORD : "<< word <<std::endl;
      if(new_arc != nullptr){
        //std::cout<<"new_arc n'est pas vide "<<std::endl;
        //j'avance dans le gaddag et le plateau
        if(direction == 1){
          if(y-1 >= 0){
            // je continue à gauche
            unsigned int suivant = b->getIndice(x,y-1);
            Gen(suivant, pos-1, word, rack, new_arc, direction, b, points, move);
          }
           //j'avance à droite
          //std::cout<<"je change de direction... vers la droite"<<std::endl;
          new_arc = new_arc->getNode('+');
          // à condition que la nouvelle branche n'est pas vide, que la case
          // directement à gauche est vide, et qu'il éxiste une case à droite
          //std::cout<<"y - 1 = "<< y-1<<std::endl;
          //std::cout<<"y - pos + 1 = "<< y- pos + 1<<std::endl;
          //if(new_arc == nullptr) std::cout<<"new_arc est vide"<<std::endl;
          if ((new_arc != nullptr)
              && (((y-1>= 0)
              && ((b->getSpot(b->getIndice(x,y-1)))->getLetter() == 0))
              || (y-1 < 0))){

                if((new_arc->isFinal())
                  && ((y-pos+1 >14) || ((y-pos+1 <=14)
                  && ((b->getSpot(b->getIndice(x,y-pos+1)))->getLetter() == 0)))){
                    //appel de la fonction qui calcule le score
                    Move temp_move (word,b->getIndice(x, y),'D');
                    unsigned short int new_points = score(temp_move); // = l'appel récursif
                    std::cout << "Dun coup possible " << word
                              << " ; qui donne : " << new_points <<  " points" << std::endl;
                    if (new_points > points){
                      move = temp_move;
                      points = new_points;
                    }
                  }

                if(y-pos+1 <= 14){
                  unsigned int suivant = b->getIndice(x,y-pos+1);
                  Gen(suivant, 1, word, rack, new_arc, direction, b, points, move);
                }

              }

        }
        else{

          if(x-1 >= 0){
            // je continue à gauche
            unsigned int suivant = b->getIndice(x-1,y);
            Gen(suivant, pos-1, word, rack, new_arc, direction, b, points, move);
          }
          // j'avance à droite
          new_arc = new_arc->getNode('+');
          // à condition que la nouvelle branche n'est pas vide, que la case
          // directement à gauche est vide, et qu'il éxiste une case à droite
          //std::cout<<"x - 1 = "<< x-1<<std::endl;
          //std::cout<<"x - pos + 1 = "<< x - pos + 1<<std::endl;
          //if(new_arc == nullptr) std::cout<<"new_arc est vide"<<std::endl;
          if ((new_arc != nullptr)
              && (((x-1 >= 0)
              && ((b->getSpot(b->getIndice(x-1,y)))->getLetter() == 0))
              || (x-1 < 0))){

                if((new_arc->isFinal())
                  && ((x-pos+1 >14) || ((x-pos+1 <=14)
                  && ((b->getSpot(b->getIndice(x-pos+1,y)))->getLetter() == 0)))){
                    //appel de la fonction qui calcule le score
                    Move new_move(word,b->getIndice(x, y),'B');
                    unsigned short int new_points = score(new_move); // = l'appel récursif
                    std::cout << "Bun coup possible " << word
                              << " ; qui donne : " << new_points <<  " points" << std::endl;
                    if (new_points > points){
                      move = new_move;
                      points = new_points;
                    }
                  }

                if(x-pos+1 <= 14){
                  unsigned int suivant = b->getIndice(x-pos+1,y);
                  Gen(suivant, 1, word, rack, new_arc, direction, b, points, move);
                }
              }
        }
      }
  }
  else if (pos > 0){ //se déplacer à droite
    //std::cout<<"pos est > 0 "<<std::endl;
    //std::cout<<"j'ajoute à mon mot la lettre: "<< L << " à droite"<<std::endl;
    word = word + L;
    //std::cout<<"WORD : "<< word <<std::endl;

    if((new_arc != nullptr) && (new_arc->isFinal())){
      //std::cout<<"je rentre avec la lettre "<< L <<" et elle est finale" <<std::endl;
      // si la lettre est finale , et qu'il n'y a pas de case non vide
      // directement à droite -> j'enregistre de coup
      if(direction == 1){

        if (((y + 1 <= 14)
            && ((b->getSpot(b->getIndice(x,y+1)))->getLetter() == 0))
            ||(y + 1 > 14)){
              //recordplay
              Move new_move (word,square,'G');
              unsigned short int new_points = score(new_move); // = l'appel récursif
              std::cout << "Gun coup possible " << word
                        << " ; qui donne : " << new_points <<  " points" << std::endl;

              if (new_points > points){
                move = new_move;
                points = new_points;
              }
        }
      }
      else{
        if (((x + 1 <= 14)
            && ((b->getSpot(b->getIndice(x + 1,y)))->getLetter() == 0))
            ||(x + 1 > 14)){
              //recordplay
              Move new_move = Move (word,b->getIndice(x, y),'H');
              unsigned short int new_points = score(new_move); // = l'appel récursif
              std::cout << "Hun coup possible " << word
                        << " ; qui donne : " << new_points <<  " points" << std::endl;
              if (new_points > points){
                move = new_move;
                points = new_points;
              }
        }
      }
    }
    //sinon si la branche est vide je continue d'avancer à droite
    //if(new_arc == nullptr) std::cout<<"new_arc est vide"<<std::endl;
    if(new_arc != nullptr){
      if(direction == 1){
        if(y+1 <= 14){
          unsigned int suivant = b->getIndice(x,y+1);
          Gen(suivant, pos+1, word, rack, new_arc, direction, b, points, move);
        }

      }
      else{
        if(x+1 <= 14){
          unsigned int suivant = b->getIndice(x+1,y);
          Gen(suivant, pos+1, word, rack, new_arc, direction, b, points, move);
        }
      }
    }
  }
}
