#pragma once

class Agent
{
public:
	Agent(int *s, int *n);
	~Agent();

	void Act();

	bool NakuDekiru = false;
	bool PonDekiru = false;
	bool KanDekiru = false;
	bool ChiDekiru = false;
	bool RonDekiru = false;

	bool WaitForKiru = false;

	int *Suteru;
	int *NakuState;

};

