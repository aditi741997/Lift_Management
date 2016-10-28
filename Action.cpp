#include "Header.h"

Action::Action(char c)
{
	Val = c;
}

string Action::to_string()
{
	return lift_str(Val && L1posnMask, 1) + " " + lift_str(Val && L2posnMask, 2);
}

