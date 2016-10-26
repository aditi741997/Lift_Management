#include "Header.h"

void State::preProcess()
{
	// SHORTEN THIS!!
	if (Val && L1posnMask == 0)
	{
		// any action with L1 go down is invalid.
		Action a;
		Action b;
		a.Val = Down << 3;
		b.Val = Open_Down << 3;
		for (int i = 0; i < 5; i++)
		{
			a.Val = a.Val || i;
			b.Val = b.Val || i;
			Qsa[this][a] = INT_MAX;
			Qsa[this][b] = INT_MAX;
			a.Val = a.Val && !i;
			b.Val = b.Val && !i;
		}
	}
	if (Val && L1posnMask == N-1)
	{
		// any action with L1 go up is invalid.
		Action a;
		Action b;
		a.Val = Up << 3;
		b.Val = Open_Up << 3;
		for (int i = 0; i < 5; i++)
		{
			a.Val = a.Val || i;
			b.Val = b.Val || i;
			Qsa[this][a] = INT_MAX;
			Qsa[this][b] = INT_MAX;
			a.Val = a.Val && !i;
			b.Val = b.Val && !i;
		}
	}
	if ((Val && L2posnMask >> 3) == 0)
	{
		// any action with L1 go up is invalid.
		Action a;
		Action b;
		a.Val = Down;
		b.Val = Open_Down;
		for (int i = 0; i < 5; i++)
		{
			a.Val = a.Val || (i << 3);
			b.Val = b.Val || (i << 3);
			Qsa[this][a] = INT_MAX;
			Qsa[this][b] = INT_MAX;
			a.Val = a.Val && !(i << 3);
			b.Val = b.Val && !(i << 3);
	}
	if ((Val && L2posnMask >> 3) == N-1)
	{
		// any action with L1 go up is invalid.
		Action a;
		Action b;
		a.Val = Up;
		b.Val = Open_Up;
		for (int i = 0; i < 5; i++)
		{
			a.Val = a.Val || (i << 3);
			b.Val = b.Val || (i << 3);
			Qsa[this][a] = INT_MAX;
			Qsa[this][b] = INT_MAX;
			a.Val = a.Val && !(i << 3);
			b.Val = b.Val && !(i << 3);
		}
	}
	// all buttons > f, lift wale bhi > f.
	if (Val && L1_buttonMask )
}