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
    res += temp.first;
    if (temp.second > wf)
      wf = temp.second;
    copy.pop_back();
  }
  return (wf * res);
}


void Game::getCrossSetsHorizontal(const unsigned char & square,
                                  char tab_horizontal[], bool final) {
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

            if (copy->getNode(i) != nullptr) {

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
                                  char tab_vertical[], bool final) {
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

            if (copy->getNode(i) != nullptr) {

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
    else
    {
      for(int i = 0; i < 26; i++){
        tab_vertical[i] = gad->getLetter(i);
      }
    }

  }
  else
  {
    for(int i = 0; i < 26; i++){
      tab_vertical[i] = '/';
    }
  }
}


void Game::Gen(unsigned char square, int pos, std::string& word,
         unsigned int rack[], Node* arc, unsigned int direction, Board* b){

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
    GoOn(square, pos,letter, word, rack, next_arc, arc, direction, b);

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
          GoOn(square, pos,'A'+ i, word, rack, next_arc, arc, direction, b);
        }
    }

  }
}


void Game::GoOn(unsigned char  square, int pos, char L,std:: string& word,
          unsigned int rack[],Node* new_arc,
          Node* old_arc,unsigned int direction, Board* b){

  unsigned char x = (b->getIndice(square)).first;
  unsigned char y = (b->getIndice(square)).second;
  //std::cout<<"je rentre dans la fontion GoOn"<<std::endl;
  if(pos <= 0 ){ // se déplacer à gauche
      //std::cout<<"pos est <= 0 "<<std::endl;
      //std::cout<<"j'ajoute à mon mot la lettre: "<< L << " à gauche"<<std::endl;
      word = L + word;
      //std::cout<<"WORD : "<< word <<std::endl;
      if(new_arc->isFinal()){
        //std::cout<<"je rentre avec la lettre "<< L <<" et elle est finale" <<std::endl;
        // si la lettre est finale , et qu'il n'y a pas de case non vide
        // directement à gauche -> j'enregistre de coup
        if(direction == 1){
          if ((b->getSpot(b->getIndice(x,y-1)))->getLetter() == 0){
                //recordplay
                std::cout<< "un * coup possible " << word <<std::endl;
          }
        }
        else{
          if ((b->getSpot(b->getIndice(x-1,y)))->getLetter() == 0){
                //recordplay
                std::cout<< "un *  coup possible " << word <<std::endl;
          }
        }
      }

      if(new_arc != nullptr){
        //std::cout<<"new_arc n'est pas vide "<<std::endl;
        //j'avance dans le gaddag et le plateau
        if(direction == 1){
          if(y-1 >= 0){
            // je continue à gauche
            unsigned int suivant = b->getIndice(x,y-1);
            Gen(suivant, pos-1, word, rack, new_arc, direction, b);
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
                  && ((b->getSpot(b->getIndice(x,y-pos+1)))->getLetter() == 0))))
                  std::cout<<"coup possible "<< word <<std::endl;
                //std::cout<<"je rentre dans le if"<<std::endl;
                if(y-pos+1 <= 14){
                  unsigned int suivant = b->getIndice(x,y-pos+1);
                  Gen(suivant, 1, word, rack, new_arc, direction, b);
                }

              }

        }
        else{

          if(x-1 >= 0){
            // je continue à gauche
            unsigned int suivant = b->getIndice(x-1,y);
            Gen(suivant, pos-1, word, rack, new_arc, direction, b);
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
                  && ((b->getSpot(b->getIndice(x-pos+1,y)))->getLetter() == 0))))
                  std::cout<<"coup possible "<< word <<std::endl;

                if(x-pos+1 <= 14){
                  unsigned int suivant = b->getIndice(x-pos+1,y);
                  Gen(suivant, 1, word, rack, new_arc, direction, b);
                }
              }
        }

      }
  }
  else if (pos > 0){ //se déplacer à droite
    //std::cout<<"j'ajoute à mon mot la lettre: "<< L << " à droite"<<std::endl;
    word = word + L;
    //std::cout<<"WORD : "<< word <<std::endl;
    //std::cout<<"pos est > 0 "<<std::endl;
    if((new_arc != nullptr) && (new_arc->isFinal())){
      //std::cout<<"je rentre avec la lettre "<< L <<" et elle est finale" <<std::endl;
      // si la lettre est finale , et qu'il n'y a pas de case non vide
      // directement à droite -> j'enregistre de coup
      if(direction == 1){

        if (((y + 1 <= 14)
            && ((b->getSpot(b->getIndice(x,y+1)))->getLetter() == 0))
            ||(y + 1 > 14)){
              std::cout<< "un coup possible " << word <<std::endl;
        }
      }
      else{
        if (((x + 1 <= 14)
            && ((b->getSpot(b->getIndice(x + 1,y)))->getLetter() == 0))
            ||(x + 1 > 14)){
              //recordplay
              std::cout<< "un coup possible " << word <<std::endl;
        }
      }
    }
    //sinon si la branche est vide je continue d'avancer à droite
    //if(new_arc == nullptr) std::cout<<"new_arc est vide"<<std::endl;
    if(new_arc != nullptr){
      if(direction == 1){
        if(y+1 <= 14){
          unsigned int suivant = b->getIndice(x,y+1);
          Gen(suivant, pos+1, word, rack, new_arc, direction, b);
        }

      }
      else{
        if(x+1 <= 14){
          unsigned int suivant = b->getIndice(x+1,y);
          Gen(suivant, pos+1, word, rack, new_arc, direction, b);
        }
      }
    }
  }
}
