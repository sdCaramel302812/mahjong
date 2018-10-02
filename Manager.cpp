#include "stdafx.h"
#include "Manager.h"

std::map<std::string, Layout *> Manager::LayoutList;
Room *Manager::GameRoom = new Room();
std::string Manager::CurrentLayout = "Menu";

Manager::Manager()
{
}


Manager::~Manager()
{
}
