#ifndef LIFT_H
#define LIFT_H

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <unordered_map>
#include <sstream>
#include <limits.h>
#include <float.h>
#include <list>
#include <cstdlib>
#include <ctime>


// everything assuming N <= 5, K = 2.
extern int N;
extern int K;
extern int Max_Depth, Max_Time;
extern float p;
extern float q;
extern float r;
extern float tu;
extern char L1posnMask, L2posnMask;
extern int L1_buttonMask, L2_buttonMask;
extern int L1B_shift, L2B_shift;
extern int Floor_buttonMask;
extern int Up, Down, Open_Up, Open_Down,Still;
// extern long long Total_Expl;
// extern long double SumQs;

// not all states are valid. these 2 used for UCT.
// Q denotes cost. Hence, UCT uses -Q + sqrt(log(#times visited))

using namespace std;

struct State
{
	// L1B L2B 1u 2u2d 3u3d 4u4d 5d L1 3, L23
	// L1B L2B 1u 2u2d 3u3d 4d 3,3
	int Val;
	State(int);
	// void preProcess();
// if all buttons pressed are >=(<=) curr floor, go up(down). iska Q -inf
// if button of floor pressed -> open. iska Q -inf
};

void preProcess(int&);

struct Action
{
	// 5(3 bits) for l1, 5(3 bits) for l2.
	char Val;
	Action(char);
	string to_string();
	char getVal() const
	{
		return Val;
	};
};

// struct action_hash{
// 	inline std::size_t operator()(const Action &a) const {
// 		std::hash<char> char_hasher;
// 		return char_hasher(a.Val);
// 	}
// };

// struct pair_hash {
//     inline std::size_t operator()(const std::pair<int,Action> & v) const {
//         std::hash<int> int_hasher;
//         return int_hasher(v.first) ^ int_hasher(v.second.Val);
//     }
// };

extern unordered_map<int, unordered_map<char, float> > Qsa;
// extern unordered_map<pair<int,Action>, float, pair_hash> Qsa;
extern unordered_map<int, unordered_map<char, long> > Exploration;

inline bool operator==(const Action& lhs, const Action& rhs)
{
	return (lhs.getVal() == rhs.getVal());
}

inline string to_string(int x)
{
	stringstream s;
	s << x;
	return s.str();
}

// inline string to_string(int x)
// {
// 	stringstream s;
// 	s >> x;
// 	return s.str();
// }

inline string lift_str(char a, char l)
{
	switch (a)
	{
		case 1:
			return "AU" + to_string(l);
		case 2:
			return "AD" + to_string(l);
		case 3:
			return "AOU" + to_string(l);
		case 0:
			return "AOD" + to_string(l);
		default:
			return "";
	}
}

inline string char_to_String(char Val)
{
	return lift_str((Val & L1posnMask) >> 3, 1) + " " + lift_str(Val & L2posnMask, 2);
}

// inline 
// sampling : start state = 0's.
// goal state : 
// IDS se 

#endif