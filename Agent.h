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

	bool NakuDekiru = false;		//��_��P
	bool PonDekiru = false;			//��_�I�P
	bool KanDekiru = false;			//��_�b�P
	bool ChiDekiru = false;			//��_�Y�P
	bool RonDekiru = false;			//��_�M�P
	bool TsumoDekiru = false;		//��_�ۺN�M�P
	bool AnKanDekiru = false;		//��_�t�b / �[�b
	bool RichiDekiru = false;		//��_�ߪ�

	bool WaitForKiru = false;
	bool IsAI = true;

	/*
	return
	0			���M�w
	-1			���n
	1			�n
	*/
	int WantToPon = 0;
	int WantToChi = 0;
	int WantToKan = 0;
	int WantToRon = 0;
	int WantToTsumo = 0;
	int WantToRichi = 0;

	/*
	���m��_��P�M�O�_�Q�n��P�����A
	*/
	void ResetActState();

	int PonDekiruPai = -1;
	/*
			(�P , �� / �[)
				, 0  / 1
	*/
	std::vector<std::pair<int, int>> KanDekiruList;
	int KanCase = -1;
	/*
				(	(	�i�H�Y���P	)	,	�Y���覡	)
	*/
	std::vector<std::pair<std::pair<int, int>, int>> ChiDekiruList;
	int ChiCase = -1;							// index of ChiDekiruList

	int *Suteru;
	int *NakuState;
	bool *Agari;

	std::vector<int> *tehai;

	//	���P����
	bool WaitForDaPai = true;
	int DaPaiWaitingTime = 0;
	int dt = 0;
	int elapsed_time = 0;
	int last_clock = 0;
	int current_clock = 0;

};

