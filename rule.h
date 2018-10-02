#pragma once
#include <utility>

class Rule {
public:
	bool Kuitan = true;
	bool Kuigae = false;
	bool Aka = true;
	bool Hako = true;
	bool Hanchan = true;		//”¼äµ

	int Mochiten = 25000;		//”z‹‹Œ´êy
	int Kaeshiten = 30000;		//Œ´êy
	std::pair<int, int> Uma;
};
