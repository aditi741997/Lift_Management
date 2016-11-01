#include "Simulator.h"

Simulator::Simulator(char lifts, char floors, float p_p, float p_q, float p_r, float t_t_u, bool x)
{
	srand(time(NULL));

	no_floors = floors;
	no_lifts = lifts;
	p = p_p;
	q = p_q;
	r = p_r;
	t_u = t_t_u;
	is_real_life = x;

	for(char i=0; i<lifts; i++)
		lift_pos.push_back(0);

	for(char i=0; i<floors; i++)
		buttons_on_floor.push_back(std::make_pair(false, false));

	for(char i=0; i<lifts; i++)
		buttons_on_lift.push_back(0);

	for(char i=0; i<lifts; i++)
	{
		std::unordered_multiset< Person, Person_Hash > people_one_lift;
		people_in_lift.push_back(people_one_lift);
	}

	for(char i=0; i<floors; i++)
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

	char sz = no_floors;

	state_integer += (int)(buttons_on_floor[sz].second) << 6;

	int j = 0;
	for(char i = sz-2; i>= 1; j++, i--)
		state_integer += ( ( ((int)(buttons_on_floor[i].first) << 1) + (int)(buttons_on_floor[i].second) ) << (7+2*j) ); 
	
	state_integer += ((int)(buttons_on_floor[0].first) << (7+2*j)) ;

	state_integer += (buttons_on_lift[1] << (8+2*j));
	state_integer += (buttons_on_lift[0] << (13+2*j));

	return state_integer;
}


void Simulator::updateWithAction(const char action[])
{
	total_wait_cost += total_people_system;
	for(char i=0; i<no_lifts; i++)
	{
		// std::cerr << (int)(action[i]) << std::endl;
		switch((int)(action[i]))
		{
			case 1:
				lift_pos[i] += 1;
				// std::cout << "Act 1 New posn of ith lift :" << lift_pos[i] << std::endl;
				total_electricity_cost ++;
				break;
			case 2:
				lift_pos[i] -= 1;
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
			case 0:
				buttons_on_floor[ lift_pos[i] ].second = false;
				for(auto it = people_in_floor[ lift_pos[i] ].begin(); it != people_in_floor[ lift_pos[i] ].end(); )
				{
					// cout << 				
					if(it->direction == false)
					{
						people_in_lift[i].insert(it->copyP());
						buttons_on_lift[i] |= (1 << it->copyP().destination);
						it = people_in_floor[ lift_pos[i] ].erase(it);
					}
					else
						it++;
				}
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
			default:
				break;
		}
	}

	if (!is_real_life)
	{
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

			// if(newPerson.destination > newPerson.start_floor)
			// 	newPerson.direction = true;
			// else
			// 	newPerson.direction = false;
			newPerson.direction = (newPerson.destination > newPerson.start_floor);

			if(newPerson.direction == true)
				buttons_on_floor[newPerson.start_floor].first = true;
			else 
				buttons_on_floor[newPerson.start_floor].second = true;

			people_in_floor[newPerson.start_floor].insert(newPerson);
			total_people_system ++;
		}		
	}

}

void Simulator::display()
	{
		std::cerr << "\nEpisode X ===========================================================\n";

		std::cerr << "Position of elevators: " << "1:" << (int)(lift_pos[0]) << " 2:" << (int)(lift_pos[1]) << std::endl;

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

		for(char i=0; i<no_lifts; i++)
		{
			std::cerr << "\n";

			std::cerr << "People in lift "<<i+1<<": ";

			for(auto it = people_in_lift[i].begin(); it!=people_in_lift[i].end(); it++)
			{
				std::cerr <<"("<< (int)(it->start_floor)<<":"<<(int)(it->destination)<<":"<<it->direction<<")";
			}
		}

		for(char i=0; i<no_floors; i++)
		{
			std::cerr << "\n";
			std::cerr << "People in floor "<<i<<": ";

			for(auto it = people_in_floor[i].begin(); it!=people_in_floor[i].end(); it++)
			{
				std::cerr <<"("<< (int)(it->start_floor)<<":"<<(int)(it->destination)<<":"<<it->direction<<")";
			}
		}
	}

// int main()
// {
// 	Simulator sim(2, 5, 0.3, 0.4, 0.3, 1);

// 	char arr[] = {0,0};

// 	for(char i=0; i<100; i++)
// 	{
// 		std::cerr << sim.getState();
// 		// std::cerr << "\nenter action:\n";
// 		std::cin >> arr[0] >> arr[1];
// 		arr[0] -= '0';
// 		arr[1] -= '0';
// 		sim.updateWithAction(arr);
// 		sim.display();
// 	}

// 	return 0;
// }