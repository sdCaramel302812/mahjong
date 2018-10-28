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

	std::vector<std::vector<int>> SpecialPeiPai();

	int MoPai();
	int MoRinshan();
	void Kan();
	
	std::vector<int> PaiSan;

	/*
	嶺上牌 : 0 1 2 3
	指示牌 : 4 6 8 10 12
			 5 7 9 11 13
	海底牌 : 14 (每一槓加一)
	*/
	int Rinshanhai = 0;
	int Hyoujihai1 = 4;
	int Hyoujihai2 = 6;
	int Hyoujihai3 = 8;
	int Hyoujihai4 = 10;
	int Hyoujihai5 = 12;
	int UraHyoujihai1 = 5;
	int UraHyoujihai2 = 7;
	int UraHyoujihai3 = 9;
	int UraHyoujihai4 = 11;
	int UraHyoujihai5 = 13;
	int Haiteihai = 14;

};

