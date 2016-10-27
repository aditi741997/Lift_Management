#include <iostream>
#include <cstdlib>
#include <cmath>
#include <unordered_map>


// everything assuming N <= 5, K = 2.
extern int N;
extern int K;
extern float p;
extern float q;
extern float r;
extern float tu;
extern int L1posnMask, L2posnMask;
extern int L1_buttonMask, L2_buttonMask;
extern int L1B_shift, L2B_shift;
extern int Floor_buttonMask;
extern int Up, Down, Open_Up, Open_Down,Still;

extern unordered_map<pair<int,char>, float> Qsa;
extern unordered_map<pair<State,Action>, long> Exploration;
// not all states are valid. these 2 used for UCT.
// Q denotes cost. Hence, UCT uses -Q + sqrt(log(#times visited))

using namespace std;
using namespace Types;

struct State
{
	// L1B L2B 1u 2u2d 3u3d 4u4d 5d L1 3, L23
	// L1B L2B 1u 2u2d 3u3d 4d 3,3
	int Val;
	State(int);
	void preProcess();
// if all buttons pressed are >=(<=) curr floor, go up(down). iska Q -inf
// if button of floor pressed -> open. iska Q -inf
};

struct Action
{
	// 5(3 bits) for l1, 5(3 bits) for l2.
	char Val;
	Action(char);
	string to_string();
};



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