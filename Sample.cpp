#include "Sample.h"

Sampling::Sampling()
{
	c = 1;
}

inline void Sampling::findUVal(char& act, int& state, float& val, int& ns)
{
	if (Exploration[state][act] != 0)
		val = -1*Qsa[state][act] + c*sqrt(log(ns)/Exploration[state][act]);
	else if (Qsa[state][act] < INT_MAX)
		val = FLT_MAX;
	else
		val = -FLT_MAX;
}

inline float Sampling::getAlpha(int& it_no, int& depth)
{
	return (1 - ((it_no)/(float)depth));
}

inline float Sampling::newQ(float& cost, int& depth)
{
	return cost/depth;
}

void Sampling::chooseAction(char& action, int& state)
{
	int ns = 1;
	for (char i = 0; i < 4; i++)
		ns += Exploration[state][i];
	float pie_max = -FLT_MAX;
	for (char i = 0; i < 4; i++)
	{
		float new_pie;
		findUVal(i,state,new_pie,ns);
		if (new_pie > pie_max)
		{
			pie_max = new_pie;
			action = i;
		}
	}
	State_Action.push_back(make_pair(state,action));
}

void Sampling::updateVals(float& cost, int& depth)
{
	int itern_no = 0;
	for (auto it = State_Action.begin(); it != State_Action.end(); it++)
	{		
		cerr << "State: "<< it->first << "Action: " << (int)(it->second) << "Purana QSA:" << Qsa[it->first][it->second] << endl;

		Exploration[it->first][it->second] += 1;
		if (Qsa[it->first][it->second] < INT_MAX)
			Qsa[it->first][it->second] += (getAlpha(itern_no,depth))*(newQ(cost,depth) - Qsa[it->first][it->second]);
		itern_no += 1;

		cerr << "State: "<< it->first << "Action: " << (int)(it->second) << "Naya QSA:" << Qsa[it->first][it->second] << endl;
	}
}