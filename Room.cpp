#include "stdafx.h"
#include "Room.h"


Room::Room()
{
	yama = new Yama();
	rule = new Rule();
	pl1 = new Player();
	pl2 = new Player();
	pl3 = new Player();
	pl4 = new Player();

	pl1->SetAgariCallback(&WhoIsAgari[0]);
	pl2->SetAgariCallback(&WhoIsAgari[1]);
	pl3->SetAgariCallback(&WhoIsAgari[2]);
	pl4->SetAgariCallback(&WhoIsAgari[3]);

	pl1->agent->IsAI = false;
}


Room::~Room()
{
}

void Room::Init()
{
	yama->Init(rule->Aka);
	pl1->Init();
	pl2->Init();
	pl3->Init();
	pl4->Init();

	round = 1;
}

void Room::Play()
{
	//while (!gameover) {
		if (kyoukuover) {
			NextKyouku();
			UpdateScene = true;
			kyoukuover = false;
		}

		for (int i = 0; i < 4; ++i) {
			if (WhoIsAgari[i]) {
				kyoukuover = true;
				WhoIsAgari[0] = false;
				WhoIsAgari[1] = false;
				WhoIsAgari[2] = false;
				WhoIsAgari[3] = false;
				return;
			}
		}

		if (round == 2) {
			pl1->FirstRoundKesu();
			pl2->FirstRoundKesu();
			pl3->FirstRoundKesu();
			pl4->FirstRoundKesu();
		}

		pl1->agent->Act();
		pl2->agent->Act();
		pl3->agent->Act();
		pl4->agent->Act();
		/*
		等待玩家切牌
		若尚未決定
		則回傳 -1
		若捨牌完成
		則檢查他家能否鳴牌
		*/
		if (WaitingState == 0) {
			//vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv			等待切牌
			switch (CurrentPlayer)
			{
			case 1:
				Sutehai = pl1->Kiru();
				break;
			case 2:
				Sutehai = pl2->Kiru();
				break;
			case 3:
				Sutehai = pl3->Kiru();
				break;
			case 4:
				Sutehai = pl4->Kiru();
				break;
			}
			if (Sutehai != -1) {
				UpdateScene = true;
				bool wait = NakuCheck(Sutehai);
				if (wait) {
					WaitingState = 1;
					Debug::Log("wait");
					return;
				}
				else {
					Sutehai = -1;
					NextPlayer();
					int NewPai = yama->MoPai();
					if (NewPai == -1) {
						kyoukuover = true;
						UpdateScene = true;
						return;
					}
					else {
						switch (CurrentPlayer)
						{
						case 1:
							pl1->Tsumo(NewPai);
							if (AgariCheck(pl1->tehai)) {
								pl1->agent->TsumoDekiru = true;
							}
							++round;
							break;
						case 2:
							pl2->Tsumo(NewPai);
							break;
						case 3:
							pl3->Tsumo(NewPai);
							break;
						case 4:
							pl4->Tsumo(NewPai);
							break;
						}
					}
				}
			}
			//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^			等待切牌
		}
		else if (WaitingState == 1) {
			//vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv			等待鳴牌
			int result1;
			int result2;
			int result3;
			UpdateScene = true;						//不確定

			///////////////////////////////////////////			自家捨牌
			switch (CurrentPlayer)
			{
			case 1:
				result1 = pl2->Naku(Sutehai);
				result2 = pl3->Naku(Sutehai);
				result3 = pl4->Naku(Sutehai);
				if (result1 == -1 || result2 == -1 || result3 == -1) {
					return;
				}
				if (result1 == 0 && result2 == 0 && result3 == 0) {
					Sutehai = -1;
					pl4->NakuState = -1;
					pl2->NakuState = -1;
					pl3->NakuState = -1;
					NextPlayer();
					WaitingState = 0;
					int NewPai = yama->MoPai();
					if (NewPai == -1) {
						kyoukuover = true;
						UpdateScene = true;
						return;
					}
					switch (CurrentPlayer)
					{
					case 1:
						pl1->Tsumo(NewPai);
						break;
					case 2:
						pl2->Tsumo(NewPai);
						break;
					case 3:
						pl3->Tsumo(NewPai);
						break;
					case 4:
						pl4->Tsumo(NewPai);
						break;
					}
				}
				else {
					pl1->Nakasareru();
					WaitingState = 0;
					if (result1 == 1 || result1 == 2) {
						CurrentPlayer = 2;
						pl2->NakuState = -1;
						if (result1 == 1) {
							pl2->tehai->Pon(Sutehai, 0);
							pl2->agent->WaitForKiru = true;
						}
						else {
							pl2->tehai->Daiminkan(Sutehai, 0);
							pl2->Tsumo(yama->MoRinshan());
							pl2->agent->WaitForKiru = true;
						}
					}
					else if (result2 == 1 || result2 == 2) {
						CurrentPlayer = 3;
						pl3->NakuState = -1;
						if (result2 == 1) {
							pl3->tehai->Pon(Sutehai, 1);
							pl3->agent->WaitForKiru = true;
						}
						else {
							pl3->tehai->Daiminkan(Sutehai, 1);
							pl3->Tsumo(yama->MoRinshan());
							pl3->agent->WaitForKiru = true;
						}
					}
					else if (result3 == 1 || result3 == 2) {
						CurrentPlayer = 4;
						pl4->NakuState = -1;
						if (result3 == 1) {
							pl4->tehai->Pon(Sutehai, 2);
							pl4->agent->WaitForKiru = true;
						}
						else {
							pl4->tehai->Daiminkan(Sutehai, 2);
							pl4->Tsumo(yama->MoRinshan());
							pl4->agent->WaitForKiru = true;
						}
					}
					else if (result1 > 2) {
						int sutenum = Sutehai;
						if (sutenum % 10 == 0) {
							sutenum += 5;
						}
						CurrentPlayer = 2;
						pl2->NakuState = -1;
						pl2->agent->WaitForKiru = true;
						if (result1 == 3) {
							pl2->tehai->Chi(Sutehai, sutenum++, sutenum += 2);
						}
						else if (result1 == 4) {
							pl2->tehai->Chi(Sutehai, sutenum--, sutenum++);
						}
						else if (result1 == 5) {
							pl2->tehai->Chi(Sutehai, sutenum -= 2, sutenum--);
						}
					}
					Sutehai = -1;
				}
				break;
			///////////////////////////////////////////			下家捨牌
			case 2:
				result3 = pl1->Naku(Sutehai);
				result1 = pl3->Naku(Sutehai);
				result2 = pl4->Naku(Sutehai);
				//Debug::Log(TString("state1 : ") + TString().number(result3));
				//Debug::Log(TString("state2 : ") + TString().number(result1));
				//Debug::Log(TString("state3 : ") + TString().number(result2));
				if (result1 == -1 || result2 == -1 || result3 == -1) {
					return;
				}
				if (result1 == 0 && result2 == 0 && result3 == 0) {
					Sutehai = -1;
					pl1->NakuState = -1;
					pl4->NakuState = -1;
					pl3->NakuState = -1;
					NextPlayer();
					WaitingState = 0;
					int NewPai = yama->MoPai();
					if (NewPai == -1) {
						kyoukuover = true;
						UpdateScene = true;
						return;
					}
					switch (CurrentPlayer)
					{
					case 1:
						pl1->Tsumo(NewPai);
						break;
					case 2:
						pl2->Tsumo(NewPai);
						break;
					case 3:
						pl3->Tsumo(NewPai);
						break;
					case 4:
						pl4->Tsumo(NewPai);
						break;
					}
				}
				else {
					pl2->Nakasareru();
					WaitingState = 0;
					if (result1 == 1 || result1 == 2) {
						CurrentPlayer = 3;
						pl3->NakuState = -1;
						if (result1 == 1) {
							pl3->tehai->Pon(Sutehai, 0);
							pl3->agent->WaitForKiru = true;
						}
						else {
							pl3->tehai->Daiminkan(Sutehai, 0);
							pl3->Tsumo(yama->MoRinshan());
							pl3->agent->WaitForKiru = true;
						}
					}
					else if (result2 == 1 || result2 == 2) {
						CurrentPlayer = 4;
						pl4->NakuState = -1;
						if (result2 == 1) {
							pl4->tehai->Pon(Sutehai, 1);
							pl4->agent->WaitForKiru = true;
						}
						else {
							pl4->tehai->Daiminkan(Sutehai, 1);
							pl4->Tsumo(yama->MoRinshan());
							pl4->agent->WaitForKiru = true;
						}
					}
					else if (result3 == 1 || result3 == 2) {
						pl1->NakuState = -1;
						CurrentPlayer = 1;
						if (result3 == 1) {
							pl1->tehai->Pon(Sutehai, 2);
							pl1->agent->WaitForKiru = true;
						}
						else {
							pl1->tehai->Daiminkan(Sutehai, 2);
							pl1->Tsumo(yama->MoRinshan());
							pl1->agent->WaitForKiru = true;
						}
					}
					else if (result1 > 2) {
						int sutenum = Sutehai;
						if (sutenum % 10 == 0) {
							sutenum += 5;
						}
						pl3->agent->WaitForKiru = true;
						CurrentPlayer = 3;
						pl3->NakuState = -1;
						if (result1 == 3) {
							pl3->tehai->Chi(Sutehai, sutenum++, sutenum += 2);
						}
						else if (result1 == 4) {
							pl3->tehai->Chi(Sutehai, sutenum--, sutenum++);
						}
						else if (result1 == 5) {
							pl3->tehai->Chi(Sutehai, sutenum -= 2, sutenum--);
						}
					}
					Sutehai = -1;
				}
				break;
			///////////////////////////////////////////			對家捨牌
			case 3:
				result2 = pl1->Naku(Sutehai);
				result3 = pl2->Naku(Sutehai);
				result1 = pl4->Naku(Sutehai);
				//Debug::Log(TString("state1 : ") + TString().number(result2));
				//Debug::Log(TString("state2 : ") + TString().number(result1));
				//Debug::Log(TString("state3 : ") + TString().number(result3));
				if (result1 == -1 || result2 == -1 || result3 == -1) {
					return;
				}
				if (result1 == 0 && result2 == 0 && result3 == 0) {
					Sutehai = -1;
					pl1->NakuState = -1;
					pl2->NakuState = -1;
					pl4->NakuState = -1;
					NextPlayer();
					WaitingState = 0;
					int NewPai = yama->MoPai();
					if (NewPai == -1) {
						kyoukuover = true;
						UpdateScene = true;
						return;
					}
					switch (CurrentPlayer)
					{
					case 1:
						pl1->Tsumo(NewPai);
						break;
					case 2:
						pl2->Tsumo(NewPai);
						break;
					case 3:
						pl3->Tsumo(NewPai);
						break;
					case 4:
						pl4->Tsumo(NewPai);
						break;
					}
				}
				else {
					pl1->NakuState = -1;
					pl2->NakuState = -1;
					pl4->NakuState = -1;
					pl3->Nakasareru();
					WaitingState = 0;
					if (result1 == 1 || result1 == 2) {
						CurrentPlayer = 4;
						if (result1 == 1) {
							pl4->tehai->Pon(Sutehai, 0);
							pl4->agent->WaitForKiru = true;
						}
						else {
							pl4->tehai->Daiminkan(Sutehai, 0);
							pl4->Tsumo(yama->MoRinshan());
							pl4->agent->WaitForKiru = true;
						}
					}
					else if (result2 == 1 || result2 == 2) {
						
						CurrentPlayer = 1;
						if (result2 == 1) {
							pl1->tehai->Pon(Sutehai, 1);
							pl1->agent->WaitForKiru = true;
						}
						else {
							pl1->tehai->Daiminkan(Sutehai, 1);
							pl1->Tsumo(yama->MoRinshan());
							pl1->agent->WaitForKiru = true;
						}
					}
					else if (result3 == 1 || result3 == 2) {
						CurrentPlayer = 2;
						if (result3 == 1) {
							pl2->tehai->Pon(Sutehai, 2);
							pl2->agent->WaitForKiru = true;
						}
						else {
							pl2->tehai->Daiminkan(Sutehai, 2);
							pl2->Tsumo(yama->MoRinshan());
							pl2->agent->WaitForKiru = true;
						}
					}
					else if (result1 > 2) {
						int sutenum = Sutehai;
						if (sutenum % 10 == 0) {
							sutenum += 5;
						}
						pl4->agent->WaitForKiru = true;
						CurrentPlayer = 4;
						if (result1 == 3) {
							pl4->tehai->Chi(Sutehai, sutenum++, sutenum += 2);
						}
						else if (result1 == 4) {
							pl4->tehai->Chi(Sutehai, sutenum--, sutenum++);
						}
						else if (result1 == 5) {
							pl4->tehai->Chi(Sutehai, sutenum -= 2, sutenum--);
						}
					}
					Sutehai = -1;
				}
				break;
			///////////////////////////////////////////			上家捨牌
			case 4:
				result1 = pl1->Naku(Sutehai);
				result2 = pl2->Naku(Sutehai);
				result3 = pl3->Naku(Sutehai);
				//Debug::Log(TString("state1 : ") + TString().number(result1));
				//Debug::Log(TString("state2 : ") + TString().number(result2));
				//Debug::Log(TString("state3 : ") + TString().number(result3));
				if (result1 == -1 || result2 == -1 || result3 == -1) {
					return;
				}
				if (result1 == 0 && result2 == 0 && result3 == 0) {
					Sutehai = -1;
					pl1->NakuState = -1;
					pl2->NakuState = -1;
					pl3->NakuState = -1;
					NextPlayer();
					WaitingState = 0;
					int NewPai = yama->MoPai();
					if (NewPai == -1) {
						kyoukuover = true;
						UpdateScene = true;
						return;
					}
					switch (CurrentPlayer)
					{
					case 1:
						pl1->Tsumo(NewPai);
						break;
					case 2:
						pl2->Tsumo(NewPai);
						break;
					case 3:
						pl3->Tsumo(NewPai);
						break;
					case 4:
						pl4->Tsumo(NewPai);
						break;
					}
				}
				else {
					pl1->NakuState = -1;
					pl2->NakuState = -1;
					pl3->NakuState = -1;
					pl4->Nakasareru();
					WaitingState = 0;
					if (result1 == 1 || result1 == 2) {
						
						CurrentPlayer = 1;
						if (result1 == 1) {
							pl1->tehai->Pon(Sutehai, 0);
							pl1->agent->WaitForKiru = true;
						}
						else {
							pl1->tehai->Daiminkan(Sutehai, 0);
							pl1->Tsumo(yama->MoRinshan());
							pl1->agent->WaitForKiru = true;
						}
					}
					else if (result2 == 1 || result2 == 2) {
						CurrentPlayer = 2;
						if (result1 == 1) {
							pl2->tehai->Pon(Sutehai, 1);
							pl2->agent->WaitForKiru = true;
						}
						else {
							pl2->tehai->Daiminkan(Sutehai, 1);
							pl2->Tsumo(yama->MoRinshan());
							pl2->agent->WaitForKiru = true;
						}
					}
					else if (result3 == 1 || result3 == 2) {
						CurrentPlayer = 3;
						if (result1 == 1) {
							pl3->tehai->Pon(Sutehai, 2);
							pl3->agent->WaitForKiru = true;
						}
						else {
							pl3->tehai->Daiminkan(Sutehai, 2);
							pl3->Tsumo(yama->MoRinshan());
							pl3->agent->WaitForKiru = true;
						}
					}
					else if (result1 > 2) {
						int sutenum = Sutehai;
						if (sutenum % 10 == 0) {
							sutenum += 5;
						}
						pl1->agent->WaitForKiru = true;
						CurrentPlayer = 1;
						if (result1 == 3) {
							pl1->tehai->Chi(Sutehai, sutenum++, sutenum += 2);
						}
						else if (result1 == 4) {
							pl1->tehai->Chi(Sutehai, sutenum--, sutenum++);
						}
						else if (result1 == 5) {
							pl1->tehai->Chi(Sutehai, sutenum -= 2, sutenum--);
						}
					}
					Sutehai = -1;
				}
				break;
			}

			UpdateScene = true;
			//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^			等待鳴牌
		}
		else if (WaitingState == 2) {
			//vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv			和牌 / 流局結算


			//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^			和牌 / 流局結算
		}
	//}
}

void Room::NextKyouku()
{
	Init();
	std::vector<std::vector<int>> pp = yama->Peipai();
	pl1->tehai->Peipai(pp.at(0));
	pl2->tehai->Peipai(pp.at(1));
	pl3->tehai->Peipai(pp.at(2));
	pl4->tehai->Peipai(pp.at(3));

	if (Kyouku <= 4) {
		++Kyouku;
	}
	if (Kyouku == 5 ) {
		Kyouku = 1;
		if (Chanfon == TON) {
			Chanfon = NAN;
		}
		else {

		}
	}
	if (Oya <= 4) {
		++Oya;
	}
	if (Oya == 5) {
		Oya = 1;
	}

	CurrentPlayer = Oya;
	WaitingState = 0;

	UpdateScene = true;

	switch (CurrentPlayer) {
	case 1:
		pl1->Tsumo(yama->MoPai());
		break;
	case 2:
		pl2->Tsumo(yama->MoPai());
		break;
	case 3:
		pl3->Tsumo(yama->MoPai());
		break;
	case 4:
		pl4->Tsumo(yama->MoPai());
		break;
	}
}

bool Room::NakuCheck(int pai)
{
	bool result1;
	bool result2;
	bool result3;
	switch (CurrentPlayer)
	{
	case 1:
		result1 = pl2->NakuDekiru(pai);
		result2 = pl3->NakuDekiru(pai);
		result3 = pl4->NakuDekiru(pai);
		if (!result1 && !result2 && !result3) {
			return false;
		}
		else {
			return true;
		}
		break;
	case 2:
		result1 = pl1->NakuDekiru(pai);
		result2 = false;// pl3->NakuDekiru(pai);
		result3 = false;//pl4->NakuDekiru(pai);
		if (!result1 && !result2 && !result3) {
			return false;
		}
		else {
			return true;
		}
		break;
	case 3:
		result1 = pl1->NakuDekiru(pai);
		result2 = false;//pl2->NakuDekiru(pai);
		result3 = false;//pl4->NakuDekiru(pai);
		if (!result1 && !result2 && !result3) {
			return false;
		}
		else {
			return true;
		}
		break;
	case 4:
		result1 = pl1->NakuDekiru(pai);
		result2 = false;//pl2->NakuDekiru(pai);
		result3 = false;//pl3->NakuDekiru(pai);
		if (!result1 && !result2 && !result3) {
			return false;
		}
		else {
			return true;
		}
		break;
	}
}

void Room::NextPlayer()
{
	if (CurrentPlayer == 4) {
		CurrentPlayer = 1;
	}
	else {
		++CurrentPlayer;
	}
}
