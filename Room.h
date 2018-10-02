#pragma once
#include "Yama.h"
#include "rule.h"
#include "GM.h"
#include "Player.h"

class Room
{
public:
	Room();
	~Room();

	void Init();
	void Play();			//game loop

	Yama *yama;
	Rule *rule;

	int Chanfon = TON;		//����
	int Kyuku = 1;			//����
	int Honba = 0;			//������
	int Kyoutaku = 0;		//�ѰU
	int Oya = 1;
	bool kyoukuover = true;
	bool gameover = false;

	void NextKyouku();
	bool NakuCheck(int pai);
	void NextPlayer();

	bool WaitForTsumo = true;
	bool WaitForKiru = false;
	bool WaitForNaku = false;

	/*
	0 : wait for kiru
	1 : wait for naku
	*/
	int WaitingState = 0;


	int CurrentPlayer = 1;
	int Sutehai = -1;

	Player *pl1;
	Player *pl2;
	Player *pl3;
	Player *pl4;
};

