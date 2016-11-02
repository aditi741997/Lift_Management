#include "Agent.h"

Agent::Agent(int &N,int &K,float &p,float &q,float &r,float &tu)
{
	Button_Floor = vector<pair<bool,bool> > (N, make_pair(false,false));
	Button_Lifts = vector<vector<bool> > (K, vector<bool> (N,false));
	Lift_Positions = vector<int> (K,0);
	Lift_Mode = vector<int> (K,0);
}

vector<int> Agent::getActions()
{
	vector<int> ans(K,0);
	// decide mode
	// decide open/move
	for (int i = 0; i < K; i++)
	{
		int currr_floor = Lift_Positions[i];
		bool go_down = true; // > curr pe no floor/lift button pressed.
		for (int j = N-1; j > currr_floor; j--)
			go_down = go_down && (!Button_Floor[j].first) && (!Button_Floor[j].second) && (!Button_Lifts[i][j]);
		bool go_up = true;   // < curr pe no floor/lift button pressed.
		for (int j = 0; j < currr_floor; j++)
			go_up = go_up && (!Button_Floor[j].first) && (!(Button_Floor[j].second)) && (!Button_Lifts[i][j]);

		// if (currr_floor == 0)
		// 	Lift_Mode[i] = true;
		// else if (currr_floor == N-1)
		// 	Lift_Mode[i] = false;

		// if (Lift_Mode[i] == 1)
		// {
		// 	// up mode.
		// 	if (Button_Floor[currr_floor].first || Button_Lifts[i][currr_floor])
		// 		ans[i] = 3;
		// 	else if (go_down)
		// 	{
		// 		if (currr_floor > 0)
		// 		{
		// 			Lift_Mode[i] = false;
		// 			if (Button_Floor[currr_floor].second)
		// 				ans[i] = 0;
		// 			else
		// 				ans[i] = 2;		// CONFIRM!			
		// 		}
		// 		else
		// 			ans[i] = 3;
		// 	}
		// 	else
		// 		ans[i] = 1;
		// }
		// else if (Lift_Mode[i] == 2)
		// {
		// 	// down mode.
		// 	if (Button_Floor[currr_floor].second || Button_Lifts[i][currr_floor])
		// 		ans[i] = 0;
		// 	else if (go_up)
		// 	{
		// 		if (currr_floor < N-1)
		// 		{
		// 			Lift_Mode[i] = true;
		// 			if (Button_Floor[currr_floor].first)
		// 				ans[i] = 3;
		// 			else if (go_down)		// CONFIRM!
		// 				ans[i] = 0;
		// 			else
		// 				ans[i] = 2;
		// 		}
		// 		else
		// 			ans[i] = 0;
		// 	}
		// 	else
		// 		ans[i] = 2;
		// }
		// else
		// {
		// 	// vella mode
		// }

		// 3 MODES:
	}
	// for (int i = 0; i < K; i++)
	// {
	// 	int currr_floor = Lift_Positions[i];
	// 	if (Lift_Mode[i])
	// 	{
	// 		// choose b/w 1,3
	// 		if (Button_Lifts[i][currr_floor] || Button_Floor[currr_floor].first)
	// 			ans[i] = 3;
	// 		else
	// 			ans[i] = 1;
	// 	}
	// 	else
	// 	{
	// 		// choose b/w 0,2
	// 		if (Button_Lifts[i][currr_floor] || Button_Floor[currr_floor].second)
	// 			ans[i] = 2;
	// 		else
	// 			ans[i] = 0;
	// 	}
	// }
	return ans;
}

void Agent::updateState(vector<int> &v)
{
	for (int i = 0; i < K; i++)
	{
		int currr_floor = Lift_Positions[i];
		switch (v[i])
		{
			case 0:
				Button_Floor[currr_floor].second = false;
				Button_Lifts[i][currr_floor] = false;
				break;
			case 1:
				Lift_Positions[i] += 1;
				break;
			case 2:
				Lift_Positions[i] -= 1;
				break;
			case 3:
				Button_Floor[currr_floor].first = false;
				Button_Lifts[i][currr_floor] = false;
				break;
			default:
				break;
		}
	}
}

void Agent::updateStateWithObs(string &inputStream)
{
	// TODO : AAYAN
	// parse the observations, change buttons

    istringstream iss(inputStream);
    while (iss)
    {
        string oneObs;
        iss >> oneObs;

        cout << oneObs << " 1st obsn \n";
        
        if(oneObs == "0" || oneObs == "" || oneObs == "\n")
        {
        	//donothing
        	break;
        }
        else
        {
        	for(auto it = oneObs.begin(); it != oneObs.end(); it++)
        		if(*it == '_')
        			*it = ' ';

        	istringstream pieces(oneObs);

        	string firstpiece;
        	pieces >> firstpiece;
        	cout << "1st piece = " << firstpiece << endl;

        	if(firstpiece == "BU" || firstpiece == "BD")
        	{
        		int manzil;
        		pieces >> manzil;
        		cout << "manzil = " << manzil << endl;
        		if(firstpiece[1] == 'U')
        			Button_Floor[manzil].first = true;
        		if(firstpiece[1] == 'D')
        			Button_Floor[manzil].second = true;
        	}	
        	else if (firstpiece[0] == 'B')
        	{
				int manzil, lift;
        		pieces >> manzil;
        		pieces >> lift;

        		Button_Lifts[lift][manzil] = true;		
        	}
        	else
        	{
        		cout << "WTF WHILE PARSING?????????????????"<<endl;
        	}

        }
        //cout << "Substring: " << sub << endl;
    }
}