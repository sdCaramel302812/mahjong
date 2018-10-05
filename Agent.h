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

	bool NakuDekiru = false;		//��_��P
	bool PonDekiru = false;			//��_�I�P
	bool KanDekiru = false;			//��_�b�P
	bool ChiDekiru = false;			//��_�Y�P
	bool RonDekiru = false;			//��_�M�P
	bool TsumoDekiru = false;		//��_�ۺN�M�P
	bool AnKanDekiru = false;		//��_�t�b / �[�b

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

	int PonDekiruPai = -1;
	std::vector<int> KanDekiruList;
	std::vector<int> ChiDekiruList;

	int *Suteru;
	int *NakuState;
	bool *Agari;

	std::vector<int> *tehai;

};

