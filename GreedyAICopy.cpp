	#include "GreedyAI.h"
	#include <iostream>

	using namespace std;

	GreedyAI::GreedyAI(){
		name = "GreedyAI";

	}

	GreedyAI::~GreedyAI(){
		
	}

	string GreedyAI::getName(){
		return name;
	}

	void GreedyAI::initialize(Dictionary* dict){
		d= dict;
		set<string>temp = dict->allWords();
		for(set<string>::iterator it = temp.begin(); it!=temp.end(); ++it){
			string lol="";
			for(unsigned int i=0; i<=(*it).length(); i++){
				string lol = (*it).substr(0,i);
				if(prefix.find(lol)==prefix.end()){ //not found
					//cout<<lol<<endl;
					prefix.insert(lol);
				}
			}
		}

	}



	Move GreedyAI::getMove (const Board & board, const Player & player, std::map<char, int> initialTileCount){

		moves.clear();
		scores.clear();


		string word;
		set<Tile*> temp = player.getHandTiles();
		for(set<Tile*>::iterator it = temp.begin(); it!=temp.end(); ++it){
			word+=(*it)->getLetter();
		}
		//cout<<boolalpha;
		//cout<<"ISLEGALWORD TEST: "<<d->isLegalWord("DIE");
		cout<<"WORD: "<<word<<endl;

		vector<string>words;

		for(unsigned int i=0; i<word.length(); i++){
			string s;
			s.push_back(word[i]);
			words.push_back(s);
		}

		// cout<<"TEST: "<<endl;
		// stirng s = needles;
		// int index;
		// size_t found = str.find(s);
		// while()



	for(int i=1; i<=8; i++){ //doesn't make moves other than on the starting tile?
		for(int j=1; j<=8; j++){
			if(board.getSquare(i,j+1)->isOccupied()){
				cout<<"HERE"<<endl;
				cout<<i<<j+1<<endl;
				int counter=0;
				string what;
				while(board.getSquare(i,j+1+counter)->isOccupied()){
					what+=board.getSquare(i,j+1+counter)->getLetter();
				}
				cout<<"what: "<<what<<endl;
				words.push_back(what);
				//func(i,j,"","",words,player,board);
			}
			else{
			func(i,j,"","", words, player, board);
			}
		}
	}

		cout<<"VECTOR TEST: ";
		for(unsigned int i=0; i<words.size(); i++){
			cout<<words[i]<<" ";
		}
		cout<<endl;

		cout<<"MOVES SIZE: "<<moves.size()<<endl;
		// int max = 0;
		// int index =0;
		// for(unsigned int i=0; i<scores.size(); i++){
		// 	if(scores[i]>max){
		// 		max = scores[i];
		// 		index = i;
		// 	}
		// }
 
		//  Move* m = moves[index];
		//  return *m;

		Move* m = new Move();
		return *m;

	 }

	//void GreedyAI::func(int rows, int cols, const Board& board, const Player& player, string temp, string remaining){
	void GreedyAI::func(int rows, int cols, string used, string temp, vector<string> remaining, const Player& player, const Board& board){

		// if(cols == board.getColumns()-1){
		// 	return;
		// }

		if(remaining.length()==0){
			cout<<new_temp<<endl;
			return;			
		}

		else{

	        string new_temp;
	        string new_remaining;
	        //string new_used;

	        new_used = temp + remaining[i];
			new_temp = temp + remaining[i];
			new_remaining = remaining;
			new_remaining.erase(0);
			
			//cout<<"ENTER FOR LOOP. i = "<<i<<"  new_temp = "<<new_temp<<", new_remaining = "<<new_remaining<<endl;
			//cout<<temp<<endl;
			if(prefix.find(new_temp)!=prefix.end()){
				 if(d->isLegalWord(new_temp)){				
					// try{
					// Move* currMove = new Move(rows,cols, true, new_used, player);
					// int x=0;
					// board.getWords(*currMove,x);
					// //cout<<"ROWS: "<<rows<<", COLS: "<<cols<<", WORD: "<<new_temp<<", USED: "<<new_used<<", SCORE: "<<x<<endl;
					// moves.push_back(currMove);
					// scores.push_back(x);
					// }

					// catch(MoveException &m){
					// cout<<"ROWS: "<<rows<<", COLS: "<<cols<<", WORD: "<<new_temp<<", USED: "<<new_used<<endl;

					// 	cerr<<m.getMessage()<<endl;
					// }
					cout<<new_temp<<endl;				
				}
				
				//remaining.erase(remaining.begin());
				//cout<<"BEFORE RECURSIVE CALL. "<<endl;
				func(rows,cols, new_used, new_temp, new_remaining, player, board);

			} //end of if prefix

			}//end of for loop
		} //end of else

	}

bool GreedyAI::solveHelperHorizontal(int rows, int cols, const Board& board, const Player& player, const string& hand){
		string buffer;
		string input;

		if(rows > board.getRows()){
			return true;
		}

		else if( cols == board.getColumns()-1){
			return solveHelperHorizontal(rows+1,0, board, player, hand);
		}

		else{
			if(board.getSquare(rows,cols)->isOccupied()==true){ //how do I check every square?
				buffer+=board.getSquare(rows,cols)->getLetter();
				return solveHelperHorizontal(rows,cols+1,board, player, hand);
			}

			else{
				for(unsigned int i=0; i<hand.size(); i++){ 
					buffer+=hand[i];
					if(prefix.find(buffer)!=prefix.end()){
						// vector<> nextHand(hand.begin(), hand.end());
						// nextHand.erase(nextHand.begin() + i);
						if(d->isLegalWord(buffer)){
							//construct move;
							try{
							Move* currMove = new Move(rows,cols, true, buffer, player);
							cout<<rows<<" "<<cols<<endl;
							int x=0;
							board.getWords(*currMove,x);
							moves.push_back(currMove);
							return true; //?
							}

							catch(MoveException &m){
								cerr<<m.getMessage()<<endl;
								return false; //?
							}

						} //end of dictionary if

					}//end of prefix if


				}//end of for loop
				
				buffer=buffer.substr(0,buffer.length()-1);

			}
		 } //end of else

		 return false;

	}

	// bool GreedyAI::solveHelperVertical(int rows, int cols, Board board, Player player){

	// }

