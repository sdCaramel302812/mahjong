#pragma once
#include "Layout.h"
#include <vector>
#include "mj_def.h"
#include "Tehai.h"
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>
#include "Agent.h"

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

	void GetInfo(const Tehai *pai1, const Tehai *pai2, const Tehai *pai3, const Tehai *pai4);

	void SetAgent(Agent *p);
	Agent *player;

	std::vector<int> reorder;				//將赤五放入正常排牌位置

	CEGUI::Window *background;
	std::vector<CEGUI::Window *>leftPaiSan;
	std::vector<CEGUI::Window *>rightPaiSan;
	std::vector<CEGUI::Window *>topPaiSan;
	std::vector<CEGUI::Window *>downPaiSan;
	std::vector<CEGUI::Window *>leftPlayer;
	std::vector<CEGUI::Window *>rightPlayer;
	std::vector<CEGUI::Window *>frontPlayer;
	std::vector<CEGUI::Window *>myPai;
};

