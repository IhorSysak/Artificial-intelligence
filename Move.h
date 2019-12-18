/*
 * Move.h
 *
 *  Created on: Sep 18, 2016
 *      Author: kempe
 */

/* The class Move encodes a move made by one player, including its type
   (PASS, EXCHANGE, PLACE), the tiles used (and use for blanks),
   start square, and direction (if needed).
   It has a number of constructors for different types of moves and
   different ways of constructing them, and also does some basic legality checks
   on the moves. */

#ifndef MOVE_H_
#define MOVE_H_

#include <vector>
#include <string>
#include "Tile.h"
#include "Player.h"

class Player;

class Move {
public:
	Move (std::string m, const Player &p); 
	/* Parses the given move m, and constructs the corresponding move.
	   m is assumed to be in the format for the console version of the game.
	   The player passed in is used to verify that the proposed tiles are
	   in fact in the player's hand.
	   It can handle all three types of move (PASS, EXCHANGE, PLACE).
	   Coordinates start with 1.
	   Can throw MoveException, with the following messages:
	   - "EMPTY": The player proposed to place/exchange 0 tiles.
	   - "MALFORMED": Format error in expression, e.g., missing direction or garbage characters.
	   - "UNKNOWN": Unknown type of command (other than PASS, EXCHANGE, PLACE)
	   - "NOTLETTER": The player typed something other than a letter or '?' to place/exchange.
	   - "WRONGTILES": The player did not have all of the proposed tiles.
	*/

        Move (int x, int y, bool horizontal, std::vector<Tile*> tiles);
	/* Creates a PLACE move, starting at row y, column x, placing the tiles
	   described by the vector tiles. If "horizontal" is true, then the tiles
	   are placed horizontally, otherwise vertically.
	   Coordinates start with 1.
	   Throws MoveException with message "EMPTY" if the tile vector is empty.
	*/

        Move (int x, int y, bool horizontal, std::string m, const Player &p);
	/* Creates a PLACE move, starting at row y, column x, placing the tiles
	   described by the string m. If "horizontal" is true, then the tiles
	   are placed horizontally, otherwise vertically.
	   Coordinates start with 1.
	   The player passed in is used to verify that the proposed tiles are
	   in fact in the player's hand.
	   The string m is in the format described in HW4; in particular, a '?'
	   must be followed by the letter it is to be used as.
	   Can throw MoveException, with the following messages:
	   - "EMPTY": The player proposed to place 0 tiles.
	   - "NOTLETTER": The player typed something other than a letter or '?' to place.
	   - "WRONGTILES": The player did not have all of the proposed tiles.
	*/

        Move (std::vector<Tile*> tiles);
        /* Creates an EXCHANGE move, exchanging the tiles in the vector tiles.
	   Throws a MoveException with message "EMPTY" if the vector is empty. */
        Move (bool dummy, std::string m, const Player &p);
        /* Creates an EXCHANGE move, exchanging the tiles described by m.
	   The player passed in is used to verify that the proposed tiles are
	   in fact in the player's hand.
	   The dummy variable is completely ignored - it is only there to 
	   distinguish this constructor from the "generic" one above.
	   The string m is just the sequence of letters (or '?') to be exchanged.
	   Can throw MoveException, with the following messages:
	   - "EMPTY": The player proposed to exchange 0 tiles.
	   - "NOTLETTER": The player typed something other than a letter or '?' to exchange.
	   - "WRONGTILES": The player did not have all of the proposed tiles.
	*/

        Move ();
        // creates a PASS move

	bool isPass () const;
	/* Returns true iff the move is a PASS move */

	bool isExchange () const;
	/* Returns true iff the move is an EXCHANGE move */

	bool isWord () const;
	/* Returns true iff the move is a PLACE move */

	int x () const;
	/* Returns the value of the x coordinate for a PLACE move.
	   Return value could be arbitrary for other types of moves. 
	   Coordinates start with 1. */

	int y () const;
	/* Returns the value of the y coordinate for a PLACE move.
	   Return value could be arbitrary for other types of moves. 
	   Coordinates start with 1. */

	bool isHorizontal () const;
	/* Returns the direction (true for horizontal) for a PLACE move.
	   Return value could be arbitrary for other types of moves. */

	std::vector<Tile*> tileVector () const;
	/* Returns the vector of tiles associated with a PLACE/EXCHANGE move.
	   Return value could be arbitrary for PASS moves. */

protected:
	bool _exchange, _pass;
	int _x, _y;
	bool _horizontal;
	std::vector<Tile*> _tiles;

	void checkForLetter (std::string s);
};


#endif /* MOVE_H_ */
