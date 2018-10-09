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

	std::vector<int>				tehai;		//��P
	int								tsumohai = -1;	//�ۺN�P
	int								ronhai = -1;//�a�M�P
	std::vector<int>				agarihai;	//�M�P
	std::vector<std::vector<int>>	chi;
	/*
	4p	5p	6p		�Y�|��
	2m	1m	3m		�Y�G�U
	*/
	std::vector<std::vector<int>>	pon;
	std::vector<std::vector<int>>	minkan;
	/*
	6m 6m 6m 0			�ӦۤU�a
	9s 9s 9s 1			�Ӧ۹�a
	1p 1p 1p 2			�ӦۤW�a
	*/
	std::vector<int>				ankan;
	bool							richi;

	void Init();

	void Peipai(int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8, int p9, int p10, int p11, int p12, int p13);
	void Peipai(int *pai);
	void Peipai(std::vector<int> pai);
	/*
	p1 ���ӦۤW�a���P
	*/
	bool Chi(int p1, int p2, int p3);
	/*
	from :
	0 : �ӦۤU�a
	1 : �Ӧ۹�a
	2 : �ӦۤW�a
	*/
	bool Pon(int pai, int from);
	/*
	from :
	0 : �ӦۤU�a
	1 : �Ӧ۹�a
	2 : �ӦۤW�a
	*/
	bool Daiminkan(int pai, int from);
	bool Kakan(int pai);
	bool Ankan(int pai);
	void Tsumo(int pai);
	int Kiru(int pai);
	void Ron(int pai);

	void ShowTehai();
};

