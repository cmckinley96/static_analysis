/*

  Ethan Malenchek   CS2401    Project 6       April 2018

  This is the header file for the Mancala class,
  which is a child of the parent class, used in the
  textbook.

*/

#include "colors.h"
#include "game.h"

using namespace main_savitch_14;

class Mancala: public game {
public:
  //phase1
  Mancala();
  void display_status()const;
  bool is_legal(const std::string& move)const;
  void make_move(const std::string& move);
  int convert(const std::string& move)const;
  //phases 2 & 3
  game* clone()const;
  game::who winning()const;
  void compute_moves(std::queue<std::string>& moves)const;
  int evaluate()const;
  bool is_game_over()const;
private:
  int board[14];
};
