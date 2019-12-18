#ifndef ABSTRACTAI_H_
#define ABSTRACTAI_H_

#include <string>
#include <map>

#include "Move.h"
#include "Dictionary.h"
#include "Board.h"
#include "Player.h"

class AbstractAI {
 public:
  virtual std::string getName() = 0;
  // returns the name by which the AI would like to be called

  virtual void initialize (Dictionary* dict) = 0;
  /* you can use this function to do pre-processing, such as 
     constructing maps for fast lookup.
     We will call initilalize on your AI before asking it for its first move. */

  virtual Move getMove (const Board & board, const Player & player, std::map<char, int> initialTileCount) = 0;
  /* This will be the main function doing the work.
     You will get the board and player, and have hopefully stored the dictionary.
     You also get a map giving you the initial number of each type of tiles in the bag.
     (The board class allows you to find out how many of each type have been placed.)
     You should return a Move object describing the move your AI wants to make.
  */
};

#endif // ABSTRACTAI_H_
