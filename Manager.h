#pragma once
#include "Layout.h"
#include <vector>
#include "Room.h"
#include <string>
#include <map>

class Manager
{
public:
	Manager();
	~Manager();

	static Room *GameRoom;

	static std::map<std::string, Layout *> LayoutList;

	/*
	Menu
	Game		�C����
	*/
	static std::string CurrentLayout;
};

