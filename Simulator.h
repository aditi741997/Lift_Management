#ifndef SIM_H
#define SIM_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <unordered_set>
#include <cmath>
#include <limits.h>

struct Person
{
	char start_floor;
	char destination;
	bool direction;

	Person copyP() const
	{
		Person p;
		p.start_floor = start_floor;
		p.destination = destination;
		p.direction = direction;
		return p;
	}

	bool operator==(const Person &p) const
	{
		if(start_floor == p.start_floor && destination == p.destination && direction == p.direction)
			return true;
		else
			return false;
	}
};

struct Person_Hash
{
	std::size_t operator()(const Person &person ) const
    {
        return (person.start_floor*107+person.destination*91+((int)(person.direction))*73)%89;
    }
};

class Simulator
{

	const char Up = 1;
	const char Down = 2;
	const char Open_Up = 3;
	const char Open_Down = 0;
	bool is_real_life;

	char no_lifts, no_floors;
	float p,q,r,t_u;

	std::vector< char > lift_pos;
	std::vector< std::pair<bool, bool> > buttons_on_floor;
	std::vector< char > buttons_on_lift;
	std::vector< std::unordered_multiset< Person, Person_Hash > > people_in_lift;
	std::vector< std::unordered_multiset< Person, Person_Hash > > people_in_floor;

	int total_wait_cost = 0;
	int total_electricity_cost = 0;
	int total_people_system = 0;

	public:
	
	Simulator(char, char, float, float, float, float, bool);
	
	int getState();

	inline int getShift(char);
	
	inline float getCost()
	{
		return (total_electricity_cost+(total_wait_cost*2));
	}

	void updateWithAction(const char []);

	void display();
	
};

#endif