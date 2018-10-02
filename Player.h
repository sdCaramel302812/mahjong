﻿#pragma once
#include "Tehai.h"
#include "Agent.h"

class Player
{
public:
	Player();
	~Player();

	void IbatsuKesu();				//消一發
	void FirstRoundKesu();			//消首巡

	void Init();

	bool NakuDekiru(int pai);		//確認能否鳴牌

	//return 牌的編號	
	int Kiru();						//切牌				//***
	int Suteru = -1;
	void Tsumo(int pai);			//自摸				//***

	/*
	由外部更改
	-1 : 未決定
	 0 : 不鳴牌
	 1 : 碰牌
	 2 : 槓牌
	 3 : 吃，形式為 1 2 3
	 4 : 吃，形式為 2 1 3
	 5 : 吃，形式為 3 1 2
	*/
	int NakuState = -1;	
	/*
	return -1 : 未決定
	return  0 : 不鳴牌
	return  1 : 鳴牌
	*/
	int Naku();						//鳴牌				//***

	void Nakasareru();				//被鳴牌
	void Nagashu();					//流局

	Tehai *tehai;					//手牌
	std::vector<int> Sutehai;		//捨牌
	std::vector<int> SutehaiInOther;//被副露走的捨牌
	bool ibatsu = false;			//一發狀態
	bool firstR = true;				//首巡
	bool Furiten = false;			//振聽

	int Point;

	Agent *agent;
};
