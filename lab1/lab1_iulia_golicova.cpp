#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <iostream>
#include <sstream>


using namespace std;

struct MyStruct//the priority queue for Astar
{
	int key;//the path cost of the node
	string stringValue;//the path for the priority queue for Astar

	MyStruct(int k, const string& s) : key(k), stringValue(s) {}

	bool operator < (const MyStruct& str) const//use this sort sort the queue in ascending order
	{
		return (key < str.key);
	}
};

class HaveYouEverHeardTheTragedyofDarthPlagueisTheWise
{
public:
HaveYouEverHeardTheTragedyofDarthPlagueisTheWise();
int BFS();
int DFS();
int UCS(); 
int Astar(); 
void opener();
void printer(string goalpath);
bool BFSTieBreak(queue<string> temp_explored, queue<string> currentFrontier, string nod);
bool DFSTieBreak(queue<string> temp_explored, stack<string> currentFrontierDFS, string nod);
void UCSTieBreak(queue<string> tchild, queue<int> tchildcost, int temp_cost, queue<string> exploredUCS);
void AStarTieBreak(queue<string> tchild, queue<int> tchildcost, int temp_cost, queue<string> exploredastar);


vector<string> holder;
vector<string> Astarlines;
vector<string> nodes;
vector<int> pathcost;
vector<int> Distance;
queue<string> explored;
queue<string> frontier;
stack<string> frontierdfs;//dfs
vector<MyStruct> AUfrontier;



string function;
string goal;
string start;
int lines;
int sunlines;
int counter;
};

HaveYouEverHeardTheTragedyofDarthPlagueisTheWise::HaveYouEverHeardTheTragedyofDarthPlagueisTheWise()
{

}

int HaveYouEverHeardTheTragedyofDarthPlagueisTheWise::BFS()
{
	bool searched = false;
	string temp_path;
	queue<string> tchild;
	frontier.push(start);
	while (!searched)
	{
		if (frontier.empty())
		{
			searched = true;
			cout << "Empty this fails." << endl;
			break;
		}
		temp_path = frontier.front();
		frontier.pop();
		if (temp_path.at(0) == goal.at(0))
		{
			break;
		}
		explored.push(temp_path);
		for (int i = 0; i < holder.size(); i++)
		{
			if (holder[i].at(0) == temp_path.at(0))
			{
				tchild.push(holder[i].at(2) + temp_path);
			}
		}
		while (!tchild.empty())
		{
			string temp_again = tchild.front();
			temp_again = temp_again.at(0);
			if (!BFSTieBreak(explored, frontier, temp_again))
			{
				frontier.push(tchild.front());
			}
			tchild.pop();
		}
	}
	reverse(temp_path.begin(), temp_path.end());
	printer(temp_path);
	return 0;
}

bool HaveYouEverHeardTheTragedyofDarthPlagueisTheWise::BFSTieBreak(queue<string> temp_explored, queue<string> temp_frontier, string nod)
{
	while (!temp_frontier.empty())
	{
		if (temp_frontier.front().at(0) == nod.at(0))
		{
			return true;
		}
		temp_frontier.pop();
	}
	while (!temp_explored.empty())
	{
		if (temp_explored.front().at(0) == nod.at(0))
		{
			return true;
		}
		temp_explored.pop();
	}
	return false;
}


int HaveYouEverHeardTheTragedyofDarthPlagueisTheWise::DFS()
{
	bool searched = false;
	string temp_path;
	queue<string> tchild;
	frontierdfs.push(start);
	while (!searched)
	{
		if (frontierdfs.empty())
		{
			searched = true;
			break;
			cout << "Empty this fails." << endl;
		}
		temp_path = frontierdfs.top();
		frontierdfs.pop();
		if (temp_path.at(0) == goal.at(0))
		{
			break;
		}
		explored.push(temp_path);
		for (int i = 0; i < holder.size(); i++)
		{
			if (holder[i].at(0) == temp_path.at(0))
			{
				tchild.push(holder[i].at(2) + temp_path);
			}
		}
		while (!tchild.empty())
		{
			string temp_again = tchild.front();
			temp_again = temp_again.at(0);
			if (!DFSTieBreak(explored, frontierdfs, temp_again))
			{
				frontierdfs.push(tchild.front());
			}
			tchild.pop();
		}
	}
	reverse(temp_path.begin(), temp_path.end());
	printer(temp_path);
	return 0;
}

bool HaveYouEverHeardTheTragedyofDarthPlagueisTheWise::DFSTieBreak(queue<string> temp_explored, stack<string> temp_frontierDFS, string nod)
{
	while (!temp_frontierDFS.empty())
	{
		if (temp_frontierDFS.top().at(0) == nod.at(0))//while the queue is not empty check if the frontier contains our child
		{
			return true;
		}
		temp_frontierDFS.pop();
	}
	while (!temp_explored.empty())
	{
		if (temp_explored.front().at(0) == nod.at(0))//while the queue is not empty check if the explored contains our child
		{
			return true;
		}
		temp_explored.pop();
	}
	return false;
}

int HaveYouEverHeardTheTragedyofDarthPlagueisTheWise::UCS()
{
	bool searched = false;
	string temp_path;
	int temp_cost;
	queue<string> tchild;
	queue<int>tchildcost;
	AUfrontier.push_back(MyStruct(0, start));
		while(!searched)
		{
			if (AUfrontier.empty())
			{
				searched = true;
				break;
			}
			temp_path = AUfrontier.front().stringValue;
			temp_cost = AUfrontier.front().key;
			AUfrontier.erase(AUfrontier.begin());
			if (temp_path.at(0) == goal.at(0))
			{
				break;
			}
			explored.push(temp_path);
			for (int i = 0; i < holder.size(); i++)
			{
				if (holder[i].at(0) == temp_path.at(0))
				{
					string quickhold;
					tchild.push(holder[i].at(2) + temp_path);
					for (int j = 4; j < holder.size(); j++)
					{
						quickhold += holder[i].at(j);
					}
					tchildcost.push(stoi(quickhold));
				}
			}
			UCSTieBreak(tchild, tchildcost, temp_cost, explored);
			sort(AUfrontier.begin(), AUfrontier.end());
        }

		reverse(temp_path.begin(), temp_path.end());
		printer(temp_path);
	return 0;
}

void HaveYouEverHeardTheTragedyofDarthPlagueisTheWise::UCSTieBreak(queue<string> tchild, queue<int> tchildcost, int temp_cost, queue<string> exploredUCS)
{
	bool isexplored = false;//set a bool if our child exists inf rontier or explored
	bool isfrontier = false;
	while (!tchild.empty())//while children exist to be pushed do
	{
		queue<string> exp = exploredUCS;//create a explored queue to see if our child exists in the explored
		isexplored = false;//reset the bools each tieration
		isfrontier = false;
		int t = tchildcost.front() + temp_cost;//add up the path cost of the child and the parent nodes
		while (!exp.empty())//check to see if the child exists in the explored queue
		{
			if (exp.front().at(0) == tchild.front().at(0))
			{
				isexplored = true;
			}
			exp.pop();
		}
		for (int i = 0; i < AUfrontier.size(); i++)//check if the child exists in the frontier queue
		{
			if (AUfrontier[i].stringValue.at(0) == tchild.front().at(0))
			{
				isfrontier = true;
				if (AUfrontier[i].key > t)//replace if the child we are going to enter has a lwoer cost
				{
					cout << endl << "replace " << AUfrontier[i].stringValue.at(0) << " " << AUfrontier[i].key << " with " << tchild.front().at(0) << " " << t << endl;
					AUfrontier[i].key = t;
					AUfrontier[i].stringValue = tchild.front();
				}
			}
		}
		if (isexplored == false && isfrontier == false)//if the child is not in the frontier or explored then push it to the
		{
			AUfrontier.push_back(MyStruct(t, tchild.front()));
		}
		tchild.pop();
		tchildcost.pop();
	}
}

int HaveYouEverHeardTheTragedyofDarthPlagueisTheWise::Astar()
{
	bool searched = false;
	string temp_path;
	int temp_cost;
	int more_temp_cost;
	int temp_start = 0;
	int heuristic;
	queue<string> tchild;
	queue<int> tchildcost;
	AUfrontier.push_back(MyStruct(temp_start, start));
	for (int i = 0; i < Astarlines.size(); i++)
	{
		if (AUfrontier.front().stringValue.at(0) == Astarlines[i].at(0))
		{
			string temp;
			for (int j = 2; j < Astarlines[i].size(); j++)
			{
				temp += Astarlines[i].at(j);
			}
			heuristic = stoi(temp);
		}
	}
	AUfrontier.front().key = heuristic;
	while (!searched)
	{
		if (AUfrontier.empty())
		{
			searched = true;
			break;
		}
		for (int i = 0; i < Astarlines.size(); i++)
		{
			if (AUfrontier.front().stringValue.at(0) == Astarlines[i].at(0))
			{
				string temp;
				for (int j = 2; j < Astarlines[i].size(); j++)
				{
					temp += Astarlines[i].at(j);
				}
				heuristic = stoi(temp);
			}
		}
		temp_path = AUfrontier.front().stringValue;
		more_temp_cost = AUfrontier.front().key;
		AUfrontier.front().key = more_temp_cost - heuristic;
		temp_cost = AUfrontier.front().key;
		AUfrontier.erase(AUfrontier.begin());
		if (temp_path.at(0) == goal.at(0))
		{
			break;
		}
		explored.push(temp_path);
		for (int i = 0; i < holder.size(); i++)
		{
			if (holder[i].at(0) == temp_path.at(0))
			{
				string quickhold;
				tchild.push(holder[i].at(2) + temp_path);
				for (int j = 4; j < holder[i].size(); j++)
				{
					quickhold += holder[i].at(j);
				}
				tchildcost.push(stoi(quickhold));
			}
		}
		AStarTieBreak(tchild, tchildcost, temp_cost, explored);
		sort(AUfrontier.begin(), AUfrontier.end());

	}
	reverse(temp_path.begin(), temp_path.end());
	printer(temp_path);
	return 0;
}

void HaveYouEverHeardTheTragedyofDarthPlagueisTheWise::AStarTieBreak(queue<string> tchild, queue<int> tchildcost, int temp_cost, queue<string> exploredastar)
{
	int heuristic;//saves the heuristic value for the current child node
	bool isexplored = false;//set a bool if our child exists inf rontier or explored
	bool isfrontier = false;
	while (!tchild.empty())//while children exist to be pushed do
	{
		for (int i = 0; i < Astarlines.size(); i++)//find the heuristic value of the current child
		{
			if (tchild.front().at(0) == Astarlines[i].at(0))
			{
				string temp;
				for (int j = 2; j < Astarlines[i].size(); j++)
				{
					temp += Astarlines[i].at(j);
				}
				heuristic = stoi(temp);
			}
		}
		queue<string> exp = exploredastar;//create a explored queue to see if our child exists in the explored
		isexplored = false;//reset the bools each tieration
		isfrontier = false;
		int t = tchildcost.front() + temp_cost + heuristic;//add up the path cost of the child and the parent nodes and the heuristic values
		while (!exp.empty())
		{
			if (exp.front().at(0) == tchild.front().at(0))
			{
				isexplored = true;
			}
			exp.pop();
		}
		for (int i = 0; i < AUfrontier.size(); i++)//check if the child exists in the frontier queue
		{
			if (AUfrontier[i].stringValue.at(0) == tchild.front().at(0))
			{
				isfrontier = true;
				if (AUfrontier[i].key > t)//replace if the child we are going to enter has a lower cost
				{
					cout << endl << "replace " << AUfrontier[i].stringValue.at(0) << " " << AUfrontier[i].key << " with " << tchild.front().at(0) << " " << t << endl;
					AUfrontier[i].key = t;
					AUfrontier[i].stringValue = tchild.front();
				}
			}
		}
		if (isexplored == false && isfrontier == false)//if the child is not in the frontier or explored then push it to the frontier
		{
			AUfrontier.push_back(MyStruct(t, tchild.front()));
		}
		tchild.pop();
		tchildcost.pop();
	}
}
//opens input.txt and prints out so it can be used
void HaveYouEverHeardTheTragedyofDarthPlagueisTheWise::opener()
{
	ifstream infile;
	string buffer;
	infile.open("input.txt");
	counter = 0;
	if (!infile.good())
	{
		cout << "file not found" << endl;
	}
	else
	{
		cout << "file opened. Reading contents..." << endl;
		while (getline(infile, buffer))
		{
			if (counter == 0)
			{
				function = buffer;
			}
			else if (counter == 1)
			{
				start = buffer;
			}
			else if (counter == 2)
			{
				goal = buffer;
			}
			else if (counter == 3)
			{
				lines = stoi(buffer);
			}
			else if (counter < 4 + lines)
			{
				holder.push_back(buffer);
			}
			else if (counter < 5 + lines)
			{
				sunlines = stoi(buffer);
			}
			else if (counter < 6 + lines + sunlines)
			{
				Astarlines.push_back(buffer);
			}
			counter++;
		}
	}
	infile.close();
}

//This code will update the output.txt and print it out answer for good measure
void HaveYouEverHeardTheTragedyofDarthPlagueisTheWise::printer(string goalpath)
{
	vector<int> temppathcosts;
	vector<int> finalpathcosts;
	cout << endl << function << " Algorithm path is: " <<goalpath;
	int pathsize = goalpath.size();
	string temppath;
	temppathcosts.push_back(0);//start state pathcost is always 0
	cout << endl;
	for (int i = 1; i < goalpath.size(); i++)//get the pathcost and save into a string
	{
		temppath = goalpath.at(i - 1);//save the path of each step ie: (A B) or (B D)
		temppath += " ";
		temppath += goalpath.at(i);
		for (int j = 0; j < holder.size(); j++)//compare path with each line to get the path cost
		{
			string str;
			string t = holder[j];
			str += t.at(0);
			str += t.at(1);
			str += t.at(2);
			if (temppath == str)
			{
				string tst;
				for (int i = 4; i < holder[j].size(); i++)
				{
					tst += t.at(i);
				}
				int trt = stoi(tst);
				temppathcosts.push_back(trt);//push the path csot so addition may be computed
			}
		}
	}
	for (int i = 0; i < temppathcosts.size(); i++)
	{
		if (i == 0)
		{
			finalpathcosts.push_back(temppathcosts[i]);
		}
		else
		{
			int tempnum = finalpathcosts[i - 1] + temppathcosts[i];
			finalpathcosts.push_back(tempnum);
		}
	}

	ofstream file("Output.txt");
	for (int i = 0; i < finalpathcosts.size(); i++)
	{
		file << goalpath.at(i);
		file << " ";
		file << finalpathcosts[i];
		file << endl;
	}
}


int main()
{

	HaveYouEverHeardTheTragedyofDarthPlagueisTheWise haveyoueverheardthetragedyofdarthplagueisthewise;
	haveyoueverheardthetragedyofdarthplagueisthewise.opener();

	if (haveyoueverheardthetragedyofdarthplagueisthewise.function == "BFS")
	{
		cout << "BFS running" << endl;
		haveyoueverheardthetragedyofdarthplagueisthewise.BFS();
	}
	else if (haveyoueverheardthetragedyofdarthplagueisthewise.function == "DFS")
	{
		cout << "DFS running" << endl;
		haveyoueverheardthetragedyofdarthplagueisthewise.DFS();
	}
	else if (haveyoueverheardthetragedyofdarthplagueisthewise.function == "UCS")
	{
		cout << "UCS running" << endl;
		haveyoueverheardthetragedyofdarthplagueisthewise.UCS();
	}
	else if (haveyoueverheardthetragedyofdarthplagueisthewise.function == "A*")
	{
		cout << "AStar running" << endl;
		haveyoueverheardthetragedyofdarthplagueisthewise.Astar();
	}
	system("pause");	
}