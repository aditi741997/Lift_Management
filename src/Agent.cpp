#include "Agent.h"

Agent::Agent(int &N,int &K,float &p,float &q,float &r,float &tu)
{
	Button_Floor = vector<pair<bool,bool> > (N, make_pair(false,false));
	Button_Lifts = vector<vector<bool> > (K, vector<bool> (N,false));
	Lift_Positions = vector<int> (K,0);
	Lift_Mode = vector<int> (K,0);
	// Exp_people = vector<float> (N,0);
	Time_open_Up = vector<int> (N,0);
	Time_open_Down = vector<int> (N,0);
}

void Agent::idle_Action1(int currr_floor, int i, vector<int> &ans)
{
	int close_up = closest_Up(currr_floor);
	int close_down = closest_Down(currr_floor);
	// cout << "For lift " << i << ", close up, down = " << close_up << close_down << endl;
	if (Button_Floor[currr_floor].second)
		ans[i] = 0;
	else if (Button_Floor[currr_floor].first)
		ans[i] = 3;
	else if (Button_Lifts[i][currr_floor])
	{
		if (currr_floor == N-1)
			ans[i] = 0;
		else
			ans[i] = 3;
	}
	else if (close_up == N)
	{
		if (close_down > -1)
			ans[i] = 2;
		else
			ans[i] = 4;
	}
	else
	{
		if (close_down == -1)
			ans[i] = 1;
		else if ( (currr_floor - close_down) < (close_up - currr_floor) )
			ans[i] = 2;
		else
			ans[i] = 1;
	}
}

inline float Agent::getVal(int f, int lfloor)
{
	return (1.1*abs(f - lfloor)) - min(Time_open_Up[f],Time_open_Down[f]);
}

void Agent::idle_Action2(int currr_floor, int i, vector<int> &ans)
{
	// ith lift, idle,
	if (Button_Floor[currr_floor].second)
		ans[i] = 0;
	else if (Button_Floor[currr_floor].first)
		ans[i] = 3;
	else if (Button_Lifts[i][currr_floor])
	{
		if (currr_floor == N-1)
			ans[i] = 0;
		else
			ans[i] = 3;
	}
	else
	{		
		float curr_min = exp(35);
		int assign_floor = -1;
		for (int f = 0; f < N; f++)
		{
			if (f != currr_floor && Button_Floor[f].first || Button_Floor[f].second)
			{
				if (getVal(f,currr_floor) < curr_min)
				{
					curr_min = getVal(f,currr_floor);
					assign_floor = f;
				}
			}
		}
		if (assign_floor > -1)
		{
			if (assign_floor < currr_floor)
				ans[i] = 2;
			else
				ans[i] = 1;		
		}
		else
			ans[i] = 4;
	}
}

void Agent::updateMode()
{
	for (int i = 0; i < K; i++)
	{
		if (button_up(i))
			Lift_Mode[i] = 1;
		else if (button_down(i))
			Lift_Mode[i] = 2;
		else
			Lift_Mode[i] = 0;
		cerr << "New mode of lift " << i << " is : " << Lift_Mode[i] << endl;
	}
}

vector<int> Agent::getActions()
{
	vector<int> ans(K,0);
	// decide mode
	// decide open/move
	for (int i = 0; i < K; i++)
	{
		int currr_floor = Lift_Positions[i];
		// bool go_down = true; // > curr pe no floor/lift button pressed.
		// for (int j = N-1; j > currr_floor; j--)
		// 	go_down = go_down && (!Button_Floor[j].first) && (!Button_Floor[j].second) && (!Button_Lifts[i][j]);
		// bool go_up = true;   // < curr pe no floor/lift button pressed.
		// for (int j = 0; j < currr_floor; j++)
		// 	go_up = go_up && (!Button_Floor[j].first) && (!(Button_Floor[j].second)) && (!Button_Lifts[i][j]);

		switch (Lift_Mode[i])
		{
			case 1:
				if (Button_Floor[currr_floor].first)
					ans[i] = 3;
				else if (Button_Lifts[i][currr_floor])
				{
					if (currr_floor == N-1)
						ans[i] = 0;
					else
						ans[i] = 3;
				}
				else
					ans[i] = 1;
				break;
			case 2:
				if (Button_Floor[currr_floor].second)
					ans[i] = 0;
				else if (Button_Lifts[i][currr_floor])
				{
					if (currr_floor == 0)
						ans[i] = 3;
					else
						ans[i] = 0;
				}
				else
					ans[i] = 2;
				break;
			case 0:
				idle_Action1(currr_floor,i,ans);
				break;
		}

		// 3 MODES:
	}
	return ans;
}

void Agent::updateState(vector<int> &v)
{
	for (int i = 0; i < N; i++)
	{
		Time_open_Up[i] += 1;
		Time_open_Down[i] += 1;
	}

	for (int i = 0; i < K; i++)
	{
		int currr_floor = Lift_Positions[i];
		switch (v[i])
		{
			case 0:
				Button_Floor[currr_floor].second = false;
				Button_Lifts[i][currr_floor] = false;
				Time_open_Down[currr_floor] = 0;
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
				Time_open_Up[currr_floor] = 0;
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

        if(oneObs == "0")
        {
        	;
        }
        else if( oneObs == "" || oneObs == "\n")
        {
        	break;
        }
        else
        {
        	//cout << oneObs << " 1st obsn \n";

        	for(auto it = oneObs.begin(); it != oneObs.end(); it++)
        		if(*it == '_')
        			*it = ' ';

        	istringstream pieces(oneObs);

        	string firstpiece;
        	pieces >> firstpiece;
        	//cout << "1st piece = " << firstpiece << endl;

        	if(firstpiece == "BU" || firstpiece == "BD")
        	{
        		int manzil;
        		pieces >> manzil;
        		//cout << "manzil = " << manzil << endl;
        		if(firstpiece[1] == 'U')
        			Button_Floor[manzil-1].first = true;

        		if(firstpiece[1] == 'D')
        			Button_Floor[manzil-1].second = true;
        	}
        	else if (firstpiece[0] == 'B')
        	{
				int manzil, lift;
        		pieces >> manzil;
        		pieces >> lift;

        		//cout << "manzil = " << manzil << "lift = " << lift << endl;

        		Button_Lifts[lift-1][manzil-1] = true;		
        	}
        	else
        	{
        		//cout << "WTF WHILE PARSING?????????????????"<<endl;
        	}

        }
        //cout << "Substring: " << sub << endl;
    }
}