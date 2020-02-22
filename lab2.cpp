/*
 * Author		: Julia Gulia in Collaboration with Chris Goosman
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
#include <algorithm>

using namespace std;

// possibly a structure for the children of the board state
// UPDATE TO SOMETHING ELSE IF NEEDED OR CHANGE VARIABLES FOR CLEARER UNDERSTANDING
struct State
{
	vector<string> nodeState; // state of the children of the parent state
	string move;			  // stores the move made (e.g. B3)
	string moveType;		  // stores the type of move made. (e.g. STAKE OR RAID)
	int eval;				  // evaluation of the node
	bool leftEdge;
	bool rightEdge;
	bool middle;

	State()
	{
		moveType = "Steak";
		leftEdge = false;
		rightEdge = false;
		middle = false;
	}
};

class Board
{
public:
	Board();		  // default constructor
	void Input();	 // read input from file
	void PrintData(); // print member variable values

	//int minimax(int eval, bool m, int d);
	int minimax(State s, int d, bool max, string p);

	//alphabeta
	int alphabeta(State s, int d, bool max, string p, int alpha, int beta);

	// check for adjacency adn for raid
	bool is_adjacent(State &s, string p, int pos);
	bool is_raid(State &s, string p, int pos);

	void setEval(State &s);
	void setMove(State &s, int i);

	void runAlgorithm();

	void printBestState()
	{
		for (int i = 0; i < size * size; i++)
		{
			if (i % size == 0)
				cout << endl;
			cout << bestState.nodeState[i];
		}
		cout << bestState.move << endl;
		cout << bestState.moveType << endl;
		cout << bestState.eval << endl;
	}

	// GETTER FUNCTIONS
	//vector<string> getBoardState() { return boardState; };
	int getDepth() { return depth; }
	string getPlayer() { return player; }
	State getInit()
	{
		return initialState;
	}

private:
	string arr[26] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
	int size;				   	// store value that will determine the size of the board
	string mode;			   	// store value for the game mode (MINIMAX, ALPHABETA
	string player;			   	// store the player whose turn it is. (X or O)a
	int depth;				   	// store the value of the depth limit of search. (>=1)
	int alpha;				   	// alpha value to be used with alphabeta pruning
	int beta;				   	// beta value to be used with alphabeta pruning
	vector<int> cellValues;		// hold the integer values of the board cells
	//vector<string> boardState; 	// hold the starting state of the board
	State initialState;			// holds initial state of the board
	State bestState;			// holds the state with the best move
};

Board::Board()
{
	//Initialize member variables to invalid values
	size = 0;
	mode = "";
	player = "";
	depth = 0;
	// set alpha and beta to lowest int value and greatest int value
	alpha = numeric_limits<int>::min();
	beta = numeric_limits<int>::max();
	bestState.eval = numeric_limits<int>::min();
} // end Board

void Board::Input()
{
	// create ifstream object to open file for input
	ifstream infile("input.txt");

	// validate that the file did open
	if (!infile.is_open())
	{
		cout << "ERROR: FILE FAILED TO LOAD.\n";
		exit(1);
	}

	string temp;	 // hold temporary line of the file
	int counter = 1; // hold index of the file
	while (getline(infile, temp))
	{
		if (counter == 1)
		{ // indexed on line holding the size of the board
			size = stoi(temp);
			//available = size * size;
		}
		else if (counter == 2)
		{ // indexed on line holding the mode of the game
			mode = temp;
		}
		else if (counter == 3)
		{ // indexed on line holding the player value
			player = temp;
		}
		else if (counter == 4)
		{ // indexed on line holding the depth limit of the search
			depth = stoi(temp);
		}
		else if (counter < (5 + size))
		{ // indexed on lines holding the cell values
			// insert line into a stringstream object
			stringstream ss(temp);
			int val; // will hold value from line
			// separate line into three separate integers and push into cellValues vector
			for (int i = 0; i < size; i++)
			{
				ss >> val;
				cellValues.push_back(val);
			}
		}
		else if (counter < (5 + (size * 2)))
		{ // indexed on lines holding board state
			//separate line into three separate strings and push intop boardState vector
			for (int i = 0; i < size; i++)
			{
				string val(1, temp.at(i));
				initialState.nodeState.push_back(val);
			}
		}
		// increment the counter
		counter++;
	}
	infile.close();
} // end Input

void Board::PrintData()
{
	// print member variables
	cout << size << endl;
	cout << mode << endl;
	cout << player << endl;
	cout << depth << endl;
	//cout << available << endl;

	// print the cell values grid
	for (int i = 0; i < cellValues.size(); i++)
	{
		if (i % size == 0)
			cout << endl;
		cout << cellValues[i] << " ";
	}
	cout << endl;

	// print the board state grid
	for (int i = 0; i < size * size; i++)
	{
		if (i % size == 0)
			cout << endl;
		cout << initialState.nodeState[i];
	}
} // end PrintData

/* 
The setEval function needs to be called somewhere in the makeChildren function after the State has been initialized by temp. 
It only needs to be called if we are at a terminal node.
*/
void Board::setEval(State &s)
{
	int Opoints = 0;
	int Xpoints = 0;

	for (int i = 0; i < s.nodeState.size(); i++)
	{
		if (s.nodeState[i] == "O")
		{
			Opoints += cellValues[i];
		}
		else if (s.nodeState[i] == "X")
		{
			Xpoints += cellValues[i];
		}
	}
	if (player == "O")
	{
		s.eval = Opoints - Xpoints;
	}

	else
	{
		s.eval = Xpoints - Opoints;
	}
} // end setEval

int main()
{
	Board board;
	board.Input();
	board.PrintData();
	board.runAlgorithm();
	board.printBestState();
	return 0;
}

bool Board::is_adjacent(State &s, string p, int pos)
{
	// check position of move
	if (pos % this->size == 0)
	{
		// we are in a left column node
		s.leftEdge = true;

		if (s.nodeState[pos + 1] == p)
			return true;
		else if (s.nodeState[pos + size] == p and (pos + size) < size * size)
			return true;
		else if (s.nodeState[pos - size] == p and (pos - size) >= 0)
			return true;
		else
			return false;
	}

	/*
	0 1 2
	3 4 5
	6 7 8
	*/
	else if (pos + 1 % this->size == 0)
	{
		// we are in a right column node
		s.rightEdge = true;

		if (s.nodeState[pos - 1] == p)
			return true;
		else if (s.nodeState[pos + size] == p and (pos + size) < size * size)
			return true;
		else if (s.nodeState[pos - size] == p and (pos - size) > 0)
			return true;
		else
			return false;
	}
	else
	{ // we are in a center node
		s.middle = true;
		if (s.nodeState[pos - 1] == p)
			return true;
		else if (s.nodeState[pos + 1] == p)
			return true;
		else if (s.nodeState[pos + size] == p and (pos + size) < size * size)
			return true;
		else if (s.nodeState[pos - size] == p and (pos - size) > 0)
			return true;
		else
			return false;
	}

	return false;
} // end is_adjacent

bool Board::is_raid(State &s, string p, int pos)
{
	// look for opponent on adjacent cells
	string opponent = "";
	bool raid = false;
	// set opponent
	if (p == "O")
		opponent = "X";
	else
		opponent = "O";

	if (s.leftEdge)
	{
		if (s.nodeState[pos + 1] == opponent)
		{
			s.nodeState[pos + 1] = p;
			raid = true;
		}
		if (s.nodeState[pos + size] == opponent and (pos + size) < size * size)
		{
			s.nodeState[pos + size] = p;
			raid = true;
		}
		if (s.nodeState[pos - size] == opponent and (pos - size) >= 0)
		{
			s.nodeState[pos - size] = p;
			raid = true;
		}
	}
	else if (s.rightEdge)
	{
		if (s.nodeState[pos - 1] == opponent)
		{
			s.nodeState[pos - 1] = p;
			raid = true;
		}

		if (s.nodeState[pos + size] == opponent and (pos + size) < size * size)
		{
			s.nodeState[pos + size] = p;
			raid = true;
		}

		if (s.nodeState[pos - size] == opponent and (pos - size) > 0)
		{
			s.nodeState[pos - size] = p;
			raid = true;
		}
	}
	else if (s.middle)
	{
		if (s.nodeState[pos - 1] == opponent)
		{
			s.nodeState[pos - 1] = p;
			raid = true;
		}
		if (s.nodeState[pos + 1] == opponent)
		{
			s.nodeState[pos + 1] = p;
			raid = true;
		}
		if (s.nodeState[pos + size] == opponent and (pos + size) < size * size)
		{
			s.nodeState[pos + size] = p;
			raid = true;
		}
		if (s.nodeState[pos - size] == opponent and (pos - size) > 0)
		{
			s.nodeState[pos - size] = p;
			raid = true;
		}
	}
	return raid;
} // end is_raid

void Board::setMove(State &s, int i)
{
	s.move = arr[i % size];
	s.move += to_string((i / size) + 1);
} // end setMove

// {a, 0, 1, 2, b, 0, 1, 2}

int Board::minimax(State s, int d, bool m, string p)
{
	if (d == 0)
	{
		setEval(s);
		return s.eval;
	}

	int bestScore;

	if (m)
	{ // this is for max
		bestScore = numeric_limits<int>::min();

		for (int i = 0; i < size * size; i++)
		{
			State tempState;
			tempState.nodeState = s.nodeState;
			if (tempState.nodeState[i] == ".")
			{
				tempState.nodeState[i] = p;
				setMove(tempState, i);
				if (is_adjacent(tempState, p, i))
				{
					if (is_raid(tempState, p, i))
					{
						tempState.moveType = "Raid";
					}
				}
				int score;
				p = (p == "O") ? "X" : "O";
				score = minimax(tempState, d - 1, false, p);
				p = (p == "O") ? "X" : "O";
				// compare scores
				bestScore = max(bestScore, score);
				// hold bestState
				if (bestScore > bestState.eval and d == depth)
				{
					bestState.nodeState = tempState.nodeState;
					bestState.move = tempState.move;
					bestState.moveType = tempState.moveType;
					bestState.eval = bestScore;
				}
			}
		}
		return bestScore;
	}

	else
	{ // this is for min
		bestScore = numeric_limits<int>::max();
		for (int i = 0; i < size * size; i++)
		{
			State tempState;
			tempState.nodeState = s.nodeState;
			if (tempState.nodeState[i] == ".")
			{
				tempState.nodeState[i] = p;
				setMove(tempState, i);
				if (is_adjacent(tempState, p, i))
				{
					if (is_raid(tempState, p, i))
					{
						tempState.moveType = "Raid";
					}
				}
				int score;
				p = (p == "O") ? "X" : "O";
				score = minimax(tempState, d - 1, true, p);
				p = (p == "O") ? "X" : "O";
				// compare scores
				bestScore = min(bestScore, score);
			}
		}
		return bestScore;
	}
}

int Board::alphabeta(State s, int d, bool m, string p, int alpha, int beta)
{
	if (d == 0)
	{
		setEval(s);
		return s.eval;
	}

	int bestScore;

	if (m)
	{ // this is for max
		bestScore = numeric_limits<int>::min();

		for (int i = 0; i < size * size; i++)
		{
			State tempState;
			tempState.nodeState = s.nodeState;
			if (tempState.nodeState[i] == ".")
			{
				tempState.nodeState[i] = p;
				setMove(tempState, i);
				if (is_adjacent(tempState, p, i))
				{
					if (is_raid(tempState, p, i))
					{
						tempState.moveType = "Raid";
					}
				}
				int score;
				p = (p == "O") ? "X" : "O";
				score = alphabeta(tempState, d - 1, false, p, alpha, beta);
				p = (p == "O") ? "X" : "O";
				// compare scores
				bestScore = max(bestScore, score);
				alpha = max(bestScore, alpha);
				if(alpha >= beta) break;
				// hold bestState
				if (bestScore > bestState.eval and d == depth)
				{
					bestState.nodeState = tempState.nodeState;
					bestState.move = tempState.move;
					bestState.moveType = tempState.moveType;
					bestState.eval = bestScore;
				}
			}
		}
		return bestScore;
	}

	else
	{ // this is for min
		bestScore = numeric_limits<int>::max();
		for (int i = 0; i < size * size; i++)
		{
			State tempState;
			tempState.nodeState = s.nodeState;
			if (tempState.nodeState[i] == ".")
			{
				tempState.nodeState[i] = p;
				setMove(tempState, i);
				if (is_adjacent(tempState, p, i))
				{
					if (is_raid(tempState, p, i))
					{
						tempState.moveType = "Raid";
					}
				}
				int score;
				p = (p == "O") ? "X" : "O";
				score = alphabeta(tempState, d - 1, true, p, alpha, beta);
				p = (p == "O") ? "X" : "O";
				// compare scores
				bestScore = min(bestScore, score);
				beta = min(bestScore, beta);
				if(beta <= alpha) break;
			}
		}
		return bestScore;
	}
}

void Board::runAlgorithm(){
	if(mode == "MINIMAX"){
			bestState.eval = minimax(initialState, depth, true, player);
	}
	// alphabeta
	else {
		bestState.eval = alphabeta(initialState, depth, true, player, alpha, beta);
	}

	// OUTPUT FILE
	ofstream outfile("output.txt");

	outfile << bestState.move << " " << bestState.moveType;

	for(int i = 0; i < size * size; i++){
		if(i % size == 0) outfile << endl;
		outfile << bestState.nodeState[i];
	}

	outfile.close();
}
