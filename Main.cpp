#include "Sample.h"
#include "Simulator.h"

int Max_Depth, Max_Time;
int N;
int K;
float p;
float q;
float r;
float tu;
unordered_map<int, unordered_map<char, float> > Qsa;
unordered_map<int,float> Avg_Qsa;
unordered_map<int, unordered_map<char, long> > Exploration;
char L1posnMask, L2posnMask;
int L1_buttonMask, L2_buttonMask;
int Floor_buttonMask;
int L1B_shift, L2B_shift;

int Up, Down, Open_Up, Open_Down,Still;

void runSimulation(int &depth, Sampling &sampler)
{
	Simulator s (K,N,p,q,r,tu,false);
	char x[2];
	for(int i = 0; i < depth; i++)
	{
		char act;
		int curr_state = s.getState();
		preProcess(curr_state);
		sampler.chooseAction(act,curr_state);
		// cout << "Preprocessing state " << curr_state << endl;
		x[0] = (act & L1posnMask) >> 3;
		x[1] = (act & L2posnMask);
		// cout << "Action picked = " << (int)x[0] << (int)x[1] << endl;
		s.updateWithAction(x);
	}
	float f = s.getCost();
	sampler.updateVals(f,depth);
}

int main(int argc, char const *argv[])
{
	time_t Start_time = time(0);
	N = atoi(argv[1]);
	K = atoi(argv[2]);
	p = atof(argv[3]);
	q = atof(argv[4]);
	r = atof(argv[5]);
	tu = atof(argv[6]);
	Max_Depth = pow(10,3);
	Max_Time = 30;
	L1posnMask = 7 << 3; // 111
	L2posnMask = 7; // 111
	L1_buttonMask = (N == 4) ? (15 << 16) : (31 << 19) ;
	L1B_shift = (N == 4) ? 16 : 19;
	L2_buttonMask = (N == 4) ? (15 << 12) : (31 << 14) ;
	L2B_shift = (N == 4) ? 12 : 14;
	Floor_buttonMask = ((N == 4) ? 63: 127) << 6;
	Up = 1;
	Down = 2;
	Open_Up = 3;
	Open_Down = 0;
	// cout << (L1posnMask + 3) << " is the l1 mask" << endl;
	// Action a (16);
	// cout << a.to_string() << endl;
	// State s (((1 << 17) + 64));

//<<<<<<< HEAD
//	State start(0);

	Sampling sam;
	int i = 0;
// =======
// 	// State start(0);
// 	Sampling sam;
// 	int i = 0;
// 	int state = 2 + (1 << 19);
// 	preProcess(state);
// 	// char c;
// 	// cin >> c;
// >>>>>>> 3ac5b022d10a79e89e345bc5ed1baa328d83f3de
	while ((time(0) - Start_time) < Max_Time)
	{
		// int depth = 2000;
		// runSimulation(depth,s);

		int depth = 5;
		while (((time(0) - Start_time) < Max_Time) && depth <= Max_Depth)
		{
			runSimulation(depth,sam);
			depth += 5;
			// cout << "Depth = " << depth << " States = " << Qsa.size() << endl;
		}
		cout << "Iteration " << i << ", States covered : " << Qsa.size() << endl;
		cout << "Time taken : " << time(0) - Start_time << endl;
		i += 1;
	}
// print vals, check??
	// for (auto it = Qsa.begin(); it != Qsa.end(); it++)
	// 	for (auto it1 = (it->second).begin(); it1 != (it->second).end(); it++)
	// 		cout << "State = " << (it->first) << ", Action = " << (it1->second) << ", val = " << (it1->second) << endl;

	cout << "0" << endl;
	Simulator s(K,N,p,q,r,tu,false);
	while (true)
	{
		int state = s.getState();
		cout << state << endl;
		preProcess(state);
		char best_Action[2];
		best_Action[0] = 0;
		best_Action[1] = 0;
		float best_Val = FLT_MAX;
		if (Qsa.find(state) != Qsa.end())
		{
			for (char i = 0; i < 4; i++)
				for (char j = 0; j < 4; j++)
				{
					char act = (i << 3) | j;
					if (Qsa[state].find(act) != Qsa[state].end())
					{
						cout << "Val = " << Qsa[state][act] << "\t of action " << (int)i << "," << (int)j << endl;					
						if (Qsa[state][act] < best_Val)
						{
							best_Val = Qsa[state][act];
							best_Action[0] = i;
							best_Action[1] = j;
						}
					}
				}		
			cout << Qsa[state][(best_Action[0] << 3) | (best_Action[1])] << " is the Q value, action = " << (int)(best_Action[0]) <<","<< (int)(best_Action[1]) << endl;
		}
		else
		{
			// not explored!
			cout << "NOT EXPLORED!!!!! \n";
			best_Action[0] = 3;
			best_Action[1] = 1;
		}
		s.updateWithAction(best_Action);
		s.display();
		cout << "TOTAL COST = " << s.getCost() << endl;
		char c;
		cin >> c;
	}
	// Simulator s (K,N,p,q,r,tu,true);
	// while (true)
	// {
	// 	char arr[K];
	// 	for (int i = 0; i < K; i++)
	// 	{
	// 		string s;
	// 		cin >> s;
	// 		// switch (s.substr(0,s.length() - 1))
	// 		// {
	// 		// 	case "AOD":
	// 		// 		arr[i] = Open_Down;
	// 		// 		break;
	// 		// 	case "AOU":
	// 		// 		arr[i] = Open_Up;
	// 		// 		break;
	// 		// 	case "AU":
	// 		// 		arr[i] = Up;
	// 		// 		break;
	// 		// 	case "AO":
	// 		// 		arr[i] = Down;
	// 		// 		break;
	// 		// }
	// 	}
	// 	// pass to simulator, updates action!!

	// 	char act[K];
	// 	// select action
	// 	char action = 0;
	// 	float best_val = -FLT_MAX;
	// 	for (char i = 0; i < 4; i++)
	// 		for (char j = 0; j < 4; j++)
	// 		{

	// 		}
	// 	s.updateWithAction(act);
	// 	int state = s.getState();

	// }
 	// do IDS forever
	return 0;
}