#include "Agent.h"

Agent::Agent(int &N,int &K,float &p,float &q,float &r,float &tu)
{
	Button_Floor = vector<pair<bool,bool> > (N, make_pair(false,false));
	Button_Lifts = vector<vector<bool> > (K, vector<bool> (N,false));
	Lift_Positions = vector<int> (K,0);
	Lift_Mode = vector<bool> (K,true);
}

vector<int> Agent::getActions()
{
	vector<int> ans(K,0);
	// decide mode
	// decide open/move
	for (int i = 0; i < K; i++)
	{
		int currr_floor = Lift_Positions[i];
		if (currr_floor == 0)
			Lift_Mode[i] = true;
		else if (currr_floor == N-1)
			Lift_Mode[i] = false;
		else
		{
			bool go_down = true;
			for (int j = N-1; j > currr_floor; j--)
				go_down = go_down && (!Button_Floor[j].first) && (!Button_Floor[j].second) && (!Button_Lifts[i][j]);
			bool go_up = true;
			for (int j = 0; j < currr_floor; j++)
				go_up = go_up && (!Button_Floor[j].first) && (!(Button_Floor[j].second)) && (!Button_Lifts[i][j]);
			if (go_down && go_up)
			{

			}
			else if (go_down)
			{
				Lift_Mode[i] = false;
			}
			else if (go_up)
			{
				Lift_Mode[i] = true;
			}
			else
			{

			}
		}
	}
	for (int i = 0; i < K; i++)
	{
		int currr_floor = Lift_Positions[i];
		if (Lift_Mode[i])
		{
			// choose b/w 1,3
			if (Button_Lifts[i][currr_floor] || Button_Floor[currr_floor].first)
				ans[i] = 3;
			else
				ans[i] = 1;
		}
		else
		{
			// choose b/w 0,2
			if (Button_Lifts[i][currr_floor] || Button_Floor[currr_floor].second)
				ans[i] = 2;
			else
				ans[i] = 0;
		}
	}
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

    do
    {
        string oneObs;
        iss >> oneObs;
        
        if(oneObs == "0")
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
        	pieces << firstpiece;

        	if(pieces == "BU" || pieces == "BD")
        	{
        		string manzil;
        		pieces << manzil;

        		if(pieces[1] == 'U')
        			Button_Floor[atoi(manzil)].first = true;
        		if(pieces[1] == 'D')
        			Button_Floor[atoi(manzil)].second = true;
        	}	
        	else (pieces[0] == 'B')
        	{
				string manzil, lift;
        		pieces << manzil;
        		pieces << lift;

        		Button_Lifts[stoi(lift)][stoi(manzil)] = true;		
        	}
        	else
        	{
        		cout << "WTF WHILE PARSING?????????????????"<<endl;
        	}

        }
        //cout << "Substring: " << sub << endl;
    } while (iss);
}