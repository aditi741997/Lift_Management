#ifndef SAMPLE_H
#define SAMPLE_H

#include "Header.h"

class Sampling
{
private:
	list<pair<int,char> > State_Action;
	// float c;
	inline float getAlpha(int&,int&,long&);
	inline float newQ(float&,int&);
	inline void findUVal(char&,int&,float&,long&,float&);
	inline float getGamma();

public:
	list<pair<long,float> > Ns_CostSoFar;
	list<int> Next_State;
	Sampling();
	long int chooseAction(char&,int&,float); // take state from Sim, give action, add to list.
	void updateVals(float&,int&);
	void clear();
};

void runSimulation(int&,Sampling&);

#endif