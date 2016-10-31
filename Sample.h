#ifndef SAMPLE_H
#define SAMPLE_H

#include "Header.h"

class Sampling
{
private:
	list<pair<int,char> > State_Action;
	float c;
	inline float getAlpha(int&,int&);
	inline float newQ(float&,int&);
	inline void findUVal(char&,int&,float&,int&);

public:
	Sampling();
	void chooseAction(char&,int&); // take state from Sim, give action, add to list.
	void updateVals(float&,int&);
};

void runSimulation(int&,Sampling&);

#endif