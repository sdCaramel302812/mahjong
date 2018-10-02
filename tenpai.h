#pragma once
#include "Yaku.h"
#include "Tehai.h"

Yaku YakuCheck(Tehai *pai, int Chanfon, int Menfon, bool last = false, bool first = false, bool rinshan = false, bool chankan = false, bool ibatsu = false);

bool AgariCheck(Tehai *pai);

std::vector<int> TenpaiCheck(Tehai *pai);

bool ChitoiCheck(Tehai *pai);

bool KokushiCheck(Tehai *pai);




