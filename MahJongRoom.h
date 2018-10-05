#pragma once
#include "Layout.h"
#include <vector>
#include "mj_def.h"
#include "Tehai.h"
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>
#include "Agent.h"
#include "Player.h"
#include "nstdlib.h"

class MahJongRoom : public Layout
{
public:
	MahJongRoom();
	~MahJongRoom();

	virtual bool init();
	virtual void destroy();
	virtual void update();

	void Act();
	void Reset();

	void ShowPaiSan();
	void ShowOthersPai();
	void ShowTehai();

	void GetInfo(const Player *pai1, const Player *pai2, const Player *pai3, const Player *pai4);

	void SetAgent(Agent *p);
	Agent *player;

	void ButtonFunction(int n);

	std::vector<int> reorder;				//�N������J���`�ƵP��m
	int tsumohai = -1;

	CEGUI::Window *background;
	//vvvvvvvvvvvvvvv						�P�s
	std::vector<CEGUI::Window *>leftPaiSan;
	std::vector<CEGUI::Window *>rightPaiSan;
	std::vector<CEGUI::Window *>topPaiSan;
	std::vector<CEGUI::Window *>downPaiSan;
	//^^^^^^^^^^^^^^^						
	//vvvvvvvvvvvvvvv						��P
	std::vector<CEGUI::Window *>leftPlayer;
	std::vector<CEGUI::Window *>rightPlayer;
	std::vector<CEGUI::Window *>frontPlayer;
	std::vector<CEGUI::Window *>myPai;
	//^^^^^^^^^^^^^^^
	//vvvvvvvvvvvvvvv						�˵P
	std::vector<CEGUI::Window *>mySutehai;
	std::vector<CEGUI::Window *>rightSutehai;
	std::vector<CEGUI::Window *>leftSutehai;
	std::vector<CEGUI::Window *>frontSutehai;
	//^^^^^^^^^^^^^^^						�˵P
	//vvvvvvvvvvvvvvv						���s
	int ButtonCase = 0;			//	1		2		3		4		5		6		7		8		9		10		11		12		13		14		15		16
	CEGUI::Window *button1;		//															pass	pass	pass	pass			pass	pass	pass
	CEGUI::Window *button2;		//	pass	pass	pass	pass	pass	pass	pass	�Y		�Y		�Y		�ߪ�	pass	�ߪ�	�I		�Y		pass
	CEGUI::Window *button3;		//	�ۺN	�ߪ�	�Y		�M		�I		�b		�I		�I		�I		�I		�ۺN	�ۺN	�ۺN	�M		�M		�I
	CEGUI::Window *button4;		//													�b				�b		�b				�b		�b						�b
	CEGUI::Window *button5;		//																			�M												�M
	
	CEGUI::Window *testbutton;
	//^^^^^^^^^^^^^^^						���s

	int myRichi = 0;
	int rightRichi = 0;
	int leftRichi = 0;
	int frontRichi = 0;
	//vvvvvvvvvvvvvvvv		�˵P�ƶq
	int mySuteNumber = 0;
	int rightSuteNumber = 0;
	int leftSuteNumber = 0;
	int frontSuteNumber = 0;
	//^^^^^^^^^^^^^^^^		�˵P�ƶq
	//vvvvvvvvvvvvvvvv		���S
	std::vector<std::vector<CEGUI::Window *>> myFuRou;
	std::vector<std::vector<CEGUI::Window *>> rightFuRou;
	std::vector<std::vector<CEGUI::Window *>> frontFuRou;
	std::vector<std::vector<CEGUI::Window *>> leftFuRou;
	
	/*
	1 : ��˪��Ĥ@�i�P
	2 : ��˪��ĤG�i�P
	3 : �����Ĥ@�i�P
	4 : �����ĤG�i�P
	*/
	std::vector<std::vector<int>> myFuRouPai;
	std::vector<std::vector<int>> rightFuRouPai;
	std::vector<std::vector<int>> frontFuRouPai;
	std::vector<std::vector<int>> leftFuRouPai;
	//^^^^^^^^^^^^^^^^		���S
};

