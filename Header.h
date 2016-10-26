#include <iostream>
#include <cstdlib>
#include <cmath>
#include <unordered_map>


// everything assuming N <= 5, K = 2.
extern int N;
extern int K;
extern double p;
extern double q;
extern double r;
extern double tu;

extern unordered_map<pair<State,Action>, double> Qsa;
extern unordered_map<pair<State,Action>, long> Exploration;
// not all states are valid. these 2 used for UCT.
// Q denotes cost. Hence, UCT uses -Q + sqrt(log(#times visited))

using namespace std;
using namespace Types;

struct State
{
	int Val;
// 24 bits.
};

struct Action
{
	char Val;
	string to_string();
};

void preProcess();
// if all buttons pressed are >=(<=) curr floor, go up(down). iska Q -inf
// if button of floor pressed -> open. iska Q -inf


// sampling : start state = 0's.
// goal state : 
// IDS se 
class Sampling
{
	int getObservation(); // probability se observation.
// IDS.
	// UCT se choose action
	Action getAction(State&);
	void sample(int); // int : no of episodes till which sample.
}