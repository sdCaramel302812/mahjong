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
	current_clock = clock();
	dt = current_clock - last_clock;
	last_clock = current_clock;
	elapsed_time += dt;

	//vvvvvvvvvvvvvvvvvvvvvvvvv			測試用 AI
	if (IsAI) {
		if (RonDekiru || TsumoDekiru) {
			*Agari = true;
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
				cout << "why" << endl;
				if (KanDekiruList.size() != 0) {
					cout << "it doesn't make sence" << endl;
					AnKanDekiru = false;
					*NakuState = 2;
					KanCase = 0;
				}
			}
			else {
				int rnd = rand() % 2;
				if (rnd == 1) {
					*Suteru = tehai->back();
				}
				else {
					*Suteru = tehai->front();
				}
				return;
			}
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
	//^^^^^^^^^^^^^^^^^^^^^^^^^			測試用 AI

	if (!IsAI) {
		if (!ChiDekiru && !PonDekiru && !KanDekiru && !RonDekiru) {
			*NakuState = 0;
		}
		else {
			*NakuState = -1;
		}


		if ((AnKanDekiru && WantToKan == -1) || (ChiDekiru && WantToChi == -1) || (PonDekiru && WantToPon == -1) || (KanDekiru && WantToKan == -1) || (RonDekiru && WantToRon == -1) || (TsumoDekiru && WantToTsumo == -1)) {
			*NakuState = 0;
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

	ChiDekiruList.clear();
	//KanDekiruList.clear();

	WantToChi = 0;
	WantToKan = 0;
	WantToPon = 0;
	WantToRon = 0;
	WantToTsumo = 0;

	ChiCase = -1;
}
