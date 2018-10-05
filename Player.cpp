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

bool Player::NakuDekiru(int pai)
{
	agent->RonDekiru = false;
	tehai->ronhai = pai;

	///////////////////////////////				確認可否吃
	///////////////////////////////				確認可否碰
	for (int i = 0; i < tehai->tehai.size() - 1; ++i) {
		if (tehai->tehai.at(i) == tehai->tehai.at(i + 1) && tehai->tehai.at(i) == pai) {
			agent->PonDekiruPai = pai;
			agent->PonDekiru = true;
		}
	}
	///////////////////////////////				確認可否槓
	for (int i = 0; i < tehai->tehai.size() - 2; ++i) {
		if (tehai->tehai.at(i) == tehai->tehai.at(i + 1) && tehai->tehai.at(i) == tehai->tehai.at(i + 2) && tehai->tehai.at(i) == pai) {
			agent->KanDekiruList.push_back(pai);
			agent->KanDekiru = true;
		}
	}
	///////////////////////////////				確認可否榮和
	if (AgariCheck(tehai)) {

		cout << endl;
		cout << "fuck error" << endl;
		tehai->ShowTehai();
		cout << "fuck error" << endl;
		Yaku yaku = YakuCheck(tehai, TON, TON);
		yaku.ShowYaku();
		cout << endl;

	

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
	tehai->Tsumo(pai);
	agent->WaitForKiru = true;
}

int Player::Naku(int pai)
{
	if (!agent->ChiDekiru && !agent->PonDekiru && !agent->RonDekiru && !agent->KanDekiru && !agent->NakuDekiru) {
	//	NakuState = 0;
	}
	if (4 - tehai->tehai.size() / 3 == FuRouOrder.size()) {
		if (NakuState == 1) {
			FuRouOrder.push_back(Pon);
		}
		else if (NakuState == 2) {
			FuRouOrder.push_back(Kan);
		}
		else if (NakuState == 3 || NakuState == 4 || NakuState == 5) {
			FuRouOrder.push_back(Chi);
		}
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

void Player::Nagashu()
{
}

void Player::SetAgariCallback(bool * a)
{
	Agari = a;
	agent->Agari = a;
}
