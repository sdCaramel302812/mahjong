#include "stdafx.h"
#include "Debug.h"

bool Debug::Active = true;

Debug::Debug()
{
}


Debug::~Debug()
{
}

void Debug::Log(TString text)
{
	if (Active) {
		std::cerr << text.wstr2str(text.data()) << std::endl;
	}
}
