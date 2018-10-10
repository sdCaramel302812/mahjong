#include "stdafx.h"
#include "Player.h"


Player::Player()
{
	tehai = new Tehai();
	agent = new Agent(&Suteru, &NakuState, &tehai->tehai);
	Init();
}


Player::~Player()
{
}

void Player::IbatsuKesu()
{
	ibatsu = false;
}

void Player::FirstRoundKesu()
{
	firstR = false;
}

void Player::Init()
{
	Suteru = -1;
	NakuState = -1;
	tehai->Init();
	for (int i = 0; i < tehai->tehai.size(); ++i) {
		tehai->tehai.at(i) = -1;
	}
	Sutehai.clear();
	agent->Init();
	ibatsu = false;
	firstR = true;

	FuRouOrder.clear();
}

bool Player::NakuDekiru(int pai, bool ShanJa)
{
	int PaiNoR = pai;
	if (PaiNoR == 0 || PaiNoR == 10 || PaiNoR == 20) {
		PaiNoR += 5;
	}
	///////////////////////////////				確認可否吃
	if (pai < 30 && ShanJa && tehai->tehai.size() > 2) {
		
		/*
		分別為 :
				pai - 2 , pai - 1 , pai + 1 , pai + 2
		*/
		bool paiAri[4] = { false };
		for (int i = 0; i < tehai->tehai.size(); ++i) {
			int p;
			if (tehai->tehai.at(i) == 0 || tehai->tehai.at(i) == 10 || tehai->tehai.at(i) == 20) {
				p = tehai->tehai.at(i) + 5;
			}
			else {
				p = tehai->tehai.at(i);
			}
			if (PaiNoR % 10 != 1 && PaiNoR - p == 2) {
				paiAri[0] = true;
			}
			if (PaiNoR % 10 != 1 && PaiNoR - p == 1) {
				paiAri[1] = true;
			}
			if (PaiNoR % 10 != 9 && PaiNoR - p == -1) {
				paiAri[2] = true;
			}
			if (PaiNoR % 10 != 9 && PaiNoR - p == -2 && p < TON) {
				paiAri[3] = true;
			}
		}
		if ((paiAri[0] && paiAri[1])) {
			agent->ChiDekiru = true;
			agent->ChiDekiruList.push_back(std::pair<std::pair<int, int>, int>(std::pair<int, int>(PaiNoR - 2, PaiNoR - 1), 5));
		}
		if ((paiAri[1] && paiAri[2])) {
			agent->ChiDekiru = true;
			agent->ChiDekiruList.push_back(std::pair<std::pair<int, int>, int>(std::pair<int, int>(PaiNoR - 1, PaiNoR + 1), 4));
		}
		if ((paiAri[2] && paiAri[3])) {
			agent->ChiDekiru = true;
			agent->ChiDekiruList.push_back(std::pair<std::pair<int, int>, int>(std::pair<int, int>(PaiNoR + 1, PaiNoR + 2), 3));
		}
	}
	///////////////////////////////				確認可否碰
	int samepainum = 0;
	for (int i = 0; i < tehai->tehai.size(); ++i) {
		int p = tehai->tehai.at(i);
		if (p == 0 || p == 10 || p == 20) {
			p += 5;
		}
		if (p == PaiNoR) {
			++samepainum;
		}
	}
	if (samepainum >= 2) {
		agent->PonDekiru = true;
	}
	///////////////////////////////				確認可否明槓
	if (samepainum == 3) {
		agent->KanDekiru = true;
	}
	///////////////////////////////				確認可否榮和
	agent->RonDekiru = false;
	tehai->ronhai = pai;
	
	if (AgariCheck(tehai)) {
		//cout << endl;
		//cout << "fuck error" << endl;
		//tehai->ShowTehai();
		//cout << "fuck error" << endl;
		//try {
			Yaku yaku = YakuCheck(tehai, Chanfon, Menfon);
		//	yaku.ShowYaku();
		//}
		//catch (...) {
		//	cout << "crash situation : point checking" << endl;
		//}
		//cout << endl;

	

		agent->RonDekiru = true;
	}
	else {
		tehai->ronhai = -1;
	}


	if (agent->RonDekiru || agent->PonDekiru || agent->KanDekiru || agent->ChiDekiru) {
		return true;
	}
	else {
		return false;
	}
}

void Player::AnKanTsumoCheck()
{
	if (AgariCheck(tehai)) {
		agent->TsumoDekiru = true;
	}
	else {
//		WhatToTenPai = RichiCheck(tehai);
//		if (!WhatToTenPai.empty() && tehai->agarihai.size() == 14) {
//			agent->RichiDekiru = true;
//		}
	}

	int pin[9] = { 0 };
	int man[9] = { 0 };
	int sou[9] = { 0 };
	int other[7] = { 0 };
	for (int i = 0; i < tehai->agarihai.size(); ++i) {
		if (tehai->agarihai.at(i) >= 30) {
			++other[tehai->agarihai.at(i) - 30];
		}
		else if (tehai->agarihai.at(i) >= 20) {
			if (tehai->agarihai.at(i) == 20) {
				++sou[4];
			}
			else {
				++sou[tehai->agarihai.at(i) - 21];
			}
		}
		else if (tehai->agarihai.at(i) >= 10) {
			if (tehai->agarihai.at(i) == 10) {
				++man[4];
			}
			else {
				++man[tehai->agarihai.at(i) - 11];
			}
		}
		else {
			if (tehai->agarihai.at(i) == 0) {
				++pin[4];
			}
			else {
				++pin[tehai->agarihai.at(i) - 1];
			}
		}
	}
	agent->KanDekiruList.clear();
	for (int i = 0; i < 9; ++i) {
		if (pin[i] == 4) {
			agent->AnKanDekiru = true;
			agent->KanDekiruList.push_back(std::pair<int, int>(i + 1, 0));
			cout << "kan : " << i + 1 << endl;
		}
		if (man[i] == 4) {
			agent->AnKanDekiru = true;
			agent->KanDekiruList.push_back(std::pair<int, int>(i + 11, 0));
			cout << "kan : " << i + 11 << endl;
		}
		if (sou[i] == 4) {
			agent->AnKanDekiru = true;
			agent->KanDekiruList.push_back(std::pair<int, int>(i + 21, 0));
			cout << "kan : " << i + 21 << endl;
		}
	}
	for (int i = 0; i < 7; ++i) {
		if (other[i] == 4) {
			agent->AnKanDekiru = true;
			agent->KanDekiruList.push_back(std::pair<int, int>(i + 30, 0));
			cout << "kan : " << i + 30 << endl;
		}
	}


	for (int i = 0; i < tehai->pon.size(); ++i) {
		int p = tehai->pon.at(i).at(0);
		if (p == 0 || p == 10 || p == 20) {
			p += 5;
		}
		for (int j = 0; j < tehai->agarihai.size(); ++j) {
			if (tehai->agarihai.at(j) == 0 || tehai->agarihai.at(j) == 10 || tehai->agarihai.at(j) == 20) {
				if (tehai->agarihai.at(j) == p - 5) {
					agent->AnKanDekiru = true;
					agent->KanDekiruList.push_back(std::pair<int, int>(p, 1));
					cout << "kan : " << p << endl;
				}
			}
			else {
				if (tehai->agarihai.at(j) == p) {
					agent->AnKanDekiru = true;
					agent->KanDekiruList.push_back(std::pair<int, int>(p, 1));
					cout << "kan : " << p << endl;
				}
			}
		}
	}
}

int Player::Kiru()
{
	if (NakuState == 2) {
//		cout << "fuck you\t" << id << endl;
	}

	if (Suteru != -1) {
		int s = Suteru;
		tehai->Kiru(s);
		Sutehai.push_back(s);
		agent->WaitForKiru = false;
		Suteru = -1;
		return s;
	}
	return -1;
}

void Player::Tsumo(int pai)
{
	tehai->ronhai = -1;
	tehai->Tsumo(pai);
	agent->WaitForKiru = true;
}

bool Player::Ankan()
{
	if (NakuState == 2) {
		cout << "fuck " << agent->KanDekiruList.size() << endl;
		NakuState = -1;
		if (agent->KanDekiruList.size() > agent->KanCase && agent->KanDekiruList.at(agent->KanCase).second == 0) {
			tehai->Ankan(agent->KanDekiruList.at(agent->KanCase).first);
			FuRouOrder.push_back(AnKan);
			cout << "ankan" << endl;
		}
		else if(agent->KanDekiruList.size() > agent->KanCase) {
			cout << "kakan" << endl;
			int pon_pos = 0;
			for (int i = 0; i < tehai->pon.size(); ++i) {
				if ((tehai->pon.at(i).at(0) == 0 || tehai->pon.at(i).at(0) == 10 || tehai->pon.at(i).at(0) == 20)) {
					if (tehai->pon.at(i).at(0) == agent->KanDekiruList.at(agent->KanCase).first - 5) {
						pon_pos = i;
					}
				}
				else {
					if (tehai->pon.at(i).at(0) == agent->KanDekiruList.at(agent->KanCase).first) {
						pon_pos = i;
					}
				}
			}
			tehai->Kakan(agent->KanDekiruList.at(agent->KanCase).first);
			for (int i = 0; i < FuRouOrder.size(); ++i) {
				if (FuRouOrder.at(i) == Pon) {
					--pon_pos;
				}
				if (pon_pos == -1) {
					FuRouOrder.at(i) = MinKan;
					break;
				}
			}
		}
		agent->KanCase = -1;
		agent->KanDekiruList.clear();
		agent->WaitForKiru = false;
		agent->AnKanDekiru = false;
		return true;
	}
	else {
		return false;
	}
}

int Player::Naku(int pai)
{
	if (!agent->ChiDekiru && !agent->PonDekiru && !agent->RonDekiru && !agent->KanDekiru && !agent->NakuDekiru) {
		//	NakuState = 0;
	}
	try {
		if ((4 - (int)tehai->tehai.size() / 3) == FuRouOrder.size()) {
			if (NakuState == 1) {
				FuRouOrder.push_back(Pon);
			}
			else if (NakuState == 2) {
				FuRouOrder.push_back(MinKan);
			}
			else if (NakuState == 3 || NakuState == 4 || NakuState == 5) {
				FuRouOrder.push_back(Chi);
			}
		}
		else if ((4 - (int)tehai->tehai.size() / 3) < FuRouOrder.size()) {
			if (NakuState == 1) {
				FuRouOrder.back() = Pon;
			}
			else if (NakuState == 2) {
				FuRouOrder.back() = MinKan;
			}
			else if (NakuState == 3 || NakuState == 4 || NakuState == 5) {
				FuRouOrder.back() = Chi;
			}
		}
	}
	catch (...) {
		cout << "crash situation : update furou order" << endl;
	}

	if (id == 1) {
//		cout << "player state : " << NakuState << endl;
	}
	return NakuState;
}

void Player::Nakasareru()
{
	IbatsuKesu();
	FirstRoundKesu();
	SutehaiInOther.push_back(Sutehai.back());
	Sutehai.pop_back();
}

void Player::Nagasu()
{
}

void Player::SetAgariCallback(bool * a)
{
	Agari = a;
	agent->Agari = a;
}
