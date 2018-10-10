#pragma once
#include "Yama.h"
#include "rule.h"
#include "GM.h"
#include "Player.h"
#include "tenpai.h"
#include "Debug.h"

class Room
{
public:
	Room();
	~Room();

	void Init();
	void Play();			//game loop

	Yama *yama;				//牌山
	Rule *rule;				//房間規則

	int Chanfon = TON;		//場風
	int Kyouku = 0;			//局數
	int Honba = 0;			//本場數
	int Kyoutaku = 0;		//供託
	int Oya = 1;			//莊家
	bool kyoukuover = true;
	bool gameover = false;
	int round = 1;			//巡數

	bool WhoIsAgari[4] = { false };

	void NextKyouku();
	bool NakuCheck(int pai);
	void NextPlayer();

	//vvvvv		後來似乎沒用到
	bool WaitForKiru = false;
	bool WaitForNaku = false;
	//^^^^^		後來似乎沒用到

	//			是否更新畫面
	bool UpdateScene = true;

	/*
	0 : wait for kiru
	1 : wait for naku
	2 : wait for tsumo
	3 : wait for next kyouku
	*/
	int WaitingState = 0;
	bool MoRinShan = false;


	int CurrentPlayer = 1;
	int Sutehai = -1;			//	當前捨牌


	Player *pl1;
	Player *pl2;
	Player *pl3;
	Player *pl4;

	void ResetNakuState();		//	重置各家的鳴牌狀態

	int dt = 0;
	int elapse_time = 0;
	int last_clock = 0;
	int current_clock = 0;
	int elapse_time_for_pfs = 0;
	int fps = 0;

	//	摸牌延遲
	bool WaitForMoPai = true;		
	int MoPaiWaitingTime = 0;
	//	摸牌延遲
};

