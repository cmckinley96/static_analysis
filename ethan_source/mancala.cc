/*

    Ethan Malenchek   CS2401    Project 6   April 2018

    This is the implementation file (.cc) for the
    mancala.h header file. Provides implementation
    for all files in the Mancala class.

*/

#include <iostream>
#include <string>
#include <iomanip>
#include "game.h"
#include "mancala.h"

using namespace main_savitch_14;

Mancala::Mancala() {
  //Initiates the board.
  board[0] = 0;
  board[1] = 4;
  board[2] = 4;
  board[3] = 4;
  board[4] = 4;
  board[5] = 4;
  board[6] = 4;
  board[7] = 0;
  board[8] = 4;
  board[9] = 4;
  board[10] = 4;
  board[11] = 4;
  board[12] = 4;
  board[13] = 4;

}

void Mancala::display_status()const {

  if(game::moves_completed() == 0) {
    cout << string(20, '-') << "Starting Game" << string(22, '-') << endl;
  } else if(next_mover() == COMPUTER) {
      cout << string(20, '-') << "Computer Turn" << string(21, '-') << endl;
    } else {
        cout << string(20, '-') << "Player Turn" << string(20, '-') << endl;
      }


  cout << GREEN;
  cout << B_WHITE << string(11,' ') << 'A' << string(5, ' ') << 'B' << string(5, ' ') << 'C' <<
    string(5, ' ') << 'D' << string(5, ' ') << 'E' << string(5, ' ') << 'F' << string(12, ' ');
  cout << "   " << B_GREEN << string(48, ' ') << B_WHITE << "   " << endl;
  cout << B_WHITE << " 1 " << B_GREEN << " " << B_WHITE << "   " << B_GREEN << " ";
  for(int i = 13; i > 7; i--) {
    cout << B_GREEN << " " << B_WHITE << std::setw(3) << board[i] << " " << B_GREEN << " ";
  }
  cout << B_GREEN << " " << B_WHITE << "    " << B_GREEN << " " << B_WHITE << "   " << endl;
  cout << B_WHITE << "   " << B_GREEN << " " << B_WHITE << RED << std::setw(3) << board[0] << BLUE << " " << B_GREEN << " ";
  cout << B_GREEN << string(36, ' ');
  cout << B_GREEN << " " << B_WHITE << GREEN << std::setw(3) << board[7] << BLUE << " " << B_GREEN << " " << B_WHITE << "   " << endl;
  cout << B_WHITE << " 2 " << B_GREEN << " " << B_WHITE << "   " << B_GREEN << " ";
  for(int i = 1; i < 7; i++) {
    cout << B_GREEN << " " <<  B_WHITE << std::setw(3) << board[i]<< " " << B_GREEN << " ";
  }
  cout << B_GREEN << " " << B_WHITE << "   " << B_GREEN << " " << B_WHITE << "   " << endl;
  cout << B_WHITE << "   " << B_GREEN << string(48, ' ') << B_WHITE << "   " << endl;
  cout << B_WHITE << string(54, ' ') << endl;
  cout << RESET;


}

int Mancala::convert(const std::string& move)const {
  int pos = (move[0] - 'A') + 1;
  int row = atoi(&move[1]);

  if(row == 1) {
    row = 14 - pos;
    return row;
  } else {
    return pos;
  }

}

bool Mancala::is_legal(const std::string& move)const {
  int pos = convert(move);
  int row = atoi(&move[1]);
  if(next_mover() != COMPUTER) {
    if(((pos >= 1 && pos <= 6) && row == 2) && board[pos] != 0) {
      return true;
    } else {
        if(((pos >= 8 && pos <= 13) && row == 1) && board[pos] != 0) {
          return true;
        }
      }
    }
return false;
}

void Mancala::make_move(const std::string& move) {
    bool extra_turn = false;
    int index = convert(move);

    int stones = board[index];
    board[index] = 0;

    int end;

    if((stones + index) > 13) {
        end = (stones + index) - 14;
        if(next_mover() != COMPUTER) {
          if(end == 0) {
            end = 1;
          }
        } else if(next_mover() == COMPUTER) {
            if(end == 7) {
              end = 8;
            }
        }
    } else {
        end = stones + index;
        if(next_mover() != COMPUTER && end == 0) {
          end = 1;
        } else if(next_mover() == COMPUTER && end == 7) {
            end = 8;
          }
      }

      if(next_mover() != COMPUTER) {
        if(((stones + index) - 7) == 0) {
          extra_turn = true;
        }
      } else {
          if(((stones + index) - 14) == 0) {
            extra_turn = true;
          }
        }


          index++;
          size_t count = 0;

          for(; count < stones; count++) {
                  if(index >= 14) {
                          index = 0;
                  }

                  if(next_mover() != COMPUTER) {
                          if(index == 0) {
                                  index = 1;
                          }
                          board[index]++;
                          index++;
                  }
                  else{
                          if(index == 7) {
                                  index = 8;
                          }
                          board[index]++;
                          index++;
                  }

          }

          if(next_mover() != COMPUTER) {
                  if(end == 1) {
                          board[end] += board[13];
                          board[13] = 0;
                  }
                  if(end == 2) {
                          board[end] += board[12];
                          board[12] = 0;
                  }
                  if(end == 3) {
                          board[end] += board[11];
                          board[11] = 0;
                  }
                  if(end == 4) {
                          board[end] += board[10];
                          board[10] = 0;
                  }
                  if(end == 5) {
                          board[end] += board[9];
                          board[9] = 0;
                  }
                  if(end == 6) {
                          board[end] += board[8];
                          board[8] = 0;
                  }
          }
          else{
                  if(end == 13) {
                          board[end] += board[1];
                          board[1] = 0;
                  }
                  if(end == 12) {
                          board[end] += board[2];
                          board[2] = 0;
                  }
                  if(end == 11) {
                          board[end] += board[3];
                          board[3] = 0;
                  }
                  if(end == 10) {
                          board[end] += board[4];
                          board[4] = 0;
                  }
                  if(end == 9) {
                          board[end] += board[5];
                          board[5] = 0;
                  }
                  if(end == 8) {
                          board[end] += board[6];
                          board[6] = 0;
                  }
          }

          if(is_game_over()) {
                  board[0] = board[0] + board[8] + board[9] + board[10] + board[11] + board[12] + board[13];
                  for(size_t i = 8; i < 14; i++) {
                          board[i] = 0;
                  }
                  board[7] = board[7] + board[1] + board[2] + board[3] + board[4] + board[5] + board[6];
                  for(size_t i = 1; i < 7; i++) {
                          board[i] = 0;
                  }
          }

          if(extra_turn == false) {
                  game::make_move(move);
          }
          else{
                  cout << "EXTRA TURN" << endl;
          }


  }



bool Mancala::is_game_over()const {
  if(board[1] == 0 && board[2] == 0 && board[3] == 0 && board[4] == 0 && board[5] == 0 && board[6] == 0) {
               return true;
  }
  if(board[8] == 0 && board[9] == 0 && board[10] == 0 && board[11] == 0 && board[12] == 0 && board[13] == 0) {
               return true;
  }
  return false;
}



game* Mancala::clone()const {
    Mancala *tmp;
    tmp = new Mancala;
    for(size_t i = 0; i < 14; i++) {
      tmp -> board[i] = board[i];
    }
    return tmp;
}

void Mancala::compute_moves(std::queue<std::string>& moves)const {
  char c;
  string tmp;

  if(next_mover() == COMPUTER) {
    for(size_t i = 13;i > 7; i--) {
      if(board[i] != 0) {
        c = ((14 - i) + 'A' - 1);
        tmp.push_back(c);
        tmp.push_back('1');
        moves.push(tmp);
      }
    }
  } else {
    for(size_t i = 1; i < 7; i++) {
      if(board[i] != 0) {
        c = i + 'A' - 1;
        tmp.push_back(c);
        tmp.push_back('2');
        moves.push(tmp);
      }
    }
  }
}



game::who Mancala::winning()const {
  if(board[0] > board[7]) {
    return COMPUTER;
  }
  if(board[0] < board[7]) {
    return HUMAN;
  }
  return NEUTRAL;
}

int Mancala::evaluate()const {
  return board[0] - board[7];
}
