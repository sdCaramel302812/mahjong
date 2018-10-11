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

	//vvvvvvvvvvvvv		似乎也是沒用到的
	void ShowPaiSan();
	void ShowOthersPai();
	void ShowTehai();
	//^^^^^^^^^^^^^		似乎也是沒用到的

	void GetInfo(const Player *pai1, const Player *pai2, const Player *pai3, const Player *pai4);

	void SetAgent(Agent *p);
	Agent *player;

	void ButtonFunction(int n);

	/*
	將赤五放入正常排牌位置
	reorder 和 tsumohai 為顯示手牌用途
	*/
	std::vector<int> reorder;				
	int tsumohai = -1;

	CEGUI::Window *background;
	//vvvvvvvvvvvvvvv						牌山
	std::vector<CEGUI::Window *>leftPaiSan;
	std::vector<CEGUI::Window *>rightPaiSan;
	std::vector<CEGUI::Window *>topPaiSan;
	std::vector<CEGUI::Window *>downPaiSan;
	//^^^^^^^^^^^^^^^						
	//vvvvvvvvvvvvvvv						手牌
	std::vector<CEGUI::Window *>leftPlayer;
	std::vector<CEGUI::Window *>rightPlayer;
	std::vector<CEGUI::Window *>frontPlayer;
	std::vector<CEGUI::Window *>myPai;
	//^^^^^^^^^^^^^^^
	//vvvvvvvvvvvvvvv						立直棒
	CEGUI::Window *myRichiBo;
	CEGUI::Window *rightRichiBo;
	CEGUI::Window *frontRichiBo;
	CEGUI::Window *leftRichiBo;
	//^^^^^^^^^^^^^^^
	//vvvvvvvvvvvvvvv						捨牌
	std::vector<CEGUI::Window *>mySutehai;
	std::vector<CEGUI::Window *>rightSutehai;
	std::vector<CEGUI::Window *>leftSutehai;
	std::vector<CEGUI::Window *>frontSutehai;
	//^^^^^^^^^^^^^^^						捨牌
	//vvvvvvvvvvvvvvv						按鈕
	//			太麻煩了放棄，改成一對一的按鈕
	//			pass
	//			吃
	//			碰
	//			槓
	//			立直
	//			自摸
	//			和
	int ButtonCase = 0;			//	1		2		3		4		5		6		7		8		9		10		11		12		13		14		15		16		17
	CEGUI::Window *button1;		//															pass	pass	pass	pass			pass	pass	pass			pass
	CEGUI::Window *button2;		//	pass	pass	pass	pass	pass	pass	pass	吃		吃		吃		立直	pass	立直	碰		吃		pass	吃
	CEGUI::Window *button3;		//	自摸	立直	吃		和		碰		槓		碰		碰		碰		碰		自摸	自摸	自摸	和		和		碰		碰
	CEGUI::Window *button4;		//													槓				槓		槓				槓		槓						槓
	CEGUI::Window *button5;		//																			和												和		和
								//	o		x		o		o		o		x		o		o		x		x		x		x		x		o		o		o
	CEGUI::Window *button6;
	CEGUI::Window *button7;

	CEGUI::Window *testbutton;
	//^^^^^^^^^^^^^^^						按鈕

	bool switchChi = false;
	bool switchKan = false;
	bool switchRichi = false;

	std::vector<int> richiDekiruPai;

	//	立直巡數
	int myRichi = 0;
	int rightRichi = 0;
	int leftRichi = 0;
	int frontRichi = 0;
	//vvvvvvvvvvvvvvvv		捨牌數量
	int mySuteNumber = 0;
	int rightSuteNumber = 0;
	int leftSuteNumber = 0;
	int frontSuteNumber = 0;
	//^^^^^^^^^^^^^^^^		捨牌數量
	//vvvvvvvvvvvvvvvv		副露
	std::vector<std::vector<CEGUI::Window *>> myFuRou;
	std::vector<std::vector<CEGUI::Window *>> rightFuRou;
	std::vector<std::vector<CEGUI::Window *>> frontFuRou;
	std::vector<std::vector<CEGUI::Window *>> leftFuRou;
	
	/*
	1 : 橫倒的第一張牌
	2 : 橫倒的第二張牌
	3 : 直的第一張牌
	4 : 直的第二張牌
	*/
	std::vector<std::vector<int>> myFuRouPai;
	std::vector<std::vector<int>> rightFuRouPai;
	std::vector<std::vector<int>> frontFuRouPai;
	std::vector<std::vector<int>> leftFuRouPai;
	//^^^^^^^^^^^^^^^^		副露
};

