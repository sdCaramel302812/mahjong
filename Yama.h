#pragma once
#include "rule.h"
#include <vector>
#include <ctime>
#include <cstdlib>

class Yama
{
public:
	Yama();
	~Yama();

	void Init(bool aka);
	std::vector<std::vector<int>> Peipai();

	int MoPai();
	int MoRinshan();
	void Kan();
	
	std::vector<int> PaiSan;

	/*
	���W�P : 0 1 2 3
	���ܵP : 4 6 8 10
			 5 7 9 11
	�����P : 12 (�C�@�b�[�@)
	*/
	int Rinshanhai = 0;
	int Shijihai1 = 4;
	int Shijihai2 = 6;
	int Shijihai3 = 8;
	int Shijihai4 = 10;
	int UraShijihai1 = 5;
	int UraShijihai2 = 7;
	int UraShijihai3 = 9;
	int UraShijihai4 = 11;
	int Haiteihai = 12;

};

