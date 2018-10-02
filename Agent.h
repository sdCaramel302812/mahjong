#pragma once
#include <vector>

class Agent
{
public:
	Agent(int *s, int *n, std::vector<int> *t);
	~Agent();

	void Act();

	bool NakuDekiru = false;		//��_��P
	bool PonDekiru = false;			//��_�I�P
	bool KanDekiru = false;			//��_�b�P
	bool ChiDekiru = false;			//��_�Y�P
	bool RonDekiru = false;			//��_�M�P

	bool WaitForKiru = false;
	bool IsAI = true;

	int *Suteru;
	int *NakuState;

	std::vector<int> *tehai;

};

