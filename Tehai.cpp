#include "stdafx.h"
#include "Tehai.h"
#include <iostream>


Tehai::Tehai()
{
	tehai.resize(13);
}


Tehai::~Tehai()
{
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
}

void Tehai::Peipai(std::vector<int> pai)
{
	tehai = pai;
	std::sort(tehai.begin(), tehai.end());
}

void Tehai::Chi(int p1, int p2, int p3)
{
	bool first = false;
	bool second = false;
	for (std::vector<int>::iterator i = agarihai.begin(); i != agarihai.end(); ++i) {
		if (*i == p2) {
			first = true;
		}
		if (*i == p3) {
			second = true;
		}
	}
	if (!first || !second) {
		return;
	}

	for (std::vector<int>::iterator i = tehai.begin(); i != tehai.end(); ++i) {
		if (*i == p2) {
			tehai.erase(i);
			break;
		}
	}
	for (std::vector<int>::iterator i = tehai.begin(); i != tehai.end(); ++i) {
		if (*i == p3) {
			tehai.erase(i);
			break;
		}
	}
	for (std::vector<int>::iterator i = agarihai.begin(); i != agarihai.end(); ++i) {
		if (*i == p2) {
			agarihai.erase(i);
			break;
		}
	}
	for (std::vector<int>::iterator i = agarihai.begin(); i != agarihai.end(); ++i) {
		if (*i == p3) {
			agarihai.erase(i);
			break;
		}
	}

	std::vector<int> chipai;
	chipai.push_back(p1);
	chipai.push_back(p2);
	chipai.push_back(p3);
	chi.push_back(chipai);
	return;
}

void Tehai::Pon(int pai, int from)
{
	bool first = false;
	bool second = false;
	for (std::vector<int>::iterator i = agarihai.begin(); i != agarihai.end(); ++i) {
		if (*i == pai) {
			if (!first) {
				first = true;
				continue;
			}
			else {
				second = true;
				break;
			}
		}
	}
	if (!first || !second) {
		return;
	}

	for (int j = 0; j < 2; ++j) {
		for (std::vector<int>::iterator i = tehai.begin(); i != tehai.end(); ++i) {
			if (*i == pai) {
				tehai.erase(i);
				break;
			}
		}
		for (std::vector<int>::iterator i = agarihai.begin(); i != agarihai.end(); ++i) {
			if (*i == pai) {
				agarihai.erase(i);
				break;
			}
		}
	}

	std::vector<int> ponpai;
	ponpai.push_back(pai);
	ponpai.push_back(from);
	pon.push_back(ponpai);
	return;
}

void Tehai::Daiminkan(int pai, int from)
{
	bool first = false;
	bool second = false;
	bool third = false;
	for (std::vector<int>::iterator i = agarihai.begin(); i != agarihai.end(); ++i) {
		if (*i == pai) {
			if (!first) {
				first = true;
				continue;
			}
			else if(!second){
				second = true;
				continue;
			}
			else {
				third = true;
				break;
			}
		}
	}
	if (!first || !second || !third) {
		return;
	}

	for (int j = 0; j < 3; ++j) {
		for (std::vector<int>::iterator i = tehai.begin(); i != tehai.end(); ++i) {
			if (*i == pai) {
				tehai.erase(i);
				break;
			}
		}
		for (std::vector<int>::iterator i = agarihai.begin(); i != agarihai.end(); ++i) {
			if (*i == pai) {
				agarihai.erase(i);
				break;
			}
		}
	}

	std::vector<int> kanpai;
	kanpai.push_back(pai);
	kanpai.push_back(from);
	minkan.push_back(kanpai);
	return;
}

void Tehai::Kakan(int pai)
{
	for (std::vector<std::vector<int>>::iterator i = pon.begin(); i != pon.end(); ++i) {
		if (i->at(0) == pai) {
			std::vector<int> kanpai;
			kanpai.push_back(pai);
			kanpai.push_back(i->at(1));
			minkan.push_back(kanpai);
			pon.erase(i);
			for (std::vector<int>::iterator i = tehai.begin(); i != tehai.end(); ++i) {
				if (*i == pai) {
					tehai.erase(i);
					break;
				}
			}
			for (std::vector<int>::iterator i = agarihai.begin(); i != agarihai.end(); ++i) {
				if (*i == pai) {
					agarihai.erase(i);
					break;
				}
			}
			break;
		}
	}
}

void Tehai::Ankan(int pai)
{
	bool first = false;
	bool second = false;
	bool third = false;
	bool forth = false;
	for (std::vector<int>::iterator i = agarihai.begin(); i != agarihai.end(); ++i) {
		if (*i == pai) {
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
		return;
	}

	for (int j = 0; j < 4; ++j) {
		for (std::vector<int>::iterator i = tehai.begin(); i != tehai.end(); ++i) {
			if (*i == pai) {
				tehai.erase(i);
				break;
			}
		}
		for (std::vector<int>::iterator i = agarihai.begin(); i != agarihai.end(); ++i) {
			if (*i == pai) {
				agarihai.erase(i);
				break;
			}
		}
	}

	ankan.push_back(pai);
	return;
}

void Tehai::Tsumo(int pai)
{
	tsumohai = pai;
	agarihai = tehai;
	agarihai.push_back(tsumohai);
	//std::sort(agarihai.begin(), agarihai.end());
}

/*
return 0		¥¢±Ñ
return 1		¤â¤Á
return 2		¦ÛºN¤Á
*/
int Tehai::Kiru(int pai)
{
	if (pai == tsumohai) {
		tsumohai = -1;
		return 2;
	}
	for (std::vector<int>::iterator i = tehai.begin(); i != tehai.end(); ++i) {
		if (*i == pai) {
			tehai.erase(i);
			if (tehai.size() % 3 == 0) {
				tehai.push_back(tsumohai);
			}
			std::sort(tehai.begin(), tehai.end());
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
