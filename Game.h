/*
 * Game.h
 *
 *  Created on: Oct 11, 2016
 *      Author: kempe
 */

/* Encodes the state of the Scrabble game, with all players, the board,
   the dictionary, and the bag.
   Allows to add players, make moves, and obtain information about the
   current state.
*/

#ifndef GAME_H_
#define GAME_H_

#include <string>
#include <vector>
#include <map>
#include "Board.h"
#include "Bag.h"
#include "Dictionary.h"

class Game {
public:
	Game (std::string config_file_name);
	/* Constructor initializing the game from the configuration file.
	   Will not add any players to the game.
	   Can throw two types of exceptions, with different messages:
	   ConfigParameterException:
	   - "NUMBER": The config file did not specify the number of tiles for a hand.
	   - "BOARD": The config file did not specify a file to read the board from.
	   - "TILES": The config file did not specify a file to read the bag from.
	   - "DICTIONARY": The config file did not specify a file to read the dictionary from.
	   FileException:
	   - "CONFIG": The config file could not be opened.
	   - "BAG": The bag file could not be opened.
	   - "BOARD": The board file could not be opened.
	   - "BOARDCONTENT": The board file contained a wrong symbol.
	   - "INIT": The initialization file cound not be opened.
	   - "INITCONTENT": The initialization file contained a wrong symbol.
	   - "DICTIONARY": The dictionary file could not be opened.
	*/

	~Game ();

        void addPlayer (std::string name);
	/* Adds the player with the given name to the game.
	   The player will also be given their tiles at this time. 
	*/

	Board* getBoard () const;
	/* Returns a pointer to the board the game uses. */

	Player* getCurrentPlayer () const;
	/* Returns a pointer to the player whose turn it is. */

	std::vector<std::pair<std::string,int> > getScores() const;
	/* Returns the current scores of all players as a vector of pairs,
	   where each pair consists of the name of the player and their score. */

	std::vector<std::string> getWinners() const;
	/* Returns a vector with all the players that are tied for the win. */

	void refillTiles ();
	/* Fill the hand of the current player back up to the required number of tiles,
	   by drawing random tiles from the bag.
	*/

	void makeMove (const Move & m);
	/* Tries to execute the given move, and if possible, does execute it.
	   Otherwise throws an exception that describes the error.
	   The exceptions are exactly the ones thrown by Board::getWords, 
	   with one additional MoveException possible:
	   - "WORD:<word>" signals that the given <word> was not in the dictionary. 
	     (E.g., "WORD:brillig" would signal that the move was illegal because 
	     "brillig" was not in the dictionary.)
	   When an exception happens, the state of the game is not altered.

	   When a move is executed, the following happens:
	   - PASS: nothing
	   - EXCHANGE: the proposed tiles are returned to the bag, and the player 
	               draws new tiles to refill their hand.
	   - PLACE: the word is placed on the board, the score (including possibly
	            the 50 point bonus) is added for the player,
		    the tiles are removed from the player's hand and deleted from the game,
		    and the player's hand is refilled.
	    The player is not yet advanced to the next round, nor is the information
	    on whether the game is finished updated (see Game::finalizeMove).
	*/
	   
	void finalizeMove ();
	/* This finalizes a round, by doing the following:
	   - updating the information on whether the game is finished by 
	     emptying the bag.
	   - advancing the player for the next round if the game is finished.

	   The reason this is not done in Game::makeMove is so that the UI
	   can show the player their new score, new tiles, etc., which would
	   be harder if the turn is advanced already.
	   When the game is finished, the player is not advanced at all so
	   that the final calculations (score transfer) can be computed correctly.
	*/

	std::vector<std::pair<std::string,int> > finalSubtraction ();
	/* Performs the final subtraction, where the player who finished their
	   tiles first gets points for the tiles the other players had in their hand.
	   It returns a representation of this subtraction as a vector of pairs.
	   Each entry contains the name of a player (a string), 
	   and an integer for the number of points this player gave to the finisher.
	*/

	bool isFinished () const;
	/* Returns true iff one of the game ending conditions applies,
	   i.e., if all players have passed, 
	   or a player finished their tiles when the bag is empty. */

	bool bagEmpty () const;
	/* Returns true iff the bag is empty. */

	int getRecentScore () const;
	/* Returns the score of the most recent move. 
	   This is helpful for displaying to a player what their
	   score for the last move was. */

	std::vector<std::string> getRecentWords() const;
	/* Returns the vector of all the words formed by the most recent
	   PLACE move. This is useful for displaying to a player what
	   words they formed. */

	std::string getRecentDraw() const;
	/* Returns the most recent draw of tiles to be added to a hand.
	   This is useful for showing players what tiles they just drew
	   to add to their hand. */

	std::map<char,int> initialTileCount() const;
	/* Returns a map, giving for each character (upper-case letter or '?')
	   the number of copies of that tile that were *initially* in the bag. */

	Dictionary* getDictionary() const;
	/* Returns a pointer to the dictionary object used in the game. */

protected:
	void readConfigFile (std::string config_file_name,
			     std::string & dictionary_file_name,
			     std::string & board_file_name,
			     std::string & bag_file_name,
			     std::string & init_file_name,
			     unsigned int & hand_size);

	Board *board;
	Bag *bag;
	Dictionary *dict;
	unsigned int numTiles;
	std::vector<Player*> players;

	unsigned int passes;
	unsigned int currentPlayer;
	int recentScore; // most recent move's score
	std::set<Tile*> newTiles; // tiles about to be added
	std::string recentDraw; // most recently added tiles
	std::vector<std::string> recentWords; // most recently placed words
	bool finished;
};


#endif /* GAME_H_ */
