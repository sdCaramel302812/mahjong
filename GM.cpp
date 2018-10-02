#include "stdafx.h"
#include "GM.h"


GM::GM()
{
}


GM::~GM()
{
}

void GM::NextKyouku()
{
}

void GM::NakuCheck()
{
}

void GM::NextPlayer()
{
	if (CurrentPlayer == 4) {
		CurrentPlayer = 1;
	}
	else {
		++CurrentPlayer;
	}
}

