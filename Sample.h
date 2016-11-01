#ifndef SAMPLE_H
#define SAMPLE_H

#include "Header.h"

class Sampling
{
private:
	list<pair<int,char> > State_Action;
	list<long> Ns;
	// float c;
	inline float getAlpha(int&,int&,long&);
	inline float newQ(float&,int&);
	inline void findUVal(char&,int&,float&,long&,float&);

public:
	Sampling();
	void chooseAction(char&,int&); // take state from Sim, give action, add to list.
	void updateVals(float&,int&);
	void clear();
};

void runSimulation(int&,Sampling&);

#endif