#pragma once
#include <utility>

class Rule {
public:
	bool Kuitan = true;
	bool Kuigae = false;
	bool Aka = true;
	bool Hako = true;
	bool Hanchan = true;		//���

	int Mochiten = 25000;		//�z�����y
	int Kaeshiten = 30000;		//���y
	std::pair<int, int> Uma;
};
