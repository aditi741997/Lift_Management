#ifndef AGENT_H
#define AGENT_H

#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

extern int N,K;
extern float p,q,r,tu;

using namespace std;

extern vector<string> ActionMap;

struct Agent
{
	vector<pair<bool,bool> > Button_Floor;
	vector<vector<bool> > Button_Lifts;
	vector<int> Lift_Positions;
	vector<int> Lift_Mode;
	// true = up
	// false = down

	Agent(int&,int&,float&,float&,float&,float&);
	vector<int> getActions();
	void updateState(vector<int>&);
	void updateStateWithObs(string&);

};

inline string to_string(int x)
{
	stringstream s;
	s >> x;
	return s.str();
}


string getString(vector<int>&);

#endif