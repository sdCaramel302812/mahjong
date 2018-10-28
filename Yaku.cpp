#include "stdafx.h"
#include "Yaku.h"
#include "Log.h"

std::map<std::pair<int, int>, std::pair<int, int>> Yaku::TsumoTable;
std::map<std::pair<int, int>, int> Yaku::OyaTsumoTable;
std::map<std::pair<int, int>, int> Yaku::RonTable;
std::map<std::pair<int, int>, int> Yaku::OyaRonTable;

Yaku::Yaku()
{
	agari = false;
	dora = 0;
	akadora = 0;
	uradora = 0;
}


Yaku::~Yaku()
{
}

void Yaku::ShowYaku()
{/*
	if (!agari) {
		return;
	}
	if (!YakuAri) {
		cout << "無役" << endl;
		Log::LogFile << "無役" << endl;
		return;
	}
	pair<int, int>point = LookupTable(oya, tsumo, Fu, Han);
	if (point.second == 0) {
		cout << "親 " << point.first << " all" << endl;
		Log::LogFile << "親 " << point.first << " all" << endl;
	}
	else if (point.second == 1) {
		if (oya) {
			cout << "親 " << point.first << endl;
			Log::LogFile << "親 " << point.first << endl;
		}
		else {
			cout << "子 " << point.first << endl;
			Log::LogFile << "子 " << point.first << endl;
		}
	}
	else {
		cout << "子 " << point.first << " " << point.second << endl;
		Log::LogFile << "子 " << point.first << " " << point.second << endl;
	}

	if (Suanko || DaiSushi || Shousushi || Chinroto || Kokushi || Sukantsu || Daisangen || Tsuiso || Ryuiso || Kyuren || Tenho || Chiho || SuankoDanki || Kokushi13 || Junseikyuren) {
		if (Suanko) {
			cout << "四暗刻" << endl;
			Log::LogFile << "四暗刻" << endl;
		}
		if (DaiSushi) {
			cout << "大四喜" << endl;
			Log::LogFile << "大四喜" << endl;
		}
		if (Shousushi) {
			cout << "小四喜" << endl;
			Log::LogFile << "小四喜" << endl;
		}
		if (Chinroto) {
			cout << "清老頭" << endl;
			Log::LogFile << "清老頭" << endl;
		}
		if (Kokushi) {
			cout << "國士無雙" << endl;
			Log::LogFile << "國士無雙" << endl;
		}
		if (Sukantsu) {
			cout << "四槓子" << endl;
			Log::LogFile << "四槓子" << endl;
		}
		if (Daisangen) {
			cout << "大三元" << endl;
			Log::LogFile << "大三元" << endl;
		}
		if (Tsuiso) {
			cout << "字一色" << endl;
			Log::LogFile << "字一色" << endl;
		}
		if (Ryuiso) {
			cout << "綠一色" << endl;
			Log::LogFile << "綠一色" << endl;
		}
		if (Kyuren) {
			cout << "九蓮寶燈" << endl;
			Log::LogFile << "九蓮寶燈" << endl;
		}
		if (Tenho) {
			cout << "天和" << endl;
			Log::LogFile << "天和" << endl;
		}
		if (Chiho) {
			cout << "地和" << endl;
			Log::LogFile << "地和" << endl;
		}
		if (SuankoDanki) {
			cout << "四暗刻單騎" << endl;
			Log::LogFile << "四暗刻單騎" << endl;
		}
		if (Kokushi13) {
			cout << "國士無雙十三面聽" << endl;
		}
		if (Junseikyuren) {
			cout << "純正九蓮寶燈" << endl;
		}
	}
	else {
		if (Haku) {
			cout << "白" << endl;
			Log::LogFile << "白" << endl;
		}
		if (Fa) {
			cout << "發" << endl;
			Log::LogFile << "發" << endl;
		}
		if (Chun) {
			cout << "中" << endl;
			Log::LogFile << "中" << endl;
		}
		if (Chanfon) {
			cout << "場風" << endl;
			Log::LogFile << "場風" << endl;
		}
		if (Menfon) {
			cout << "門風" << endl;
			Log::LogFile << "門風" << endl;
		}
		if (Tanyao) {
			cout << "斷么" << endl;
			Log::LogFile << "斷么" << endl;
		}
		if (Pinhu) {
			cout << "平和" << endl;
			Log::LogFile << "平和" << endl;
		}
		if (Chinitsu) {
			cout << "清一色" << endl;
			Log::LogFile << "清一色" << endl;
		}
		if (Honitsu) {
			cout << "混一色" << endl;
			Log::LogFile << "混一色" << endl;
		}
		if (SanshukuJ) {
			cout << "三色同順" << endl;
			Log::LogFile << "三色同順" << endl;
		}
		if (Ikki) {
			cout << "一氣通貫" << endl;
			Log::LogFile << "一氣通貫" << endl;
		}
		if (Ipeiko) {
			cout << "一杯口" << endl;
			Log::LogFile << "一杯口" << endl;
		}
		if (Ryanpeiko) {
			cout << "兩杯口" << endl;
			Log::LogFile << "兩杯口" << endl;
		}
		if (Chanta) {
			cout << "全帶么" << endl;
			Log::LogFile << "全帶么" << endl;
		}
		if (Junchan) {
			cout << "純全帶么" << endl;
			Log::LogFile << "純全帶么" << endl;
		}
		if (Toitoi) {
			cout << "對對和" << endl;
			Log::LogFile << "對對和" << endl;
		}
		if (Sananko) {
			cout << "三暗刻" << endl;
			Log::LogFile << "三暗刻" << endl;
		}
		if (Sankantsu) {
			cout << "三槓子" << endl;
			Log::LogFile << "三槓子" << endl;
		}
		if (Honrotou) {
			cout << "混老頭" << endl;
			Log::LogFile << "混老頭" << endl;
		}
		if (SanshukuK) {
			cout << "三色同刻" << endl;
			Log::LogFile << "三色同刻" << endl;
		}
		if (Shousangen) {
			cout << "小三元" << endl;
			Log::LogFile << "小三元" << endl;
		}
		if (Chitoi) {
			cout << "七對子" << endl;
			Log::LogFile << "七對子" << endl;
		}

		if (RichiW) {
			cout << "雙立直" << endl;
			Log::LogFile << "雙立直" << endl;
		}
		if (Richi) {
			cout << "立直" << endl;
			Log::LogFile << "立直" << endl;
		}
		if (Ibatsu) {
			cout << "一發" << endl;
			Log::LogFile << "一發" << endl;
		}
		if (Tsumo) {
			cout << "自摸" << endl;
			Log::LogFile << "自摸" << endl;
		}
		if (Rinshan) {
			cout << "嶺上開花" << endl;
			Log::LogFile << "嶺上開花" << endl;
		}
		if (Chankan) {
			cout << "搶槓" << endl;
			Log::LogFile << "搶槓" << endl;
		}
		if (Haitei) {
			cout << "海底撈月" << endl;
			Log::LogFile << "海底撈月" << endl;
		}
		if (Houtei) {
			cout << "河底撈魚" << endl;
			Log::LogFile << "河底撈魚" << endl;
		}
	}
	if (Han >= 5 || (Han == 4 && Fu >= 40) || Han == 3 && Fu >= 70) {
		if (Han <= 5) {
			cout << Han << "翻 滿貫" << endl;
			Log::LogFile << Han << "翻 滿貫" << endl;
		}
		else if(Han <= 7) {
			cout << Han << "翻 跳滿" << endl;
			Log::LogFile << Han << "翻 跳滿" << endl;
		}
		else if (Han <= 10) {
			cout << Han << "翻 倍滿" << endl;
			Log::LogFile << Han << "翻 倍滿" << endl;
		}
		else if (Han <= 12) {
			cout << Han << "翻 三倍滿" << endl;
			Log::LogFile << Han << "翻 三倍滿" << endl;
		}
		else {
			cout << Han << "翻 役滿" << endl;
			Log::LogFile << Han << "翻 役滿" << endl;
		}
	}
	else {
		cout << Fu << " 符 " << Han << " 翻" << endl;
		Log::LogFile << Fu << " 符 " << Han << " 翻" << endl;
	}*/
}

void Yaku::SetTable()
{
	//子家自摸
	TsumoTable[pair<int, int>(20, 2)] = pair<int, int>(400, 700);
	TsumoTable[pair<int, int>(20, 3)] = pair<int, int>(700, 1300);
	TsumoTable[pair<int, int>(20, 4)] = pair<int, int>(1300, 2600);
	TsumoTable[pair<int, int>(25, 2)] = pair<int, int>(400, 800);
	TsumoTable[pair<int, int>(25, 3)] = pair<int, int>(800, 1600);
	TsumoTable[pair<int, int>(25, 4)] = pair<int, int>(1600, 3200);
	TsumoTable[pair<int, int>(30, 1)] = pair<int, int>(300, 500);
	TsumoTable[pair<int, int>(30, 2)] = pair<int, int>(500, 1000);
	TsumoTable[pair<int, int>(30, 3)] = pair<int, int>(1000, 2000);
	TsumoTable[pair<int, int>(30, 4)] = pair<int, int>(2000, 3900);
	TsumoTable[pair<int, int>(40, 1)] = pair<int, int>(400, 700);
	TsumoTable[pair<int, int>(40, 2)] = pair<int, int>(700, 1300);
	TsumoTable[pair<int, int>(40, 3)] = pair<int, int>(1300, 2600);
	TsumoTable[pair<int, int>(50, 1)] = pair<int, int>(400, 800);
	TsumoTable[pair<int, int>(50, 2)] = pair<int, int>(800, 1600);
	TsumoTable[pair<int, int>(50, 3)] = pair<int, int>(1600, 3200);
	TsumoTable[pair<int, int>(60, 1)] = pair<int, int>(500, 1000);
	TsumoTable[pair<int, int>(60, 2)] = pair<int, int>(1000, 2000);
	TsumoTable[pair<int, int>(60, 3)] = pair<int, int>(2000, 3900);
	TsumoTable[pair<int, int>(70, 1)] = pair<int, int>(600, 1200);
	TsumoTable[pair<int, int>(70, 2)] = pair<int, int>(1200, 2300);
	TsumoTable[pair<int, int>(80, 1)] = pair<int, int>(700, 1300);
	TsumoTable[pair<int, int>(80, 2)] = pair<int, int>(1300, 2600);
	TsumoTable[pair<int, int>(90, 1)] = pair<int, int>(800, 1500);
	TsumoTable[pair<int, int>(90, 2)] = pair<int, int>(1500, 2900);
	TsumoTable[pair<int, int>(100, 1)] = pair<int, int>(800, 1600);
	TsumoTable[pair<int, int>(100, 2)] = pair<int, int>(1600, 3200);
	TsumoTable[pair<int, int>(110, 2)] = pair<int, int>(1800, 3600);
	TsumoTable[pair<int, int>(30, 5)] = pair<int, int>(2000, 4000);
	TsumoTable[pair<int, int>(30, 6)] = pair<int, int>(3000, 6000);
	TsumoTable[pair<int, int>(30, 7)] = pair<int, int>(3000, 6000);
	TsumoTable[pair<int, int>(30, 8)] = pair<int, int>(4000, 8000);
	TsumoTable[pair<int, int>(30, 9)] = pair<int, int>(4000, 8000);
	TsumoTable[pair<int, int>(30, 10)] = pair<int, int>(4000, 8000);
	TsumoTable[pair<int, int>(30, 11)] = pair<int, int>(6000, 12000);
	TsumoTable[pair<int, int>(30, 12)] = pair<int, int>(6000, 12000);
	TsumoTable[pair<int, int>(30, 13)] = pair<int, int>(8000, 16000);

	//子家榮和
	RonTable[pair<int, int>(25, 2)] = 1600;
	RonTable[pair<int, int>(25, 3)] = 3200;
	RonTable[pair<int, int>(25, 4)] = 6400;
	RonTable[pair<int, int>(30, 1)] = 1000;
	RonTable[pair<int, int>(30, 2)] = 2000;
	RonTable[pair<int, int>(30, 3)] = 3900;
	RonTable[pair<int, int>(30, 4)] = 7700;
	RonTable[pair<int, int>(40, 1)] = 1300;
	RonTable[pair<int, int>(40, 2)] = 2600;
	RonTable[pair<int, int>(40, 3)] = 5200;
	RonTable[pair<int, int>(50, 1)] = 1600;
	RonTable[pair<int, int>(50, 2)] = 3200;
	RonTable[pair<int, int>(50, 3)] = 6400;
	RonTable[pair<int, int>(60, 1)] = 2000;
	RonTable[pair<int, int>(60, 2)] = 3900;
	RonTable[pair<int, int>(60, 3)] = 7700;
	RonTable[pair<int, int>(70, 1)] = 2300;
	RonTable[pair<int, int>(70, 2)] = 4500;
	RonTable[pair<int, int>(80, 1)] = 2600;
	RonTable[pair<int, int>(80, 2)] = 5200;
	RonTable[pair<int, int>(90, 1)] = 2900;
	RonTable[pair<int, int>(90, 2)] = 5800;
	RonTable[pair<int, int>(100, 1)] = 3200;
	RonTable[pair<int, int>(100, 2)] = 6400;
	RonTable[pair<int, int>(110, 1)] = 3600;
	RonTable[pair<int, int>(110, 2)] = 7100;
	RonTable[pair<int, int>(30, 5)] = 8000;
	RonTable[pair<int, int>(30, 6)] = 12000;
	RonTable[pair<int, int>(30, 7)] = 12000;
	RonTable[pair<int, int>(30, 8)] = 16000;
	RonTable[pair<int, int>(30, 9)] = 16000;
	RonTable[pair<int, int>(30, 10)] = 16000;
	RonTable[pair<int, int>(30, 11)] = 24000;
	RonTable[pair<int, int>(30, 12)] = 24000;
	RonTable[pair<int, int>(30, 13)] = 32000;

	//親家自摸
	OyaTsumoTable[pair<int, int>(20, 2)] = 700;
	OyaTsumoTable[pair<int, int>(20, 3)] = 1300;
	OyaTsumoTable[pair<int, int>(20, 4)] = 2600;
	OyaTsumoTable[pair<int, int>(25, 2)] = 800;
	OyaTsumoTable[pair<int, int>(25, 3)] = 1600;
	OyaTsumoTable[pair<int, int>(25, 4)] = 3200;
	OyaTsumoTable[pair<int, int>(30, 1)] = 500;
	OyaTsumoTable[pair<int, int>(30, 2)] = 1000;
	OyaTsumoTable[pair<int, int>(30, 3)] = 2000;
	OyaTsumoTable[pair<int, int>(30, 4)] = 3900;
	OyaTsumoTable[pair<int, int>(40, 1)] = 700;
	OyaTsumoTable[pair<int, int>(40, 2)] = 1300;
	OyaTsumoTable[pair<int, int>(40, 3)] = 2600;
	OyaTsumoTable[pair<int, int>(50, 1)] = 800;
	OyaTsumoTable[pair<int, int>(50, 2)] = 1600;
	OyaTsumoTable[pair<int, int>(50, 3)] = 3200;
	OyaTsumoTable[pair<int, int>(60, 1)] = 1000;
	OyaTsumoTable[pair<int, int>(60, 2)] = 2000;
	OyaTsumoTable[pair<int, int>(60, 3)] = 3900;
	OyaTsumoTable[pair<int, int>(70, 1)] = 1200;
	OyaTsumoTable[pair<int, int>(70, 2)] = 2300;
	OyaTsumoTable[pair<int, int>(80, 1)] = 1300;
	OyaTsumoTable[pair<int, int>(80, 2)] = 2600;
	OyaTsumoTable[pair<int, int>(90, 1)] = 1500;
	OyaTsumoTable[pair<int, int>(90, 2)] = 2900;
	OyaTsumoTable[pair<int, int>(100, 1)] = 1600;
	OyaTsumoTable[pair<int, int>(100, 2)] = 3200;
	OyaTsumoTable[pair<int, int>(110, 2)] = 3600;
	OyaTsumoTable[pair<int, int>(30, 5)] = 4000;
	OyaTsumoTable[pair<int, int>(30, 6)] = 6000;
	OyaTsumoTable[pair<int, int>(30, 7)] = 6000;
	OyaTsumoTable[pair<int, int>(30, 8)] = 8000;
	OyaTsumoTable[pair<int, int>(30, 9)] = 8000;
	OyaTsumoTable[pair<int, int>(30, 10)] = 8000;
	OyaTsumoTable[pair<int, int>(30, 11)] = 12000;
	OyaTsumoTable[pair<int, int>(30, 12)] = 12000;
	OyaTsumoTable[pair<int, int>(30, 13)] = 16000;

	//親家榮和
	OyaRonTable[pair<int, int>(25, 2)] = 2400;
	OyaRonTable[pair<int, int>(25, 3)] = 4800;
	OyaRonTable[pair<int, int>(25, 4)] = 9600;
	OyaRonTable[pair<int, int>(30, 1)] = 1500;
	OyaRonTable[pair<int, int>(30, 2)] = 2900;
	OyaRonTable[pair<int, int>(30, 3)] = 5800;
	OyaRonTable[pair<int, int>(30, 4)] = 11600;
	OyaRonTable[pair<int, int>(40, 1)] = 2000;
	OyaRonTable[pair<int, int>(40, 2)] = 3900;
	OyaRonTable[pair<int, int>(40, 3)] = 7700;
	OyaRonTable[pair<int, int>(50, 1)] = 2400;
	OyaRonTable[pair<int, int>(50, 2)] = 4800;
	OyaRonTable[pair<int, int>(50, 3)] = 9600;
	OyaRonTable[pair<int, int>(60, 1)] = 2900;
	OyaRonTable[pair<int, int>(60, 2)] = 5800;
	OyaRonTable[pair<int, int>(60, 3)] = 11600;
	OyaRonTable[pair<int, int>(70, 1)] = 3400;
	OyaRonTable[pair<int, int>(70, 2)] = 6800;
	OyaRonTable[pair<int, int>(80, 1)] = 3900;
	OyaRonTable[pair<int, int>(80, 2)] = 7700;
	OyaRonTable[pair<int, int>(90, 1)] = 4400;
	OyaRonTable[pair<int, int>(90, 2)] = 8700;
	OyaRonTable[pair<int, int>(100, 1)] = 4800;
	OyaRonTable[pair<int, int>(100, 2)] = 9600;
	OyaRonTable[pair<int, int>(110, 1)] = 5300;
	OyaRonTable[pair<int, int>(110, 2)] = 10600;
	OyaRonTable[pair<int, int>(30, 5)] = 12000;
	OyaRonTable[pair<int, int>(30, 6)] = 18000;
	OyaRonTable[pair<int, int>(30, 7)] = 18000;
	OyaRonTable[pair<int, int>(30, 8)] = 24000;
	OyaRonTable[pair<int, int>(30, 9)] = 24000;
	OyaRonTable[pair<int, int>(30, 10)] = 24000;
	OyaRonTable[pair<int, int>(30, 11)] = 36000;
	OyaRonTable[pair<int, int>(30, 12)] = 36000;
	OyaRonTable[pair<int, int>(30, 13)] = 48000;
}

pair<int, int> Yaku::LookupTable(bool oya, bool tsumo, int fu, int han)
{
	if (oya) {
		if (tsumo) {
			if (han >= 5 || (han == 4 && fu >= 40) || han == 3 && fu >= 70) {
				if (han < 5) {
					han = 5;
				}
				return pair<int, int>(OyaTsumoTable[pair<int, int>(30, han)], 0);
			}
			else {
				return pair<int, int>(OyaTsumoTable[pair<int, int>(fu, han)], 0);
			}
		}
		else {
			if (han >= 5 || (han == 4 && fu >= 40) || han == 3 && fu >= 70) {
				if (han < 5) {
					han = 5;
				}
				return pair<int, int>(OyaRonTable[pair<int, int>(30, han)], 1);
			}
			else {
				return pair<int, int>(OyaRonTable[pair<int, int>(fu, han)], 1);
			}
		}
	}
	else {
		if (tsumo) {
			if (han >= 5 || (han == 4 && fu >= 40) || han == 3 && fu >= 70) {
				if (han < 5) {
					han = 5;
				}
				return pair<int, int>(TsumoTable[pair<int, int>(30, han)]);
			}
			else {
				return pair<int, int>(TsumoTable[pair<int, int>(fu, han)]);
			}
		}
		else {
			if (han >= 5 || (han == 4 && fu >= 40) || han == 3 && fu >= 70) {
				if (han < 5) {
					han = 5;
				}
				return pair<int, int>(RonTable[pair<int, int>(30, han)], 1);
			}
			else {
				return pair<int, int>(RonTable[pair<int, int>(fu, han)], 1);
			}
		}
	}
	return pair<int, int>();
}
