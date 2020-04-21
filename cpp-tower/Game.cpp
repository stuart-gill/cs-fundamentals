/**
 * C++ class for a game of the Tower of Hanoi puzzle.
 * 
 * @author
 *   Wade Fagen-Ulmschneider <waf@illinois.edu>
 */

#include "Game.h"
#include "Stack.h"
#include "uiuc/Cube.h"
#include "uiuc/HSLAPixel.h"

#include <iostream>
using std::cout;
using std::endl;

// remove top of i1 and move to i2
void Game::_move(unsigned i1, unsigned i2){
Cube cube = stacks_[i1].removeTop();
stacks_[i2].push_back(cube);
}

void Game::_legalMove(unsigned i1, unsigned i2){
  if(stacks_[i1].size()==0 && stacks_[i2].size()>0){
    _move(i2,i1);
  } else if (stacks_[i2].size()==0 && stacks_[i1].size()>0){
    _move(i1,i2);
  } else if (stacks_[i1].size()>0 && stacks_[i2].size()>0){
    if (stacks_[i1].peekTop().getVolume() > stacks_[i2].peekTop().getVolume()){
      _move(i2,i1);
    } else {
      _move(i1,i2);
    } 
  }
}

// Solves the Tower of Hanoi puzzle.
// (Feel free to call "helper functions" to help you solve the puzzle.)
void Game::solve() {
  // Prints out the state of the game:
  while (stacks_[2].size() < 4){
    _legalMove(0,1);
    _legalMove(0,2);
    _legalMove(2,1);
  }
    cout << *this << endl;
}

// Default constructor to create the initial state:
Game::Game() {
  // Create the three empty stacks:
  for (int i = 0; i < 3; i++) {
    Stack stackOfCubes;
    stacks_.push_back( stackOfCubes );
  }

  // Create the four cubes, placing each on the [0]th stack:
  Cube blue(4, uiuc::HSLAPixel::BLUE);
  stacks_[0].push_back(blue);

  Cube orange(3, uiuc::HSLAPixel::ORANGE);
  stacks_[0].push_back(orange);

  Cube purple(2, uiuc::HSLAPixel::PURPLE);
  stacks_[0].push_back(purple);

  Cube yellow(1, uiuc::HSLAPixel::YELLOW);
  stacks_[0].push_back(yellow);
}

std::ostream& operator<<(std::ostream & os, const Game & game) {
  for (unsigned i = 0; i < game.stacks_.size(); i++) {
    os << "Stack[" << i << "]: " << game.stacks_[i];
  }
  return os;
}
