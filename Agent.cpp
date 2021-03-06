#include "stdafx.h"
#include "Agent.h"


Agent::Agent(int *s, int *n, bool *f, std::vector<int> *t, int *tsumo)
{
	Suteru = s;
	NakuState = n;
	tehai = t;
	Furiten = f;
	tsumohai = tsumo;
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
	RichiDekiru = false;
	WantToChi = 0;
	WantToKan = 0;
	WantToPon = 0;
	WantToRon = 0;
	WantToTsumo = 0;

	richi = false;
}

void Agent::Act()
{
	current_clock = clock();
	dt = current_clock - last_clock;
	last_clock = current_clock;
	elapsed_time += dt;

	//vvvvvvvvvvvvvvvvvvvvvvvvv			���ե� AI
	if (IsAI) {
		if (RonDekiru || TsumoDekiru) {
			*Agari = true;
			return;
		}
		if (WaitForKiru) {	

			if (WaitForDaPai) {
				WaitForDaPai = false;
				elapsed_time = 0;
				return;
			}
			else {
				if (elapsed_time > DaPaiWaitingTime) {
					WaitForDaPai = true;
				}
				else {
					return;
				}
			}

			if (AnKanDekiru) {
//				cout << "why" << endl;
				if (KanDekiruList.size() != 0) {
//					cout << "it doesn't make sence" << endl;
					AnKanDekiru = false;
					*NakuState = 2;
					KanCase = 0;
				}
			}
			else if (RichiDekiru) {
				if (!WhatToTenPai.empty()) {
					int p = WhatToTenPai.front().first;
					WantToRichi = 1;
					RichiDekiru = false;
					richi = true;
					*Suteru = p;
				}
				else {
					RichiDekiru = false;
				}
			}
			else {
				if (richi) {
					*Suteru = *tsumohai;
					return;
				}
				for (int i = 0; i < (int)tehai->size() - 1; ++i) {
					if (i == 0) {
						if (tehai->at(i + 1) - tehai->at(i) > 1) {
							*Suteru = tehai->at(i);
						}
					}
					else {
						if (tehai->at(i + 1) - tehai->at(i) > 1 && tehai->at(i) - tehai->at(i - 1) > 1) {
							*Suteru = tehai->at(i);
						}
					}
				}
				if (*Suteru == -1) {
					*Suteru = tehai->back();
				}

				return;
			}
		}
		else if (false) {
			ChiDekiru = false;
			KanDekiru = false;
			PonDekiru = false;
			if (!ChiDekiruList.empty()) {
				int rnd = rand() % ChiDekiruList.size();
				*NakuState = ChiDekiruList.at(rnd).second;
				ChiDekiruList.clear();
			}
		}
		else if (false) {
			KanDekiru = false;
			PonDekiru = false;
			*NakuState = 2;
		}
		else if (false) {
			PonDekiru = false;
			*NakuState = 1;
		}
		else {
			*NakuState = 0;
		}
	}
	//^^^^^^^^^^^^^^^^^^^^^^^^^			���ե� AI

	if (!IsAI) {
		if (!ChiDekiru && !PonDekiru && !KanDekiru && !RonDekiru) {
			*NakuState = 0;
		}
		else {
			*NakuState = -1;
		}


		if ((RichiDekiru && WantToRichi == -1) || (AnKanDekiru && WantToKan == -1) || (ChiDekiru && WantToChi == -1) || (PonDekiru && WantToPon == -1) || (KanDekiru && WantToKan == -1) || (RonDekiru && WantToRon == -1) || (TsumoDekiru && WantToTsumo == -1)) {
			*NakuState = 0;
			if (WantToRon = -1) {
				*Furiten = true;
			}
			ResetActState();
			return;
		}

		if (ChiDekiru && WantToChi == 1 && ChiCase != -1 && ChiDekiruList.size() > ChiCase) {
			*NakuState = ChiDekiruList.at(ChiCase).second;
			ResetActState();
		}
		if (PonDekiru && WantToPon == 1) {
			*NakuState = 1;
			ResetActState();
		}
		if (AnKanDekiru && WantToKan == 1 && KanCase != -1 && KanDekiruList.size() > KanCase) {
			*NakuState = 2;
			ResetActState();
		}
		if (KanDekiru && WantToKan == 1) {
			*NakuState = 2;
			ResetActState();
		}
		if (RonDekiru && WantToRon == 1) {
			*Agari = true;
			*NakuState = 6;
			ResetActState();
		}
		if (TsumoDekiru && WantToTsumo == 1) {
			*Agari = true;
			ResetActState();
		}

		if (!ChiDekiru) {
			WantToChi = 0;
		}
		if (!PonDekiru) {
			WantToPon = 0;
		}
		if (!KanDekiru && !AnKanDekiru) {
			WantToKan = 0;
		}
		if (!RonDekiru) {
			WantToRon = 0;
		}
		if (!TsumoDekiru) {
			WantToTsumo = 0;
		}
		if (!RichiDekiru) {
			WantToRichi = 0;
		}
	}
	
}

void Agent::ResetActState()
{
	ChiDekiru = false;
	PonDekiru = false;
	KanDekiru = false;
	RonDekiru = false;
	AnKanDekiru = false;
	TsumoDekiru = false;
	RichiDekiru = false;

	ChiDekiruList.clear();
	//KanDekiruList.clear();

	WantToChi = 0;
	WantToKan = 0;
	WantToPon = 0;
	WantToRon = 0;
	WantToTsumo = 0;
	WantToRichi = 0;

	ChiCase = -1;
}
