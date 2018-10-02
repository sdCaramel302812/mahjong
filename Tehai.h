#pragma once
#include <algorithm>
#include <vector>
#include <list>
#include "mj_def.h"
#include <iostream>
using std::cout;
using std::endl;

class Tehai
{
public:
	Tehai();
	~Tehai();

	std::vector<int>				tehai;		//手牌
	int								tsumohai = -1;	//自摸牌
	int								ronhai = -1;//榮和牌
	std::vector<int>				agarihai;	//和牌
	std::vector<std::vector<int>>	chi;
	/*
	4p	5p	6p		吃四餅
	2m	1m	3m		吃二萬
	*/
	std::vector<std::vector<int>>	pon;
	std::vector<std::vector<int>>	minkan;
	/*
	6m 6m 6m 0			來自下家
	9s 9s 9s 1			來自對家
	1p 1p 1p 2			來自上家
	*/
	std::vector<int>				ankan;
	bool							richi;

	void Peipai(int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8, int p9, int p10, int p11, int p12, int p13);
	void Peipai(int *pai);
	void Peipai(std::vector<int> pai);
	void Chi(int p1, int p2, int p3);
	void Pon(int pai, int from);
	void Daiminkan(int pai, int from);
	void Kakan(int pai);
	void Ankan(int pai);
	void Tsumo(int pai);
	int Kiru(int pai);
	void Ron(int pai);

	void ShowTehai();
};

