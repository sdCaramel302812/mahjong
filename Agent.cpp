#include "stdafx.h"
#include "Agent.h"


Agent::Agent(int *s, int *n, std::vector<int> *t)
{
	Suteru = s;
	NakuState = n;
	tehai = t;
}


Agent::~Agent()
{
}

void Agent::Act()
{
	if (IsAI) {
		if (WaitForKiru) {
			*Suteru = tehai->at(0);
		}
	}
}
