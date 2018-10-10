#pragma once
#include <vector>
#include <iostream>
#include <utility>
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
	bool RichiDekiru = false;		//能否立直

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
	int WantToRichi = 0;

	/*
	重置能否鳴牌和是否想要鳴牌的狀態
	*/
	void ResetActState();

	int PonDekiruPai = -1;
	/*
			(牌 , 明 / 加)
				, 0  / 1
	*/
	std::vector<std::pair<int, int>> KanDekiruList;
	int KanCase = -1;
	/*
				(	(	可以吃的牌	)	,	吃的方式	)
	*/
	std::vector<std::pair<std::pair<int, int>, int>> ChiDekiruList;
	int ChiCase = -1;							// index of ChiDekiruList

	int *Suteru;
	int *NakuState;
	bool *Agari;

	std::vector<int> *tehai;

	//	打牌延遲
	bool WaitForDaPai = true;
	int DaPaiWaitingTime = 0;
	int dt = 0;
	int elapsed_time = 0;
	int last_clock = 0;
	int current_clock = 0;

};

