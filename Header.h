#include <iostream>
#include <cstdlib>
#include <cmath>

namespace Types
{
	typedef short int State;
	typedef char Action;
}

// everything assuming N <= 5, K = 2.
extern int N;
extern int K;
extern double p;
extern double q;
extern double r;
extern double tu;

using namespace std;
using namespace Types;