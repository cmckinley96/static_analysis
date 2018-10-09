/******************************************************************
// File: othello.cc
//
//  implementation file for Othello game, which is a child of game.
//  Contains specifics for conducting a game of Othello.
//
//  Colin McKinley || Ohio University
//  Today's Date 8/13/18
*******************************************************************/
#include <iostream>   //Provide cin, cout
#include <string>     //String class
#include <cctype>     //Provides toupper()
#include "game.h"     //Provide parent class
#include "piece.h"    //Provide piece class for game board
#include "othello.h"
using namespace std;


/*********************************
/   Overridden Virtual Functions /
*********************************/

//Checks all flanking directions, and flips where needed
void Othello::make_move(const string& move){
  //Check for pass
  if (move[0] == 'P') {
    main_savitch_14::game::make_move(move);
    return;
  }
  int row, col, tmp_row, tmp_col;
  row = int(toupper(move[0]) - 'A');
  col = int(move[1] - '1');
  game::who mover = game::next_mover();
  piece::color_state target;
  if (mover == HUMAN) {
    target = piece::BLK;
  } else {
    target = piece::WHTE;
  }
  board[row][col].set_color(target);
  //Test scenarios and change
  if (look_left(row, col, target)){
    change_left(row, col, target);
  }
  if (look_up_left(row, col, target)) {
    change_up_left(row, col, target);
  }
  if (look_up(row, col, target)) {
    change_up(row, col, target);
  }
  if (look_up_right(row, col, target)) {
    change_up_right(row, col, target);
  }
  if (look_right(row, col, target)) {
    change_right(row, col, target);
  }
  if (look_down_right(row, col, target)) {
    change_down_right(row, col, target);
  }
  if (look_down(row, col, target)) {
    change_down(row, col, target);
  }
  if (look_down_left(row, col, target)) {
    change_down_left(row, col, target);
  }
  main_savitch_14::game::make_move(move);
}

//Clear game board and put down pieces
void Othello::restart(){
  for (int i=0; i<DIMENSION; ++i) {
    for (int j=0; j<DIMENSION; ++j) {
      if (i == 3 && j == 3) {
        board[i][j].set_color(piece::WHTE);
      }
      else if (i == 4 && j == 4) {
        board[i][j].set_color(piece::WHTE);
      }
      else if (i == 3 && j == 4) {
        board[i][j].set_color(piece::BLK);
      }
      else if (i == 4 && j == 3){
        board[i][j].set_color(piece::BLK);
      }
      else {
        board[i][j].set_empty();
      }
    }
  }
  main_savitch_14::game::restart();
}

//Show current game board
void Othello::display_status() const{
  cout << endl;
  cout << "    1   2   3   4   5   6   7   8 " << endl;
  for (int i=0; i<DIMENSION; ++i) {
    cout << "  ---------------------------------" << endl;
    cout << char('A' + i) << " "; //Output letter for grid
    for (int j=0; j<DIMENSION; ++j) {
      cout << "|";
      board[i][j].output();
    }
    cout << "|" << endl;
  }
  cout << "  ---------------------------------" << endl;
}

//Checks if a move is legal for the next player
bool Othello::is_legal(const string& move) const{
  game::who mover = game::next_mover();
  //Check for pass
  if (move[0] == 'P' && can_player_pass(mover)) {
    return true;
  }
  piece::color_state target;
  if (mover == HUMAN) {
    target = piece::BLK;
  } else {
    target = piece::WHTE;
  }
  int row, col;
  row = int(toupper(move[0]) - 'A');
  col = int(move[1] - '1');
  if (row > 8 || row < 0 || col > 8 || col < 0) {
    return false;
  }
  if (board[row][col].color() != piece::EMPTY) {
    return false;
  }
  return (
    look_left(row, col, target) || look_up_left(row, col, target) ||
    look_up(row, col, target) || look_up_right(row, col, target) ||
    look_right(row, col, target) || look_down_right(row, col, target) ||
    look_down(row, col, target) || look_down_left(row, col, target)
  );
}

//This function is used to tell whether a given move is valid for
//the other player, for detecting end games. The way is_legal is declared in
//the parent, it restricts us to checking the next move.
//It's not a virtual function, but is included here for organization
bool Othello::is_legal_previous(const string& move) const{
  game::who mover = game::last_mover();
  piece::color_state target;
  if (mover == HUMAN) {
    target = piece::BLK;
  } else {
    target = piece::WHTE;
  }
  int row, col;
  row = int(toupper(move[0]) - 'A');
  col = int(move[1] - '1');
  if (row > 8 || row < 0 || col > 8 || col < 0) {
    return false;
  }
  if (board[row][col].color() != piece::EMPTY) {
    return false;
  }
  return (
    look_left(row, col, target) || look_up_left(row, col, target) ||
    look_up(row, col, target) || look_up_right(row, col, target) ||
    look_right(row, col, target) || look_down_right(row, col, target) ||
    look_down(row, col, target) || look_down_left(row, col, target)
  );
}

//Checks whether both players can pass. A full board satisfies this condition
bool Othello::is_game_over() const {
  game::who mover = game::next_mover();
  if (can_player_pass(mover) && can_player_pass(opposite(mover))) {
    return true;
  }
  return false;
}

//Overridden for 2 player game to show who is moving
string Othello::get_user_move() const {
  string move;
  game::who mover = game::next_mover();
  if (mover == HUMAN) {
    display_message("Players's turn\n");
  } else {
    display_message("White's turn\n");
  }
  if (can_player_pass(mover)) {
    display_message("No available moves\n");
    move = "P0";
  } else {
    move = main_savitch_14::game::get_user_move();
  }
  return move;
}

//Returns winning player
main_savitch_14::game::who Othello::winning() const {
  int score = 0; //Negative denotes Computer wins, positive is Human
  for (int i=0; i<DIMENSION; ++i) {
    for (int j=0; j<DIMENSION; ++j) {
      if (board[i][j].color() == piece::BLK) {
        --score;
      } else if (board[i][j].color() == piece::WHTE) {
        ++score;
      }
    } //Inner for loop
  } //Outer for loop
  if (score < 0) {
    return HUMAN;
  } else if (score > 0) {
    return COMPUTER;
  } else {
    return NEUTRAL;
  }
}

//Counts pieces on board with black having value -1, white +1
int Othello::evaluate() const {
  int net_score = 0; //Negative denotes Player wins, positive is CPU
  for (int i=0; i<DIMENSION; ++i) {
    for (int j=0; j<DIMENSION; ++j) {
      if (board[i][j].color() == piece::BLK) {
        --net_score;
        //If-else blocks awards additional points for corner points
        if (i==j && i==0) {
          net_score -= 5;
        } else if (i==7 && j==0) {
          net_score -= 5;
        } else if (i==0 && j==7) {
          net_score -= 5;
        }
      } else if (board[i][j].color() == piece::WHTE) {
        ++net_score;
        //If-else blocks awards additional points for corner points
        if (i==0 && j==0) {
          net_score += 5;
        } else if (i==7 && j==0) {
          net_score += 5;
        } else if (i==0 && j==7) {
          net_score += 5;
        } else if (i==7 && j==7) {
          net_score += 5;
        }
      }
    } //Inner for loop
  } //Outer for loop
  return net_score;
}

void Othello::compute_moves(std::queue<std::string>& moves) const {
  char row = 'A';
  char col = '1';
  string tmp = "  ";
  for (int i=0; i<DIMENSION; ++i) {
    for (int j=0; j<DIMENSION; ++j) {
      tmp[0] = char(row + i);
      tmp[1] = char(col + j);
      if (board[i][j].color() == piece::EMPTY){
        if (game::next_mover() == COMPUTER) {
          if (is_legal(tmp)) {
            moves.push(tmp);
          }
        } else {
           if (is_legal_previous(tmp)) {
             moves.push(tmp);
           }
        }
      }
    }
  }
}

/********************************
/   Helper functions            /
********************************/

//Iterates through game board and returns false if a valid move is found
bool Othello::can_player_pass(game::who player) const {
  char row = 'A';
  char col = '1';
  string tmp = "  ";
  for (int i=0; i<DIMENSION; ++i) {
    for (int j=0; j<DIMENSION; ++j) {
      tmp[0] = char(row + i);
      tmp[1] = char(col + j);
      if (board[i][j].color() == piece::EMPTY){
        if (player == game::next_mover()) {
          if (is_legal(tmp)) {
            return false;
          }
        } else {
           if (is_legal_previous(tmp)) {
             return false;
           }
        }
      }
    }
  }
  return true;
}



/********************************
/   Functions for searching     /
/                               /
/ Each function searches in a   /
/ given direction to see if a   /
/ flank occurs                  /
********************************/

bool Othello::look_left(int row, int col, piece::color_state target) const{
  for (int tmp_col = col-1; tmp_col>=0; --tmp_col){
    if (board[row][tmp_col].color() == piece::EMPTY){ //Check for empty space
      return false;
    } else if (board[row][tmp_col].color() == target) {
      return (col-tmp_col > 1); //Check if we have moved more than 1 space
    }
  }
  return false; //If all are of opposite color, we get here & it's not a flank
}

bool Othello::look_up_left(int row, int col, piece::color_state target) const{
  for (
    int tmp_col = col-1, tmp_row = row-1;
    tmp_col>=0 && tmp_row>=0;
    --tmp_col, --tmp_row)
  {
    if (board[tmp_row][tmp_col].color() == piece::EMPTY){ //Check for empty space
      return false;
    } else if (board[tmp_row][tmp_col].color() == target) {
      return (col-tmp_col > 1); //Check if we have moved more than 1 space
    }
  }
  return false; //If all are of opposite color, we get here & it's not a flank
}

bool Othello::look_up(int row, int col, piece::color_state target) const{
  for (int tmp_row = row-1; tmp_row>=0; --tmp_row){
    if (board[tmp_row][col].color() == piece::EMPTY){ //Check for empty space
      return false;
    } else if (board[tmp_row][col].color() == target) {
      return (row-tmp_row > 1); //Check if we have moved more than 1 space
    }
  }
  return false; //If all are of opposite color, we get here & it's not a flank
}

bool Othello::look_up_right(int row, int col, piece::color_state target) const{
  for (
    int tmp_col = col+1, tmp_row = row-1;
    tmp_col<DIMENSION && tmp_row>=0;
    ++tmp_col, --tmp_row)
  {
    if (board[tmp_row][tmp_col].color() == piece::EMPTY){ //Check for empty space
      return false;
    } else if (board[tmp_row][tmp_col].color() == target) {
      return (tmp_col-col > 1); //Check if we have moved more than 1 space
    }
  }
  return false; //If all are of opposite color, we get here & it's not a flank
}

bool Othello::look_right(int row, int col, piece::color_state target) const{
  for (int tmp_col = col+1; tmp_col<DIMENSION; ++tmp_col){
    if (board[row][tmp_col].color() == piece::EMPTY){ //Check for empty space
      return false;
    } else if (board[row][tmp_col].color() == target) {
      return (tmp_col-col > 1); //Check if we have moved more than 1 space
    }
  }
  return false; //If all are of opposite color, we get here & it's not a flank
}

bool Othello::look_down_right(int row,int col, piece::color_state target) const{
  for (
    int tmp_col = col+1, tmp_row = row+1;
    tmp_col<DIMENSION && tmp_row<DIMENSION;
    ++tmp_col, ++tmp_row)
  {
    if (board[tmp_row][tmp_col].color() == piece::EMPTY){ //Check for empty space
      return false;
    } else if (board[tmp_row][tmp_col].color() == target) {
      return (tmp_col-col > 1); //Check if we have moved more than 1 space
    }
  }
  return false; //If all are of opposite color, we get here & it's not a flank
}

bool Othello::look_down(int row, int col, piece::color_state target) const{
  for (int tmp_row = row+1; tmp_row<DIMENSION; ++tmp_row){
    if (board[tmp_row][col].color() == piece::EMPTY){ //Check for empty space
      return false;
    } else if (board[tmp_row][col].color() == target) {
      return (tmp_row-row > 1); //Check if we have moved more than 1 space
    }
  }
  return false; //If all are of opposite color, we get here & it's not a flank
}

bool Othello::look_down_left(int row, int col, piece::color_state target) const{
  for (
    int tmp_col = col-1, tmp_row = row+1;
    tmp_col>=0 && tmp_row<DIMENSION;
    --tmp_col, ++tmp_row)
  {
    if (board[tmp_row][tmp_col].color() == piece::EMPTY){ //Check for empty space
      return false;
    } else if (board[tmp_row][tmp_col].color() == target) {
      return (col-tmp_col > 1); //Check if we have moved more than 1 space
    }
  }
  return false; //If all are of opposite color, we get here & it's not a flank
}



/********************************
/   Functions for state change  /
/                               /
/   All have precondition that  /
/   there is a flank in their   /
/   direction.                  /
/                               /
/   All have postcondition that /
/   flanked pieces are flipped  /
********************************/

void Othello::change_left(int row, int col, piece::color_state target){
  int tmp_col = col-1;
  while (board[row][tmp_col].color() != target){
    board[row][tmp_col].flip();
    --tmp_col;
  }
}

void Othello::change_up_left(int row, int col, piece::color_state target){
  int tmp_col = col-1;
  int tmp_row = row-1;
  while (board[tmp_row][tmp_col].color() != target){
    board[tmp_row][tmp_col].flip();
    --tmp_col;
    --tmp_row;
  }
}

void Othello::change_up(int row, int col, piece::color_state target){
  int tmp_row = row-1;
  while (board[tmp_row][col].color() != target){
    board[tmp_row][col].flip();
    --tmp_row;
  }
}

void Othello::change_up_right(int row, int col, piece::color_state target){
  int tmp_col = col+1;
  int tmp_row = row-1;
  while (board[tmp_row][tmp_col].color() != target){
    board[tmp_row][tmp_col].flip();
    ++tmp_col;
    --tmp_row;
  }
}

void Othello::change_right(int row, int col, piece::color_state target){
  int tmp_col = col+1;
  while (board[row][tmp_col].color() != target){
    board[row][tmp_col].flip();
    ++tmp_col;
  }
}

void Othello::change_down_right(int row, int col, piece::color_state target){
  int tmp_col = col+1;
  int tmp_row = row+1;
  while (board[tmp_row][tmp_col].color() != target){
    board[tmp_row][tmp_col].flip();
    ++tmp_col;
    ++tmp_row;
  }
}

void Othello::change_down(int row, int col, piece::color_state target){
  int tmp_row = row+1;
  while (board[tmp_row][col].color() != target){
    board[tmp_row][col].flip();
    ++tmp_row;
  }
}

void Othello::change_down_left(int row, int col, piece::color_state target){
  int tmp_col = col-1;
  int tmp_row = row+1;
  while (board[tmp_row][tmp_col].color() != target){
    board[tmp_row][tmp_col].flip();
    --tmp_col;
    ++tmp_row;
  }
}
