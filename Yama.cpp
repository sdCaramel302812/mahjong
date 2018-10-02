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
	return std::vector<std::vector<int>>();
}

int Yama::MoPai()
{
	return 0;
}

int Yama::MoRinshan()
{
	return 0;
}

void Yama::Kan()
{
}
