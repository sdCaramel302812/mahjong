#include "stdafx.h"
#include "Room.h"
#include "Log.h"

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

	//pl1->agent->IsAI = false;
	pl1->id = 1;
	pl2->id = 2;
	pl3->id = 3;
	pl4->id = 4;

	srand(time(NULL));

	info.Oya = rand() % 4 + 1;
	if (info.Oya < 4) {
		info.FirstOya = info.Oya + 1;
	}
	else {
		info.FirstOya = 1;
	}
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
	current_clock = clock();
	dt = current_clock - last_clock;
	elapse_time += dt;
//	elapse_time_for_pfs += dt;
//	++fps;
	last_clock = current_clock;
//	if (elapse_time_for_pfs > 1000) {
//		cout << "fps : " << fps << endl;
//		elapse_time_for_pfs = 0;
//		fps = 0;
//	}


	//while (!gameover) {
		if (kyoukuover) {
			NextKyouku();
			info.UpdateScene = true;
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

		if (round == 2) {				//解除首巡狀態
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
			std::pair<int, int> hasKan;
			switch (info.CurrentPlayer)
			{
			case 1:
				Sutehai = pl1->Kiru();
				hasKan = pl1->Ankan();
				break;
			case 2:
				Sutehai = pl2->Kiru();
				hasKan = pl2->Ankan();
				break;
			case 3:
				Sutehai = pl3->Kiru();
				hasKan = pl3->Ankan();
				break;
			case 4:
				Sutehai = pl4->Kiru();
				hasKan = pl4->Ankan();
				break;
			}
			if (hasKan.first != 0) {
				MoRinShan = true;
				pl1->Nakasareru(false);
				pl2->Nakasareru(false);
				pl3->Nakasareru(false);
				pl4->Nakasareru(false);
				bool hasChanKan = false;
				switch (info.CurrentPlayer)
				{
				case 1:
					if (pl2->HasChanKan(hasKan.second, hasKan.first)) {
						hasChanKan = true;
					}
					if (pl3->HasChanKan(hasKan.second, hasKan.first)) {
						hasChanKan = true;
					}
					if (pl4->HasChanKan(hasKan.second, hasKan.first)) {
						hasChanKan = true;
					}
					break;
				case 2:
					if (pl1->HasChanKan(hasKan.second, hasKan.first)) {
						hasChanKan = true;
					}
					if (pl3->HasChanKan(hasKan.second, hasKan.first)) {
						hasChanKan = true;
					}
					if (pl4->HasChanKan(hasKan.second, hasKan.first)) {
						hasChanKan = true;
					}
					break;
				case 3:
					if (pl2->HasChanKan(hasKan.second, hasKan.first)) {
						hasChanKan = true;
					}
					if (pl1->HasChanKan(hasKan.second, hasKan.first)) {
						hasChanKan = true;
					}
					if (pl4->HasChanKan(hasKan.second, hasKan.first)) {
						hasChanKan = true;
					}
					break;
				case 4:
					if (pl2->HasChanKan(hasKan.second, hasKan.first)) {
						hasChanKan = true;
					}
					if (pl3->HasChanKan(hasKan.second, hasKan.first)) {
						hasChanKan = true;
					}
					if (pl1->HasChanKan(hasKan.second, hasKan.first)) {
						hasChanKan = true;
					}
					break;
				}
				if (hasChanKan) {
//					cout << "why don't you chan kan" << endl;
					WaitingState = 1;
					return;
				}

				WaitingState = 2;
//				cout << "lets me mo pai" << endl;
				return;
			}
			else if (Sutehai != -1) {
				info.UpdateScene = true;
				bool wait = NakuCheck(Sutehai);
				if (wait) {
					WaitingState = 1;
					//Debug::Log("wait");
					return;
				}
				else {
					Sutehai = -1;
					NextPlayer();
					WaitingState = 2;		//	等待下一家摸牌
				}
			}
			//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^			等待切牌
		}
		if (WaitingState == 1) {
			//vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv			等待鳴牌

			/*
			result1 : 下家
			result2 : 對家
			result3 : 上家
			*/
			int result1;
			int result2;
			int result3;
			info.UpdateScene = true;						//不確定

			/*
			捨牌相關註解以玩家視角為主
			鳴牌相關註解以捨牌方視角為主
			*/
			//vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv			自家捨牌
			switch (info.CurrentPlayer)
			{
			case 1:
				result1 = pl2->Naku(Sutehai);
				result2 = pl3->Naku(Sutehai);
				result3 = pl4->Naku(Sutehai);
				//	有人尚未決定
				if (result1 == -1 || result2 == -1 || result3 == -1) {
//					if (result1 == -1) {
//						cout << "2 no respond" << endl;
//					}
//					if (result2 == -1) {
//						cout << "3 no respond" << endl;
//					}
//					if (result3 == -1) {
//						cout << "4 no respond" << endl;
//					}
					return;
				}//	三家都不鳴牌
				if (result1 == 0 && result2 == 0 && result3 == 0) {
					Sutehai = -1;
					ResetNakuState();
					NextPlayer();
					WaitingState = 2;
				}
				else {
					ResetNakuState();
					pl1->Nakasareru(true);		//被鳴牌 ( 改變牌河 / 消除一發等狀態 )
					pl2->Nakasareru(false);
					pl3->Nakasareru(false);
					pl4->Nakasareru(false);
					WaitingState = 0;
					if (result1 == 6 || result2 == 6 || result3 == 6) {
						return;
					}
					if (result1 == 1 || result1 == 2) {			//	下家碰 / 槓牌
						info.CurrentPlayer = 2;
						if (result1 == 1) {
							pl2->tehai->Pon(Sutehai, 2);
							pl2->agent->WaitForKiru = true;
						}
						else {
							pl2->tehai->Daiminkan(Sutehai, 2);
							MoRinShan = true;
							WaitingState = 2;
						}
					}
					else if (result2 == 1 || result2 == 2) {	//	對家碰 / 槓牌
						info.CurrentPlayer = 3;
						if (result2 == 1) {
							pl3->tehai->Pon(Sutehai, 1);
							pl3->agent->WaitForKiru = true;
						}
						else {
							pl3->tehai->Daiminkan(Sutehai, 1);
							MoRinShan = true;
							WaitingState = 2;
						}
					}
					else if (result3 == 1 || result3 == 2) {	//	上家碰 / 槓牌
						info.CurrentPlayer = 4;
						if (result3 == 1) {
							pl4->tehai->Pon(Sutehai, 0);
							pl4->agent->WaitForKiru = true;
						}
						else {
							pl4->tehai->Daiminkan(Sutehai, 0);
							MoRinShan = true;
							WaitingState = 2;
						}
					}
					else if (result1 > 2) {						//	下家吃牌
						int sutenum = Sutehai;	//	調整赤牌編號
						if (sutenum % 10 == 0) {
							sutenum += 5;
						}
						info.CurrentPlayer = 2;
						pl2->agent->WaitForKiru = true;
						if (result1 == 3) {
							pl2->tehai->Chi(Sutehai, sutenum + 1, sutenum + 2);
						}
						else if (result1 == 4) {
							pl2->tehai->Chi(Sutehai, sutenum - 1, sutenum + 1);
						}
						else if (result1 == 5) {
							pl2->tehai->Chi(Sutehai, sutenum - 2, sutenum - 1);
						}
					}
				}
				Sutehai = -1;								//	位置不能改
				break;
			//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^			自家捨牌
			//vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv			下家捨牌
			case 2:
				result3 = pl1->Naku(Sutehai);
				result1 = pl3->Naku(Sutehai);
				result2 = pl4->Naku(Sutehai);
				//	有人尚未決定
				if (result1 == -1 || result2 == -1 || result3 == -1) {
//					if (result1 == -1) {
//						cout << "3 no respond" << endl;
//					}
//					if (result2 == -1) {
//						cout << "4 no respond" << endl;
//					}
//					if (result3 == -1) {
//						cout << "1 no respond" << endl;
//					}
					return;
				}//	三家都不鳴牌
				if (result1 == 0 && result2 == 0 && result3 == 0) {
					Sutehai = -1;
					ResetNakuState();
					NextPlayer();
					WaitingState = 2;
				}
				else {
					ResetNakuState();
					pl2->Nakasareru(true);		//被鳴牌 ( 改變牌河 / 消除一發等狀態 )
					pl1->Nakasareru(false);
					pl3->Nakasareru(false);
					pl4->Nakasareru(false);
					WaitingState = 0;
					if (result1 == 6 || result2 == 6 || result3 == 6) {
						return;
					}
					if (result1 == 1 || result1 == 2) {			//	下家碰 / 槓牌
						info.CurrentPlayer = 3;
						if (result1 == 1) {
							pl3->tehai->Pon(Sutehai, 2);
							pl3->agent->WaitForKiru = true;
						}
						else {
							pl3->tehai->Daiminkan(Sutehai, 2);
							MoRinShan = true;
							WaitingState = 2;
						}
					}
					else if (result2 == 1 || result2 == 2) {	//	對家碰 / 槓牌
						info.CurrentPlayer = 4;
						if (result2 == 1) {
							pl4->tehai->Pon(Sutehai, 1);
							pl4->agent->WaitForKiru = true;
						}
						else {
							pl4->tehai->Daiminkan(Sutehai, 1);
							MoRinShan = true;
							WaitingState = 2;
						}
					}
					else if (result3 == 1 || result3 == 2) {	//	上家碰 / 槓牌
						info.CurrentPlayer = 1;
						if (result3 == 1) {
							pl1->tehai->Pon(Sutehai, 0);
							pl1->agent->WaitForKiru = true;
						}
						else {
							pl1->tehai->Daiminkan(Sutehai, 0);
							MoRinShan = true;
							WaitingState = 2;
						}
					}
					else if (result1 > 2) {						//	下家吃牌
						int sutenum = Sutehai;		//調整赤牌
						if (sutenum % 10 == 0) {
							sutenum += 5;
						}
						pl3->agent->WaitForKiru = true;
						info.CurrentPlayer = 3;
						if (result1 == 3) {
							pl3->tehai->Chi(Sutehai, sutenum + 1, sutenum + 2);
						}
						else if (result1 == 4) {
							pl3->tehai->Chi(Sutehai, sutenum - 1, sutenum + 1);
						}
						else if (result1 == 5) {
							pl3->tehai->Chi(Sutehai, sutenum - 2, sutenum - 1);
						}
					}
				}
				Sutehai = -1;								//	位置不能改
				break;
			///////////////////////////////////////////			對家捨牌
			case 3:
				result2 = pl1->Naku(Sutehai);
				result3 = pl2->Naku(Sutehai);
				result1 = pl4->Naku(Sutehai);
				//	有人尚未決定
				if (result1 == -1 || result2 == -1 || result3 == -1) {
//					if (result1 == -1) {
//						cout << "4 no respond" << endl;
//					}
//					if (result2 == -1) {
//						cout << "1 no respond" << endl;
//					}
//					if (result3 == -1) {
//						cout << "2 no respond" << endl;
//					}
					return;
				}//	三家都不鳴牌
				if (result1 == 0 && result2 == 0 && result3 == 0) {
					Sutehai = -1;
					ResetNakuState();
					NextPlayer();
					WaitingState = 2;
				}
				else {
					ResetNakuState();
					pl3->Nakasareru(true);		//被鳴牌 ( 改變牌河 / 消除一發等狀態 )
					pl2->Nakasareru(false);
					pl1->Nakasareru(false);
					pl4->Nakasareru(false);
					WaitingState = 0;
					if (result1 == 6 || result2 == 6 || result3 == 6) {
						return;
					}
					if (result1 == 1 || result1 == 2) {			//	下家碰 / 槓牌
						info.CurrentPlayer = 4;
						if (result1 == 1) {
							pl4->tehai->Pon(Sutehai, 2);
							pl4->agent->WaitForKiru = true;
						}
						else {
							pl4->tehai->Daiminkan(Sutehai, 2);
							MoRinShan = true;
							WaitingState = 2;
						}
					}
					else if (result2 == 1 || result2 == 2) {	//	對家碰 / 槓牌
						info.CurrentPlayer = 1;
						if (result2 == 1) {
							pl1->tehai->Pon(Sutehai, 1);
							pl1->agent->WaitForKiru = true;
						}
						else {
							pl1->tehai->Daiminkan(Sutehai, 1);
							MoRinShan = true;
							WaitingState = 2;
						}
					}
					else if (result3 == 1 || result3 == 2) {	//	上家碰 / 槓牌
						info.CurrentPlayer = 2;
						if (result3 == 1) {
							pl2->tehai->Pon(Sutehai, 0);
							pl2->agent->WaitForKiru = true;
						}
						else {
							pl2->tehai->Daiminkan(Sutehai, 0);
							MoRinShan = true;
							WaitingState = 2;
						}
					}
					else if (result1 > 2) {						//	下家吃牌
						int sutenum = Sutehai;		//調整赤牌
						if (sutenum % 10 == 0) {
							sutenum += 5;
						}
						pl4->agent->WaitForKiru = true;
						info.CurrentPlayer = 4;
						if (result1 == 3) {
							pl4->tehai->Chi(Sutehai, sutenum + 1, sutenum + 2);
						}
						else if (result1 == 4) {
							pl4->tehai->Chi(Sutehai, sutenum - 1, sutenum + 1);
						}
						else if (result1 == 5) {
							pl4->tehai->Chi(Sutehai, sutenum - 2, sutenum - 1);
						}
					}
				}
				Sutehai = -1;								//	位置不能改
				break;
			//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^			對家捨牌
			//vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv			上家捨牌
			case 4:
				result1 = pl1->Naku(Sutehai);
				result2 = pl2->Naku(Sutehai);
				result3 = pl3->Naku(Sutehai);
				//	有人尚未決定
				if (result1 == -1 || result2 == -1 || result3 == -1) {
//					if (result1 == -1) {
//						cout << "1 no respond" << endl;
//					}
//					if (result2 == -1) {
//						cout << "2 no respond" << endl;
//					}
//					if (result3 == -1) {
//						cout << "3 no respond" << endl;
//					}
					return;
				}//	三家都不鳴牌
				if (result1 == 0 && result2 == 0 && result3 == 0) {
					Sutehai = -1;
					ResetNakuState();
					NextPlayer();
					WaitingState = 2;
				}
				else {
					ResetNakuState();
					pl4->Nakasareru(true);		//被鳴牌 ( 改變牌河 / 消除一發等狀態 )
					pl2->Nakasareru(false);
					pl3->Nakasareru(false);
					pl1->Nakasareru(false);
					WaitingState = 0;
					if (result1 == 6 || result2 == 6 || result3 == 6) {
						return;
					}
					if (result1 == 1 || result1 == 2) {			//	下家碰 / 槓牌				
						info.CurrentPlayer = 1;
						if (result1 == 1) {
							pl1->tehai->Pon(Sutehai, 2);
							pl1->agent->WaitForKiru = true;
						}
						else {
							pl1->tehai->Daiminkan(Sutehai, 2);
							MoRinShan = true;
							WaitingState = 2;
						}
					}
					else if (result2 == 1 || result2 == 2) {	//	對家碰 / 槓牌
						info.CurrentPlayer = 2;
						if (result1 == 1) {
							pl2->tehai->Pon(Sutehai, 1);
							pl2->agent->WaitForKiru = true;
						}
						else {
							pl2->tehai->Daiminkan(Sutehai, 1);
							MoRinShan = true;
							WaitingState = 2;
						}
					}
					else if (result3 == 1 || result3 == 2) {	//	上家碰 / 槓牌
						info.CurrentPlayer = 3;
						if (result1 == 1) {
							pl3->tehai->Pon(Sutehai, 0);
							pl3->agent->WaitForKiru = true;
						}
						else {
							pl3->tehai->Daiminkan(Sutehai, 0);
							MoRinShan = true;
							WaitingState = 2;
						}
					}
					else if (result1 > 2) {						//	下家吃牌
						int sutenum = Sutehai;		//	調整赤牌
						if (sutenum % 10 == 0) {
							sutenum += 5;
						}
						pl1->agent->WaitForKiru = true;
						info.CurrentPlayer = 1;
						if (result1 == 3) {
							pl1->tehai->Chi(Sutehai, sutenum + 1, sutenum + 2);
						}
						else if (result1 == 4) {
							pl1->tehai->Chi(Sutehai, sutenum - 1, sutenum + 1);
						}
						else if (result1 == 5) {
							pl1->tehai->Chi(Sutehai, sutenum - 2, sutenum - 1);
						}
					}
				}
				Sutehai = -1;								//	位置不能改
				break;
			}

			info.UpdateScene = true;
			//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^			等待鳴牌
		}
		if (WaitingState == 2) {
			//vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv			等待摸牌
			if (WaitForMoPai) {
				WaitForMoPai = false;
				elapse_time = 0;
				return;
			}
			else {
				if (elapse_time > MoPaiWaitingTime) {
					WaitForMoPai = true;
				}
				else {
					return;
				}
			}



			int NewPai;
			if (!MoRinShan) {
				NewPai = yama->MoPai();
			}
			else {
				NewPai = yama->MoRinshan();
				switch (info.CurrentPlayer)
				{
				case 1:
					pl1->RinShan = true;
					break;
				case 2:
					pl2->RinShan = true;
					break;
				case 3:
					pl3->RinShan = true;
					break;
				case 4:
					pl4->RinShan = true;
					break;
				}
				MoRinShan = false;
			}
			--info.RemainPai;
			if (NewPai == -1) {			//	摸到 -1 代表流局
				//kyoukuover = true;
				WaitingState = 3;
				info.UpdateScene = true;
				cout << "流局" << endl;
				Log::LogFile << "流局" << endl;
				return;
			}
			else {
				if (yama->PaiSan.size() <= yama->Haiteihai) {
					pl1->lastPai = true;
					pl2->lastPai = true;
					pl3->lastPai = true;
					pl4->lastPai = true;
				}

				switch (info.CurrentPlayer)
				{
				case 1:
					pl1->Tsumo(NewPai);
					pl1->AnKanTsumoCheck();
					++round;							//	巡數增加
					break;
				case 2:
					pl2->Tsumo(NewPai);
					pl2->AnKanTsumoCheck();
					break;
				case 3:
					pl3->Tsumo(NewPai);
					pl3->AnKanTsumoCheck();
					break;
				case 4:
					pl4->Tsumo(NewPai);
					pl4->AnKanTsumoCheck();
					break;
				}
			}

			info.UpdateScene = true;
			WaitingState = 0;		//回到等待切牌狀態
			//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^			等待摸牌
		}
		if (WaitingState == 3) {
			//vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv			和牌 / 流局結算
			if (WaitForResult) {
				WaitForResult = false;
				elapse_time = 0;

				if (info.RemainPai < 0) {
					bool tenpai[4] = { false };
					if (!pl1->agent->Tenpai.empty()) {
						tenpai[0] = true;
					}
					if (!pl2->agent->Tenpai.empty()) {
						tenpai[1] = true;
					}
					if (!pl3->agent->Tenpai.empty()) {
						tenpai[2] = true;
					}
					if (!pl4->agent->Tenpai.empty()) {
						tenpai[3] = true;
					}
					int point = 0;
					int ninzu = 0;
					for (int i = 0; i < 4; ++i) {
						if (tenpai[i]) {
							++ninzu;
						}
					}
					if (ninzu == 1 || ninzu == 3) {
						point = 1000;
					}
					if (ninzu == 2) {
						point = 1500;
					}
					if (tenpai[0]) {
						if (ninzu == 1) {
							pl1->Point += point * 3;
						}
						else {
							pl1->Point += point;
						}
					}
					else {
						if (ninzu == 1) {
							pl1->Point -= point;
						}
						else {
							pl1->Point -= point * 3;
						}
					}
					if (tenpai[1]) {
						if (ninzu == 1) {
							pl2->Point += point * 3;
						}
						else {
							pl2->Point += point;
						}
					}
					else {
						if (ninzu == 1) {
							pl2->Point -= point;
						}
						else {
							pl2->Point -= point * 3;
						}
					}
					if (tenpai[2]) {
						if (ninzu == 1) {
							pl3->Point += point * 3;
						}
						else {
							pl3->Point += point;
						}
					}
					else {
						if (ninzu == 1) {
							pl3->Point -= point;
						}
						else {
							pl3->Point -= point * 3;
						}
					}
					if (tenpai[3]) {
						if (ninzu == 1) {
							pl4->Point += point * 3;
						}
						else {
							pl4->Point += point;
						}
					}
					else {
						if (ninzu == 1) {
							pl4->Point -= point;
						}
						else {
							pl4->Point -= point * 3;
						}
					}
				}






				return;
			}
			else {
				if (elapse_time > ResultWaitingTime) {
					WaitForResult = true;
				}
				else {
					return;
				}
			}


			kyoukuover = true;
			//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^			和牌 / 流局結算
		}
	//}
}

void Room::NextKyouku()
{
	Init();													//	初始化牌山 / 玩家
	std::vector<std::vector<int>> pp = yama->Peipai();
	//std::vector<std::vector<int>> pp = yama->SpecialPeiPai();
	pl1->tehai->Peipai(pp.at(0));
	pl2->tehai->Peipai(pp.at(1));
	pl3->tehai->Peipai(pp.at(2));
	pl4->tehai->Peipai(pp.at(3));

	info.RemainPai = 70;

	if (info.Kyouku <= 4) {
		++info.Kyouku;
	}
	if (info.Kyouku == 5 ) {
		info.Kyouku = 1;
		if (info.Chanfon == TON) {
			info.Chanfon = NAN;
		}
		else {

		}
	}
	pl1->Chanfon = info.Chanfon;
	pl2->Chanfon = info.Chanfon;
	pl3->Chanfon = info.Chanfon;
	pl4->Chanfon = info.Chanfon;
	if (info.Oya <= 4) {
		++info.Oya;
	}
	if (info.Oya == 5) {
		info.Oya = 1;
	}
	switch (info.Oya)
	{
	case 1:
		pl1->Menfon = TON;
		pl2->Menfon = NAN;
		pl3->Menfon = SHA;
		pl4->Menfon = PEI;
		break;
	case 2:
		pl2->Menfon = TON;
		pl3->Menfon = NAN;
		pl4->Menfon = SHA;
		pl1->Menfon = PEI;
		break;
	case 3:
		pl3->Menfon = TON;
		pl4->Menfon = NAN;
		pl1->Menfon = SHA;
		pl2->Menfon = PEI;
		break;
	case 4:
		pl4->Menfon = TON;
		pl1->Menfon = NAN;
		pl2->Menfon = SHA;
		pl3->Menfon = PEI;
		break;
	}

	info.CurrentPlayer = info.Oya;
	WaitingState = 2;

	info.UpdateScene = true;
}

bool Room::NakuCheck(int pai)
{
	bool result1;
	bool result2;
	bool result3;
	switch (info.CurrentPlayer)
	{
	case 1:
		result1 =  pl2->NakuDekiru(pai, true);
		result2 =  pl3->NakuDekiru(pai, false);
		result3 =  pl4->NakuDekiru(pai, false);
		if (!result1 && !result2 && !result3) {
			return false;
		}
		else {
			if (result1) {
//				cout << "is 2" << endl;
			}
			if (result2) {
//				cout << "is 3" << endl;
			}
			if (result3) {
//				cout << "is 4" << endl;
			}
			return true;
		}
		break;
	case 2:
		result1 = pl1->NakuDekiru(pai, false);
		result2 = pl3->NakuDekiru(pai, true);
		result3 = pl4->NakuDekiru(pai, false);
		if (!result1 && !result2 && !result3) {
			return false;
		}
		else {
			if (result1) {
//				cout << "is 1" << endl;
			}
			if (result2) {
//				cout << "is 3" << endl;
			}
			if (result3) {
//				cout << "is 4" << endl;
			}
			return true;
		}
		break;
	case 3:
		result1 = pl1->NakuDekiru(pai, false);
		result2 = pl2->NakuDekiru(pai, false);
		result3 = pl4->NakuDekiru(pai, true);
		if (!result1 && !result2 && !result3) {
			return false;
		}
		else {
			if (result1) {
//				cout << "is 1" << endl;
			}
			if (result2) {
//				cout << "is 2" << endl;
			}
			if (result3) {
//				cout << "is 4" << endl;
			}
			return true;
		}
		break;
	case 4:
		result1 = pl1->NakuDekiru(pai, true);
		result2 = pl2->NakuDekiru(pai, false);
		result3 = pl3->NakuDekiru(pai, false);
		if (!result1 && !result2 && !result3) {
			return false;
		}
		else {
			if (result1) {
//				cout << "is 1" << endl;
			}
			if (result2) {
//				cout << "is 2" << endl;
			}
			if (result3) {
//				cout << "is 3" << endl;
			}
			return true;
		}
		break;
	}
}

void Room::NextPlayer()
{
	if (info.CurrentPlayer == 4) {
		info.CurrentPlayer = 1;
	}
	else {
		++info.CurrentPlayer;
	}
}

void Room::ResetNakuState()
{
	pl1->NakuState = -1;
	pl2->NakuState = -1;
	pl3->NakuState = -1;
	pl4->NakuState = -1;
}
