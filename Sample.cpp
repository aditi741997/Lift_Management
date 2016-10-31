#include "Sample.h"

Sampling::Sampling()
{
	c = 1;
}

inline void Sampling::findUVal(char& act, int& state, float& val, int& ns)
{
	if (Exploration[state][act] != 0)
		val = (Qsa[state][act] < FLT_MAX) ? (-1*Qsa[state][act] + c*sqrt(log(ns)/Exploration[state][act])) : -1*FLT_MAX;
	else if (Qsa[state][act] < FLT_MAX)
		val = FLT_MAX;
	else
		val = -FLT_MAX;
}

inline float Sampling::getAlpha(int& it_no, int& depth)
{
	return (1.001 - ((it_no)/(float)depth));
}

inline float Sampling::newQ(float& cost, int& depth)
{
	return cost/depth;
}

void Sampling::clear()
{
	State_Action.clear();
}

void Sampling::chooseAction(char& action, int& state)
{
	int ns = 1;
	for (char i = 0; i < 4; i++)
	{
		for (char j = 0; j < 4; j++)
			ns += Exploration[state][(i << 3) | j];
	}
	float pie_max = -FLT_MAX;
	for (char i = 0; i < 4; i++)
	{
		for (char j = 0; j < 4; j++)
		{
			char a = (i << 3) | j;		
			float new_pie;
			findUVal(a,state,new_pie,ns);
			if (new_pie > pie_max)
			{
				pie_max = new_pie;
				action = a;
			}
		}
	}
	State_Action.push_back(make_pair(state,action));
}

void Sampling::updateVals(float& cost, int& depth)
{
	int itern_no = 0;
	for (auto it = State_Action.begin(); it != State_Action.end(); it++)
	{
		Exploration[it->first][it->second] += 1;
		if (Qsa[it->first][it->second] < FLT_MAX)
			Qsa[it->first][it->second] += (getAlpha(itern_no,depth))*(newQ(cost,depth) - Qsa[it->first][it->second]);
		itern_no += 1;
	}
}