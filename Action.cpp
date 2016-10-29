#include "Header.h"

Action::Action(char c)
{
	Val = c;
}

string Action::to_string()
{
	cout << "My val is = " << (int)Val << endl;
	cout << ((Val & L1posnMask) >> 3) << " is l1 action" << endl;
	return lift_str((Val & L1posnMask) >> 3, 1) + " " + lift_str(Val & L2posnMask, 2);
}