#include "Header.h"

int N;
int K;
double p;
double q;
double r;
double tu;
unordered_map<pair<State,Action>, double> Qsa;
unordered_map<pair<State,Action>, long> Exploration;

int main(int argc, char const *argv[])
{
	N = atoi(argv[1]);
	K = atoi(argv[2]);
	p = atof(argv[3]);
	q = atof(argv[4]);
	r = atof(argv[5]);
	tu = atof(argv[6]);
	return 0;
}