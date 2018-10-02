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
	for (int i = 0; i < tehai->tehai.size(); ++i) {
		tehai->tehai.at(i) = -1;
	}
	ibatsu = false;
	firstR = true;
}

bool Player::NakuDekiru(int pai)
{
	return false;
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

int Player::Naku()
{
	if (NakuState == -1) {
		return -1;
	}
	else if (NakuState == 0) {
		NakuState = -1;
		return 0;
	}
	else if (NakuState == 1) {		//‹L“¾•âŠ®
		NakuState = -1;
		return 1;
	}
	else if (NakuState == 2) {
		NakuState = -1;
		return 1;
	}
	else if (NakuState == 3) {
		NakuState = -1;
		return 1;
	}
	else if (NakuState == 4) {
		NakuState = -1;
		return 1;
	}
	else if (NakuState == 5) {
		NakuState = -1;
		return 1;
	}
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
