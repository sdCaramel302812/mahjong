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
}

void Room::Play()
{
	//while (!gameover) {
		if (kyoukuover) {
			NextKyouku();
			kyoukuover = false;
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
				bool wait = NakuCheck(Sutehai);
				if (wait) {
					WaitingState = 1;
				}
				else {
					Sutehai = -1;
					NextPlayer();
					switch (CurrentPlayer)
					{
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
			}
		}
		else if (WaitingState == 1) {
			int result1;
			int result2;
			int result3;
			switch (CurrentPlayer)
			{
			case 1:
				result1 = pl2->Naku();
				result2 = pl3->Naku();
				result3 = pl4->Naku();
				if (result1 == -1 || result2 == -1 || result3 == -1) {
					return;
				}
				if (result1 == 0 && result2 == 0 && result3 == 0) {
					Sutehai = -1;
					NextPlayer();
					switch (CurrentPlayer)
					{
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
				else {
					pl1->Nakasareru();
					WaitingState = 0;
					if (result1 == 1 || result1 == 2) {
						CurrentPlayer = 2;
						if (result1 == 1) {
							pl2->tehai->Pon(Sutehai, 0);
						}
						else {
							pl2->tehai->Daiminkan(Sutehai, 0);
						}
					}
					else if (result2 == 1 || result2 == 2) {
						CurrentPlayer = 3;
						if (result1 == 1) {
							pl3->tehai->Pon(Sutehai, 1);
						}
						else {
							pl3->tehai->Daiminkan(Sutehai, 1);
						}
					}
					else if (result3 == 1 || result3 == 2) {
						CurrentPlayer = 4;
						if (result1 == 1) {
							pl4->tehai->Pon(Sutehai, 2);
						}
						else {
							pl4->tehai->Daiminkan(Sutehai, 2);
						}
					}
					else if (result1 > 2) {
						int sutenum = Sutehai;
						if (sutenum % 10 == 0) {
							sutenum += 5;
						}
						CurrentPlayer = 2;
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
			case 2:
				result3 = pl1->Naku();
				result1 = pl3->Naku();
				result2 = pl4->Naku();
				if (result1 == -1 || result2 == -1 || result3 == -1) {
					return;
				}
				if (result1 == 0 && result2 == 0 && result3 == 0) {
					Sutehai = -1;
					NextPlayer();
					switch (CurrentPlayer)
					{
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
				else {
					pl2->Nakasareru();
					WaitingState = 0;
					if (result1 == 1 || result1 == 2) {
						CurrentPlayer = 3;
						if (result1 == 1) {
							pl3->tehai->Pon(Sutehai, 0);
						}
						else {
							pl3->tehai->Daiminkan(Sutehai, 0);
						}
					}
					else if (result2 == 1 || result2 == 2) {
						CurrentPlayer = 4;
						if (result1 == 1) {
							pl4->tehai->Pon(Sutehai, 1);
						}
						else {
							pl4->tehai->Daiminkan(Sutehai, 1);
						}
					}
					else if (result3 == 1 || result3 == 2) {
						CurrentPlayer = 1;
						if (result1 == 1) {
							pl1->tehai->Pon(Sutehai, 2);
						}
						else {
							pl1->tehai->Daiminkan(Sutehai, 2);
						}
					}
					else if (result1 > 2) {
						int sutenum = Sutehai;
						if (sutenum % 10 == 0) {
							sutenum += 5;
						}
						CurrentPlayer = 3;
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
			case 3:
				result2 = pl1->Naku();
				result3 = pl2->Naku();
				result1 = pl4->Naku();
				if (result1 == -1 || result2 == -1 || result3 == -1) {
					return;
				}
				if (result1 == 0 && result2 == 0 && result3 == 0) {
					Sutehai = -1;
					NextPlayer();
					switch (CurrentPlayer)
					{
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
				else {
					pl3->Nakasareru();
					WaitingState = 0;
					if (result1 == 1 || result1 == 2) {
						CurrentPlayer = 4;
						if (result1 == 1) {
							pl4->tehai->Pon(Sutehai, 0);
						}
						else {
							pl4->tehai->Daiminkan(Sutehai, 0);
						}
					}
					else if (result2 == 1 || result2 == 2) {
						CurrentPlayer = 1;
						if (result1 == 1) {
							pl1->tehai->Pon(Sutehai, 1);
						}
						else {
							pl1->tehai->Daiminkan(Sutehai, 1);
						}
					}
					else if (result3 == 1 || result3 == 2) {
						CurrentPlayer = 2;
						if (result1 == 1) {
							pl2->tehai->Pon(Sutehai, 2);
						}
						else {
							pl2->tehai->Daiminkan(Sutehai, 2);
						}
					}
					else if (result1 > 2) {
						int sutenum = Sutehai;
						if (sutenum % 10 == 0) {
							sutenum += 5;
						}
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
			case 4:
				result1 = pl1->Naku();
				result2 = pl2->Naku();
				result3 = pl3->Naku();
				if (result1 == -1 || result2 == -1 || result3 == -1) {
					return;
				}
				if (result1 == 0 && result2 == 0 && result3 == 0) {
					Sutehai = -1;
					NextPlayer();
					switch (CurrentPlayer)
					{
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
				else {
					pl4->Nakasareru();
					WaitingState = 0;
					if (result1 == 1 || result1 == 2) {
						CurrentPlayer = 1;
						if (result1 == 1) {
							pl1->tehai->Pon(Sutehai, 0);
						}
						else {
							pl1->tehai->Daiminkan(Sutehai, 0);
						}
					}
					else if (result2 == 1 || result2 == 2) {
						CurrentPlayer = 2;
						if (result1 == 1) {
							pl2->tehai->Pon(Sutehai, 1);
						}
						else {
							pl2->tehai->Daiminkan(Sutehai, 1);
						}
					}
					else if (result3 == 1 || result3 == 2) {
						CurrentPlayer = 3;
						if (result1 == 1) {
							pl3->tehai->Pon(Sutehai, 2);
						}
						else {
							pl3->tehai->Daiminkan(Sutehai, 2);
						}
					}
					else if (result1 > 2) {
						int sutenum = Sutehai;
						if (sutenum % 10 == 0) {
							sutenum += 5;
						}
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
		}
	//}
}

void Room::NextKyouku()
{
	yama->Init(rule->Aka);
	std::vector<std::vector<int>> pp = yama->Peipai();
	pl1->tehai->Peipai(pp.at(0));
	pl2->tehai->Peipai(pp.at(1));
	pl3->tehai->Peipai(pp.at(2));
	pl4->tehai->Peipai(pp.at(3));

	
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
		if (result1 && result2 && result3) {
			return false;
		}
		else {
			return true;
		}
		break;
	case 2:
		result1 = pl1->NakuDekiru(pai);
		result2 = pl3->NakuDekiru(pai);
		result3 = pl4->NakuDekiru(pai);
		if (result1 && result2 && result3) {
			return false;
		}
		else {
			return true;
		}
			break;
	case 3:
		result1 = pl1->NakuDekiru(pai);
		result2 = pl2->NakuDekiru(pai);
		result3 = pl4->NakuDekiru(pai);
		if (result1 && result2 && result3) {
			return false;
		}
		else {
			return true;
		}
		break;
	case 4:
		result1 = pl1->NakuDekiru(pai);
		result2 = pl2->NakuDekiru(pai);
		result3 = pl3->NakuDekiru(pai);
		if (result1 && result2 && result3) {
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
