#include "stdafx.h"
#include "GameMenu.h"


GameMenu::GameMenu()
{
	init();
}


GameMenu::~GameMenu()
{
}

bool GameMenu::init()
{
	//vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv		GUI 相關
	m_gui->init("../GUI");
	m_gui->loadScheme("AlfiskoSkin.scheme");
	m_gui->loadScheme("OgreTray.scheme");
	m_gui->loadScheme("MJ_material.scheme");
	m_gui->setFont("HanSansTC-14");
	background = m_gui->createWidget("MJ_material/Image", glm::vec4(0, 0, 1, 1), glm::vec4(), "MenuBackground");
	background->setProperty("Image", "MenuBackground/BackgroundBuilding");
	CharacterImage = m_gui->createWidget("MJ_material/Image", glm::vec4(0.6, 0.15, 0.279, 0.85), glm::vec4(), "", background);
	CharacterImage->setProperty("Image", "SakiCharacter/SakiNormal");
	CharacterImage->setEnabled(false);
	CharacterImage->setRotation(CEGUI::Quaternion::axisAngleDegrees(CEGUI::Vector3f(0, 1, 0), 180));
	backgroundTop = m_gui->createWidget("MJ_material/Image", glm::vec4(0, 0, 1, 0.08), glm::vec4(), "", background);
	backgroundTop->setProperty("Image", "MenuBackground/HorizontalBar");
	backgroundDown = m_gui->createWidget("MJ_material/Image", glm::vec4(0, 0.92, 1, 0.08), glm::vec4(), "", background);
	backgroundDown->setProperty("Image", "MenuBackground/HorizontalBar");
	//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^		GUI 相關

	

	ChallengeButton = m_gui->createWidget("OgreTray/Button", glm::vec4(0.04, 0.15, 0.15, 0.07), glm::vec4(), "", background);
	FreeGameButton = m_gui->createWidget("OgreTray/Button", glm::vec4(0.04, 0.26, 0.15, 0.07), glm::vec4(), "", background);
	OnlineGameButton = m_gui->createWidget("OgreTray/Button", glm::vec4(0.04, 0.37, 0.15, 0.07), glm::vec4(), "", background);
	CharacterButton = m_gui->createWidget("OgreTray/Button", glm::vec4(0.04, 0.48, 0.15, 0.07), glm::vec4(), "", background);
	AITrainingButton = m_gui->createWidget("OgreTray/Button", glm::vec4(0.04, 0.59, 0.15, 0.07), glm::vec4(), "", background);
	DataButton = m_gui->createWidget("OgreTray/Button", glm::vec4(0.04, 0.70, 0.15, 0.07), glm::vec4(), "", background);
	OptionButton = m_gui->createWidget("OgreTray/Button", glm::vec4(0.04, 0.81, 0.15, 0.07), glm::vec4(), "", background);


	wstring text1 = TString().str2wstr("挑戰");
	wstring text2 = TString().str2wstr("自由對局");
	wstring text3 = TString().str2wstr("通信對局");
	wstring text4 = TString().str2wstr("角色");
	wstring text5 = TString().str2wstr("AI訓練");
	wstring text6 = TString().str2wstr("戰績");
	wstring text7 = TString().str2wstr("設定");

	ChallengeButton->setText(wcharToUTF8(text1));
	FreeGameButton->setText(wcharToUTF8(text2));
	OnlineGameButton->setText(wcharToUTF8(text3));
	CharacterButton->setText(wcharToUTF8(text4));
	AITrainingButton->setText(wcharToUTF8(text5));
	DataButton->setText(wcharToUTF8(text6));
	OptionButton->setText(wcharToUTF8(text7));

	return true;
}

void GameMenu::destroy()
{
}
