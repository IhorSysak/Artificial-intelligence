/*
 * Player.h
 *
 *  Created on: Sep 18, 2016
 *      Author: kempe
 */

/* Encodes the state of a player, mostly the name, tiles, points. 
   The main non-trivial ability of this class is to produce a vector
   of Tile* from a string describing tiles to place/exchange. */

#ifndef PLAYER_H_
#define PLAYER_H_

#include <string>
#include <set>
#include "Tile.h"
#include "Move.h"

class Move;

class Player
{
public:
	Player (std::string name);
	/* Constructor giving the player the given name, and setting his points to 0.
	   Does not give the player any tiles. 
	*/

	~Player ();
	/* Destructor for a player. Deletes all the tiles the player still has. */

	void addPoints (int points);
	/* Increments the player's score by the given amount. */

	std::string getName () const;
	/* Returns the player's name. */

	int getPoints () const;
	/* Returns the player's current score. */

	int numberofTiles () const;
	/* Returns the number of tiles the player currently has. */

	int remainingPoints () const;
	/* Returns the total value of all tiles the player still has.
	   Used in the final subtraction of the game. */

	std::string getHand () const;
	/* Returns a string representation of the tiles the player holds.
	   Used for displaying the player's tiles in the Console version. */

	std::set<Tile*> getHandTiles() const;
	/* Returns the set of tiles the player currently holds.
	   Used in the Qt version to display the player's tiles. */

	std::vector<Tile*> getTiles (std::string move, bool resolveBlanks) const;
	/* Returns a vector of tiles corresponding to the given string.
	   The boolean resolveBlanks states whether this is a PLACE or EXCHANGE move.
	   If resolveBlanks is true, then when the string contains a '?',
	   the next letter is interpreted as the letter to use the blank as,
	   and the "use" field of the tile is set accordingly.
	   This function may throw a MoveException with message "WRONGTILES"
	   if the player does not have the tiles described by move.
	*/

	void removeTiles (Move m);
	/* Removes all the tiles stored in m from the player's hand. */

	void addTiles (std::set<Tile*> tilesToAdd);
	/* Adds all the tiles in the set to the player's hand. */

private:
	std::string _name;
	int _points;
	std::set<Tile*> _hand;
};


#endif /* PLAYER_H_ */
