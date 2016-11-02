#include "Agent.h"

int N,K,No_Eps;
float p,q,r,tu;
vector<string> ActionMap;

string getString(vector<int> &v)
{
	string ans = "";
	for (int i = 1; i <= v.size(); i++)
		ans += ActionMap[v[i-1]] + int_to_string(i) + " ";
	return ans + "\n";
}

int main(int argc, char const *argv[])
{
	N = atoi(argv[1]);
	K = atoi(argv[2]);
	p = atof(argv[3]);
	q = atof(argv[4]);
	r = atof(argv[5]);
	tu = atof(argv[6]);
	No_Eps = 0;

	Agent a (N,K,p,q,r,tu);
	ActionMap = vector<string> (5);
	ActionMap[0] = "AOD";
	ActionMap[1] = "AU";
	ActionMap[2] = "AD";
	ActionMap[3] = "AOU";
	ActionMap[4] = "AS";
	cout << "0" << endl;
	while (true)
	{
		// take input
		// move lifts
		// update all buttons
		string s;
		// cin.ignore(1000,'\n');
		getline(cin,s);
		No_Eps += 1;
		//cout << s << " OBS Got! \n";
		a.updateStateWithObs(s);
		a.updateMode();
		vector<int> action = a.getActions();
		cout << getString(action);
		a.updateState(action);
		a.updateMode();		
	}
	return 0;
}