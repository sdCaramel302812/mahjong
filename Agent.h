#pragma once
#include <vector>

class Agent
{
public:
	Agent(int *s, int *n, std::vector<int> *t);
	~Agent();

	void Act();

	bool NakuDekiru = false;		//¯à§_»ïµP
	bool PonDekiru = false;			//¯à§_¸IµP
	bool KanDekiru = false;			//¯à§_ºbµP
	bool ChiDekiru = false;			//¯à§_¦YµP
	bool RonDekiru = false;			//¯à§_©MµP

	bool WaitForKiru = false;
	bool IsAI = true;

	int *Suteru;
	int *NakuState;

	std::vector<int> *tehai;

};

