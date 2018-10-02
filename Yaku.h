#pragma once
#include <utility>
#include <map>
#include <iostream>
using std::cout;
using std::endl;
using std::pair;

class Yaku
{
public:
	Yaku();
	~Yaku();

	void ShowYaku();

	static void SetTable();
	/*
	若 pair.second 為 :
	0		: 親家自摸
	1		: 榮和
	other	: 子家自摸
	*/
	static pair<int, int> LookupTable(bool oya, bool tsumo, int fu, int han);
	static std::map<std::pair<int, int>, std::pair<int, int>> TsumoTable;
	static std::map<std::pair<int, int>, int> OyaTsumoTable;
	static std::map<std::pair<int, int>, int> RonTable;
	static std::map<std::pair<int, int>, int> OyaRonTable;

	bool agari = false;
	bool oya = false;
	bool tsumo = false;
	int Point = 0;
	int Han = 0;
	int Fu = 20;

	int dora = 0;		//寶牌
	int akadora = 0;	//赤寶牌
	int uradora = 0;	//裏寶牌

	bool Pinhu = false;		//平和
	bool Tanyao = false;	//斷么
	bool Haku = false;		//白
	bool Fa = false;		//發
	bool Chun = false;		//中
	bool Chanfon = false;	//場風
	bool Menfon = false;	//門風
	bool Tsumo = false;		//自摸
	bool Ipeiko = false;	//一杯口
	bool Rinshan = false;	//嶺上開花
	bool Chankan = false;	//搶槓
	bool Haitei = false;	//海底撈月
	bool Houtei = false;	//河底撈魚
	bool RichiW = false;	//雙立直
	bool Richi = false;		//立直
	bool Ibatsu = false;	//一發
	bool Toitoi = false;	//對對和
	bool SanshukuJ = false;	//三色同順
	bool SanshukuK = false;	//三色同刻
	bool Ikki = false;		//一氣通貫
	bool Chanta = false;	//全帶么
	bool Sananko = false;	//三暗刻
	bool Sankantsu = false;	//三槓子
	bool Honrotou = false;	//混老頭
	bool Chitoi = false;	//七對子
	bool Honitsu = false;	//混一色
	bool Ryanpeiko = false;	//兩杯口
	bool Junchan = false;	//純全帶
	bool Shousangen = false;//小三元
	bool Chinitsu = false;	//清一色
	bool Suanko = false;	//四暗刻
	bool DaiSushi = false;	//大四喜
	bool Shousushi = false;	//小四喜
	bool Chinroto = false;	//清老頭
	bool Kokushi = false;	//國士無雙
	bool Sukantsu = false;	//四槓子
	bool Daisangen = false;	//大三元
	bool Tsuiso = false;	//字一色
	bool Ryuiso = false;	//綠一色
	bool Kyuren = false;	//九蓮寶燈
	bool Tenho = false;		//天和
	bool Chiho = false;		//地和
	bool SuankoDanki = false;	//四暗刻單騎
	bool Kokushi13 = false;		//國士無雙十三面聽
	bool Junseikyuren = false;	//純正九蓮寶燈
};

