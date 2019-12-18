/*
 * Square.h
 *
 *  Created on: Sep 18, 2016
 *      Author: kempe
 */

/* This class encodes a single square of the Scrabble board.
   It functions almost as a struct, and does not do interesting computation. */

#ifndef SQUARE_H_
#define SQUARE_H_

class Square {
public:
	Square ()
	  /* Simple constructor without parameters, because we initialize
	     a 2D array of Square (rather than Square*), so we cannot really
	     give parameters at construction time. */
	{
		_LMult = 1; _WMult = 1; // should be overwritten later
		_blocked = false; // should be overwritten later
		_occupied = false;
		_start = false;
		_score = 0;
		_letter = ' ';
	}

	void set (int LMult, int WMult, bool blocked, bool start)
	  /* Sets the word and letter multipliers for a square,
	     and the information on whether it is the start square,
	     and whether it is blocked.
	     (Blocked squares are an add-on we had considered, but which
	     you should not worry about. Just assume that this is always "false".)
	  */
	{
		_LMult = LMult; _WMult = WMult;
		_blocked = blocked;
		_start = start;
	}

	void placeLetter (char letter, int score)
	/* Places a letter with the given score on the square.
	   This marks the square as occupied, and turns the multipliers
	   to 1, since they cannot be reused later. */
	{
		_occupied = true;
		_letter = letter;
		_score = score;
		_LMult = 1; _WMult = 1;
	}

	bool isOccupied () const
	/* Returns whether a tile is placed on this square. */
	{ return _occupied; }

	bool isBlocked () const
	/* Returns whether the square is blocked. Ignore this. */
	{ return _blocked; }

	bool isStart () const
	/* Returns whether the square is the start square. */
	{ return _start; }

	unsigned int getScore () const
	/* Gets the score of the letter placed on the square (if any). 
	 The score of an empty square is 0. */
	{ return _score; }

	unsigned char getLetter () const
	  /* Returns the letter placed on the square (if any).
	     If the square is empty, it returns ' '. 
	     Blanks have to be correctly dealt with in the Board class;
	     the current implementation ensures that we store not a '?'
	     but the letter that the blank is used as. */
	{ return _letter; }

	unsigned int getLMult () const
	  /* Returns the letter multiplier associated with the square.
	     If there is no letter multiplier, it returns 1. */
	{ return _LMult; }

	unsigned int getWMult () const
	  /* Returns the word multiplier associated with the square.
	     If there is no word multiplier, it returns 1. */
	{ return _WMult; }

protected:
	int _LMult, _WMult;
	bool _occupied;
	bool _blocked; 
	bool _start;
	char _letter;
	unsigned int _score;
};



#endif /* SQUARE_H_ */
