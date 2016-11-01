#include "Sample.h"

Sampling::Sampling()
{
	// c = sqrt(2);
}

inline void Sampling::findUVal(char& act, int& state, float& val, long& ns, float& c)
{
	// val = rand();
	if (Exploration[state][act] != 0)
		val = (Qsa[state][act] < FLT_MAX) ? (-1*Qsa[state][act] + c*sqrt(log(ns)/Exploration[state][act])) : -1*FLT_MAX;
		// val = (Qsa[state][act] < FLT_MAX) ? rand() : -FLT_MAX;
	else if (Qsa[state][act] < FLT_MAX)
		val = FLT_MAX;
	else
		val = -FLT_MAX;
}

inline float Sampling::getAlpha(int& it_no, int& depth, long& ns)
{
	return ( (1.2 - pow( ((it_no)/(float)depth) ,3 )) / (ns+1) );
}

inline float Sampling::newQ(float& cost, int& depth)
{
	return cost/depth;
}

void Sampling::clear()
{
	State_Action.clear();
	Ns.clear();
}

void Sampling::chooseAction(char& action, int& state)
{
	long ns = 1;
	float q_avg = 0;
	for (char i = 0; i < 4; i++)
	{
		for (char j = 0; j < 4; j++)
		{
			char x = (i << 3) | j;
			ns += Exploration[state][x];
			if (Qsa[state][x] < FLT_MAX)
				q_avg += Qsa[state][x];
		}
	}
	q_avg /= ns;
	float pie_max = -FLT_MAX;
	for (char i = 0; i < 4; i++)
	{
		for (char j = 0; j < 4; j++)
		{
			char a = (i << 3) | j;		
			float new_pie;
			findUVal(a,state,new_pie,ns,q_avg);
			// cout << "new pie : " << new_pie << endl;
			if (new_pie >= pie_max)
			{
				pie_max = new_pie;
				action = a;
			}
		}
	}
	if (!(pie_max > -FLT_MAX))
	{
		cout << "PICKING INVALID ACTION!!! \n";
		char ch;
		cin >> ch;
	}
	Exploration[state][action] += 1;
	// Total_Expl += 1;
	State_Action.push_back(make_pair(state,action));
	Ns.push_back(ns);
}

void Sampling::updateVals(float& cost, int& depth)
{
	int itern_no = 0;
	auto it1 = Ns.begin();
	for (auto it = State_Action.begin(); it != State_Action.end() && it1 != Ns.end(); it++, it1++)
	{
		// Exploration[it->first][it->second] += 1;
		if (Qsa[it->first][it->second] < FLT_MAX)
		{
			float alpha = getAlpha(itern_no,depth, (*it1));
			// c += (alpha)*(newQ(cost,depth))
			Qsa[it->first][it->second] += (alpha)*(newQ(cost,depth) - Qsa[it->first][it->second]);
			// cout << "alpha = " << getAlpha(itern_no,depth,*(it1)) << endl;
			if (alpha < 0)
			{
				cout << itern_no << " depth = " << depth << ", ns = " << (*it1) << endl;
				char c;
				cin >> c;
			}
		}
		itern_no += 1;
	}
	clear();
	// char c;
	// cin >> c;
}