﻿#include "stdafx.h"
#include "tenpai.h"

Yaku YakuCheck(Tehai *pai, int Chanfon, int Menfon, bool last, bool first, bool rinshan, bool chankan, bool ibatsu)
{
	if (AgariCheck(pai)) {
		

		Yaku yaku;
		yaku.agari = true;
		yaku.oya = (Menfon == TON ? true : false);
		yaku.tsumo = pai->tsumohai != -1 ? true : false;

		int minko19 = 0;		//么九明刻數量
		int anko19 = 0;			//么九暗刻數量
		int minko28 = 0;		//中張明刻數量
		int anko28 = 0;			//中張暗刻數量
		int minkan19 = 0;		//么九明槓數量
		int ankan19 = 0;		//么九暗槓數量
		int minkan28 = 0;		//中張明槓數量
		int ankan28 = 0;		//中張暗槓數量
		int jantou = -1;		//雀頭
		bool menzen = true;		//是否門清
		bool tanyau = true;		//是否斷么
		bool pinhu = true;
		bool yakunashi = true;	//是否無役
		bool tenpaifu = true;
		bool chitoi = false;
		bool kokushi = false;
		int peiko = 0;
		/*
		預防類似  2s 2s 3s 3s 4s 4s 5s 5s 2m 3m 4m 2p 3p 4p 的牌型出現
		*/
		int ipeikoWithJantou = 0;		//	0 : 無	1 : 餅		2 : 萬		3 : 索
		int lastPai = -1;		//和的那張牌
		if (pai->tsumohai != -1) {
			if (pai->tsumohai == 20) {
				lastPai = 25;
			}
			else if (pai->tsumohai == 10) {
				lastPai = 15;
			}
			else if (pai->tsumohai == 0) {
				lastPai = 5;
			}
			else {
				lastPai = pai->tsumohai;
			}
		}
		else {
			if (pai->ronhai == 20) {
				lastPai = 25;
			}
			else if (pai->ronhai == 10) {
				lastPai = 15;
			}
			else if (pai->ronhai == 0) {
				lastPai = 5;
			}
			else {
				lastPai = pai->ronhai;
			}
		}


		std::vector<std::vector<int>> mentsu;
		Tehai checkpai = *pai;

		if (checkpai.ronhai != -1 && checkpai.tsumohai == -1 && checkpai.agarihai.size() % 3 == 1) {
			checkpai.agarihai.push_back(pai->ronhai);
		}

		//將赤牌轉為一般牌方便檢查
		for (int i = 0; i < checkpai.ankan.size(); ++i) {
			if (checkpai.ankan.at(i) == 25 || checkpai.ankan.at(i) == 15) {
				++yaku.akadora;
			}
			if (checkpai.ankan.at(i) == 5) {
				yaku.akadora += 2;
			}
		}
		for (int i = 0; i < checkpai.agarihai.size(); ++i) {
			if (checkpai.agarihai.at(i) == 0) {
				checkpai.agarihai.at(i) = 5;
				++yaku.akadora;
			}
			if (checkpai.agarihai.at(i) == 10) {
				checkpai.agarihai.at(i) = 15;
				++yaku.akadora;
			}
			if (checkpai.agarihai.at(i) == 20) {
				checkpai.agarihai.at(i) = 25;
				++yaku.akadora;
			}
		}
		for (int i = 0; i < checkpai.chi.size(); ++i) {
			for (int j = 0; j < checkpai.chi.at(i).size(); ++j) {
				if (checkpai.chi.at(i).at(j) == 0) {
					checkpai.chi.at(i).at(j) = 5;
					++yaku.akadora;
				}
				if (checkpai.chi.at(i).at(j) == 10) {
					checkpai.chi.at(i).at(j) = 15;
					++yaku.akadora;
				}
				if (checkpai.chi.at(i).at(j) == 20) {
					checkpai.chi.at(i).at(j) = 25;
					++yaku.akadora;
				}
			}
		}
		for (int i = 0; i < checkpai.pon.size(); ++i) {
			for (int j = 0; j < 3; ++j) {
				if (checkpai.pon.at(i).at(j) == 0) {
					checkpai.pon.at(i).at(j) = 5;
					++yaku.akadora;
				}
				if (checkpai.pon.at(i).at(j) == 10) {
					checkpai.pon.at(i).at(j) = 15;
					++yaku.akadora;
				}
				if (checkpai.pon.at(i).at(j) == 20) {
					checkpai.pon.at(i).at(j) = 25;
					++yaku.akadora;
				}
			}
		}
		for (int i = 0; i < checkpai.minkan.size(); ++i) {
		//	for (int j = 0; j < 4; ++j) {
				if (checkpai.minkan.at(i).at(0) == 0) {
					checkpai.minkan.at(i).at(0) = 5;
					++yaku.akadora;
				}
				if (checkpai.minkan.at(i).at(0) == 10) {
					checkpai.minkan.at(i).at(0) = 15;
					++yaku.akadora;
				}
				if (checkpai.minkan.at(i).at(0) == 20) {
					checkpai.minkan.at(i).at(0) = 25;
					++yaku.akadora;
				}
		//	}
		}
		std::sort(checkpai.agarihai.begin(), checkpai.agarihai.end());

		if (!pai->chi.empty() || !pai->pon.empty() || !pai->minkan.empty()) {
			menzen = false;
		}
		for (int i = 0; i < checkpai.pon.size(); ++i) {
			if (checkpai.pon.at(i).at(0) == 1 || checkpai.pon.at(i).at(0) == 9 || checkpai.pon.at(i).at(0) == 11 || checkpai.pon.at(i).at(0) == 19 || checkpai.pon.at(i).at(0) == 21 || checkpai.pon.at(i).at(0) >= 29) {
				++minko19;
				if (checkpai.pon.at(i).at(0) == Chanfon) {
					yaku.Chanfon = true;
					yaku.YakuAri = true;
					++yaku.Han;
				}
				if (checkpai.pon.at(i).at(0) == Menfon) {
					yaku.Menfon = true;
					yaku.YakuAri = true;
					++yaku.Han;
				}
				if (checkpai.pon.at(i).at(0) == HAKU) {
					yaku.YakuAri = true;
					yaku.Haku = true;
					++yaku.Han;
				}
				if (checkpai.pon.at(i).at(0) == FA) {
					yaku.Fa = true;
					yaku.YakuAri = true;
					++yaku.Han;
				}
				if (checkpai.pon.at(i).at(0) == CHUN) {
					yaku.Chun = true;
					yaku.YakuAri = true;
					++yaku.Han;
				}
				tanyau = false;
			}
			else {
				++minko28;
			}
		}
		for (int i = 0; i < checkpai.minkan.size(); ++i) {
			if (checkpai.minkan.at(i).at(0) == 1 || checkpai.minkan.at(i).at(0) == 9 || checkpai.minkan.at(i).at(0) == 11 || checkpai.minkan.at(i).at(0) == 19 || checkpai.minkan.at(i).at(0) == 21 || checkpai.minkan.at(i).at(0) >= 29) {
				++minkan19;
				if (checkpai.minkan.at(i).at(0) == Chanfon) {
					yaku.Chanfon = true;
					yaku.YakuAri = true;
					++yaku.Han;
				}
				if (checkpai.minkan.at(i).at(0) == Menfon) {
					yaku.Menfon = true;
					yaku.YakuAri = true;
					++yaku.Han;
				}
				if (checkpai.minkan.at(i).at(0) == HAKU) {
					yaku.YakuAri = true;
					yaku.Haku = true;
					++yaku.Han;
				}
				if (checkpai.minkan.at(i).at(0) == FA) {
					yaku.Fa = true;
					yaku.YakuAri = true;
					++yaku.Han;
				}
				if (checkpai.minkan.at(i).at(0) == CHUN) {
					yaku.Chun = true;
					yaku.YakuAri = true;
					++yaku.Han;
				}
				tanyau = false;
			}
			else {
				++minkan28;
			}
		}
		for (int i = 0; i < checkpai.ankan.size(); ++i) {
			if (checkpai.ankan.at(i) == 1 || checkpai.ankan.at(i) == 9 || checkpai.ankan.at(i) == 11 || checkpai.ankan.at(i) == 19 || checkpai.ankan.at(i) == 21 || checkpai.ankan.at(i) >= 29) {
				++ankan19;
				if (checkpai.ankan.at(i) == Chanfon) {
					yaku.Chanfon = true;
					yaku.YakuAri = true;
					++yaku.Han;
				}
				if (checkpai.ankan.at(i) == Menfon) {
					yaku.Menfon = true;
					yaku.YakuAri = true;
					++yaku.Han;
				}
				if (checkpai.ankan.at(i) == HAKU) {
					yaku.YakuAri = true;
					yaku.Haku = true;
					++yaku.Han;
				}
				if (checkpai.ankan.at(i) == FA) {
					yaku.Fa = true;
					yaku.YakuAri = true;
					++yaku.Han;
				}
				if (checkpai.ankan.at(i) == CHUN) {
					yaku.Chun = true;
					yaku.YakuAri = true;
					++yaku.Han;
				}
				tanyau = false;
			}
			else {
				++ankan28;
			}
		}

		

		//確認面子
		if (checkpai.agarihai.size() == 2) {
			jantou = checkpai.agarihai.at(0);
			tenpaifu = true;
			pinhu = false;
		}
		if (!KokushiCheck(&checkpai) && checkpai.agarihai.size() > 2) {
			bool done = false;

			for (int i = 0; i < checkpai.agarihai.size() - 1; ++i) {
				if (done) {
					break;
				}
				//找雀頭
				std::vector<int> nokoripai;		//扣除雀頭後的手牌
				if (checkpai.agarihai.at(i) == checkpai.agarihai.at(i + 1)) {
					jantou = checkpai.agarihai.at(i);
					if (jantou == Chanfon || jantou == Menfon || jantou >= 34) {
						pinhu = false;
					}
					else {
						pinhu = true;
					}
					for (int j = 0; j < checkpai.agarihai.size(); ++j) {
						if (j != i && j != i + 1) {
							nokoripai.push_back(checkpai.agarihai.at(j));
						}
					}
					mentsu.clear();
					//確認面子
					for (int j = (int)nokoripai.size() - 1;;) {
						if (j <= 0) {
							done = true;
							break;
						}
						if (nokoripai.at(j) >= 30) {
							if (j > 2 && nokoripai.at(j) == nokoripai.at(j - 1) && nokoripai.at(j) == nokoripai.at(j - 2)) {
								std::vector<int> men;
								men.push_back(nokoripai.at(j));
								men.push_back(nokoripai.at(j));
								men.push_back(nokoripai.at(j));
								mentsu.push_back(men);
								nokoripai.pop_back();
								nokoripai.pop_back();
								nokoripai.pop_back();
								j -= 3;
								continue;
							}
							else {
								break;
							}
						}
						else if (nokoripai.at(j) > 20) {
							if (j > 2 && nokoripai.at(j) == nokoripai.at(j - 1) && nokoripai.at(j) == nokoripai.at(j - 2)) {
								std::vector<int> men;
								men.push_back(nokoripai.at(j));
								men.push_back(nokoripai.at(j));
								men.push_back(nokoripai.at(j));
								mentsu.push_back(men);
								nokoripai.pop_back();
								nokoripai.pop_back();
								nokoripai.pop_back();
								j -= 3;
								continue;
							}
							else if (j > 2 && nokoripai.at(j) - nokoripai.at(j - 1) == 1 && nokoripai.at(j - 1) - nokoripai.at(j - 2) == 1) {
								std::vector<int> men;
								men.push_back(nokoripai.at(j));
								men.push_back(nokoripai.at(j - 1));
								men.push_back(nokoripai.at(j - 2));
								mentsu.push_back(men);
								nokoripai.pop_back();
								nokoripai.pop_back();
								nokoripai.pop_back();
								j -= 3;
								
								continue;
							}
							else if (j > 3 && nokoripai.at(j - 1) == nokoripai.at(j - 2) && nokoripai.at(j - 1) == nokoripai.at(j - 3)) {
								std::vector<int> men;
								men.push_back(nokoripai.at(j - 1));
								men.push_back(nokoripai.at(j - 1));
								men.push_back(nokoripai.at(j - 1));
								mentsu.push_back(men);
								int temp = nokoripai.at(j);
								nokoripai.pop_back();
								nokoripai.pop_back();
								nokoripai.pop_back();
								nokoripai.pop_back();
								nokoripai.push_back(temp);
								j -= 3;
								
							}
							else if (j > 3 && nokoripai.at(j) - nokoripai.at(j - 1) == 1 && nokoripai.at(j - 1) - nokoripai.at(j - 3) == 1) {
								std::vector<int> men;
								men.push_back(nokoripai.at(j));
								men.push_back(nokoripai.at(j - 1));
								men.push_back(nokoripai.at(j - 3));
								mentsu.push_back(men);
								int temp = nokoripai.at(j - 1);
								nokoripai.pop_back();
								nokoripai.pop_back();
								nokoripai.pop_back();
								nokoripai.pop_back();
								nokoripai.push_back(temp);
								j -= 3;
								
								continue;
							}
							else if (j >= 5 && nokoripai.at(j) - nokoripai.at(j - 2) == 1 && nokoripai.at(j - 2) - nokoripai.at(j - 4) == 1 && nokoripai.at(j - 2) == nokoripai.at(j - 3)) {
								std::vector<int> men;
								men.push_back(nokoripai.at(j));
								men.push_back(nokoripai.at(j - 2));
								men.push_back(nokoripai.at(j - 4));
								mentsu.push_back(men);
								int temp1 = nokoripai.at(j);
								int temp2 = nokoripai.at(j - 2);
								if (j > 10 && nokoripai.at(j) - nokoripai.at(j - 2) == 1 && nokoripai.at(j - 2) - nokoripai.at(j - 4) == 1 && nokoripai.at(j - 4) - nokoripai.at(j - 6) == 1 && nokoripai.at(j - 6) - nokoripai.at(j - 8) == 1 && nokoripai.at(j - 8) - nokoripai.at(j - 10) == 1 && jantou == nokoripai.at(j - 10) - 1) {
									tenpaifu = false;
								}
								for (int k = 0; k < 5; ++k) {
									nokoripai.pop_back();
								}
								nokoripai.push_back(temp2);
								nokoripai.push_back(temp1);
								j -= 3;
								++peiko;
								if (jantou == temp2 - 2) {
									ipeikoWithJantou = 3;
									if (jantou == lastPai || temp2 == lastPai) {
										tenpaifu = false;
									}

								}
								continue;
							}
							else {
								break;
							}
						}
						else if (nokoripai.at(j) > 10) {
							if (j > 2 && nokoripai.at(j) == nokoripai.at(j - 1) && nokoripai.at(j) == nokoripai.at(j - 2)) {
								std::vector<int> men;
								men.push_back(nokoripai.at(j));
								men.push_back(nokoripai.at(j));
								men.push_back(nokoripai.at(j));
								mentsu.push_back(men);
								nokoripai.pop_back();
								nokoripai.pop_back();
								nokoripai.pop_back();
								j -= 3;
								
								continue;
							}
							else if (j > 2 && nokoripai.at(j) - nokoripai.at(j - 1) == 1 && nokoripai.at(j - 1) - nokoripai.at(j - 2) == 1) {
								std::vector<int> men;
								men.push_back(nokoripai.at(j));
								men.push_back(nokoripai.at(j - 1));
								men.push_back(nokoripai.at(j - 2));
								mentsu.push_back(men);
								nokoripai.pop_back();
								nokoripai.pop_back();
								nokoripai.pop_back();
								j -= 3;
								
								continue;
							}
							else if (j > 3 && nokoripai.at(j - 1) == nokoripai.at(j - 2) && nokoripai.at(j - 1) == nokoripai.at(j - 3)) {
								std::vector<int> men;
								men.push_back(nokoripai.at(j - 1));
								men.push_back(nokoripai.at(j - 1));
								men.push_back(nokoripai.at(j - 1));
								mentsu.push_back(men);
								int temp = nokoripai.at(j);
								nokoripai.pop_back();
								nokoripai.pop_back();
								nokoripai.pop_back();
								nokoripai.pop_back();
								nokoripai.push_back(temp);
								j -= 3;
								
							}
							else if (j > 3 && nokoripai.at(j) - nokoripai.at(j - 1) == 1 && nokoripai.at(j - 1) - nokoripai.at(j - 3) == 1) {
								std::vector<int> men;
								men.push_back(nokoripai.at(j));
								men.push_back(nokoripai.at(j - 1));
								men.push_back(nokoripai.at(j - 3));
								mentsu.push_back(men);
								int temp = nokoripai.at(j - 1);
								nokoripai.pop_back();
								nokoripai.pop_back();
								nokoripai.pop_back();
								nokoripai.pop_back();
								nokoripai.push_back(temp);
								j -= 3;
								
								continue;
							}
							else if (j > 5 && nokoripai.at(j) - nokoripai.at(j - 2) == 1 && nokoripai.at(j - 2) - nokoripai.at(j - 4) == 1 && nokoripai.at(j - 2) == nokoripai.at(j - 3)) {
								std::vector<int> men;
								men.push_back(nokoripai.at(j));
								men.push_back(nokoripai.at(j - 2));
								men.push_back(nokoripai.at(j - 4));
								mentsu.push_back(men);
								int temp1 = nokoripai.at(j);
								int temp2 = nokoripai.at(j - 2);
								if (j > 10 && nokoripai.at(j) - nokoripai.at(j - 2) == 1 && nokoripai.at(j - 2) - nokoripai.at(j - 4) == 1 && nokoripai.at(j - 4) - nokoripai.at(j - 6) == 1 && nokoripai.at(j - 6) - nokoripai.at(j - 8) == 1 && nokoripai.at(j - 8) - nokoripai.at(j - 10) == 1 && jantou == nokoripai.at(j - 10) - 1) {
									tenpaifu = false;
								}
								for (int k = 0; k < 5; ++k) {
									nokoripai.pop_back();
								}
								nokoripai.push_back(temp2);
								nokoripai.push_back(temp1);
								j -= 3;
								++peiko;
								if (jantou == temp2 - 2) {
									ipeikoWithJantou = 2;
									if (jantou == lastPai || temp2 == lastPai) {
										tenpaifu = false;
									}
									
								}
								continue;
							}
							else {
								break;
							}
						}
						else {
							if (j > 2 && nokoripai.at(j) == nokoripai.at(j - 1) && nokoripai.at(j) == nokoripai.at(j - 2)) {
								std::vector<int> men;
								men.push_back(nokoripai.at(j));
								men.push_back(nokoripai.at(j));
								men.push_back(nokoripai.at(j));
								mentsu.push_back(men);
								nokoripai.pop_back();
								nokoripai.pop_back();
								nokoripai.pop_back();
								j -= 3;
								
								continue;
							}
							else if (j > 2 && nokoripai.at(j) - nokoripai.at(j - 1) == 1 && nokoripai.at(j - 1) - nokoripai.at(j - 2) == 1) {
								std::vector<int> men;
								men.push_back(nokoripai.at(j));
								men.push_back(nokoripai.at(j - 1));
								men.push_back(nokoripai.at(j - 2));
								mentsu.push_back(men);
								nokoripai.pop_back();
								nokoripai.pop_back();
								nokoripai.pop_back();
								j -= 3;
								
								continue;
							}
							else if (j > 3 && nokoripai.at(j - 1) == nokoripai.at(j - 2) && nokoripai.at(j - 1) == nokoripai.at(j - 3)) {
								std::vector<int> men;
								men.push_back(nokoripai.at(j - 1));
								men.push_back(nokoripai.at(j - 1));
								men.push_back(nokoripai.at(j - 1));
								mentsu.push_back(men);
								int temp = nokoripai.at(j);
								nokoripai.pop_back();
								nokoripai.pop_back();
								nokoripai.pop_back();
								nokoripai.pop_back();
								nokoripai.push_back(temp);
								j -= 3;
								
							}
							else if (j > 3 && nokoripai.at(j) - nokoripai.at(j - 1) == 1 && nokoripai.at(j - 1) - nokoripai.at(j - 3) == 1) {
								std::vector<int> men;
								men.push_back(nokoripai.at(j));
								men.push_back(nokoripai.at(j - 1));
								men.push_back(nokoripai.at(j - 3));
								mentsu.push_back(men);
								int temp = nokoripai.at(j - 1);
								nokoripai.pop_back();
								nokoripai.pop_back();
								nokoripai.pop_back();
								nokoripai.pop_back();
								nokoripai.push_back(temp);
								j -= 3;

								continue;
							}
							else if (j > 5 && nokoripai.at(j) - nokoripai.at(j - 2) == 1 && nokoripai.at(j - 2) - nokoripai.at(j - 4) == 1 && nokoripai.at(j - 2) == nokoripai.at(j - 3)) {
								std::vector<int> men;
								men.push_back(nokoripai.at(j));
								men.push_back(nokoripai.at(j - 2));
								men.push_back(nokoripai.at(j - 4));
								mentsu.push_back(men);
								int temp1 = nokoripai.at(j);
								int temp2 = nokoripai.at(j - 2);
								if (j > 10 && nokoripai.at(j) - nokoripai.at(j - 2) == 1 && nokoripai.at(j - 2) - nokoripai.at(j - 4) == 1 && nokoripai.at(j - 4) - nokoripai.at(j - 6) == 1 && nokoripai.at(j - 6) - nokoripai.at(j - 8) == 1 && nokoripai.at(j - 8) - nokoripai.at(j - 10) == 1 && jantou == nokoripai.at(j - 10) - 1) {
									tenpaifu = false;
								}
								for (int k = 0; k < 5; ++k) {
									nokoripai.pop_back();
								}
								nokoripai.push_back(temp2);
								nokoripai.push_back(temp1);
								j -= 3;
								++peiko;
								if (jantou == temp2 - 2) {
									ipeikoWithJantou = 1;
									if (jantou == lastPai || temp2 == lastPai) {
										tenpaifu = false;
									}

								}
								continue;
							}
							else {
								break;
							}
						}
					}
				}
			}
		}
		//else {
			if (ChitoiCheck(&checkpai)) {
				chitoi = true;
				cout << "there is fucking chitoi" << endl;
			}
			else if (KokushiCheck(&checkpai)) {
				kokushi = true;
			}
		//}

		for (int i = 0; i < mentsu.size(); ++i) {
			//if (pai->tsumohai == jantou || pai->ronhai == jantou) {
			//	pinhu = false;
			//}
			if (mentsu.at(i).at(0) == mentsu.at(i).at(1)) {
				bool anko = true;
				if (pai->ronhai == mentsu.at(i).at(0)) {
					anko = false;
				}
				if (mentsu.at(i).at(0) == 34) {
					yaku.Haku = true;
					yaku.YakuAri = true;
					++yaku.Han;
					if (anko) {
						++anko19;
					}
					else {
						++minko19;
					}
					tanyau = false;
				}
				else if (mentsu.at(i).at(0) == 35) {
					yaku.Fa = true;
					++yaku.Han;
					yaku.YakuAri = true;
					if (anko) {
						++anko19;
					}
					else {
						++minko19;
					}
					tanyau = false;
				}
				else if (mentsu.at(i).at(0) == 36) {
					yaku.Chun = true;
					++yaku.Han;
					yaku.YakuAri = true;
					if (anko) {
						++anko19;
					}
					else {
						++minko19;
					}
					tanyau = false;
				}
				else if (mentsu.at(i).at(0) == Chanfon) {
					yaku.Chanfon = true;
					++yaku.Han;
					if (mentsu.at(i).at(0) == Menfon) {
						yaku.Menfon = true;
						++yaku.Han;
					}
					if (anko) {
						++anko19;
					}
					else {
						++minko19;
					}
					tanyau = false;
				}
				else if (mentsu.at(i).at(0) == Menfon) {
					yaku.Menfon = true;
					++yaku.Han;
					if (anko) {
						++anko19;
					}
					else {
						++minko19; 
					}
					tanyau = false;
				}
				else if (mentsu.at(i).at(0) == 1 || mentsu.at(i).at(0) == 9 || mentsu.at(i).at(0) == 11 || mentsu.at(i).at(0) == 19 || mentsu.at(i).at(0) == 21 || mentsu.at(i).at(0) == 29) {
					if (anko) {
						++anko19;
					}
					else {
						++minko19;
					}
					tanyau = false;
				}
				else {
					if (anko) {
						++anko28;
					}
					else {
						++minko28;
					}
				}
			}
			else {
				//平和判斷
				
				//if (!((mentsu.at(i).at(0) == agarihai && (mentsu.at(i).at(2) != 1 && mentsu.at(i).at(2) != 11 && mentsu.at(i).at(2) != 21)) || (mentsu.at(i).at(2) == agarihai && (mentsu.at(i).at(0) != 9 && mentsu.at(i).at(0) != 19 && mentsu.at(i).at(0) != 29)))) {
				//	tenpaifu = true;
				//}
				if (!pinhu) {
					continue;
				}
				if (!menzen) {
					pinhu = false;
					continue;
				}
				if (anko19 != 0 || ankan19 != 0 || anko28 != 0 || ankan28 != 0) {
					pinhu = false;
					continue;
				}
				//cout << mentsu.at(i).at(0) << " " << mentsu.at(i).at(1) << " " << mentsu.at(i).at(2) << endl;
				if ((mentsu.at(i).at(0) == lastPai && (mentsu.at(i).at(2) != 1 && mentsu.at(i).at(2) != 11 && mentsu.at(i).at(2) != 21)) || (mentsu.at(i).at(2) == lastPai && (mentsu.at(i).at(0) != 9 && mentsu.at(i).at(0) != 19 && mentsu.at(i).at(0) != 29))) {
					tenpaifu = false;
				}
				
			}
		}
		
		//符數計算
		int fu = 20;
		fu += minko28 * 2;
		fu += anko28 * 4;
		fu += minko19 * 4;
		fu += anko19 * 8;
		fu += minkan28 * 8;
		fu += ankan28 * 16;
		fu += minkan19 * 16;
		fu += ankan19 * 32;
		if (jantou == Chanfon) {
			fu += 2;
		}
		if (jantou == Menfon) {
			fu += 2;
		}
		if (jantou >= 34) {
			fu += 2;
		}
		if (pai->tsumohai != -1) {
			fu += 2;
		}
		if (menzen && pai->ronhai != -1) {
			fu += 10;
		}
		fu += tenpaifu * 2;
		if (chitoi) {
			fu = 25;
		}
		if (pinhu && pai->tsumohai != -1) {
			fu = 20;
		}
		else if (pinhu && pai->ronhai != -1) {
			fu = 30;
		}
		else if (fu <= 30) {
			fu = 30;
		}
		else if (fu <= 40) {
			fu = 40;
		}
		else if (fu <= 50) {
			fu = 50;
		}
		else if (fu <= 60) {
			fu = 60;
		}
		else if (fu <= 70) {
			fu = 70;
		}
		else if (fu <= 80) {
			fu = 80;
		}
		else if (fu <= 90) {
			fu = 90;
		}
		else if (fu <= 100) {
			fu = 100;
		}
		else {
			fu = 110;
		}
		yaku.Fu = fu;
		//cout << "crash" << endl;
		//役種確認
		if (yaku.akadora > 0) {
			yaku.Han += yaku.akadora;
		}
		//平和
		if (pinhu && !tenpaifu && !chitoi) {
			yaku.Pinhu = true;
			++yaku.Han;
			yakunashi = false;
		}
		//斷么
		if (minkan19 == 0 && minko19 == 0 && anko19 == 0 && ankan19 == 0) {
			for (int i = 0; i < mentsu.size(); ++i) {
				//if (mentsu.at(i).at(0) != mentsu.at(i).at(1)) {
					if (mentsu.at(i).at(0) == 9 || mentsu.at(i).at(0) == 19 || mentsu.at(i).at(0) == 29 || mentsu.at(i).at(2) == 1 || mentsu.at(i).at(2) == 11 || mentsu.at(i).at(2) == 21 || mentsu.at(i).at(0) >= 30) {
						tanyau = false;
					}
				//}
			}
			if (jantou >= 30) {
				tanyau = false;
			}
			if (tanyau) {
				yaku.Tanyao = true;
				++yaku.Han;
				yakunashi = false;
			}
		}
		//自摸
		if (menzen&&pai->tsumohai != -1) {
			yaku.Tsumo = true;
			++yaku.Han;
			yakunashi = false;
		}
		//嶺上開花
		if (rinshan) {
			yaku.Rinshan = true;
			++yaku.Han;
			yakunashi = false;
		}
		//搶槓
		if (chankan) {
			yaku.Chankan = true;
			++yaku.Han;
			yakunashi = false;
		}
		//海底撈月
		if (last&&pai->tsumohai != -1) {
			yaku.Haitei = true;
			++yaku.Han;
			yakunashi = false;
		}
		//河底撈魚
		if (last&&pai->ronhai != -1) {
			yaku.Houtei = true;
			++yaku.Han;
			yakunashi = false;
		}
		//雙立直
		if (first&&pai->richi) {
			yaku.RichiW = true;
			yaku.Han += 2;
			yakunashi = false;
		}
		//立直
		if (pai->richi && !yaku.RichiW) {
			yaku.Richi = true;
			++yaku.Han;
			yakunashi = false;
		}
		//一發
		if (ibatsu) {
			yaku.Ibatsu = true;
			++yaku.Han;
			yakunashi = false;
		}
		//對對和
		if (ankan19 + ankan28 + anko19 + anko28 + minkan19 + minkan28 + minko19 + minko28 == 4) {
			yaku.Toitoi = true;
			yaku.Han += 2;
			yakunashi = false;
		}
		//三色同順
		{
			int pin[7] = { 0 };
			int sou[7] = { 0 };
			int man[7] = { 0 };
			for (int i = 0; i < checkpai.chi.size(); ++i) {
				int min = 50;
				for (int j = 0; j < 3; ++j) {
					if (min > checkpai.chi.at(i).at(j)) {
						min = checkpai.chi.at(i).at(j);
					}
				}
				if (min > 20) {
					++sou[min - 21];
				}
				else if (min > 10) {
					++man[min - 11];
				}
				else {
					++pin[min - 1];
				}
			}
			for (int i = 0; i < mentsu.size(); ++i) {
				if (mentsu.at(i).at(0) == mentsu.at(i).at(1)) {
					continue;
				}
				if (mentsu.at(i).at(2) > 20) {
					++sou[mentsu.at(i).at(2) - 21];
				}
				else if (mentsu.at(i).at(2) > 10) {
					++man[mentsu.at(i).at(2) - 11];
				}
				else {
					++pin[mentsu.at(i).at(2) - 1];
				}
			}
			if (ipeikoWithJantou != 0) {
				if (ipeikoWithJantou == 1) {
					for (int i = 1; i < 7; ++i) {
						if (pin[i] > 0) {
							++pin[i - 1];
							break;
						}
					}
				}
				else if (ipeikoWithJantou == 2) {
					for (int i = 1; i < 7; ++i) {
						if (man[i] > 0) {
							++man[i - 1];
							break;
						}
					}
				}
				else if (ipeikoWithJantou == 3) {
					for (int i = 1; i < 7; ++i) {
						if (sou[i] > 0) {
							++sou[i - 1];
							break;
						}
					}
				}
			}
			for (int i = 0; i < 7; ++i) {
				if (pin[i] > 0 && man[i] > 0 && sou[i] > 0) {
					yaku.SanshukuJ = true;
					yakunashi = false;
					if (menzen) {
						yaku.Han += 2;
					}
					else {
						++yaku.Han;
					}
					break;
				}
			}
		}
		//三色同刻
		{
			int pin[9] = { 0 };
			int sou[9] = { 0 };
			int man[9] = { 0 };
			for (int i = 0; i < checkpai.pon.size(); ++i) {
				int min = 50;
				min = checkpai.pon.at(i).at(0);
				if (min >= 30) {
					continue;
				}
				if (min > 20) {
					++sou[min - 21];
				}
				else if (min > 10) {
					++man[min - 11];
				}
				else {
					++pin[min - 1];
				}
			}
			for (int i = 0; i < checkpai.minkan.size(); ++i) {
				int min = 50;
				min = checkpai.minkan.at(i).at(0);
				if (min >= 30) {
					continue;
				}
				if (min > 20) {
					++sou[min - 21];
				}
				else if (min > 10) {
					++man[min - 11];
				}
				else {
					++pin[min - 1];
				}
			}
			for (int i = 0; i < checkpai.ankan.size(); ++i) {
				int min = 50;
				min = checkpai.ankan.at(i);
				if (min >= 30) {
					continue;
				}
				if (min > 20) {
					++sou[min - 21];
				}
				else if (min > 10) {
					++man[min - 11];
				}
				else {
					++pin[min - 1];
				}
			}
			for (int i = 0; i < mentsu.size(); ++i) {
				if (mentsu.at(i).at(0) != mentsu.at(i).at(1)) {
					continue;
				}
				if (mentsu.at(i).at(2) >= 30) {
					continue;
				}
				if (mentsu.at(i).at(2) > 20) {
					++sou[mentsu.at(i).at(2) - 21];
				}
				else if (mentsu.at(i).at(2) > 10) {
					++man[mentsu.at(i).at(2) - 11];
				}
				else {
					++pin[mentsu.at(i).at(2) - 1];
				}
			}
			for (int i = 0; i < 9; ++i) {
				if (pin[i] > 0 && man[i] > 0 && sou[i] > 0) {
					yaku.SanshukuK = true;
					yaku.Han += 2;
					yakunashi = false;
					break;
				}
			}
		}
		//一氣通貫
		{
			int pin[3] = { 0 };
			int sou[3] = { 0 };
			int man[3] = { 0 };
			for (int i = 0; i < checkpai.chi.size(); ++i) {
				int min = 50;
				for (int j = 0; j < 3; ++j) {
					if (min > checkpai.chi.at(i).at(j)) {
						min = checkpai.chi.at(i).at(j);
					}
				}
				if (min % 10 == 0) {
					min += 5;
				}
				if (min > 20 && (min - 20) % 3 == 1) {
					++sou[(min - 20) / 3];
				}
				else if (min > 10 && (min - 10) % 3 == 1) {
					++man[(min - 10) / 3];
				}
				else if (min % 3 == 1) {
					++pin[min / 3];
				}
			}
			for (int i = 0; i < mentsu.size(); ++i) {
				if (mentsu.at(i).at(0) == mentsu.at(i).at(1)) {
					continue;
				}
				int smallPai = mentsu.at(i).at(2);
				switch (smallPai)
				{
				case 1:
					++pin[0];
					break;
				case 4:
					++pin[1];
					break;
				case 7:
					++pin[2];
					break;
				case 11:
					++man[0];
					break;
				case 14:
					++man[1];
					break;
				case 17:
					++man[2];
					break;
				case 21:
					++sou[0];
					break;
				case 24:
					++sou[1];
					break;
				case 27:
					++sou[2];
					break;
				}
			}
			if ((pin[0] > 0 && pin[1] > 0 && pin[2] > 0) || (man[0] > 0 && man[1] > 0 && man[2] > 0) || (sou[0] > 0 && sou[1] > 0 && sou[2] > 0)) {
				yaku.Ikki = true;
				yakunashi = false;
				if (menzen) {
					yaku.Han += 2;
				}
				else {
					++yaku.Han;
				}

			}
		}
		//三暗刻
		if (ankan19 + ankan28 + anko19 + anko28 == 3) {
			yaku.Sananko = true;
			yaku.Han += 2;
			yakunashi = false;
		}
		//三槓子
		if (ankan19 + ankan28 + minkan19 + minkan28 == 3) {
			yaku.Sankantsu = true;
			yaku.Han += 2;
			yakunashi = false;
		}
		//兩杯口
		if (peiko == 2) {
			yaku.Ryanpeiko = true;
			yaku.Han += 3;
			yakunashi = false;
		}
		//一杯口
		if (peiko == 1 && !chitoi) {
			yaku.Ipeiko = true;
			++yaku.Han;
			yakunashi = false;
		}
		//七對子
		if (chitoi && peiko != 2) {
			yaku.Chitoi = true;
			yaku.Han += 2;
			yakunashi = false;
		}
		{
			//清一色
			int n = 0;
			bool chin = true;
			bool hon = true;
			int color[14] = { 0 };
			for (int i = 0; i < checkpai.agarihai.size(); ++i) {
				color[n] = checkpai.agarihai.at(i) / 10;
				++n;
			}
			for (int i = 0; i < checkpai.chi.size(); ++i) {
				color[n] = checkpai.chi.at(i).at(0) / 10;
				color[n + 1] = checkpai.chi.at(i).at(0) / 10;
				color[n + 2] = checkpai.chi.at(i).at(0) / 10;
				n += 3;
			}
			for (int i = 0; i < checkpai.pon.size(); ++i) {
				color[n] = checkpai.pon.at(i).at(0) / 10;
				color[n + 1] = checkpai.pon.at(i).at(0) / 10;
				color[n + 2] = checkpai.pon.at(i).at(0) / 10;
				n += 3;
			}
			for (int i = 0; i < checkpai.minkan.size(); ++i) {
				color[n] = checkpai.minkan.at(i).at(0) / 10;
				color[n + 1] = checkpai.minkan.at(i).at(0) / 10;
				color[n + 2] = checkpai.minkan.at(i).at(0) / 10;
				n += 3;
			}
			for (int i = 0; i < checkpai.ankan.size(); ++i) {
				color[n] = checkpai.ankan.at(i) / 10;
				color[n + 1] = checkpai.ankan.at(i) / 10;
				color[n + 2] = checkpai.ankan.at(i) / 10;
				n += 3;
			}
			for (int i = 1; i < 14; ++i) {
				if (color[i] != color[0] || color[0] == 3) {
					chin = false;
					break;
				}
			}
			if (chin) {
				yaku.Chinitsu = true;
				yakunashi = false;
				if (menzen) {
					yaku.Han += 6;
				}
				else {
					yaku.Han += 5;
				}
			}
			//混一色
			int honiro[4] = { 0 };
			for (int i = 1; i < 14; ++i) {
				++honiro[color[i]];
			}
			if ((honiro[0] > 0 && honiro[1] > 0) || (honiro[0] > 0 && honiro[2] > 0) || (honiro[1] > 0 && honiro[2] > 0)) {
				hon = false;
			}
			if (hon && !chin) {
				yaku.Honitsu = true;
				yakunashi = false;
				if (menzen) {
					yaku.Han += 3;
				}
				else {
					yaku.Han += 2;
				}
			}
		}
		//純全帶
		
		//混老頭				//未考慮七對
		if (minkan19 + minko19 + anko19 + ankan19 == 4 && (jantou == 1 || jantou == 9 || jantou == 11 || jantou == 19 || jantou == 21 || jantou >= 29)) {
			yaku.Honrotou = true;
			yaku.Han += 2;
			yakunashi = false;
		}
		//全帶么

		//小三元
		int sangen = 0;
		if (yaku.Haku) {
			++sangen;
		}
		if (yaku.Fa) {
			++sangen;
		}
		if (yaku.Chun) {
			++sangen;
		}
		if (sangen == 2 && jantou >= HAKU) {
			yaku.Shousangen = true;
			yaku.Han += 2;
			yakunashi = false;
		}
		{
			//大四喜
			int fonPai[4] = { 0 };
			int fonNum = 0;
			for (int i = 0; i < checkpai.pon.size(); ++i) {
				if (checkpai.pon.at(i).at(0) == 30) {
					fonPai[0] = 1;
				}
				if (checkpai.pon.at(i).at(0) == 31) {
					fonPai[1] = 1;
				}
				if (checkpai.pon.at(i).at(0) == 32) {
					fonPai[2] = 1;
				}
				if (checkpai.pon.at(i).at(0) == 33) {
					fonPai[3] = 1;
				}
			}
			for (int i = 0; i < checkpai.minkan.size(); ++i) {
				if (checkpai.minkan.at(i).at(0) == 30) {
					fonPai[0] = 1;
				}
				if (checkpai.minkan.at(i).at(0) == 31) {
					fonPai[1] = 1;
				}
				if (checkpai.minkan.at(i).at(0) == 32) {
					fonPai[2] = 1;
				}
				if (checkpai.minkan.at(i).at(0) == 33) {
					fonPai[3] = 1;
				}
			}
			for (int i = 0; i < checkpai.ankan.size(); ++i) {
				if (checkpai.ankan.at(i) == 30) {
					fonPai[0] = 1;
				}
				if (checkpai.ankan.at(i) == 31) {
					fonPai[1] = 1;
				}
				if (checkpai.ankan.at(i) == 32) {
					fonPai[2] = 1;
				}
				if (checkpai.ankan.at(i) == 33) {
					fonPai[3] = 1;
				}
			}
			for (int i = 0; i < mentsu.size(); ++i) {
				if (mentsu.at(i).at(0) == 30) {
					fonPai[0] = 1;
				}
				if (mentsu.at(i).at(0) == 31) {
					fonPai[1] = 1;
				}
				if (mentsu.at(i).at(0) == 32) {
					fonPai[2] = 1;
				}
				if (mentsu.at(i).at(0) == 33) {
					fonPai[3] = 1;
				}
			}
			for (int i = 0; i < 4; ++i) {
				fonNum += fonPai[i];
			}
			if (fonNum == 4) {
				yaku.DaiSushi = true;
				yaku.Han = 13;
				yakunashi = false;
			}
			//小四喜
			if (fonNum == 3) {
				for (int i = 0; i < 4; ++i) {
					if (fonPai[i] == 0 && jantou - 30 == i) {
						yaku.Shousushi = true;
						yaku.Han = 13;
						yakunashi = false;
					}
				}
			}
		}
		//清老頭

		//四槓子
		if (ankan19 + ankan28 + minkan19 + minkan28 == 4) {
			yaku.Sukantsu = true;
			yaku.Han = 13;
			yakunashi = false;
		}
		//大三元
		if (sangen == 3) {
			yaku.Daisangen = true;
			yaku.Han = 13;
			yakunashi = false;
		}
		//字一色

		//綠一色

		//天和
		if (first && !pai->richi&&Menfon == TON) {
			yaku.Tenho = true;
			yaku.Han = 13;
			yakunashi = false;
		}
		//地和
		if (first && !pai->richi&&Menfon != TON) {
			yaku.Tenho = true;
			yaku.Han = 13;
			yakunashi = false;
		}
		//四暗刻單騎

		//四暗刻
		if (ankan19 + ankan28 + anko19 + anko28 == 4) {
			yaku.Suanko = true;
			yaku.Han = 13;
			yakunashi = false;
		}
		//國士無雙十三面聽

		//國士無雙
		if (kokushi) {
			yaku.Kokushi = true;
			yaku.Han = 13;
			yakunashi = false;
		}
		{
			//純正九蓮寶燈
			bool kyu = false;
			bool junsei = false;
			int k[9] = { 0 };
			int ahai = -1;
			if (checkpai.tsumohai != -1) {
				ahai = checkpai.tsumohai;
			}
			else{
				ahai = checkpai.ronhai;
			}
			if (menzen && yaku.Chinitsu) {
				kyu = true;
				for (int i = 0; i < checkpai.agarihai.size(); ++i) {
					int s = checkpai.agarihai.at(i) % 10;
					++k[s - 1];
				}
				for (int i = 0; i < 9; ++i) {
					if (i == 0 || i == 8) {
						if (k[i] < 3) {
							kyu = false;
						}
					}
					else{
						if (k[i] < 1) {
							kyu = false;
						}
					}
				}
			}
			if (kyu) {
				if (ahai % 10 == 1 || ahai % 10 == 9) {
					if ((ahai % 10 == 1 && k[0] == 4) || (ahai % 10 == 9 && k[8] == 4)) {
						junsei = true;
					}
				}
				else {
					if (k[ahai % 10 - 1] == 2) {
						junsei = true;
					}
				}
			}
			if (kyu&&junsei) {
				yaku.Junseikyuren = true;
				yaku.Han = 13;
			}
			//九蓮寶燈
			if (kyu && !junsei) {
				yaku.Kyuren = true;
				yaku.Han = 13;
				yakunashi = false;
			}

		}

		
		yaku.YakuAri = !yakunashi;
		return yaku;
	}
	

	return Yaku();
}

bool AgariCheck(Tehai *pai)
{
	
	Tehai checkpai = *pai;
	if (checkpai.ronhai != -1 && checkpai.tsumohai == -1 && checkpai.agarihai.size() % 3 == 2) {
	//	checkpai.agarihai.back() = pai->ronhai;
	}
	if (checkpai.ronhai != -1 && checkpai.tsumohai == -1 && checkpai.agarihai.size() % 3 == 1) {
		checkpai.agarihai.push_back(pai->ronhai);
	}
	if (checkpai.agarihai.size() % 3 != 2) {
		return false;
	}
	if (checkpai.ronhai == -1 && checkpai.tsumohai == -1) {
		return false;
	}

	//將赤牌轉為一般牌方便檢查
	for (int i = 0; i < checkpai.agarihai.size(); ++i) {
		if (checkpai.agarihai.at(i) == 0) {
			checkpai.agarihai.at(i) = 5;
		}
		if (checkpai.agarihai.at(i) == 10) {
			checkpai.agarihai.at(i) = 15;
		}
		if (checkpai.agarihai.at(i) == 20) {
			checkpai.agarihai.at(i) = 25;
		}
	}
	std::sort(checkpai.agarihai.begin(), checkpai.agarihai.end());


	if (ChitoiCheck(&checkpai)) {
		return true;
	}
	if (KokushiCheck(&checkpai)) {
		return true;
	}

	bool agari = false;

	if (checkpai.agarihai.size() < 2) {
		return false;
	}
	if (checkpai.agarihai.size() == 2) {
		if (checkpai.agarihai.at(0) == checkpai.agarihai.at(1)) {
			return true;
		}
		else {
			return false;
		}
	}
	
	for (int i = 0; i < (int)checkpai.agarihai.size() - 1; ++i) {
		//cout << "size" << checkpai.agarihai.size() << endl;
		//找雀頭
		if (agari) {
			break;
		}
		std::vector<int> nokoripai;		//扣除雀頭後的手牌
		if (checkpai.agarihai.at(i) == checkpai.agarihai.at(i + 1)) {
			
			for (int j = 0; j < checkpai.agarihai.size(); ++j) {
				if (j != i && j != i + 1) {
					nokoripai.push_back(checkpai.agarihai.at(j));
				}
			}

			//確認面子
			int size = nokoripai.size();
			for (int j = size - 1;;) {
				if (j <= 0) {
					agari = true;
					break;
				}
				if (nokoripai.at(j) >= 30) {
					//	ton	ton	ton
					if (nokoripai.at(j) == nokoripai.at(j - 1) && nokoripai.at(j) == nokoripai.at(j - 2)) {
						nokoripai.pop_back();
						nokoripai.pop_back();
						nokoripai.pop_back();
						j -= 3;
						continue;
					}
					else {
						break;
					}
				}
				else if (nokoripai.at(j) >= 20) {
					//	3s	3s	3s
					if (nokoripai.at(j) == nokoripai.at(j - 1) && nokoripai.at(j) == nokoripai.at(j - 2)) {
						nokoripai.pop_back();
						nokoripai.pop_back();
						nokoripai.pop_back();
						j -= 3;
						continue;
					}//	3s	4s	5s
					else if (nokoripai.at(j) - nokoripai.at(j - 1) == 1 && nokoripai.at(j - 1) - nokoripai.at(j - 2) == 1) {
						nokoripai.pop_back();
						nokoripai.pop_back();
						nokoripai.pop_back();
						j -= 3;
						continue;
					}//	3s	4s	4s	4s	4s	5s
					else if (j >= 3 && nokoripai.at(j - 1) == nokoripai.at(j - 2) && nokoripai.at(j - 1) == nokoripai.at(j - 3)) {
						int temp = nokoripai.at(j);
						nokoripai.pop_back();
						nokoripai.pop_back();
						nokoripai.pop_back();
						nokoripai.pop_back();
						nokoripai.push_back(temp);
						j -= 3;
						continue;
					}//	3s	4s	4s	5s	5s	6s
					else if (j >= 3 && nokoripai.at(j) - nokoripai.at(j - 1) == 1 && nokoripai.at(j - 1) - nokoripai.at(j - 3) == 1) {
						int temp = nokoripai.at(j - 1);
						nokoripai.pop_back();
						nokoripai.pop_back();
						nokoripai.pop_back();
						nokoripai.pop_back();
						nokoripai.push_back(temp);
						j -= 3;
						continue;
					}//	3s	3s	4s	4s	5s	5s
					else if (j >= 5 && nokoripai.at(j) - nokoripai.at(j - 2) == 1 && nokoripai.at(j - 2) - nokoripai.at(j - 4) == 1 && nokoripai.at(j - 2) == nokoripai.at(j - 3)) {
						int temp1 = nokoripai.at(j);
						int temp2 = nokoripai.at(j - 2);
						for (int k = 0; k < 5; ++k) {
							nokoripai.pop_back();
						}
						nokoripai.push_back(temp2);
						nokoripai.push_back(temp1);
						j -= 3;
					}
					else {
						break;
					}
				}
				else if (nokoripai.at(j) >= 10) {
					//	3m	3m	3m
					if (nokoripai.at(j) == nokoripai.at(j - 1) && nokoripai.at(j) == nokoripai.at(j - 2)) {
						nokoripai.pop_back();
						nokoripai.pop_back();
						nokoripai.pop_back();
						j -= 3;
						continue;
					}
					//	2m	3m	4m
					else if (nokoripai.at(j) - nokoripai.at(j - 1) == 1 && nokoripai.at(j - 1) - nokoripai.at(j - 2) == 1) {
						nokoripai.pop_back();
						nokoripai.pop_back();
						nokoripai.pop_back();
						j -= 3;
						continue;
					}
					//	2m	3m	3m	3m	3m	4m
					else if (j >= 3 && nokoripai.at(j - 1) == nokoripai.at(j - 2) && nokoripai.at(j - 1) == nokoripai.at(j - 3)) {
						int temp = nokoripai.at(j);
						nokoripai.pop_back();
						nokoripai.pop_back();
						nokoripai.pop_back();
						nokoripai.pop_back();
						nokoripai.push_back(temp);
						j -= 3;
					}
					//	2m	3m	3m	4m	4m	5m
					else if (j >= 3 && nokoripai.at(j) - nokoripai.at(j - 1) == 1 && nokoripai.at(j - 1) - nokoripai.at(j - 3) == 1) {
						int temp = nokoripai.at(j - 1);
						nokoripai.pop_back();
						nokoripai.pop_back();
						nokoripai.pop_back();
						nokoripai.pop_back();
						nokoripai.push_back(temp);
						j -= 3;
						continue;
					}
					//	2m	2m	3m	3m	4m	4m
					else if (j >= 5 && nokoripai.at(j) - nokoripai.at(j - 2) == 1 && nokoripai.at(j - 2) - nokoripai.at(j - 4) == 1 && nokoripai.at(j - 2) == nokoripai.at(j - 3)) {
						int temp1 = nokoripai.at(j);
						int temp2 = nokoripai.at(j - 2);
						for (int k = 0; k < 5; ++k) {
							nokoripai.pop_back();
						}
						nokoripai.push_back(temp2);
						nokoripai.push_back(temp1);
						j -= 3;
					}
					else {
						break;
					}
				}
				else {
					if (nokoripai.at(j) == nokoripai.at(j - 1) && nokoripai.at(j) == nokoripai.at(j - 2)) {
						nokoripai.pop_back();
						nokoripai.pop_back();
						nokoripai.pop_back();
						j -= 3;
						continue;
					}
					else if (nokoripai.at(j) - nokoripai.at(j - 1) == 1 && nokoripai.at(j - 1) - nokoripai.at(j - 2) == 1) {
						nokoripai.pop_back();
						nokoripai.pop_back();
						nokoripai.pop_back();
						j -= 3;
						continue;
					}
					else if (j >= 3 && nokoripai.at(j - 1) == nokoripai.at(j - 2) && nokoripai.at(j - 1) == nokoripai.at(j - 3)) {
						int temp = nokoripai.at(j);
						nokoripai.pop_back();
						nokoripai.pop_back();
						nokoripai.pop_back();
						nokoripai.pop_back();
						nokoripai.push_back(temp);
						j -= 3;
					}
					else if (j >= 3 && nokoripai.at(j) - nokoripai.at(j - 1) == 1 && nokoripai.at(j - 1) - nokoripai.at(j - 3) == 1) {
						int temp = nokoripai.at(j - 1);
						nokoripai.pop_back();
						nokoripai.pop_back();
						nokoripai.pop_back();
						nokoripai.pop_back();
						nokoripai.push_back(temp);
						j -= 3;
						continue;
					}
					else if (j >= 5 && nokoripai.at(j) - nokoripai.at(j - 2) == 1 && nokoripai.at(j - 2) - nokoripai.at(j - 4) == 1 && nokoripai.at(j - 2) == nokoripai.at(j - 3)) {
						int temp1 = nokoripai.at(j);
						int temp2 = nokoripai.at(j - 2);
						for (int k = 0; k < 5; ++k) {
							nokoripai.pop_back();
						}
						nokoripai.push_back(temp2);
						nokoripai.push_back(temp1);
						j -= 3;
					}
					else {
						break;
					}
				}
				
			}
		}

	}


	return agari;
}

std::vector<int> TenpaiCheck(Tehai *pai)
{
	Tehai checkpai = *pai;

	//將赤牌轉為一般牌方便檢查
	for (int i = 0; i < checkpai.agarihai.size(); ++i) {
		if (checkpai.agarihai.at(i) == 0) {
			checkpai.agarihai.at(i) = 5;
		}
		if (checkpai.agarihai.at(i) == 10) {
			checkpai.agarihai.at(i) = 15;
		}
		if (checkpai.agarihai.at(i) == 20) {
			checkpai.agarihai.at(i) = 25;
		}
	}
	std::sort(checkpai.agarihai.begin(), checkpai.agarihai.end());

	return std::vector<int>();
}

bool ChitoiCheck(Tehai *pai)
{
	if (pai->agarihai.size() != 14) {
		return false;
	}
	for (int i = 0; i < pai->agarihai.size(); i += 2) {
		if (pai->agarihai.at(i) != pai->agarihai.at(i + 1)) {
			return false;
		}
		if (i < 10) {
			if (pai->agarihai.at(i) == pai->agarihai.at(i + 2)) {
				return false;
			}
		}
	}
	return true;
}

bool KokushiCheck(Tehai *pai)
{
	if (pai->agarihai.size() != 14) {
		return false;
	}
	bool p1 = false;
	bool p9 = false;
	bool m1 = false;
	bool m9 = false;
	bool s1 = false;
	bool s9 = false;
	bool t = false;
	bool n = false;
	bool s = false;
	bool p = false;
	bool h = false;
	bool f = false;
	bool c = false;
	for (int i = 0; i < 14; ++i) {
		if (pai->agarihai.at(i) == 1) {
			p1 = true;
		}
		else if (pai->agarihai.at(i) == 9) {
			p9 = true;
		}
		else if (pai->agarihai.at(i) == 11) {
			m1 = true;
		}
		else if (pai->agarihai.at(i) == 19) {
			m9 = true;
		}
		else if (pai->agarihai.at(i) == 21) {
			s1 = true;
		}
		else if (pai->agarihai.at(i) == 29) {
			s9 = true;
		}
		else if (pai->agarihai.at(i) == 30) {
			t = true;
		}
		else if (pai->agarihai.at(i) == 31) {
			n = true;
		}
		else if (pai->agarihai.at(i) == 32) {
			s = true;
		}
		else if (pai->agarihai.at(i) == 33) {
			p = true;
		}
		else if (pai->agarihai.at(i) == 34) {
			h = true;
		}
		else if (pai->agarihai.at(i) == 35) {
			f = true;
		}
		else if (pai->agarihai.at(i) == 36) {
			c = true;
		}
		else {
			return false;
		}
	}
	if (p1 && p9 && m1 && m9 && s1 && s9 && t && n  && s && p && h && f && c) {
		return true;
	}
	else {
		return false;
	}
}
