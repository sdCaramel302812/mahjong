#pragma once
#include "Yama.h"
#include "rule.h"
#include "GM.h"
#include "Player.h"
#include "tenpai.h"
#include "Debug.h"

class RoomInfo {
public:
	int Chanfon = TON;			//����
	int Kyouku = 0;				//����
	int Honba = 0;				//������
	int Kyoutaku = 0;			//�ѰU
	int Oya = 1;				//���a
	bool UpdateScene = true;	//�O�_��s�e��
	int RemainPai = 70;			//�Ѿl�P��
	int FirstOya = 0;
	int CurrentPlayer = 1;
};

class Room
{
public:
	Room();
	~Room();

	void Init();
	void Play();			//game loop

	Yama *yama;				//�P�s
	Rule *rule;				//�ж��W�h

	RoomInfo info;

			
			
	bool kyoukuover = true;
	bool gameover = false;
	int round = 1;			//����

	bool WhoIsAgari[4] = { false };

	void NextKyouku();
	bool NakuCheck(int pai);
	void NextPlayer();

	//vvvvv		��Ӧ��G�S�Ψ�
	bool WaitForKiru = false;
	bool WaitForNaku = false;
	//^^^^^		��Ӧ��G�S�Ψ�

	

	/*
	0 : wait for kiru
	1 : wait for naku
	2 : wait for tsumo
	3 : wait for next kyouku
	*/
	int WaitingState = 0;
	bool MoRinShan = false;


	int Sutehai = -1;			//	��e�˵P


	Player *pl1;
	Player *pl2;
	Player *pl3;
	Player *pl4;

	void ResetNakuState();		//	���m�U�a����P���A

	int dt = 0;
	int elapse_time = 0;
	int last_clock = 0;
	int current_clock = 0;
	int elapse_time_for_pfs = 0;
	int fps = 0;

	//	�N�P����
	bool WaitForMoPai = true;		
	int MoPaiWaitingTime = 0;
	//	�N�P����

	//	���⩵��
	bool WaitForResult = true;
	int ResultWaitingTime = 10000;
	//	���⩵��
};

