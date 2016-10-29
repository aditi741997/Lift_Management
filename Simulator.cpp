#include "Simulator.h"

Simulator::Simulator(int lifts, int floors, double p_p, double p_q, double p_r, double t_t_u)
{
	srand(time(NULL));

	no_floors = floors;
	no_lifts = lifts;
	p = p_p;
	q = p_q;
	r = p_r;
	t_u = t_t_u;

	for(int i=0; i<lifts; i++)
		lift_pos.push_back(0);

	for(int i=0; i<floors; i++)
		buttons_on_floor.push_back(std::make_pair(false, false));

	for(int i=0; i<lifts; i++)
		buttons_on_lift.push_back(0);

	for(int i=0; i<lifts; i++)
	{
		std::unordered_multiset< Person, Person_Hash > people_one_lift;
		people_in_lift.push_back(people_one_lift);
	}

	for(int i=0; i<floors; i++)
	{
		std::unordered_multiset< Person, Person_Hash > people_one_floor;
		people_in_floor.push_back(people_one_floor);
	}
}

int Simulator::getState()
{
	int state_integer = 0;

	state_integer += lift_pos[1];
	state_integer += (lift_pos[0] << 3);	

	int sz = no_floors;

	state_integer += (int)(buttons_on_floor[sz].second) << 6;

	int j = 0;
	for(int i = sz-2; i>= 1; j++, i--)
		state_integer += ( ( ((int)(buttons_on_floor[i].first) << 1) + (int)(buttons_on_floor[i].second) ) << (7+2*j) ); 
	
	state_integer += ((int)(buttons_on_floor[0].first) << (7+2*j)) ;

	state_integer += (buttons_on_lift[1] << (8+2*j));
	state_integer += (buttons_on_lift[0] << (13+2*j));

	return state_integer;
}


void Simulator::updateWithAction(const int action[])
{
	total_wait_cost += total_people_system;
	for(int i=0; i<2; i++)
	{
		switch(action[i])
		{
			case 0:
				break;
			case 1:
				lift_pos[i] ++;
				total_electricity_cost ++;
				break;
			case 2:
				lift_pos[i] --;
				total_electricity_cost ++;
				break;
			case 3:
				buttons_on_floor[ lift_pos[i] ].first = false;
				for(auto it = people_in_floor[ lift_pos[i] ].begin(); it != people_in_floor[ lift_pos[i] ].end(); )
					if(it->direction == true)
					{
						people_in_lift[i].insert(it->copyP());
						buttons_on_lift[i] |= (1 << it->copyP().destination);
						it = people_in_floor[ lift_pos[i] ].erase(it);
					}
					else
						it++;
				for(auto it = people_in_lift[i].begin(); it!= people_in_lift[i].end(); )
					if(it->destination == lift_pos[i])
					{
						it = people_in_lift[i].erase(it);
						total_people_system --;
						buttons_on_lift[i] &= !(1 << lift_pos[i]);
					}
					else
						it++;
				break;
			case 4:
				buttons_on_floor[ lift_pos[i] ].second = false;
				for(auto it = people_in_floor[ lift_pos[i] ].begin(); it != people_in_floor[ lift_pos[i] ].end(); )
					if(it->direction == false)
					{
						people_in_lift[i].insert(it->copyP());
						buttons_on_lift[i] |= (1 << it->copyP().destination);
						it = people_in_floor[ lift_pos[i] ].erase(it);
					}
					else
						it++;
				for(auto it = people_in_lift[i].begin(); it!= people_in_lift[i].end(); )
					if(it->destination == lift_pos[i])
					{
						it = people_in_lift[i].erase(it);
						total_people_system --;
						buttons_on_lift[i] &= !(1 << lift_pos[i]);
					}
					else
						it++;
				break;
		}
	}

	double P_obs = (double)rand()/RAND_MAX;

	if(P_obs < p)
	{
		Person newPerson;

		double Q_obs = (double)rand()/RAND_MAX;

		if(Q_obs < q)
			newPerson.start_floor = 0;
		else
		{
			newPerson.start_floor = 1.0+((Q_obs-q)/(1-q))*(no_floors-1);
			if(Q_obs == 1)
				newPerson.start_floor = no_floors-1;
		}

		if(newPerson.start_floor == 0)
		{
			double R_obs = (double)rand()/RAND_MAX;
			newPerson.destination = 1+(int)(R_obs*(no_floors-1));
			if(R_obs == 1)
				newPerson.destination --;
		}
		else
		{
			double R_obs = (double)rand()/RAND_MAX;
			if(R_obs < r)
				newPerson.destination = 0;
			else
			{
				R_obs = (double)rand()/RAND_MAX;
				newPerson.destination = (int)(R_obs*(no_floors-1));
				if(R_obs == 1)
					newPerson.destination --;
				if(newPerson.destination >= newPerson.start_floor)
					newPerson.destination ++;
			}
		}

		if(newPerson.destination > newPerson.start_floor)
			newPerson.direction = true;
		else
			newPerson.direction = false;

		if(newPerson.direction == true)
			buttons_on_floor[newPerson.start_floor].first = true;
		else 
			buttons_on_floor[newPerson.start_floor].second = true;

		people_in_floor[newPerson.start_floor].insert(newPerson);
		total_people_system ++;
	}
}

void Simulator::display()
	{
		std::cerr << "\nEpisode X ===========================================================\n";

		std::cerr << "Position of elevators: " << "1:" << lift_pos[0] << " 2:" << lift_pos[1] << std::endl;

		std::cerr << "Buttons on each floor: ";

		for(auto it = buttons_on_floor.begin(); it!=buttons_on_floor.end(); it++)
		{
			std::cerr <<"("<< it->first<<":"<<it->second<<")";
		}

		std::cerr << "\n";

		std::cerr << "Buttons on each lift: ";

		for(auto it = buttons_on_lift.begin(); it!=buttons_on_lift.end(); it++)
		{
			std::cerr <<"("<< *it << ")";
		}

		for(int i=0; i<2; i++)
		{
			std::cerr << "\n";

			std::cerr << "People in lift "<<i+1<<": ";

			for(auto it = people_in_lift[i].begin(); it!=people_in_lift[i].end(); it++)
			{
				std::cerr <<"("<< it->start_floor<<":"<<it->destination<<":"<<it->direction<<")";
			}
		}

		for(int i=0; i<5; i++)
		{
			std::cerr << "\n";
			std::cerr << "People in floor "<<i<<": ";

			for(auto it = people_in_floor[i].begin(); it!=people_in_floor[i].end(); it++)
			{
				std::cerr <<"("<< it->start_floor<<":"<<it->destination<<":"<<it->direction<<")";
			}
		}
	}

int main()
{
	Simulator sim(2, 5, 0.3, 0.4, 0.3, 1);

	int arr[] = {0,0};

	for(int i=0; i<100; i++)
	{
		sim.getState();
		std::cerr << "\nenter action:\n";
		std::cin >> arr[0] >> arr[1];
		sim.updateWithAction(arr);
		sim.display();
	}

	return 0;
}