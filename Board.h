/*
 * Board.h
 *
 *  Created on: Sep 18, 2016
 *      Author: kempe
 */

/* The class Board encodes the state of the Scrabble board.
   It provides functions for displaying the board,
   and for returning the words (and score) that would be obtained by a move.
*/

#ifndef BOARD_H_
#define BOARD_H_

#include <string>
#include <set>
#include <map>
#include <vector>
#include "Tile.h"
#include "Square.h"
#include "Move.h"

class Board {
public:
	Board (std::string board_file_name);
        /* constructor that initializes the board state with an empty board
           and the size and bonuses and start square based on the given file. 
	   If the given file cannot be opened, will throw a FileException
	   with message "BOARD".
	   If the file contains unexpected characters, will throw a FileException
	   with message "BOARDCONTENT".
	*/

	~Board ();

	void initialize (std::string init_file_name);
        /* reads a file that will place tiles at some locations to create
	   an initial board to start from.
	   If the given file cannot be opened, will throw a FileException
	   with message "INIT".
	   If the file contains unexpected characters, will throw a FileException
	   with message "INITCONTENT".
	*/

	std::string getDisplay () const;
        /* returns the current state of the board (including all placed letters)
           as one string that can be written to cout to show the player. */

	std::vector<std::string> getWords (const Move &m, int &score) const;
        /* returns a vector of all words that would be formed by executing the
           given move. The score variable that is passed by reference is
           overwritten to contain the score of all the words combined 
           (with all multipliers, but not the 50-point bonus for all letters).
	   The last entry of the vector is always the "main" word formed
	   in the direction chosen by the user; the others could be in arbitrary
	   order. (This is helpful for backtracking search.)
           This function throws MoveException objects to signal illegal moves.
           Specifically, the following messages could be included in the
           MoveException:
           - "OUTOFBOUNDS": One or more tile would have to be placed out of bounds of the board.
           - "OCCUPIED": The proposed starting square was occupied by a tile already.
	   - "NOSTART": During the very first move, the player did not use the start square.
	   - "NOWORDS": The player did not produce any words (placed one letter at the start, or no letters later).
	   - "NONEIGHBOR": The proposed move is not adjacent to any previously placed tile.
	*/

	std::vector<std::string> getWords (const Move &m, int &score, bool &valid) const;
        /* nearly identical to the other Board::getWords() function.
	   The only difference is that it throws fewer exceptions, 
	   which could be very useful for backtracking search.
           Specifically, it only throws the following MoveException versions:
           - "OUTOFBOUNDS"
           - "OCCUPIED"
	   When the move is the first move and the start square was not included,
	   or the move was a later move not adjacent to any tiles,
	   or the move used an empty tile string,
	   it instead sets the bool valid to false.
	   If the function returns with valid == true, then the move was legal.
	*/

	void executeMove (const Move & m);
	/* Executes the given move, by placing the tiles on the board.
	   This function does not check for correctness of the move, so could
	   segfault or cause other errors if called for an incorrect move. 
	   When a blank tile '?' is placed on the board, it is treated as a letter,
	   i.e., the corresponding square has that letter (with score 0) placed on it.
	*/

	std::map<char,int> getTileCount () const;
	/* returns a map, giving for each character (upper-case letter, '?')
	   how many copies of that letter have been placed by players
	   on the board so far. 
	   This does not include tiles placed by Board::initialize, 
	   since they were not drawn from the bag.
	*/

	Square * getSquare (int x, int y) const;
	/* Returns a pointer to the Square object representing the
           (y,x) position of the board. Indexing starts at 0 here.
	   This is needed only for the Qt version, to display the board. */

	int getRows() const;
	/* Returns the number of rows of the board.
	   Needed only for the Qt version, to build the display.
	*/

	int getColumns() const;
	/* Returns the number of columns of the board.
	   Needed only for the Qt version, to build the display.
	*/

protected:
	Square ** s;
	std::map<char,int> tilecount; 
	bool _empty;
	int _x, _y;
	int _startx, _starty;

	bool inBounds (int x, int y) const;
	void calculateBoundaries (int numToPlace, int x, int y, int dx, int dy, int &sx, int &sy, int &l) const;
	void getWords (std::vector<std::string> & allWords, int sx, int sy, int dx, int dy,
		       std::vector<Tile*> v, int &score, bool main, bool &valid) const;
	bool hasOccupiedNeighbor (int x, int y) const;
};


#endif /* BOARD_H_ */
