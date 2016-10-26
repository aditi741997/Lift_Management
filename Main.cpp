#include "Header.h"

int N;
int K;
float p;
float q;
float r;
float tu;
unordered_map<pair<State,Action>, float> Qsa;
unordered_map<pair<State,Action>, long> Exploration;
int L1posnMask, L2posnMask;
int L1_buttonMask, L2_buttonMask;

int Up, Down, Open_Up, Open_Down,Still;

int main(int argc, char const *argv[])
{
	N = atoi(argv[1]);
	K = atoi(argv[2]);
	p = atof(argv[3]);
	q = atof(argv[4]);
	r = atof(argv[5]);
	tu = atof(argv[6]);
	L1posnMask = 7 << 3; // 111
	L2posnMask = 7; // 111
	L1_buttonMask = (N == 4) ? (15 << 16): (31 << 19) ;
	L1B_shift = (N == 4) ? 16: 19;
	L2_buttonMask = (N == 4) ? (15 << 12) : (31 << 14) ;
	L2B_shift = (N == 4) ? 12 : 14;
	Still = 0;
	Up = 1;
	Down = 2;
	Open_Up = 3;
	Open_Down = 4;

	return 0;
}