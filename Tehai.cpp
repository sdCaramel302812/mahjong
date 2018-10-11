#include "stdafx.h"
#include "Tehai.h"
#include <iostream>


Tehai::Tehai()
{
	tehai.resize(13);
	agarihai.resize(13);
}


Tehai::~Tehai()
{
}

void Tehai::Init()
{
	chi.clear();
	pon.clear();
	minkan.clear();
	ankan.clear();
	tsumohai = -1;
	ronhai = -1;
	tehai.resize(13);
	richi = false;
}

void Tehai::Peipai(int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8, int p9, int p10, int p11, int p12, int p13)
{
	tehai.at(0) = p1;
	tehai.at(1) = p2;
	tehai.at(2) = p3;
	tehai.at(3) = p4;
	tehai.at(4) = p5;
	tehai.at(5) = p6;
	tehai.at(6) = p7;
	tehai.at(7) = p8;
	tehai.at(8) = p9;
	tehai.at(9) = p10;
	tehai.at(10) = p11;
	tehai.at(11) = p12;
	tehai.at(12) = p13;
	std::sort(tehai.begin(), tehai.end());
	agarihai = tehai;
}

void Tehai::Peipai(int * pai)
{
	tehai.at(0) = pai[0];
	tehai.at(1) = pai[1];
	tehai.at(2) = pai[2];
	tehai.at(3) = pai[3];
	tehai.at(4) = pai[4];
	tehai.at(5) = pai[5];
	tehai.at(6) = pai[6];
	tehai.at(7) = pai[7];
	tehai.at(8) = pai[8];
	tehai.at(9) = pai[9];
	tehai.at(10) = pai[10];
	tehai.at(11) = pai[11];
	tehai.at(12) = pai[12];
	std::sort(tehai.begin(), tehai.end());
	agarihai = tehai;
}

void Tehai::Peipai(std::vector<int> pai)
{
	tehai = pai;
	std::sort(tehai.begin(), tehai.end());
	agarihai = tehai;
}

bool Tehai::Chi(int p1, int p2, int p3)
{
	bool first = false;
	bool second = false;
	bool p2red = false;
	bool p3red = false;
	//////////////////////////////////////////////////////////
	//						未處理赤牌						//
	//////////////////////////////////////////////////////////
	for (std::vector<int>::iterator i = agarihai.begin(); i != agarihai.end(); ++i) {
		if (*i != 0 && *i != 10 && *i != 20) {
			if (*i == p2) {
				first = true;
			}
			if (*i == p3) {
				second = true;
			}
		}
		else {
			if (*i + 5 == p2) {
				first = true;
				p2red = true;
			}
			if (*i + 5 == p3) {
				second = true;
				p3red = true;
			}
		}
	}
	if (!first || !second) {
		return false;
	}

	for (std::vector<int>::iterator i = tehai.begin(); i != tehai.end(); ++i) {
		if (*i != 0 && *i != 10 && *i != 20) {
			if (*i == p2) {
				tehai.erase(i);
				break;
			}
		}
		else {
			if (*i + 5 == p2) {
				tehai.erase(i);
				break;
			}
		}
	}
	for (std::vector<int>::iterator i = tehai.begin(); i != tehai.end(); ++i) {
		if (*i != 0 && *i != 10 && *i != 20) {
			if (*i == p3) {
				tehai.erase(i);
				break;
			}
		}
		else {
			if (*i + 5 == p3) {
				tehai.erase(i);
				break;
			}
		}
	}
	agarihai = tehai;

	std::vector<int> chipai;
	chipai.push_back(p1);
	if (!p2red) {
		chipai.push_back(p2);
	}
	else {
		chipai.push_back(p2 - 5);
	}
	if (!p3red) {
		chipai.push_back(p3);
	}
	else {
		chipai.push_back(p3 - 5);
	}
	chi.push_back(chipai);
	return true;
}

bool Tehai::Pon(int pai, int from)
{
	bool first = false;
	bool second = false;

	int PaiNoR = pai;
	if (PaiNoR == 0 || PaiNoR == 10 || PaiNoR == 20) {
		PaiNoR += 5;
	}
	int pai1;
	int pai2;
	
	for (std::vector<int>::iterator i = tehai.begin(); i != tehai.end(); ++i) {
		if (*i != 0 && *i != 10 && *i != 20) {
			if (*i == PaiNoR) {
				if (!first) {
					first = true;
					pai1 = *i;
					continue;
				}
				else {
					second = true;
					pai2 = *i;
					break;
				}
			}
		}
		else {
			if (*i == PaiNoR - 5) {
				if (!first) {
					first = true;
					pai1 = *i;
					continue;
				}
				else {
					second = true;
					pai2 = *i;
					break;
				}
			}
		}
	}
	if (!first || !second) {
		return false;
	}

	for (int j = 0; j < 2; ++j) {
		for (std::vector<int>::iterator i = tehai.begin(); i != tehai.end(); ++i) {
			if (*i == pai1 || *i == pai2) {
				tehai.erase(i);
				break;
			}
		}
	}
	agarihai = tehai;

	std::vector<int> ponpai;
	ponpai.push_back(pai);
	ponpai.push_back(pai1);
	ponpai.push_back(pai2);
	ponpai.push_back(from);
	pon.push_back(ponpai);
	return true;
}

bool Tehai::Daiminkan(int pai, int from)
{
	bool first = false;
	bool second = false;
	bool third = false;
	int PaiNoR = pai;
	if (PaiNoR == 0 || PaiNoR == 10 || PaiNoR == 20) {
		PaiNoR += 5;
	}
	for (std::vector<int>::iterator i = tehai.begin(); i != tehai.end(); ++i) {
		if (*i != 0 && *i != 10 && *i != 20) {
			if (*i == PaiNoR) {
				if (!first) {
					first = true;
					continue;
				}
				else if (!second) {
					second = true;
					continue;
				}
				else {
					third = true;
					break;
				}
			}
		}
		else {
			if (*i == PaiNoR - 5) {
				if (!first) {
					first = true;
					continue;
				}
				else if (!second) {
					second = true;
					continue;
				}
				else {
					third = true;
					break;
				}
			}

		}
	}
	if (!first || !second || !third) {
		return false;
	}
	
	for (int j = 0; j < 3; ++j) {
		for (std::vector<int>::iterator i = tehai.begin(); i != tehai.end(); ++i) {
			if (*i == pai) {
				tehai.erase(i);
				break;
			}
		}
	}
	agarihai = tehai;

	std::vector<int> kanpai;
	kanpai.push_back(pai);
	kanpai.push_back(from);
	minkan.push_back(kanpai);
	return true;
}

bool Tehai::Kakan(int pai)
{
	for (std::vector<std::vector<int>>::iterator i = pon.begin(); i != pon.end(); ++i) {
		if ((i->at(0) != 0 && i->at(0) != 10 && i->at(0) != 20) && i->at(0) == pai) {
			std::vector<int> kanpai;
			kanpai.push_back(pai);
			kanpai.push_back(i->at(1));
			minkan.push_back(kanpai);
			pon.erase(i);
			for (std::vector<int>::iterator j = tehai.begin(); j != tehai.end(); ++j) {
				if ((*j != 0 && *j != 10 && *j != 20) && *j == pai) {
					tehai.erase(j);
					break;
				}
				else if ((*j == 0 || *j != 10 || *j == 20) && *j == pai - 5) {
					tehai.erase(j);
					break;
				}
			}
			agarihai = tehai;
			break;
			return true;
		}	
		if ((i->at(0) == 0 && i->at(0) == 10 && i->at(0) == 20) && i->at(0) == pai - 5) {
			std::vector<int> kanpai;
			kanpai.push_back(pai);
			kanpai.push_back(i->at(1));
			minkan.push_back(kanpai);
			pon.erase(i);
			for (std::vector<int>::iterator j = tehai.begin(); j != tehai.end(); ++j) {
				if ((*j != 0 && *j != 10 && *j != 20) && *j == pai) {
					tehai.erase(j);
					break;
				}
				else if ((*j == 0 || *j == 10 || *j == 20) && *j == pai) {
					tehai.erase(j);
					break;
				}
			}
			agarihai = tehai;
			break;
			return true;
		}
	}
	return false;
}

bool Tehai::Ankan(int pai)
{
	bool first = false;
	bool second = false;
	bool third = false;
	bool forth = false;
	for (std::vector<int>::iterator i = agarihai.begin(); i != agarihai.end(); ++i) {
		if ((*i != 0 && *i != 10 && *i != 20 && *i == pai) || ((*i == 0 || *i == 10 || *i == 20) && *i == pai - 5)) {
			if (!first) {
				first = true;
				continue;
			}
			else if (!second) {
				second = true;
				continue;
			}
			else if(!third){
				third = true;
				continue;
			}
			else {
				forth = true;
				break;
			}
		}
	}
	if (!first || !second || !third || !forth) {
		return false;
	}

	for (int j = 0; j < 4; ++j) {
		for (std::vector<int>::iterator i = tehai.begin(); i != tehai.end(); ++i) {
			if ((*i != 0 && *i != 10 && *i != 20 && *i == pai) || ((*i == 0 || *i == 10 || *i == 20) && *i == pai - 5)) {
				tehai.erase(i);
				break;
			}
		}
	}
	agarihai = tehai;

	ankan.push_back(pai);
	return true;
}

void Tehai::Tsumo(int pai)
{
	tsumohai = pai;
	agarihai = tehai;
	agarihai.push_back(tsumohai);
	std::sort(agarihai.begin(), agarihai.end());


	//cout << "fuck " << pai << endl;
	//ShowTehai();
}

/*
return 0		失敗
return 1		手切
return 2		自摸切
*/
int Tehai::Kiru(int pai)
{
	if (pai == tsumohai) {
		tsumohai = -1;
		agarihai = tehai;
		return 2;
	}
	for (std::vector<int>::iterator i = tehai.begin(); i != tehai.end(); ++i) {
		if (*i == pai) {
			tehai.erase(i);
			if (tehai.size() % 3 == 0) {
				tehai.push_back(tsumohai);
			}
			std::sort(tehai.begin(), tehai.end());
			agarihai = tehai;
			tsumohai = -1;
			return 1;
		}
	}

	return 0;
}

void Tehai::Ron(int pai)
{
}

void Tehai::ShowTehai()
{
	for (int i = 0; i < tehai.size(); ++i) {
		cout << tehai.at(i) << " ";
	}
	cout << "\t" << tsumohai << endl;
	for (int i = 0; i < chi.size(); ++i) {
		for (int j = 0; j < 3; ++j) {
			cout << chi.at(i).at(j) << " ";
		}
		cout << "\t";
	}
	for (int i = 0; i < pon.size(); ++i) {
		for (int j = 0; j < 3; ++j) {
			cout << pon.at(i).at(0) << " ";
		}
		cout << "\t";
	}
	for (int i = 0; i < minkan.size(); ++i) {
		for (int j = 0; j < 4; ++j) {
			cout << minkan.at(i).at(0) << " ";
		}
		cout << "\t";
	}
	for (int i = 0; i < ankan.size(); ++i) {
		for (int j = 0; j < 4; ++j) {
			cout << ankan.at(i) << " ";
		}
		cout << "\t";
	}
	if (richi) {
		cout << "richi";
	}
	cout << endl;
	cout << "==============================================\n";
}
