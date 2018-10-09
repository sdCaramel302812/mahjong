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
	///////////////////////////////				確認可否吃
	if (pai < 30 && ShanJa && tehai->tehai.size() > 2) {
		int PaiNoR = pai;
		if (PaiNoR == 0 || PaiNoR == 10 || PaiNoR == 20) {
			PaiNoR += 5;
		}
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
	for (int i = 0; i < tehai->tehai.size() - 1; ++i) {
		if (pai == 0 || pai == 10 || pai == 20) {
			if ((tehai->tehai.at(i) == pai + 5 || tehai->tehai.at(i) == pai) && (tehai->tehai.at(i + 1) == pai + 5 || tehai->tehai.at(i + 1) == pai)) {
				agent->PonDekiruPai = pai;
				agent->PonDekiru = true;
			}
		}
		else if (pai == 5 || pai == 15 || pai == 25) {
			if ((tehai->tehai.at(i) == pai - 5 || tehai->tehai.at(i) == pai) && (tehai->tehai.at(i + 1) == pai - 5 || tehai->tehai.at(i + 1) == pai)) {
				agent->PonDekiruPai = pai;
				agent->PonDekiru = true;
			}
		}
		else if (tehai->tehai.at(i) == tehai->tehai.at(i + 1) && tehai->tehai.at(i) == pai) {
			agent->PonDekiruPai = pai;
			agent->PonDekiru = true;
		}
	}
	///////////////////////////////				確認可否槓
	if (tehai->tehai.size() > 2) {
		for (int i = 0; i < (tehai->tehai.size() - 2); ++i) {
			if (pai == 0 || pai == 10 || pai == 20) {
				if ((tehai->tehai.at(i) == pai + 5 || tehai->tehai.at(i) == pai) && (tehai->tehai.at(i + 1) == pai + 5 || tehai->tehai.at(i + 1) == pai) && (tehai->tehai.at(i + 2) == pai + 5 || tehai->tehai.at(i + 2) == pai)) {
					agent->KanDekiruList.push_back(pai);
					agent->KanDekiru = true;
				}
			}
			else if (pai == 5 || pai == 15 || pai == 25) {
				if ((tehai->tehai.at(i) == pai - 5 || tehai->tehai.at(i) == pai) && (tehai->tehai.at(i + 1) == pai - 5 || tehai->tehai.at(i + 1) == pai) && (tehai->tehai.at(i + 2) == pai - 5 || tehai->tehai.at(i + 2) == pai)) {
					agent->KanDekiruList.push_back(pai);
					agent->KanDekiru = true;
				}
			}
			else if (tehai->tehai.at(i) == tehai->tehai.at(i + 1) && tehai->tehai.at(i) == tehai->tehai.at(i + 2) && tehai->tehai.at(i) == pai) {
				agent->KanDekiruList.push_back(pai);
				agent->KanDekiru = true;
			}
		}
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
		//	Yaku yaku = YakuCheck(tehai, Chanfon, Menfon);
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

int Player::Kiru()
{
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
