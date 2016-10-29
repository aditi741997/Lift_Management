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
	int start_floor;
	int destination;
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

	const short int Still = 0;
	const short int Up = 1;
	const short int Down = 2;
	const short int Open_Up = 3;
	const short int Open_Down = 4;

	int no_lifts, no_floors;
	double p,q,r,t_u;

	std::vector< short int > lift_pos;
	std::vector< std::pair<bool, bool> > buttons_on_floor;
	std::vector< short int > buttons_on_lift;
	std::vector< std::unordered_multiset< Person, Person_Hash > > people_in_lift;
	std::vector< std::unordered_multiset< Person, Person_Hash > > people_in_floor;

	int total_wait_cost = 0;
	int total_electricity_cost = 0;
	int total_people_system = 0;

	public:
	
	Simulator(int, int, double, double, double, double);
	
	int getState();
	
	inline int getCost()
	{
		return (total_electricity_cost+(total_wait_cost*2));
	}

	void updateWithAction(const int []);
	

	void display()
	{
		std::cerr << "Position of elevators: " << "1:" << lift_pos[0] << " 2:" << lift_pos[1] << std::endl;
	}
};

#endif