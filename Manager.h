#pragma once
#include "Layout.h"
#include <vector>
#include "Room.h"


class Manager
{
public:
	Manager();
	~Manager();

	static Room *GameRoom;

	static std::vector<Layout *> LayoutList;
};

