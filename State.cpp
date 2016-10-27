#include "Header.h"

Action::Action(char c)
{
	Val = c;
}

State::State(int s)
{
	Val = s;
}

void State::preProcess()
{
	// SHORTEN THIS!!
	// vector<int> l1;
	// int l1g = (Val && L1posnMask == 0) ? (Down << 3) : -1;
	// int l1gg = (Val && L1posnMask == 0) ? (Open_Down << 3) : -1;
	// int l1t = (Val && L1posnMask == N-1) ? (Up << 3) : -1;
	// int l1tt = (Val && L1posnMask == N-1) ? (Open_Up << 3) : -1;

	// int l2g = (Val && L2posnMask == 0) ? (Down) : -1;
	// int l2t = (Val && L2posnMask == N-1) ? (Up) : -1;
	// int l2gg = (Val && L2posnMask == 0) ? (Open_Down) : -1;
	// int l2tt = (Val && L2posnMask == N-1) ? (Open_Up) : -1;

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
	if ((Val && L1posnMask >> 3) == N-1)
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
	if ((Val && L2posnMask) == 0)
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
	if ((Val && L2posnMask) == N-1)
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
	char curr_floor = (Val && L1posnMask >> 3);
	int floor_butt_up = (curr_floor == 0) ? 2*(N-1): 1 + 2*(N - 1- curr_floor);
	// all those pressed are < crfloor.
	// floor wale bhi, only < crfloor.
	int l1_b = (Val && L1_buttonMask) >> L1B_shift;
	int floors = ((Val && Floor_buttonMask) >> 6);
	if ((((l1_b)%(1 << (N - curr_floor))) == 0) && (floors%(1 << floor_butt_up) == 0))
	{
		// l1 must go down. all other actions ->
		for (int i = 0; i < 5; i++)
		{
			if (i != Down)
			{
				// L1 ka i, L2 ka any -> Qsa = int_max.
				for (int j = 0; j < 5; j++)
					Qsa[this][Action((i << 3) || j)] = INT_MAX;
			}
		}
	}
	// all those pressed are > crfloor
	// floor wale bhi, > crfloor.
	int floor_butt_down = (crfloor == 0) ? (2*(N-1) - 1): (2*(N - 2 - curr_floor) + 1);
	if ( (l1_b < (1 << (N - 1 - curr_floor))) && (floors < (1 << floor_butt_down)) )
	{
		// l1 must go up.
		for (int i = 0; i < 5; i++)
		{
			if (i != Up)
			{
				for (int j = 0; j < 5; j ++)
					Qsa[this][Action((i << 3) || j)] = INT_MAX;
			}
		}
	}
	// same thing for lift2
	// TODO!!
}