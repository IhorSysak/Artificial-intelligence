/*
 * Bag.h
 *
 *  Created on: Sep 18, 2016
 *      Author: kempe
 */

/* The class Bag encodes a bag of tiles for the players to draw tiles from. */

#ifndef BAG_H_
#define BAG_H_

#include <vector>
#include <string>
#include <set>
#include <map>
#include "Tile.h"

class Bag {

public:
	Bag (const std::string bag_file_name, int random_seed);
        /* constructor that receives the name of the file to read the bag
           from and a random seed to use for the random draws. 
	   Throws a FileException with message "BAG" if the file could not be opened.
	*/

	~Bag ();
        /* The destructor for the bag will delete all of the remaining
           tiles in the bag. */

	void addTile (Tile *tile);
        /* adds a single Tile* to the bag. */

	void addTiles (std::vector<Tile*> tiles);
        /* adds all of the Tile* in the vector to the bag. */

	std::set<Tile*> drawTiles (int number);
        /* returns a random set of tiles of the given number.
           If the bag does not contain enough tiles, then it
           returns all of the remaining tiles. */

	int tilesRemaining () const;
        /* returns the number of tiles remaining in the bag. */

	std::map<char,int> initialTileCount() const;
	/* returns a map, giving for each character (upper-case letter or '?')
	   the number of copies of that tile that were *initially* in the bag. */

private:
	std::vector<Tile*> _tiles;
	std::map<char,int> _initcount;
};


#endif /* BAG_H_ */
