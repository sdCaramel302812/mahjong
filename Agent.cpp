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
			int rnd = rand() % 2;
			if (rnd == 1) {
				*Suteru = tehai->back();
			}
			else {
				*Suteru = tehai->front();
			}
		}
		if (RonDekiru || TsumoDekiru) {
			*Agari = true;
		}
		else if (ChiDekiru) {
			ChiDekiru = false;
			KanDekiru = false;
			PonDekiru = false;
			if (!ChiDekiruList.empty()) {
				int rnd = rand() % ChiDekiruList.size();
				*NakuState = ChiDekiruList.at(rnd).second;
				ChiDekiruList.clear();
			}
		}
		else if (KanDekiru) {
			KanDekiru = false;
			PonDekiru = false;
			*NakuState = 2;
		}
		else if (PonDekiru) {
			PonDekiru = false;
			*NakuState = 1;
		}
		else {
			*NakuState = 0;
		}
	}

	bool hasAct = false;

	if (!IsAI && !ChiDekiru && !PonDekiru && !KanDekiru && !RonDekiru && !TsumoDekiru) {
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
			if (*NakuState == -1 && !hasAct) {
				*NakuState = 0;
			}
		}
		WantToPon = 0;
	}
	else {
		WantToPon = 0;
	}
	if (ChiDekiru) {
		if (WantToChi == 1) {
			hasAct = true;
			if (ChiCase != -1) {
				ChiDekiru = false;
				*NakuState = ChiDekiruList.at(ChiCase).second;
				ChiCase = -1;
				ChiDekiruList.clear();
				WantToChi = 0;
			}
		}
		if (WantToChi == -1) {
			ChiDekiru = false;
			ChiCase = -1;
			if (*NakuState == -1 && !hasAct) {
				*NakuState = 0;
			}
			ChiDekiruList.clear();
			WantToChi = 0;
		}
		
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
			if (*NakuState == -1 && !hasAct) {
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
			if (*NakuState == -1 && !hasAct) {
				*NakuState = 0;
			}
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
