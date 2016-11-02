#include "Sample.h"

Sampling::Sampling()
{
	// c = sqrt(2);
}

inline void Sampling::findUVal(char& act, int& state, float& val, long& ns, float& c)
{
	// val = rand();
	if (Exploration[state][act] != 0)
		val = (Qsa[state][act] < FLT_MAX) ? (-1*Qsa[state][act] - 200*c*sqrt(log(ns)/Exploration[state][act])) : -1*FLT_MAX;
	else if (Qsa[state][act] < FLT_MAX)
		val = FLT_MAX;
	else
		val = -FLT_MAX;
}

inline float Sampling::getAlpha(int& it_no, int& depth, long& ns)
{
	return ( (1.2 /*- pow( ((it_no)/(float)depth) ,7 )*/) / (ns+1) );
}

inline float Sampling::newQ(float& cost, int& depth)
{
	return cost/depth;
}

inline float Sampling::getGamma()
{
	return 0.9;
}

void Sampling::clear()
{
	State_Action.clear();
	Ns_CostSoFar.clear();
	Next_State.clear();
}

void Sampling::chooseAction(char& action, int& state, float cost)
{
	long ns = 1;
	float pie_max = -FLT_MAX;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			ns += Exploration[state][(i << 3) | j];
	// cout << "ns is " <<  ns << endl;

	for (char i = 0; i < 4; i++)
	{
		for (char j = 0; j < 4; j++)
		{
			char a = (i << 3) | j;
			float new_pie;

			findUVal(a,state,new_pie,ns,Avg_Qsa[state]);
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
	Ns_CostSoFar.push_back(make_pair(ns,cost));
}

void Sampling::updateVals(float& cost, int& depth)
{
	int itern_no = 0;

	auto it1 = Ns_CostSoFar.begin();
	auto it2 = Next_State.begin();
	// if (depth == Max_Depth)
	// 	cout << "Curr Avg = " << cost/Max_Depth << endl;
	for (auto it = State_Action.begin(); it != State_Action.end() && it1 != Ns_CostSoFar.end() && it2 != Next_State.end(); it++, it1++, it2++)
	{
		// Exploration[it->first][it->second] += 1;
		if (Qsa[it->first][it->second] < FLT_MAX)
		{
			float alpha = getAlpha(itern_no,depth, (it1->first));
			// float delta = (alpha)*(newQ(cost,depth) - Qsa[it->first][it->second]);

			// Avg_Qsa[it->first] += (delta - Avg_Qsa[it->first])/(it1->firsr + 1);
			
			// Qsa[it->first][it->second] += delta;
			// // cout << "alpha = " << getAlpha(itern_no,depth,(it1->first)) << endl;
			// if (alpha < 0)
			// {
			// 	cout << itern_no << " depth = " << depth << ", ns = " << (it1->first) << endl;
			// 	char c;
			// 	cin >> c;
			// }

			// NEW METHOD ------------------->
			float min_so_far = FLT_MAX;
			for (char i = 0; i < 4; i++)
				for (char j = 0; j < 4; j ++)
				{
					char act = (i << 3) | j;
					int next = *it2;
					if (Qsa[next].find(act) != Qsa[next].end())
					{
						// better?
						min_so_far = min(min_so_far, Qsa[next][act]);
					}
				}
			if (min_so_far < FLT_MAX)
				Qsa[it->first][it->second] += alpha*(it1->second + getGamma()*(min_so_far) - Qsa[it->first][it->second]);
		}
		itern_no += 1;

		//cerr << "State: "<< it->first << "Action: " << (int)(it->second) << "Naya QSA:" << Qsa[it->first][it->second] << endl;
	}
	clear();
	// cout << State_Action.size() << "is the final length \n";
	// char c;
	// cin >> c;
}