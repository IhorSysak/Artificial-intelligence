/*
 * Dictionary.h
 *
 *  Created on: Sep 18, 2016
 *      Author: kempe
 */

/* The class Dictionary encodes the list of all legal words. */

#ifndef DICTIONARY_H_
#define DICTIONARY_H_

#include <set>
#include <string>

class Dictionary {
public:
	Dictionary (std::string dictionary_file_name);
	/* The constructor gets passed the name of the file from which
	   to read the word list.
	   If the file cannot be opened, it will throw a FileException
           with message "DICTIONARY". */

	~Dictionary ();

	bool isLegalWord (std::string word) const;
	/* Checks whether the given word is in the dictionary, and returns true if so.
	   Case does not matter. */

	std::set<std::string> allWords () const;
	/* Returns the set of all words in the dictionary.
	   Mostly meant for a computer player that wants to use this set to
	   construct useful search-curtailing maps. */

private:
	std::set<std::string> _wordset;
};


#endif /* DICTIONARY_H_ */
