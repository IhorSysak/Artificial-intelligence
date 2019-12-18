#include "AbstractAI.h"
#include "Move.h"
#include "Dictionary.h"
#include "Exceptions.h"
#include <string>
#include <vector>

using namespace std;

class GreedyAI : public AbstractAI{

public:

	GreedyAI();

	//GreedyAI(Board* b);

	~GreedyAI();

	string getName();

	void initialize(Dictionary* dict);

	Move getMove (const Board & board, const Player & player, std::map<char, int> initialTileCount);

	void solveHelperHorizontal(int rows, int cols, int start_row, int start_col, string used, string temp, string remaining, const Player& player, const Board& board);

	void solveHelperVertical(int rows, int cols, int start_row, int start_col, string used, string temp, string remaining, const Player& player, const Board& board);
	
	//bool solveHelperHorizontal(int rows, int cols, const Board& board, const Player& player, const string& hand);	

	//bool solveHelperVertical(int rows, int cols, Board& board, Player& player, string& hand);

	//void func(int rows, int cols, const Board& board, const Player& player, string temp, string word);

	//void func(int rows, int cols, string used, string temp, string remaining, const Player& player, const Board& board);


private:
	Dictionary* d;
	set<string>prefix;
	vector<vector<string> >moves;
	vector<int>scores;


};
