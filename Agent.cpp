#include "stdafx.h"
#include "Agent.h"


Agent::Agent(int *s, int *n, std::vector<int> *t)
{
	Suteru = s;
	NakuState = n;
	tehai = t;
}


Agent::~Agent()
{
}

void Agent::Init()
{
	NakuDekiru = false;
	PonDekiru = false;
	KanDekiru = false;
	ChiDekiru = false;
	RonDekiru = false;
	TsumoDekiru = false;
	WaitForKiru = false;
	WantToChi = 0;
	WantToKan = 0;
	WantToPon = 0;
	WantToRon = 0;
	WantToTsumo = 0;
}

void Agent::Act()
{
	if (IsAI) {
		if (WaitForKiru) {
			*Suteru = tehai->at(0);
		}
		*NakuState = 0;
	}

	if (PonDekiru) {
		if (WantToPon == 1) {
			PonDekiru = false;
			PonDekiruPai = -1;
			*NakuState = 1;
		}
		if (WantToPon == -1) {
			PonDekiru = false;
			PonDekiruPai = -1;
			if (*NakuState == -1) {
				*NakuState = 0;
			}
		}
		WantToPon = 0;
	}
	else {
		WantToPon = 0;
	}
	if (ChiDekiru) {

	}
	else {
		WantToChi = 0;
	}
	if (KanDekiru) {
		if (WantToKan == 1) {
			KanDekiru = false;
			*NakuState = 2;
		}
		if (WantToKan == -1) {
			KanDekiru = false;
			if (*NakuState == -1) {
				*NakuState = 0;
			}
		}
		WantToKan = 0;
	}
	else {
		WantToKan = 0;
	}
	if (RonDekiru) {
		if (WantToRon == 1) {
			RonDekiru = false;
			*Agari = true;
		}
		if (WantToRon == -1) {
			RonDekiru = false;
		}
		WantToRon = 0;
	}
	else {
		WantToRon = 0;
	}
	if (TsumoDekiru) {
		if (WantToTsumo == 1) {
			TsumoDekiru = false;
			*Agari = true;
		}
		if (WantToTsumo == -1) {
			TsumoDekiru = false;
		}
		WantToTsumo = 0;
	}
	else {
		WantToTsumo = 0;
	}
}
