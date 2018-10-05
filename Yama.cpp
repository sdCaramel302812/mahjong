#include "stdafx.h"
#include "Yama.h"


Yama::Yama()
{
}


Yama::~Yama()
{
}

void Yama::Init(bool aka)
{
	srand(time(NULL));
	Rinshanhai = 0;
	Haiteihai = 12;
	PaiSan.resize(136);
	int akaN = 0;
	for (int i = 0; i < 37; ++i) {
		if (i == 0) {
			++akaN;
			continue;
		}
		else if (i == 10) {
			++akaN;
			continue;
		}
		else if (i == 20) {
			++akaN;
			continue;
		}
		else {
			PaiSan.at((i - akaN) * 4) = i;
			PaiSan.at((i - akaN) * 4 + 1) = i;
			PaiSan.at((i - akaN) * 4 + 2) = i;
			PaiSan.at((i - akaN) * 4 + 3) = i;
		}
	}
	if (aka) {
		PaiSan.at(16) = 0;
		PaiSan.at(17) = 0;
		PaiSan.at(52) = 10;
		PaiSan.at(88) = 20;
	}

	for (int i = 0; i < 136; ++i) {
		int swap = rand() % 136;
		int temp = PaiSan.at(swap);
		PaiSan.at(swap) = PaiSan.at(i);
		PaiSan.at(i) = temp;
	}
}

std::vector<std::vector<int>> Yama::Peipai()
{
	std::vector<std::vector<int>> pai;
	std::vector<int> p1, p2, p3, p4;
	for (int i = 0; i < 13; ++i) {
		p1.push_back(PaiSan.back());
		PaiSan.pop_back();
		p2.push_back(PaiSan.back());
		PaiSan.pop_back();
		p3.push_back(PaiSan.back());
		PaiSan.pop_back();
		p4.push_back(PaiSan.back());
		PaiSan.pop_back();
	}
	pai.push_back(p1);
	pai.push_back(p2);
	pai.push_back(p3);
	pai.push_back(p4);
	return pai;
}

int Yama::MoPai()
{
	if (PaiSan.size() > Haiteihai) {
		int p = PaiSan.back();
		PaiSan.pop_back();
		return p;
	}
	return -1;
}

int Yama::MoRinshan()
{
	++Rinshanhai;
	++Haiteihai;
	return PaiSan.at(Rinshanhai - 1);
}

void Yama::Kan()
{
}
