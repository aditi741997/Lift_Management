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
	vector<float> Exp_people;
	// true = up
	// false = down

	Agent(int&,int&,float&,float&,float&,float&);
	inline int closest_Up(int);
	inline int closest_Down(int);
	inline bool button_up(int);
	inline bool button_down(int);

	void assignFloor();
	void updateMode();
	vector<int> getActions();
	void updateState(vector<int>&);
	void updateStateWithObs(string&);

};

inline int Agent::closest_Up(int cfloor)
{
	int ans = cfloor+1;
	while (ans < N)
	{
		if (Button_Floor[ans].first || Button_Floor[ans].second)
			return ans;
		else
			ans++;
	}
	return N;
}

inline int Agent::closest_Down(int cfloor)
{
	int ans = cfloor-1;
	while (ans >= 0)
	{
		if (Button_Floor[ans].first || Button_Floor[ans].second)
			return ans;
		else
			ans--;
	}
	return -1;
}

inline bool Agent::button_up(int lift_no)
{
	bool ans = false;
	for (int i = Lift_Positions[lift_no] + 1; i < N && !ans; i++)
		ans = ans || Button_Lifts[lift_no][i];
	return ans;
}

inline bool Agent::button_down(int lift_no)
{
	bool ans = false;
	for (int i = Lift_Positions[lift_no] - 1; i >= 0 && !ans; i--)
		ans = ans || Button_Lifts[lift_no][i];
	return ans;

}

inline string int_to_string(int x)
{
	stringstream s;
	s << x;
	return s.str();
}


string getString(vector<int>&);

#endif