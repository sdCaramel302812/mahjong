#pragma once
#include "Layout.h"
#include "nstdlib.h"

class GameMenu : public Layout 
{
public:
	GameMenu();
	~GameMenu();

	virtual bool init();
	virtual void destroy();

	CEGUI::Window *background;
	CEGUI::Window *backgroundTop;
	CEGUI::Window *backgroundDown;

	CEGUI::Window *ChallengeButton;
	CEGUI::Window *FreeGameButton;
	CEGUI::Window *OnlineGameButton;
	CEGUI::Window *CharacterButton;
	CEGUI::Window *AITrainingButton;
	CEGUI::Window *DataButton;
	CEGUI::Window *OptionButton;
};

