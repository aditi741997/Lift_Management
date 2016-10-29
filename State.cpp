#include "Header.h"

State::State(int s)
{
	Val = s;
	preProcess();
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

	if ((Val & L1posnMask) == 0)
	{
		// any action with L1 go down is invalid.
		cout << "yo, loop 1 \n";
		Action a ((Down << 3)); // AD1 (4 acts of 2)
		Action b ((Open_Down << 3)); // AOD1 (4 acts of 2)
		for (char i = 0; i < 4; i++)
		{
			a.Val = a.Val | i;
			b.Val = b.Val | i;
			cout << "Disabling : " << a.to_string() << endl;
			cout << "Disabling : " << b.to_string() << endl;
			Qsa[Val][a] = INT_MAX;
			Qsa[Val][b] = INT_MAX;
			a.Val = (a.Val & (~i));
			b.Val = (b.Val & (~i));
		}
	}
	if ((Val & L1posnMask >> 3) == N-1)
	{
		// any action with L1 go up is invalid.
		Action a (Up << 3);
		Action b (Open_Up << 3);
		for (char i = 0; i < 4; i++)
		{
			a.Val = a.Val | i;
			b.Val = b.Val | i;
			cout << "Disabling : " << a.to_string() << endl;
			cout << "Disabling : " << b.to_string() << endl;
			Qsa[Val][a] = INT_MAX;
			Qsa[Val][b] = INT_MAX;
			a.Val = (a.Val & (~i));
			b.Val = (b.Val & (~i));
		}
	}
	if ((Val & L2posnMask) == 0)
	{
		// any action with L1 go up is invalid.
		cout << "yo, loop 3 \n";
		Action a (Down);
		Action b (Open_Down);
		for (char i = 0; i < 4; i++)
		{
			a.Val = a.Val | (i << 3);
			b.Val = b.Val | (i << 3);
			cout << "Disabling : " << a.to_string() << endl;
			cout << "Disabling : " << b.to_string() << endl;
			Qsa[Val][a] = INT_MAX;
			Qsa[Val][b] = INT_MAX;
			a.Val = a.Val & (~(i << 3));
			b.Val = b.Val & (~(i << 3));
		}
	}
	if ((Val & L2posnMask) == N-1)
	{
		// any action with L1 go up is invalid.
		Action a (Up);
		Action b (Open_Up);
		for (char i = 0; i < 4; i++)
		{
			a.Val = a.Val | (i << 3);
			b.Val = b.Val | (i << 3);
			cout << "Disabling : " << a.to_string() << endl;
			cout << "Disabling : " << b.to_string() << endl;
			Qsa[Val][a] = INT_MAX;
			Qsa[Val][b] = INT_MAX;
			a.Val = a.Val & (~(i << 3));
			b.Val = b.Val & (~(i << 3));
		}
	}
	char curr_floor1 = (Val & L1posnMask >> 3);
	char curr_floor2 = (Val & L2posnMask >> 3);
	char floor_butt_up1 = (curr_floor1 == 0) ? 2*(N-1): 1 + 2*(N - 1- curr_floor1);
	char floor_butt_down1 = (curr_floor1 == 0) ? (2*(N-1) - 1): (2*(N - 2 - curr_floor1) + 1);

	char floor_butt_up2 = (curr_floor2 == 0) ? 2*(N-1): 1 + 2*(N - 1- curr_floor2);
	char floor_butt_down2 = (curr_floor2 == 0) ? (2*(N-1) - 1): (2*(N - 2 - curr_floor2) + 1);
	// all those pressed are < crfloor.
	// floor wale bhi, only < crfloor.
	char l1_b = (Val & L1_buttonMask) >> L1B_shift;
	char l2_b = (Val & L2_buttonMask) >> L2B_shift;
	short int floors = ((Val & Floor_buttonMask) >> 6);

	cout << "Now preProcess part 2 ------------ \n";

	if ((l1_b) > 0)
	{
		if ((((l1_b)%(1 << (N - curr_floor1))) == 0) && (floors%(1 << floor_butt_up1) == 0) && curr_floor1 != 0)
		{
			cout << "l1 must go down. all other actions disable" << endl;
			for (char i = 0; i < 4; i++)
			{
				if (i != Down)
				{
					// L1 ka i, L2 ka any -> Qsa = int_max.
					for (char j = 0; j < 4; j++)
					{
						Action a((i << 3) | j);
						cout << "Disabling " << a.to_string() << endl;
						Qsa[Val][a] = INT_MAX;
					}
				}
			}
		}
		// all those pressed are > crfloor
		// floor wale bhi, > crfloor.
		if ( (l1_b < (1 << (N - 1 - curr_floor1))) && (floors < (1 << floor_butt_down1)) && (curr_floor1 < N-1))
		{
			cout << "l1 must go up." << endl;
			for (char i = 0; i < 4; i++)
			{
				if (i != Up)
				{
					for (char j = 0; j < 4; j ++)
					{
						Action a((i << 3) | j);
						cout << "Disabling " << a.to_string() << endl;
						Qsa[Val][a] = INT_MAX;
					}
				}
			}
		}		
	}
	// same thing for lift2
	// TODO!!
	if ((l2_b) > 0)
	{
		if ((((l2_b)%(1 << (N - curr_floor2))) == 0) && (floors%(1 << floor_butt_up2) == 0) && curr_floor2 > 0)
		{
			// l2 must go down. all other actions ->
			cout << "l2 down \n";
			for (char i = 0; i < 4; i++)
			{
				if (i != Down)
				{
					// L1 ka i, L2 ka any -> Qsa = int_max.
					for (char j = 0; j < 4; j++)
					{
						Action a((j << 3) | i);
						cout << "Disabling " << a.to_string() << endl;
						Qsa[Val][a] = INT_MAX;
					}
				}
			}
		}
		// all those pressed are > crfloor
		// floor wale bhi, > crfloor.
		if ( (l2_b < (1 << (N - 1 - curr_floor2))) && (floors < (1 << floor_butt_down2)) && curr_floor2 < N-1)
		{
			// l2 must go up.
			cout << "l2 up \n";
			for (char i = 0; i < 4; i++)
			{
				if (i != Up)
				{
					for (char j = 0; j < 4; j ++)
					{
						Action a((j << 3) | i);
						cout << "Disabling " << a.to_string() << endl;
						Qsa[Val][a] = INT_MAX;
					}
				}
			}
		}		
	}
}