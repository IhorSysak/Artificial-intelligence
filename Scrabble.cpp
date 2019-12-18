#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <stdexcept>
#include <algorithm>
#include <map>

#include "Bag.h"
#include "Board.h"
#include "Dictionary.h"
#include "Exceptions.h"
#include "Move.h"
#include "Game.h"
#include "Player.h"
#include "Square.h"
#include "Tile.h"
#include "Util.h"
#include "AbstractAI.h"
#include "GreedyAI.h"
#include "LongestAI.h"

using namespace std;

void printInstructions(){
	cout<<"To pass your turn, type PASS."<<endl;
	cout<<"To discard tiles, type EXCHANGE, followed by a string of those tiles."<<endl;
	cout<<"To place a word, type PLACE, followed by the following:"<<endl;
 	cout<<"first, either a | or - for vertical/horizontal placement;"<<endl;
 	cout<<"second, the row (from the top), the column (from the left),"<<endl;
 	cout<<"third, a sequence of letters to place;"<<endl;
 	cout<<"to use a blank tile, type ? followed by the letter you want to use it for."<<endl;
}

int main (int args, char **argv)
{
	if (args < 2 || args > 2)
		throw FileException("Incorrect Files!");

		try{
		Game game(argv[1]);
		
		Dictionary* dict = game.getDictionary();
		set<string>words = dict->allWords();
		// cout<<"WORDS: "<<endl;
		// for(set<string>::iterator it = words.begin(); it!= words.end(); ++it){
		// 	cout<<*it<<endl;
		// }
		vector<GreedyAI>AIholder;
		unsigned int AICounter=0;
		vector<LongestAI>AIholder2;
		unsigned int AICounter2=0;

		int players;
		cout<<"Please enter the number of players(1-8): ";
		cin>>players;

		for(int i=0; i<players; i++){
			string name;
			cout<<"Enter name of player "<<i+1<<endl;
			cin>>name;
			cin.ignore();
			game.addPlayer(name);
			if(name == "CPUS"){
				// GreedyAI* gai = new GreedyAI();
				// gai->initialize(dict);
				// AIholder.push_back(gai);
				GreedyAI gai;
				gai.initialize(dict);
				AIholder.push_back(gai);			
			}
			else if(name == "CPUL"){
				// LongestAI* gus = new LongestAI();
				// gus->initialize(dict);
				// AIholder2.push_back(gus);
				LongestAI gai;
				gai.initialize(dict);
				AIholder2.push_back(gai);				
			}						
		 }



		while(game.isFinished()==false){ //while the game is still running

		Player* p = game.getCurrentPlayer();
		cout<<endl<<p->getName()<<" it's your move."<<endl<<endl;
		cout<<"Current Scores: "<<endl;
		vector<pair<string,int> > temp = game.getScores();
		//cout<< temp.size() << endl;
		for(unsigned int i=0; i<temp.size(); i++){ //this prints out the score
			cout<<temp[i].first<<": "<<temp[i].second<<endl;
		}
		cout<<game.getBoard()->getDisplay()<<endl; //prints out board every round
		printInstructions(); //prints out instructions
		cout<<"Your Tiles: "<<p->getHand()<<endl<<endl;

		try{

		Move m;
		if(p->getName()=="CPUS"){
			GreedyAI AI = AIholder[AICounter];
			m = AI.getMove(*(game.getBoard()), *p ,game.initialTileCount());	
			if(AICounter==AIholder.size()-1){
				AICounter=0;
			}
			else{
				AICounter++;
			}					
		}

		else if(p->getName()=="CPUL"){
			LongestAI AI = AIholder2[AICounter2];
			m = AI.getMove(*(game.getBoard()), *p ,game.initialTileCount());	
			if(AICounter2==AIholder2.size()-1){
				AICounter2=0;
			}
			else{
				AICounter2++;
			}					
		}

		else{
		string input;
		getline(cin, input);
		input = strtoupper(input);
		Move temp(input,*p);
		m=temp;
		}

		if(m.isPass()){
			cout<<p->getName()<<" passes their turn."<<endl;
			game.makeMove(m);
			game.finalizeMove();
		}

		else if(m.isExchange()){
			game.makeMove(m);							
			cout<<p->getName()<<" exchanges their tiles."<<endl;
			cout<<"They drew: "<<game.getRecentDraw()<<endl;
			game.finalizeMove();
		}

		else if(m.isWord()){
			cout<<p->getName()<<" places their tiles."<<endl;
			game.makeMove(m);
			cout<<"They drew: "<<game.getRecentDraw()<<endl;
			vector<string>temp = game.getRecentWords();
			cout<<"Recent words formed: "<<endl;
			for(auto it = temp.begin(); it!=temp.end(); ++it){
				cout<<*it<<" ";
			}
			cout<<endl;
			cout<<"Score this round: "<<game.getRecentScore()<<endl;
			cout<<"Your new score: "<<p->getPoints()<<endl;
			cout<<endl;
			game.finalizeMove();
		}
	}

	catch(MoveException &m){
		cerr<<m.getMessage()<<endl;
	}	


	}//end of while loop

	if(game.isFinished()){
		cout<<endl;
		cout<<"Final Scores:"<<endl;
		vector<pair<string,int> > temp3 = game.getScores();
		for(vector<pair<string,int> >::iterator it = temp3.begin(); it!=temp3.end(); ++it){
			cout<<it->first<<" "<<it->second<<endl;
		}

		cout<<endl;
		cout<<"Winner/s!"<<endl;
		vector<string> temp = game.getWinners();
		for(vector<string>::iterator it = temp.begin(); it!=temp.end(); ++it){
			cout<<*it<<endl;
		}
		cout<<endl;
		cout<<"Final Subtraction: "<<endl;
		vector<pair<string,int> > temp2 = game.finalSubtraction();
		for(vector<pair<string,int> >::iterator it = temp2.begin(); it!=temp2.end(); ++it){
			cout<<it->first<<" "<<it->second<<endl;
		}

		delete dict;

	}

}//End of Try
	catch (FileException &f){ 
		cerr<<f.getMessage()<<endl;
	}

	catch (ConfigParameterException &c){
		cerr<<c.getMessage()<<endl;
	}

	// catch(MoveException &m){
	// 	cerr<<m.getMessage()<<endl;
	// }	
	return 1;
}
