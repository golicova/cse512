/*
 * Author		: Karant
 * Course		: CSE-512
 * Assignment	: Lab Assignment 2
 * Description	: Program takes input containing data of the starting state
 *				: of a Stake and Raid game. Program must evaluate the best move
 *				: for the player to make after performing the minimax or alphabeta
 *				: algorithm in a depth limited search. 
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <limits> // for alpha and beta values

using namespace std;

// possibly a structure for the children of the board state
// UPDATE TO SOMETHING ELSE IF NEEDED OR CHANGE VARIABLES FOR CLEARER UNDERSTANDING
struct State {
	vector<string> nodeState; // state of the children of the parent state
    string move; // stores the move made (e.g. B3)
    string moveType; // stores the type of move made. (e.g. STAKE OR RAID)
	int eval; // evaluation of the node
};

class Board {
public:
	Board(); // default constructor
	void Input(); // read input from file
	void PrintData(); // print member variable values

	//recursive call to make children board states
	void makeChildren(int d, vector<string> bs, string p);
	
	// check for adjacency and for raid 
	bool is_adjacent(State s, string p, int pos);
	
	void setEval(State& s);

	// GETTER FUNCTIONS
	vector<string> getBoardState() { return boardState; };
	int getDepth() { return depth; }
    string getPlayer() {return player;}

private:
	int size; // store value that will determine the size of the board
	string mode; // store value for the game mode (MINIMAX, ALPHABETA
	string player; // store the player whose turn it is. (X or O)a
	int depth; // store the value of the depth limit of search. (>=1)
	//int available; // stores the value of available spaces on the board
	int alpha; // alpha value to be used with alphabeta pruning
	int beta; // beta value to be used with alphabeta pruning
	vector<int>	cellValues; // hold the integer values of the board cells
	vector<string> boardState; // hold the starting state of the board
	vector<State> children; // children nodes of the board state
};

Board::Board() {
	//Initialize member variables to invalid values
	size = 0;
	mode = "";
	player = "";
	depth = 0;
	//available = 0;
	// set alpha and beta to lowest int value and greatest int value
	alpha = numeric_limits<int>::min();
	beta = numeric_limits<int>::max();
}// end Board

void Board::Input() {
	// create ifstream object to open file for input
	ifstream infile("input.txt");

	// validate that the file did open
	if (!infile.is_open()) {
		cout << "ERROR: FILE FAILED TO LOAD.\n";
		exit(1);
	}

	string temp; // hold temporary line of the file
	int counter = 1; // hold index of the file
	while (getline(infile, temp)) {
		if (counter == 1) { // indexed on line holding the size of the board
			size = stoi(temp);
			//available = size * size;
		}
		else if (counter == 2) { // indexed on line holding the mode of the game
			mode = temp;
		}
		else if (counter == 3) { // indexed on line holding the player value
			player = temp;
		}
		else if (counter == 4) { // indexed on line holding the depth limit of the search
			depth = stoi(temp);
		}
		else if (counter < (5 + size)) { // indexed on lines holding the cell values
			// insert line into a stringstream object
			stringstream ss(temp);
			int val; // will hold value from line
			// separate line into three separate integers and push into cellValues vector
			for (int i = 0; i < size; i++) {
				ss >> val;
				cellValues.push_back(val);
			}
		}
		else if (counter < (5 + (size * 2)) ) { // indexed on lines holding board state
			//separate line into three separate strings and push intop boardState vector
			for (int i = 0; i < size; i++) {
				string val(1, temp.at(i));
				/* checks to see if any spaces are occupied and updates available spaces
				if (val != ".") available--; */
				boardState.push_back(val);
			}
		}
		// increment the counter
		counter++;
	}
} // end Input

void Board::PrintData() {

	// print member variables
	cout << size << endl;
	cout << mode << endl;
	cout << player << endl;
	cout << depth << endl;
	//cout << available << endl;

	// print the cell values grid
	for (int i = 0; i < cellValues.size(); i++) {
		if (i % size == 0) cout << endl;
		cout << cellValues[i] << " ";
	}
	cout << endl;

	// print the board state grid
	for (int i = 0; i < boardState.size(); i++) {
		if (i % size == 0) cout << endl;
		cout << boardState[i];
	}

	/***************************/
	// print the children state
	// MAKE INTO A RECURSIVE FUNCTION FOR ALL CHILDREN
	for(int i = 0; i < children.size(); i++) {
		cout << endl;
		for (int j = 0; j < children[i].nodeState.size(); j++) {
			if (j % size == 0) cout << endl;
			cout << children[i].nodeState[j];
		}
		cout << "\tEvaluation: " << children[i].eval;
	}
}// end PrintData

/**************
****************
****************/
// UPDATE TO BE RECURSIVE UNTIL ALL CHILDREN ALL CREATED FOR ALL DEPTHS
void Board::makeChildren(int d, vector<string> bs, string p) {
    // decrement depth of search
    d--;
	for (int i = 0; i < size*size; i++) {
		vector<string> temp = bs;
		State state;
				
		if (bs[i] == ".") {
			temp[i] = p;
			state.nodeState = temp;
			if(d == 0) {
				setEval(state);
			}

			children.push_back(state);
            // call function until all children are created
            
			if(d != 0){
                string pp = p;
                if (pp == "O") pp = "X";
                else pp = "O";
                makeChildren(d, state.nodeState, pp);
            }
		}
	}
}// end makeChildren

/* 
The setEval function needs to be called somewhere in the makeChildren function after the State has been initialized by temp. 
It only needs to be called if we are at a terminal node.
*/
void Board::setEval(State& s) {
	int Opoints = 0; 
	int Xpoints = 0; 

	for (int i = 0; i < s.nodeState.size(); i++) {
		if (s.nodeState[i] == "O") {
			Opoints += cellValues[i];
		}
		else if (s.nodeState[i] == "X") {  
			Xpoints += cellValues[i];
		}
	}
	if(player == "O") {
		s.eval = Opoints - Xpoints; 
	}

	else {
		s.eval = Xpoints - Opoints; 
	}
} // end setEval

int main() {
	Board board;
	board.Input();
	board.makeChildren(board.getDepth(), board.getBoardState(), board.getPlayer());
	board.PrintData();
	return 0;
}

bool Board::is_adjacent(State s, string p, int pos){
	// check position of move
	if(pos % this->size == 0){
		// we are in a left column node
		if(s.nodeState[pos+1}] == this->player)
			return true;
		else if(s.nodeState[pos + 3] == this->player)
			return true;
	}
	else if(pos+1 % this->size == 0){
		// we are in a right column node
		
	}
	else{ // we are in a center node

	}

	return false;
}// end is_adjacent




