#pragma once
#include <string>
#include <iostream>
#include "nstdlib.h"

class Debug
{
public:
	Debug();
	~Debug();

	static bool Active;
	static void Log(TString text);
};

