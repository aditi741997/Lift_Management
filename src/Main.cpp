#include "Agent.h"

int N,K;
float p,q,r,tu;
vector<string> ActionMap;

string getString(vector<int> &v)
{
	string ans = "";
	for (int i = 1; i <= v.size(); i++)
		ans += ActionMap[i-1] + to_string(i) + " ";
	return ans;
}

int main(int argc, char const *argv[])
{
	cin >> N >> K >> p >> q >> r >> tu;
	Agent a (N,K,p,q,r,tu);
	ActionMap[0] = "AOD";
	ActionMap[1] = "AU";
	ActionMap[2] = "AD";
	ActionMap[3] = "AOU";
	cout << "0" << endl;
	cin.ignore();
	while (true)
	{
		// take input
		// move lifts
		// update all buttons
		string s;
		getline(cin,s);
		cout << "OBS Got! \n";
		a.updateStateWithObs(s);
		vector<int> action = a.getActions();
		for (int i = 0; i < K; i++)
			cout << action[i] << " ith action \n";
		cout << getString(action);
		a.updateState(action);			
	}
	return 0;
}