all: Scrabble 

Scrabble: Bag.o Board.o Dictionary.o Game.o Move.o Player.o Util.o GreedyAI.o LongestAI.o Scrabble.cpp
	g++ -g -Wall Bag.o Board.o Dictionary.o Game.o Move.o Player.o Util.o GreedyAI.o LongestAI.o Scrabble.cpp -o Scrabble

GreedyAI.o: AbstractAI.h GreedyAI.h GreedyAI.cpp
	g++ -g -Wall -c GreedyAI.cpp -o GreedyAI.o

LongestAI.o: AbstractAI.h LongestAI.h LongestAI.cpp
	g++ -g -Wall -c LongestAI.cpp -o LongestAI.o

clean:
	rm Scrabble


