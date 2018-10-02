#pragma once
#include "Layout.h"
#include <vector>
#include "mj_def.h"
#include "Tehai.h"
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>
#include "Agent.h"
#include "Player.h"

class MahJongRoom : public Layout
{
public:
	MahJongRoom();
	~MahJongRoom();

	virtual bool init();
	virtual void destroy();
	virtual void update();

	void ShowPaiSan();
	void ShowOthersPai();
	void ShowTehai();

	void GetInfo(const Player *pai1, const Player *pai2, const Player *pai3, const Player *pai4);

	void SetAgent(Agent *p);
	Agent *player;

	std::vector<int> reorder;				//將赤五放入正常排牌位置
	int tsumohai = -1;

	CEGUI::Window *background;
	std::vector<CEGUI::Window *>leftPaiSan;
	std::vector<CEGUI::Window *>rightPaiSan;
	std::vector<CEGUI::Window *>topPaiSan;
	std::vector<CEGUI::Window *>downPaiSan;
	std::vector<CEGUI::Window *>leftPlayer;
	std::vector<CEGUI::Window *>rightPlayer;
	std::vector<CEGUI::Window *>frontPlayer;
	std::vector<CEGUI::Window *>myPai;

	std::vector<CEGUI::Window *>mySutehai;
	std::vector<CEGUI::Window *>rightSutehai;
	std::vector<CEGUI::Window *>leftSutehai;
	std::vector<CEGUI::Window *>frontSutehai;
	int myRichi = 0;
	int rightRichi = 0;
	int leftRichi = 0;
	int frontRichi = 0;
	//vvvvvvvvvvvvvvvv		捨牌數量
	int mySuteNumber = 0;
	int rightSuteNumber = 0;
	int leftSuteNumber = 0;
	int frontSuteNumber = 0;
	//^^^^^^^^^^^^^^^^^
};

