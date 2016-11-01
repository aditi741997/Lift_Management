#include "Header.h"

State::State(int s)
{
	Val = s;
	// preProcess();
}

void preProcess(int& Val)
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
		// cout << "yo, loop 1 \n";
		char a = ((Down << 3)); // AD1 (4 acts of 2)
		char b = ((Open_Down << 3)); // AOD1 (4 acts of 2)
		for (char i = 0; i < 4; i++)
		{
			a = a | i;
			b = b | i;
			// cout << "Disabling : " << char_to_String(a) << endl;
			// cout << "Disabling : " << char_to_String(b) << endl;
			Qsa[Val][a] = FLT_MAX;
			Qsa[Val][b] = FLT_MAX;
			a = a & (~i);
			b = b & (~i);
		}
	}
	if (((Val & L1posnMask) >> 3) == N-1)
	{
		// any action with L1 go up is invalid.
		char a = (Up << 3);
		char b = (Open_Up << 3);
		for (char i = 0; i < 4; i++)
		{
			a = a | i;
			b = b | i;
			// cout << "Disabling : " << char_to_String(a) << endl;
			// cout << "Disabling : " << char_to_String(b) << endl;
			Qsa[Val][a] = FLT_MAX;
			Qsa[Val][b] = FLT_MAX;
			a = a & (~i);
			b = b & (~i);
		}
	}
	if ((Val & L2posnMask) == 0)
	{
		// any action with L1 go up is invalid.
		// cout << "yo, loop 3 \n";
		char a = (Down);
		char b = (Open_Down);
		for (char i = 0; i < 4; i++)
		{
			a = a | (i << 3);
			b = b | (i << 3);
			// cout << "Disabling : " << char_to_String(a) << endl;
			// cout << "Disabling : " << char_to_String(b) << endl;
			Qsa[Val][a] = FLT_MAX;
			Qsa[Val][b] = FLT_MAX;
			a = a & (~(i << 3));
			b = b & (~(i << 3));
		}
	}
	if ((Val & L2posnMask) == N-1)
	{
		// any action with L1 go up is invalid.
		char a = (Up);
		char b = (Open_Up);
		for (char i = 0; i < 4; i++)
		{
			a = a | (i << 3);
			b = b | (i << 3);
			// cout << "Disabling : " << char_to_String(a) << endl;
			// cout << "Disabling : " << char_to_String(b) << endl;
			Qsa[Val][a] = FLT_MAX;
			Qsa[Val][b] = FLT_MAX;
			a = a & (~(i << 3));
			b = b & (~(i << 3));
		}
	}
	char curr_floor1 = ((Val & L1posnMask) >> 3);
	char curr_floor2 = (Val & L2posnMask);
	char floor_butt_up1 = (curr_floor1 == 0) ? 2*(N-1) : 1 + 2*(N - 1 - curr_floor1);
	char floor_butt_down1 = (2*(N - 2 - curr_floor1) + 1);

	char floor_butt_up2 = (curr_floor2 == 0) ? 2*(N-1): 1 + 2*(N - 1- curr_floor2);
	char floor_butt_down2 = (2*(N - 2 - curr_floor2) + 1);
	// all those pressed are < crfloor.
	// floor wale bhi, only < crfloor.
	char l1_b = (Val & L1_buttonMask) >> L1B_shift;
	char l2_b = (Val & L2_buttonMask) >> L2B_shift;
	short int floors = ((Val & Floor_buttonMask) >> 6);

	// cout << "Now preProcess part 2 ------------ \n";

	if ((l1_b) > 0)
	{
		if ((((l1_b)%(1 << (N - curr_floor1))) == 0) && (floors%(1 << floor_butt_up1) == 0) && curr_floor1 != 0)
		{
			cout << "l1 must go down. all other actions disable" << endl;
			for (char i = 0; i < 4; i++)
			{
				if (i != Down)
				{
					// L1 ka i, L2 ka any -> Qsa = FLT_MAX.
					for (char j = 0; j < 4; j++)
					{
						char a = ((i << 3) | j);
						// cout << "Disabling " << char_to_String(a) << endl;
						Qsa[Val][a] = FLT_MAX;
					}
				}
			}
		}
		// all those pressed are > crfloor
		// floor wale bhi, > crfloor.
		if ((curr_floor1 < N-1) && (l1_b < (1 << (N - 1 - curr_floor1))) && (floors < (1 << floor_butt_down1)))
		{
			cout << "l1 must go up." << endl;
			for (char i = 0; i < 4; i++)
			{
				if (i != Up)
				{
					for (char j = 0; j < 4; j ++)
					{
						char a = ((i << 3) | j);
						// cout << "Disabling " << char_to_String(a) << endl;
						Qsa[Val][a] = FLT_MAX;
					}
				}
			}
		}		
	}
	// // same thing for lift2
	// // TODO!!
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
					// L1 ka i, L2 ka any -> Qsa = FLT_MAX.
					for (char j = 0; j < 4; j++)
					{
						char a = ((j << 3) | i);
						// cout << "Disabling " << char_to_String(a) << endl;
						Qsa[Val][a] = FLT_MAX;
					}
				}
			}
		}
		// all those pressed are > crfloor
		// floor wale bhi, > crfloor.
		if ((curr_floor2 < N-1) && (l2_b < (1 << (N - 1 - curr_floor2))) && (floors < (1 << floor_butt_down2)))
		{
			// l2 must go up.
			cout << "l2 up \n";
			for (char i = 0; i < 4; i++)
			{
				if (i != Up)
				{
					for (char j = 0; j < 4; j ++)
					{
						char a = ((j << 3) | i);
						// cout << "Disabling " << char_to_String(a) << endl;
						Qsa[Val][a] = FLT_MAX;
					}
				}
			}
		}

		// lift1 :
		if ((Val & (1 << (6+2+2*(N-2)+N+N-1-curr_floor1))) != 0)
		{
			// open up or open down.
			for (char i = 0; i < 4; i++)
			{
				if (i == Up || i == Down)
				{
					for (char j = 0; j < 4; j++)
						Qsa[(i << 3) | j] = FLT_MAX;
				}
			}
		}

		// lift2 :
		if ((Val & (1 << (6+2+2*(N-2)+N-1-curr_floor2))) != 0)
		{
			for (char i = 0; i < 4; i++)
			{
				if (i == Up || i == Down)
					for (char j = 0; j < 4; j++)
						Qsa[i | (j << 3)] = FLT_MAX;
			}
		}
	}
}