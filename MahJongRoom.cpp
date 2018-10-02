#include "stdafx.h"
#include "MahJongRoom.h"


MahJongRoom::MahJongRoom() 
{
	m_gui = new GUI();
	init();
}


MahJongRoom::~MahJongRoom()
{
}

bool MahJongRoom::init()
{
	m_gui->init("../GUI");
	m_gui->loadScheme("AlfiskoSkin.scheme");
	m_gui->loadScheme("TaharezLook.scheme");
	m_gui->loadScheme("MJ_material.scheme");
	m_gui->setFont("HanSansTC-14");
	background = m_gui->createWidget("MJ_material/Image", glm::vec4(0, 0, 1, 1), glm::vec4(), "background");
	background->setProperty("Image", "MJ_material/MJ_Table");

	topPaiSan.resize(17);
	downPaiSan.resize(17);
	leftPaiSan.resize(17);
	rightPaiSan.resize(17);
	leftPlayer.resize(14);
	rightPlayer.resize(14);
	frontPlayer.resize(14);
	myPai.resize(14);
	for (int i = 0; i < 17; ++i) {
		CEGUI::Window *tmp = m_gui->createWidget("MJ_material/Image", glm::vec4(0.322 + 0.024 * i, 0.065, 0.024, 0.088), glm::vec4(), "", background);
		tmp->setProperty("Image", "MJ_material/PaiVer2");
		topPaiSan.at(i) = tmp;
	}
	for (int i = 0; i < 17; ++i) {
		CEGUI::Window *tmp = m_gui->createWidget("MJ_material/Image", glm::vec4(0.2725, 0.074 + 0.042 * i, 0.032, 0.0746), glm::vec4(), "", background);
		tmp->setProperty("Image", "MJ_material/PaiHor2");
		leftPaiSan.at(i) = tmp;
	}
	for (int i = 0; i < 17; ++i) {
		CEGUI::Window *tmp = m_gui->createWidget("MJ_material/Image", glm::vec4(0.272 + 0.024 * i, 0.815, 0.024, 0.088), glm::vec4(), "", background);
		tmp->setProperty("Image", "MJ_material/PaiVer2");
		downPaiSan.at(i) = tmp;
	}
	for (int i = 0; i < 17; ++i) {
		CEGUI::Window *tmp = m_gui->createWidget("MJ_material/Image", glm::vec4(0.2725 + 0.422, 0.150 + 0.042 * i, 0.032, 0.0746), glm::vec4(), "", background);
		tmp->setProperty("Image", "MJ_material/PaiHor2");
		rightPaiSan.at(i) = tmp;
	}
	for (int i = 0; i < 14; ++i) {
		CEGUI::Window *tmp = m_gui->createWidget("MJ_material/Image", glm::vec4(0.332 + 0.024*i, 0.03, 0.024, 0.016), glm::vec4(), "", background);
		tmp->setProperty("Image", "MJ_material/PaiSide");
		tmp->setRotation(CEGUI::Quaternion::axisAngleDegrees(CEGUI::Vector3f(0,0,1),180));
		frontPlayer.at(i) = tmp;
	}
	for (int i = 0; i < 14; ++i) {
		CEGUI::Window *tmp = m_gui->createWidget("MJ_material/Image", glm::vec4(0.23 , 0.22 + 0.0444 * i, 0.024, 0.016), glm::vec4(), "", background);
		tmp->setProperty("Image", "MJ_material/PaiSide");
		tmp->setRotation(CEGUI::Quaternion::axisAngleDegrees(CEGUI::Vector3f(0, 0, 1), 90));
		leftPlayer.at(i) = tmp;
	}
	for (int i = 0; i < 14; ++i) {
		CEGUI::Window *tmp = m_gui->createWidget("MJ_material/Image", glm::vec4(0.75 , 0.23 + 0.0444 * i, 0.024, 0.016), glm::vec4(), "", background);
		tmp->setProperty("Image", "MJ_material/PaiSide");
		tmp->setRotation(CEGUI::Quaternion::axisAngleDegrees(CEGUI::Vector3f(0, 0, 1), 270));
		rightPlayer.at(i) = tmp;
	}
	for (int i = 0; i < 14; ++i) {
		CEGUI::Window *tmp = m_gui->createWidget("MJ_material/Button", glm::vec4(0.23 + 0.035 * i, 0.9, 0.035, 0.08295), glm::vec4(), "", background);
		tmp->setProperty("NormalImage", "MJ_material/PaiVer");
		tmp->setProperty("HoverImage", "MJ_material/PaiVer");
		tmp->setProperty("PushedImage", "MJ_material/PaiVer");
		tmp->subscribeEvent(CEGUI::PushButton::EventMouseEntersArea, CEGUI::Event::Subscriber([=]() {
			tmp->setYPosition(tmp->getYPosition() + CEGUI::UDim(-0.01, 0));
		}));
		tmp->subscribeEvent(CEGUI::PushButton::EventMouseLeavesArea, CEGUI::Event::Subscriber([=]() {
			tmp->setYPosition(tmp->getYPosition() + CEGUI::UDim(0.01, 0));
		}));
		tmp->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber([=]() {
			if (player->WaitForKiru) {
				*player->Suteru = reorder.at(i);
			}
		}));
		myPai.at(i) = tmp;
	}

	ShowPaiSan();
	return true;
}

void MahJongRoom::destroy()
{
}

void MahJongRoom::update()
{
}

void MahJongRoom::ShowPaiSan()
{	
}

void MahJongRoom::ShowOthersPai()
{
}

void MahJongRoom::ShowTehai()
{
}

void MahJongRoom::GetInfo(const Tehai * pai1, const Tehai * pai2, const Tehai * pai3, const Tehai * pai4)
{
	reorder = pai1->tehai;
	for (int i = 0; i < reorder.size() - 1; ++i) {
		if ((reorder.at(i) == 0 && reorder.at(i + 1) < 5) || (reorder.at(i) == 10 && reorder.at(i + 1) < 15) || (reorder.at(i) == 20 && reorder.at(i + 1) < 25)) {
			int tmp = reorder.at(i);
			reorder.at(i) = reorder.at(i + 1);
			reorder.at(i + 1) = tmp;
		}
	}

		if (pai1->tsumohai != -1) {
			switch (pai1->tsumohai)
			{
			case 0:
				myPai.at(reorder.size())->setProperty("NormalImage", "MJ_material/Pin5R");
				myPai.at(reorder.size())->setProperty("HoverImage", "MJ_material/Pin5R");
				myPai.at(reorder.size())->setProperty("PushedImage", "MJ_material/Pin5R");
				break;
			case 1:
				myPai.at(reorder.size())->setProperty("NormalImage", "MJ_material/Pin1");
				myPai.at(reorder.size())->setProperty("HoverImage", "MJ_material/Pin1");
				myPai.at(reorder.size())->setProperty("PushedImage", "MJ_material/Pin1");
				break;
			case 2:
				myPai.at(reorder.size())->setProperty("NormalImage", "MJ_material/Pin2");
				myPai.at(reorder.size())->setProperty("HoverImage", "MJ_material/Pin2");
				myPai.at(reorder.size())->setProperty("PushedImage", "MJ_material/Pin2");
				break;
			case 3:
				myPai.at(reorder.size())->setProperty("NormalImage", "MJ_material/Pin3");
				myPai.at(reorder.size())->setProperty("HoverImage", "MJ_material/Pin3");
				myPai.at(reorder.size())->setProperty("PushedImage", "MJ_material/Pin3");
				break;
			case 4:
				myPai.at(reorder.size())->setProperty("NormalImage", "MJ_material/Pin4");
				myPai.at(reorder.size())->setProperty("HoverImage", "MJ_material/Pin4");
				myPai.at(reorder.size())->setProperty("PushedImage", "MJ_material/Pin4");
				break;
			case 5:
				myPai.at(reorder.size())->setProperty("NormalImage", "MJ_material/Pin5");
				myPai.at(reorder.size())->setProperty("HoverImage", "MJ_material/Pin5");
				myPai.at(reorder.size())->setProperty("PushedImage", "MJ_material/Pin5");
				break;
			case 6:
				myPai.at(reorder.size())->setProperty("NormalImage", "MJ_material/Pin6");
				myPai.at(reorder.size())->setProperty("HoverImage", "MJ_material/Pin6");
				myPai.at(reorder.size())->setProperty("PushedImage", "MJ_material/Pin6");
				break;
			case 7:
				myPai.at(reorder.size())->setProperty("NormalImage", "MJ_material/Pin7");
				myPai.at(reorder.size())->setProperty("HoverImage", "MJ_material/Pin7");
				myPai.at(reorder.size())->setProperty("PushedImage", "MJ_material/Pin7");
				break;
			case 8:
				myPai.at(reorder.size())->setProperty("NormalImage", "MJ_material/Pin8");
				myPai.at(reorder.size())->setProperty("HoverImage", "MJ_material/Pin8");
				myPai.at(reorder.size())->setProperty("PushedImage", "MJ_material/Pin8");
				break;
			case 9:
				myPai.at(reorder.size())->setProperty("NormalImage", "MJ_material/Pin9");
				myPai.at(reorder.size())->setProperty("HoverImage", "MJ_material/Pin9");
				myPai.at(reorder.size())->setProperty("PushedImage", "MJ_material/Pin9");
				break;
			case 10:
				myPai.at(reorder.size())->setProperty("NormalImage", "MJ_material/Man5R");
				myPai.at(reorder.size())->setProperty("HoverImage", "MJ_material/Man5R");
				myPai.at(reorder.size())->setProperty("PushedImage", "MJ_material/Man5R");
				break;
			case 11:
				myPai.at(reorder.size())->setProperty("NormalImage", "MJ_material/Man1");
				myPai.at(reorder.size())->setProperty("HoverImage", "MJ_material/Man1");
				myPai.at(reorder.size())->setProperty("PushedImage", "MJ_material/Man1");
				break;
			case 12:
				myPai.at(reorder.size())->setProperty("NormalImage", "MJ_material/Man2");
				myPai.at(reorder.size())->setProperty("HoverImage", "MJ_material/Man2");
				myPai.at(reorder.size())->setProperty("PushedImage", "MJ_material/Man2");
				break;
			case 13:
				myPai.at(reorder.size())->setProperty("NormalImage", "MJ_material/Man3");
				myPai.at(reorder.size())->setProperty("HoverImage", "MJ_material/Man3");
				myPai.at(reorder.size())->setProperty("PushedImage", "MJ_material/Man3");
				break;
			case 14:
				myPai.at(reorder.size())->setProperty("NormalImage", "MJ_material/Man4");
				myPai.at(reorder.size())->setProperty("HoverImage", "MJ_material/Man4");
				myPai.at(reorder.size())->setProperty("PushedImage", "MJ_material/Man4");
				break;
			case 15:
				myPai.at(reorder.size())->setProperty("NormalImage", "MJ_material/Man5");
				myPai.at(reorder.size())->setProperty("HoverImage", "MJ_material/Man5");
				myPai.at(reorder.size())->setProperty("PushedImage", "MJ_material/Man5");
				break;
			case 16:
				myPai.at(reorder.size())->setProperty("NormalImage", "MJ_material/Man6");
				myPai.at(reorder.size())->setProperty("HoverImage", "MJ_material/Man6");
				myPai.at(reorder.size())->setProperty("PushedImage", "MJ_material/Man6");
				break;
			case 17:
				myPai.at(reorder.size())->setProperty("NormalImage", "MJ_material/Man7");
				myPai.at(reorder.size())->setProperty("HoverImage", "MJ_material/Man7");
				myPai.at(reorder.size())->setProperty("PushedImage", "MJ_material/Man7");
				break;
			case 18:
				myPai.at(reorder.size())->setProperty("NormalImage", "MJ_material/Man8");
				myPai.at(reorder.size())->setProperty("HoverImage", "MJ_material/Man8");
				myPai.at(reorder.size())->setProperty("PushedImage", "MJ_material/Man8");
				break;
			case 19:
				myPai.at(reorder.size())->setProperty("NormalImage", "MJ_material/Man9");
				myPai.at(reorder.size())->setProperty("HoverImage", "MJ_material/Man9");
				myPai.at(reorder.size())->setProperty("PushedImage", "MJ_material/Man9");
				break;
			case 20:
				myPai.at(reorder.size())->setProperty("NormalImage", "MJ_material/SOU5R");
				myPai.at(reorder.size())->setProperty("HoverImage", "MJ_material/SOU5R");
				myPai.at(reorder.size())->setProperty("PushedImage", "MJ_material/SOU5R");
				break;
			case 21:
				myPai.at(reorder.size())->setProperty("NormalImage", "MJ_material/SOU1");
				myPai.at(reorder.size())->setProperty("HoverImage", "MJ_material/SOU1");
				myPai.at(reorder.size())->setProperty("PushedImage", "MJ_material/SOU1");
				break;
			case 22:
				myPai.at(reorder.size())->setProperty("NormalImage", "MJ_material/SOU2");
				myPai.at(reorder.size())->setProperty("HoverImage", "MJ_material/SOU2");
				myPai.at(reorder.size())->setProperty("PushedImage", "MJ_material/SOU2");
				break;
			case 23:
				myPai.at(reorder.size())->setProperty("NormalImage", "MJ_material/SOU3");
				myPai.at(reorder.size())->setProperty("HoverImage", "MJ_material/SOU3");
				myPai.at(reorder.size())->setProperty("PushedImage", "MJ_material/SOU3");
				break;
			case 24:
				myPai.at(reorder.size())->setProperty("NormalImage", "MJ_material/SOU4");
				myPai.at(reorder.size())->setProperty("HoverImage", "MJ_material/SOU4");
				myPai.at(reorder.size())->setProperty("PushedImage", "MJ_material/SOU4");
				break;
			case 25:
				myPai.at(reorder.size())->setProperty("NormalImage", "MJ_material/SOU5");
				myPai.at(reorder.size())->setProperty("HoverImage", "MJ_material/SOU5");
				myPai.at(reorder.size())->setProperty("PushedImage", "MJ_material/SOU5");
				break;
			case 26:
				myPai.at(reorder.size())->setProperty("NormalImage", "MJ_material/SOU6");
				myPai.at(reorder.size())->setProperty("HoverImage", "MJ_material/SOU6");
				myPai.at(reorder.size())->setProperty("PushedImage", "MJ_material/SOU6");
				break;
			case 27:
				myPai.at(reorder.size())->setProperty("NormalImage", "MJ_material/SOU7");
				myPai.at(reorder.size())->setProperty("HoverImage", "MJ_material/SOU7");
				myPai.at(reorder.size())->setProperty("PushedImage", "MJ_material/SOU7");
				break;
			case 28:
				myPai.at(reorder.size())->setProperty("NormalImage", "MJ_material/SOU8");
				myPai.at(reorder.size())->setProperty("HoverImage", "MJ_material/SOU8");
				myPai.at(reorder.size())->setProperty("PushedImage", "MJ_material/SOU8");
				break;
			case 29:
				myPai.at(reorder.size())->setProperty("NormalImage", "MJ_material/SOU9");
				myPai.at(reorder.size())->setProperty("HoverImage", "MJ_material/SOU9");
				myPai.at(reorder.size())->setProperty("PushedImage", "MJ_material/SOU9");
				break;
			case 30:
				myPai.at(reorder.size())->setProperty("NormalImage", "MJ_material/Ton");
				myPai.at(reorder.size())->setProperty("HoverImage", "MJ_material/Ton");
				myPai.at(reorder.size())->setProperty("PushedImage", "MJ_material/Ton");
				break;
			case 31:
				myPai.at(reorder.size())->setProperty("NormalImage", "MJ_material/Nan");
				myPai.at(reorder.size())->setProperty("HoverImage", "MJ_material/Nan");
				myPai.at(reorder.size())->setProperty("PushedImage", "MJ_material/Nan");
				break;
			case 32:
				myPai.at(reorder.size())->setProperty("NormalImage", "MJ_material/Sha");
				myPai.at(reorder.size())->setProperty("HoverImage", "MJ_material/Sha");
				myPai.at(reorder.size())->setProperty("PushedImage", "MJ_material/Sha");
				break;
			case 33:
				myPai.at(reorder.size())->setProperty("NormalImage", "MJ_material/Pei");
				myPai.at(reorder.size())->setProperty("HoverImage", "MJ_material/Pei");
				myPai.at(reorder.size())->setProperty("PushedImage", "MJ_material/Pei");
				break;
			case 34:
				myPai.at(reorder.size())->setProperty("NormalImage", "MJ_material/Haku");
				myPai.at(reorder.size())->setProperty("HoverImage", "MJ_material/Haku");
				myPai.at(reorder.size())->setProperty("PushedImage", "MJ_material/Haku");
				break;
			case 35:
				myPai.at(reorder.size())->setProperty("NormalImage", "MJ_material/Fa");
				myPai.at(reorder.size())->setProperty("HoverImage", "MJ_material/Fa");
				myPai.at(reorder.size())->setProperty("PushedImage", "MJ_material/Fa");
				break;
			case 36:
				myPai.at(reorder.size())->setProperty("NormalImage", "MJ_material/Chun");
				myPai.at(reorder.size())->setProperty("HoverImage", "MJ_material/Chun");
				myPai.at(reorder.size())->setProperty("PushedImage", "MJ_material/Chun");
				break;
			}
		}
		else {
			myPai.at(reorder.size())->setProperty("NormalImage", "MJ_material/Nothing");
			myPai.at(reorder.size())->setProperty("HoverImage", "MJ_material/Nothing");
			myPai.at(reorder.size())->setProperty("PushedImage", "MJ_material/Nothing");
		}
		for (int i = 0; i < pai1->tehai.size(); ++i) {
			switch (reorder.at(i))
			{
			case 0:
				myPai.at(i)->setProperty("NormalImage", "MJ_material/Pin5R");
				myPai.at(i)->setProperty("HoverImage", "MJ_material/Pin5R");
				myPai.at(i)->setProperty("PushedImage", "MJ_material/Pin5R");
				break;
			case 1:
				myPai.at(i)->setProperty("NormalImage", "MJ_material/Pin1");
				myPai.at(i)->setProperty("HoverImage", "MJ_material/Pin1");
				myPai.at(i)->setProperty("PushedImage", "MJ_material/Pin1");
				break;
			case 2:
				myPai.at(i)->setProperty("NormalImage", "MJ_material/Pin2");
				myPai.at(i)->setProperty("HoverImage", "MJ_material/Pin2");
				myPai.at(i)->setProperty("PushedImage", "MJ_material/Pin2");
				break;
			case 3:
				myPai.at(i)->setProperty("NormalImage", "MJ_material/Pin3");
				myPai.at(i)->setProperty("HoverImage", "MJ_material/Pin3");
				myPai.at(i)->setProperty("PushedImage", "MJ_material/Pin3");
				break;
			case 4:
				myPai.at(i)->setProperty("NormalImage", "MJ_material/Pin4");
				myPai.at(i)->setProperty("HoverImage", "MJ_material/Pin4");
				myPai.at(i)->setProperty("PushedImage", "MJ_material/Pin4");
				break;
			case 5:
				myPai.at(i)->setProperty("NormalImage", "MJ_material/Pin5");
				myPai.at(i)->setProperty("HoverImage", "MJ_material/Pin5");
				myPai.at(i)->setProperty("PushedImage", "MJ_material/Pin5");
				break;
			case 6:
				myPai.at(i)->setProperty("NormalImage", "MJ_material/Pin6");
				myPai.at(i)->setProperty("HoverImage", "MJ_material/Pin6");
				myPai.at(i)->setProperty("PushedImage", "MJ_material/Pin6");
				break;
			case 7:
				myPai.at(i)->setProperty("NormalImage", "MJ_material/Pin7");
				myPai.at(i)->setProperty("HoverImage", "MJ_material/Pin7");
				myPai.at(i)->setProperty("PushedImage", "MJ_material/Pin7");
				break;
			case 8:
				myPai.at(i)->setProperty("NormalImage", "MJ_material/Pin8");
				myPai.at(i)->setProperty("HoverImage", "MJ_material/Pin8");
				myPai.at(i)->setProperty("PushedImage", "MJ_material/Pin8");
				break;
			case 9:
				myPai.at(i)->setProperty("NormalImage", "MJ_material/Pin9");
				myPai.at(i)->setProperty("HoverImage", "MJ_material/Pin9");
				myPai.at(i)->setProperty("PushedImage", "MJ_material/Pin9");
				break;
			case 10:
				myPai.at(i)->setProperty("NormalImage", "MJ_material/Man5R");
				myPai.at(i)->setProperty("HoverImage", "MJ_material/Man5R");
				myPai.at(i)->setProperty("PushedImage", "MJ_material/Man5R");
				break;
			case 11:
				myPai.at(i)->setProperty("NormalImage", "MJ_material/Man1");
				myPai.at(i)->setProperty("HoverImage", "MJ_material/Man1");
				myPai.at(i)->setProperty("PushedImage", "MJ_material/Man1");
				break;
			case 12:
				myPai.at(i)->setProperty("NormalImage", "MJ_material/Man2");
				myPai.at(i)->setProperty("HoverImage", "MJ_material/Man2");
				myPai.at(i)->setProperty("PushedImage", "MJ_material/Man2");
				break;
			case 13:
				myPai.at(i)->setProperty("NormalImage", "MJ_material/Man3");
				myPai.at(i)->setProperty("HoverImage", "MJ_material/Man3");
				myPai.at(i)->setProperty("PushedImage", "MJ_material/Man3");
				break;
			case 14:
				myPai.at(i)->setProperty("NormalImage", "MJ_material/Man4");
				myPai.at(i)->setProperty("HoverImage", "MJ_material/Man4");
				myPai.at(i)->setProperty("PushedImage", "MJ_material/Man4");
				break;
			case 15:
				myPai.at(i)->setProperty("NormalImage", "MJ_material/Man5");
				myPai.at(i)->setProperty("HoverImage", "MJ_material/Man5");
				myPai.at(i)->setProperty("PushedImage", "MJ_material/Man5");
				break;
			case 16:
				myPai.at(i)->setProperty("NormalImage", "MJ_material/Man6");
				myPai.at(i)->setProperty("HoverImage", "MJ_material/Man6");
				myPai.at(i)->setProperty("PushedImage", "MJ_material/Man6");
				break;
			case 17:
				myPai.at(i)->setProperty("NormalImage", "MJ_material/Man7");
				myPai.at(i)->setProperty("HoverImage", "MJ_material/Man7");
				myPai.at(i)->setProperty("PushedImage", "MJ_material/Man7");
				break;
			case 18:
				myPai.at(i)->setProperty("NormalImage", "MJ_material/Man8");
				myPai.at(i)->setProperty("HoverImage", "MJ_material/Man8");
				myPai.at(i)->setProperty("PushedImage", "MJ_material/Man8");
				break;
			case 19:
				myPai.at(i)->setProperty("NormalImage", "MJ_material/Man9");
				myPai.at(i)->setProperty("HoverImage", "MJ_material/Man9");
				myPai.at(i)->setProperty("PushedImage", "MJ_material/Man9");
				break;
			case 20:
				myPai.at(i)->setProperty("NormalImage", "MJ_material/SOU5R");
				myPai.at(i)->setProperty("HoverImage", "MJ_material/SOU5R");
				myPai.at(i)->setProperty("PushedImage", "MJ_material/SOU5R");
				break;
			case 21:
				myPai.at(i)->setProperty("NormalImage", "MJ_material/SOU1");
				myPai.at(i)->setProperty("HoverImage", "MJ_material/SOU1");
				myPai.at(i)->setProperty("PushedImage", "MJ_material/SOU1");
				break;
			case 22:
				myPai.at(i)->setProperty("NormalImage", "MJ_material/SOU2");
				myPai.at(i)->setProperty("HoverImage", "MJ_material/SOU2");
				myPai.at(i)->setProperty("PushedImage", "MJ_material/SOU2");
				break;
			case 23:
				myPai.at(i)->setProperty("NormalImage", "MJ_material/SOU3");
				myPai.at(i)->setProperty("HoverImage", "MJ_material/SOU3");
				myPai.at(i)->setProperty("PushedImage", "MJ_material/SOU3");
				break;
			case 24:
				myPai.at(i)->setProperty("NormalImage", "MJ_material/SOU4");
				myPai.at(i)->setProperty("HoverImage", "MJ_material/SOU4");
				myPai.at(i)->setProperty("PushedImage", "MJ_material/SOU4");
				break;
			case 25:
				myPai.at(i)->setProperty("NormalImage", "MJ_material/SOU5");
				myPai.at(i)->setProperty("HoverImage", "MJ_material/SOU5");
				myPai.at(i)->setProperty("PushedImage", "MJ_material/SOU5");
				break;
			case 26:
				myPai.at(i)->setProperty("NormalImage", "MJ_material/SOU6");
				myPai.at(i)->setProperty("HoverImage", "MJ_material/SOU6");
				myPai.at(i)->setProperty("PushedImage", "MJ_material/SOU6");
				break;
			case 27:
				myPai.at(i)->setProperty("NormalImage", "MJ_material/SOU7");
				myPai.at(i)->setProperty("HoverImage", "MJ_material/SOU7");
				myPai.at(i)->setProperty("PushedImage", "MJ_material/SOU7");
				break;
			case 28:
				myPai.at(i)->setProperty("NormalImage", "MJ_material/SOU8");
				myPai.at(i)->setProperty("HoverImage", "MJ_material/SOU8");
				myPai.at(i)->setProperty("PushedImage", "MJ_material/SOU8");
				break;
			case 29:
				myPai.at(i)->setProperty("NormalImage", "MJ_material/SOU9");
				myPai.at(i)->setProperty("HoverImage", "MJ_material/SOU9");
				myPai.at(i)->setProperty("PushedImage", "MJ_material/SOU9");
				break;
			case 30:
				myPai.at(i)->setProperty("NormalImage", "MJ_material/Ton");
				myPai.at(i)->setProperty("HoverImage", "MJ_material/Ton");
				myPai.at(i)->setProperty("PushedImage", "MJ_material/Ton");
				break;
			case 31:
				myPai.at(i)->setProperty("NormalImage", "MJ_material/Nan");
				myPai.at(i)->setProperty("HoverImage", "MJ_material/Nan");
				myPai.at(i)->setProperty("PushedImage", "MJ_material/Nan");
				break;
			case 32:
				myPai.at(i)->setProperty("NormalImage", "MJ_material/Sha");
				myPai.at(i)->setProperty("HoverImage", "MJ_material/Sha");
				myPai.at(i)->setProperty("PushedImage", "MJ_material/Sha");
				break;
			case 33:
				myPai.at(i)->setProperty("NormalImage", "MJ_material/Pei");
				myPai.at(i)->setProperty("HoverImage", "MJ_material/Pei");
				myPai.at(i)->setProperty("PushedImage", "MJ_material/Pei");
				break;
			case 34:
				myPai.at(i)->setProperty("NormalImage", "MJ_material/Haku");
				myPai.at(i)->setProperty("HoverImage", "MJ_material/Haku");
				myPai.at(i)->setProperty("PushedImage", "MJ_material/Haku");
				break;
			case 35:
				myPai.at(i)->setProperty("NormalImage", "MJ_material/Fa");
				myPai.at(i)->setProperty("HoverImage", "MJ_material/Fa");
				myPai.at(i)->setProperty("PushedImage", "MJ_material/Fa");
				break;
			case 36:
				myPai.at(i)->setProperty("NormalImage", "MJ_material/Chun");
				myPai.at(i)->setProperty("HoverImage", "MJ_material/Chun");
				myPai.at(i)->setProperty("PushedImage", "MJ_material/Chun");
				break;
			}
		}

}

void MahJongRoom::SetAgent(Agent * p)
{
	player = p;
}
