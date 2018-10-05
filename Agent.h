#pragma once
#include <vector>
#include <iostream>
using std::cout;
using std::endl;


class Agent
{
public:
	Agent(int *s, int *n, std::vector<int> *t);
	~Agent();


	void Init();
	void Act();

	bool NakuDekiru = false;		//能否鳴牌
	bool PonDekiru = false;			//能否碰牌
	bool KanDekiru = false;			//能否槓牌
	bool ChiDekiru = false;			//能否吃牌
	bool RonDekiru = false;			//能否和牌
	bool TsumoDekiru = false;		//能否自摸和牌
	bool AnKanDekiru = false;		//能否暗槓 / 加槓

	bool WaitForKiru = false;
	bool IsAI = true;

	/*
	return
	0			未決定
	-1			不要
	1			要
	*/
	int WantToPon = 0;
	int WantToChi = 0;
	int WantToKan = 0;
	int WantToRon = 0;
	int WantToTsumo = 0;

	int PonDekiruPai = -1;
	std::vector<int> KanDekiruList;
	std::vector<int> ChiDekiruList;

	int *Suteru;
	int *NakuState;
	bool *Agari;

	std::vector<int> *tehai;

};

