#pragma once
#include "Yaku.h"
#include "Tehai.h"

Yaku YakuCheck(Tehai *pai, int Chanfon, int Menfon, bool last = false, bool first = false, bool rinshan = false, bool chankan = false, bool ibatsu = false);

bool AgariCheck(Tehai *pai);

/*
if return vector size is 0
then no ten
*/
std::vector<int> TenpaiCheck(Tehai *pai);

std::vector<std::pair<int, std::vector<int>>> RichiCheck(Tehai *pai);

bool ChitoiCheck(Tehai *pai);

bool KokushiCheck(Tehai *pai);




