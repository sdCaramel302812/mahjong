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
	//vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv		GUI 相關
	m_gui->init("../GUI");
	m_gui->loadScheme("AlfiskoSkin.scheme");
	m_gui->loadScheme("TaharezLook.scheme");
	m_gui->loadScheme("MJ_material.scheme");
	m_gui->setFont("HanSansTC-14");
	background = m_gui->createWidget("MJ_material/Image", glm::vec4(0, 0, 1, 1), glm::vec4(), "background");
	background->setProperty("Image", "MJ_material/MJ_Table");
	//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^		GUI 相關

	topPaiSan.resize(17);
	downPaiSan.resize(17);
	leftPaiSan.resize(17);
	rightPaiSan.resize(17);
	leftPlayer.resize(14);
	rightPlayer.resize(14);
	frontPlayer.resize(14);
	myPai.resize(14);


	//vvvvvvvvvvvvvvvvvvv		立直棒初始化
	myRichiBo = m_gui->createWidget("MJ_material/Image", glm::vec4(0.45, 0.612, 0.095, 0.01), glm::vec4(), "", background);
	myRichiBo->setProperty("Image", "MJ_material/Point1000");
	myRichiBo->setVisible(false);
	rightRichiBo = m_gui->createWidget("MJ_material/Image", glm::vec4(0.51, 0.5, 0.095, 0.01), glm::vec4(), "", background);
	rightRichiBo->setProperty("Image", "MJ_material/Point1000");
	rightRichiBo->setRotation(CEGUI::Quaternion::axisAngleDegrees(CEGUI::Vector3f(0, 0, 1), 90));
	rightRichiBo->setVisible(false);
	frontRichiBo = m_gui->createWidget("MJ_material/Image", glm::vec4(0.45, 0.39, 0.095, 0.01), glm::vec4(), "", background);
	frontRichiBo->setProperty("Image", "MJ_material/Point1000");
	frontRichiBo->setVisible(false);
	leftRichiBo = m_gui->createWidget("MJ_material/Image", glm::vec4(0.39, 0.5, 0.095, 0.01), glm::vec4(), "", background);
	leftRichiBo->setProperty("Image", "MJ_material/Point1000");
	leftRichiBo->setRotation(CEGUI::Quaternion::axisAngleDegrees(CEGUI::Vector3f(0, 0, 1), 90));
	leftRichiBo->setVisible(false);
	//^^^^^^^^^^^^^^^^^^^		立直棒初始化
	//vvvvvvvvvvvvvvvvvvv		副露初始化
	{
		int middle[] = { 0.763, 0.723, 0.802 };
		int right[] = { 0.798, 0.723, 0.758 };
		int left[] = { 0.729, 0.768, 0.802 };
		int shift = 0.115;
	}
	for (int i = 0; i < 4; ++i) {					//	自家副露
		CEGUI::Window *tmp1 = m_gui->createWidget("MJ_material/Image", glm::vec4(0.768 + 0.115 * -i, 0.92 + 0.08 * 0, 0.034, 0.08), glm::vec4(), "", background);
		tmp1->setProperty("Image", "MJ_material/Nothing");
		CEGUI::Window *tmp2 = m_gui->createWidget("MJ_material/Image", glm::vec4(0.729 + 0.115 * -i, 0.928 + 0.08 * 0, 0.034, 0.08), glm::vec4(), "", background);
		tmp2->setProperty("Image", "MJ_material/Nothing");
		tmp2->setRotation(CEGUI::Quaternion::axisAngleDegrees(CEGUI::Vector3f(0, 0, 1), 90));
		CEGUI::Window *tmp3 = m_gui->createWidget("MJ_material/Image", glm::vec4(0.729 + 0.115 * -i, 0.865 + 0.08 * 0, 0.034, 0.08), glm::vec4(), "", background);
		tmp3->setProperty("Image", "MJ_material/Nothing");
		tmp3->setRotation(CEGUI::Quaternion::axisAngleDegrees(CEGUI::Vector3f(0, 0, 1), 90));
		CEGUI::Window *tmp4 = m_gui->createWidget("MJ_material/Image", glm::vec4(0.802 + 0.115 * -i, 0.92 + 0.08 * 0, 0.034, 0.08), glm::vec4(), "", background);
		tmp4->setProperty("Image", "MJ_material/Nothing");
		tmp1->setEnabled(false);
		tmp2->setEnabled(false);
		tmp3->setEnabled(false);
		tmp4->setEnabled(false);
		std::vector<CEGUI::Window *> furou;
		furou.push_back(tmp2);
		furou.push_back(tmp3);
		furou.push_back(tmp1);
		furou.push_back(tmp4);
		myFuRou.push_back(furou);
	}
	{
		int middle[] = { 0.065, 0.138, -0.005 };
		int right[] = { 0.005, 0.138, 0.0755 };
		int left[] = { 0.13, 0.058, -0.005 };
		int shift = 0.207;
	}
	for (int i = 0; i < 4; ++i) {					//	下家副露
		CEGUI::Window *tmp1 = m_gui->createWidget("MJ_material/Image", glm::vec4(0.798 + 0.115 * 0, -0.005 + 0.207 * i, 0.034, 0.08), glm::vec4(), "", background);
		tmp1->setProperty("Image", "MJ_material/Nothing");
		tmp1->setRotation(CEGUI::Quaternion::axisAngleDegrees(CEGUI::Vector3f(0, 0, 1), 270));
		CEGUI::Window *tmp2 = m_gui->createWidget("MJ_material/Image", glm::vec4(0.802 + 0.115 * 0, 0.13 + 0.207 * i, 0.034, 0.08), glm::vec4(), "", background);
		tmp2->setProperty("Image", "MJ_material/Nothing");
		tmp2->setRotation(CEGUI::Quaternion::axisAngleDegrees(CEGUI::Vector3f(0, 0, 1), 180));
		CEGUI::Window *tmp3 = m_gui->createWidget("MJ_material/Image", glm::vec4(0.768 + 0.115 * 0, 0.13 + 0.207 * i, 0.034, 0.08), glm::vec4(), "", background);
		tmp3->setProperty("Image", "MJ_material/Nothing");
		tmp3->setRotation(CEGUI::Quaternion::axisAngleDegrees(CEGUI::Vector3f(0, 0, 1), 180));
		CEGUI::Window *tmp4 = m_gui->createWidget("MJ_material/Image", glm::vec4(0.798 + 0.115 * 0, 0.058 + 0.207 * i, 0.034, 0.08), glm::vec4(), "", background);
		tmp4->setProperty("Image", "MJ_material/Nothing");
		tmp4->setRotation(CEGUI::Quaternion::axisAngleDegrees(CEGUI::Vector3f(0, 0, 1), 270));
		std::vector<CEGUI::Window *> furou;
		tmp1->setEnabled(false);
		tmp2->setEnabled(false);
		tmp3->setEnabled(false);
		tmp4->setEnabled(false);
		furou.push_back(tmp2);
		furou.push_back(tmp3);
		furou.push_back(tmp1);
		furou.push_back(tmp4);
		rightFuRou.push_back(furou);
	}
	{
		int middle[] = { 0.855, 0.785, 0.928 };
		int right[] = { 0.918, 0.785, 0.847 };
		int left[] = { 0.792, 0.865, 0.928 };
		int shift = 0.207;
	}
	for (int i = 0; i < 4; ++i) {					//	上家副露
		CEGUI::Window *tmp1 = m_gui->createWidget("MJ_material/Image", glm::vec4(0.17 + 0.115 * 0, 0.865 + 0.207 * -i, 0.034, 0.08), glm::vec4(), "", background);
		tmp1->setProperty("Image", "MJ_material/Nothing");
		tmp1->setRotation(CEGUI::Quaternion::axisAngleDegrees(CEGUI::Vector3f(0, 0, 1), 90));
		CEGUI::Window *tmp2 = m_gui->createWidget("MJ_material/Image", glm::vec4(0.164 + 0.115 * 0, 0.792 + 0.207 * -i, 0.034, 0.08), glm::vec4(), "", background);
		tmp2->setProperty("Image", "MJ_material/Nothing");
		CEGUI::Window *tmp3 = m_gui->createWidget("MJ_material/Image", glm::vec4(0.198 + 0.115 * 0, 0.792 + 0.207 * -i, 0.034, 0.08), glm::vec4(), "", background);
		tmp3->setProperty("Image", "MJ_material/Nothing");
		CEGUI::Window *tmp4 = m_gui->createWidget("MJ_material/Image", glm::vec4(0.17 + 0.115 * 0, 0.928 + 0.207 * -i, 0.034, 0.08), glm::vec4(), "", background);
		tmp4->setProperty("Image", "MJ_material/Nothing");
		tmp4->setRotation(CEGUI::Quaternion::axisAngleDegrees(CEGUI::Vector3f(0, 0, 1), 90));
		std::vector<CEGUI::Window *> furou;
		tmp1->setEnabled(false);
		tmp2->setEnabled(false);
		tmp3->setEnabled(false);
		tmp4->setEnabled(false);
		furou.push_back(tmp2);
		furou.push_back(tmp3);
		furou.push_back(tmp1);
		furou.push_back(tmp4);
		leftFuRou.push_back(furou);
	}
	{
		int middle[] = { 0.204, 0.244, 0.164 };
		int right[] = { 0.17, 0.245, 0.21 };
		int left[] = { 0.239, 0.199, 0.164 };
		int shift = 0.207;
	}
	for (int i = 0; i < 4; ++i) {					//	對家副露
		CEGUI::Window *tmp1 = m_gui->createWidget("MJ_material/Image", glm::vec4(0.164 + 0.115 * i, 0.005 + 0.207 * 0, 0.034, 0.08), glm::vec4(), "", background);
		tmp1->setProperty("Image", "MJ_material/Nothing");
		tmp1->setRotation(CEGUI::Quaternion::axisAngleDegrees(CEGUI::Vector3f(0, 0, 1), 180));
		CEGUI::Window *tmp2 = m_gui->createWidget("MJ_material/Image", glm::vec4(0.239 + 0.115 * i, -0.005 + 0.207 * 0, 0.034, 0.08), glm::vec4(), "", background);
		tmp2->setProperty("Image", "MJ_material/Nothing");
		tmp2->setRotation(CEGUI::Quaternion::axisAngleDegrees(CEGUI::Vector3f(0, 0, 1), 270));
		CEGUI::Window *tmp3 = m_gui->createWidget("MJ_material/Image", glm::vec4(0.239 + 0.115 * i, 0.057 + 0.207 * 0, 0.034, 0.08), glm::vec4(), "", background);
		tmp3->setProperty("Image", "MJ_material/Nothing");
		tmp3->setRotation(CEGUI::Quaternion::axisAngleDegrees(CEGUI::Vector3f(0, 0, 1), 270));
		CEGUI::Window *tmp4 = m_gui->createWidget("MJ_material/Image", glm::vec4(0.199 + 0.115 * i, 0.005 + 0.207 * 0, 0.034, 0.08), glm::vec4(), "", background);
		tmp4->setProperty("Image", "MJ_material/Nothing");
		tmp4->setRotation(CEGUI::Quaternion::axisAngleDegrees(CEGUI::Vector3f(0, 0, 1), 180));
		std::vector<CEGUI::Window *> furou;
		tmp1->setEnabled(false);
		tmp2->setEnabled(false);
		tmp3->setEnabled(false);
		tmp4->setEnabled(false);
		furou.push_back(tmp2);
		furou.push_back(tmp3);
		furou.push_back(tmp1);
		furou.push_back(tmp4);
		frontFuRou.push_back(furou);
	}
	//^^^^^^^^^^^^^^^^^^^		副露初始化
	//vvvvvvvvvvvvvvvvvvv		牌山初始化
	for (int i = 0; i < 17; ++i) {
		CEGUI::Window *tmp = m_gui->createWidget("MJ_material/Image", glm::vec4(0.322 + 0.024 * i, 0.065, 0.024, 0.088), glm::vec4(), "", background);
		tmp->setProperty("Image", "MJ_material/PaiVer2");
		tmp->setEnabled(false);
		topPaiSan.at(i) = tmp;
	}
	for (int i = 0; i < 17; ++i) {
		CEGUI::Window *tmp = m_gui->createWidget("MJ_material/Image", glm::vec4(0.2725, 0.074 + 0.042 * i, 0.032, 0.0746), glm::vec4(), "", background);
		tmp->setProperty("Image", "MJ_material/PaiHor2");
		tmp->setEnabled(false);
		leftPaiSan.at(i) = tmp;
	}
	for (int i = 0; i < 17; ++i) {
		CEGUI::Window *tmp = m_gui->createWidget("MJ_material/Image", glm::vec4(0.272 + 0.024 * i, 0.815, 0.024, 0.088), glm::vec4(), "", background);
		tmp->setProperty("Image", "MJ_material/PaiVer2");
		tmp->setEnabled(false);
		downPaiSan.at(i) = tmp;
	}
	for (int i = 0; i < 17; ++i) {
		CEGUI::Window *tmp = m_gui->createWidget("MJ_material/Image", glm::vec4(0.2725 + 0.422, 0.150 + 0.042 * i, 0.032, 0.0746), glm::vec4(), "", background);
		tmp->setProperty("Image", "MJ_material/PaiHor2");
		tmp->setEnabled(false);
		rightPaiSan.at(i) = tmp;
	}
	//^^^^^^^^^^^^^^^^^^^		牌山初始化
	//vvvvvvvvvvvvvvvvvvv		手牌初始化
	for (int i = 0; i < 14; ++i) {
		CEGUI::Window *tmp = m_gui->createWidget("MJ_material/Image", glm::vec4(0.338 + 0.024*i, 0.03, 0.024, 0.016), glm::vec4(), "", background);
		tmp->setProperty("Image", "MJ_material/PaiSide");
		tmp->setRotation(CEGUI::Quaternion::axisAngleDegrees(CEGUI::Vector3f(0,0,1),180));
		frontPlayer.at(i) = tmp;
	}
	for (int i = 0; i < 14; ++i) {
		CEGUI::Window *tmp = m_gui->createWidget("MJ_material/Image", glm::vec4(0.23 , 0.1 + 0.0444 * i, 0.024, 0.016), glm::vec4(), "", background);
		tmp->setProperty("Image", "MJ_material/PaiSide");
		tmp->setRotation(CEGUI::Quaternion::axisAngleDegrees(CEGUI::Vector3f(0, 0, 1), 90));
		leftPlayer.at(i) = tmp;
	}
	for (int i = 0; i < 14; ++i) {
		CEGUI::Window *tmp = m_gui->createWidget("MJ_material/Image", glm::vec4(0.75 , 0.3 + 0.0444 * i, 0.024, 0.016), glm::vec4(), "", background);
		tmp->setProperty("Image", "MJ_material/PaiSide");
		tmp->setRotation(CEGUI::Quaternion::axisAngleDegrees(CEGUI::Vector3f(0, 0, 1), 270));
		rightPlayer.at(i) = tmp;
	}
	for (int i = 0; i < 14; ++i) {				//		手牌按鈕
		CEGUI::Window *tmp = m_gui->createWidget("MJ_material/Button", glm::vec4(0.23 + 0.035 * i, 1 - 0.08295, 0.035, 0.08295), glm::vec4(), "", background);
		tmp->setProperty("NormalImage", "MJ_material/PaiVer");
		tmp->setProperty("HoverImage", "MJ_material/PaiVer");
		tmp->setProperty("PushedImage", "MJ_material/PaiVer");
		//vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv			hover in function
		tmp->subscribeEvent(CEGUI::PushButton::EventMouseEntersArea, CEGUI::Event::Subscriber([=]() {
			tmp->setYPosition(tmp->getYPosition() + CEGUI::UDim(-0.01, 0));
			if (switchKan&&tmp->isVisible()) {
				for (int k = 0; k < player->KanDekiruList.size(); ++k) {
					int p;
					if (reorder.size() < i) {
						break;
					}
					else if (reorder.size() == i && tsumohai != -1) {
						p = (tsumohai == 0 || tsumohai == 10 || tsumohai == 20) ? tsumohai + 5 : tsumohai;
					}
					else if (reorder.size() > i) {
						p = reorder.at(i);
					}
					if (p == player->KanDekiruList.at(k).first) {
						for (int j = 0; j < reorder.size(); ++j) {
							if (reorder.at(j) == 10 || reorder.at(j) == 20 || reorder.at(j) == 0) {
								if (i != j && reorder.at(j) == p - 5) {
									myPai.at(j)->setYPosition(myPai.at(j)->getYPosition() + CEGUI::UDim(-0.01, 0));
								}
							}
							else {
								if (i != j && reorder.at(j) == p) {
									myPai.at(j)->setYPosition(myPai.at(j)->getYPosition() + CEGUI::UDim(-0.01, 0));
								}
							}
						}
						if (tsumohai == 10 || tsumohai == 20 || tsumohai == 0) {
							if (i != reorder.size() && tsumohai == p - 5) {
								myPai.at(reorder.size())->setYPosition(myPai.at(reorder.size())->getYPosition() + CEGUI::UDim(-0.01, 0));
							}
						}
						else if (tsumohai != -1) {
							if (i != reorder.size() && tsumohai == p) {
								myPai.at(reorder.size())->setYPosition(myPai.at(reorder.size())->getYPosition() + CEGUI::UDim(-0.01, 0));
							}
						}
					}
				}
			}
			if (switchChi && tmp->isVisible()) {									//	選擇吃牌
																					//
																					//ChiDekiruList.at(k).second : 吃牌方式
																					//3 : 1 2 3	只有選到第二張時才能吃
																					//4 : 2 1 3	不管選哪張都能吃
																					//5 : 3 1 2	只有選到第一張時才能吃
																					//
				for (int k = 0; k < player->ChiDekiruList.size(); ++k) {			//	可以吃牌的種類清單
					if (reorder.size() <= i) {
						break;
					}
					//cout << player->ChiDekiruList.at(k).first.first << " " << player->ChiDekiruList.at(k).first.second << " " << player->ChiDekiruList.at(k).second  << endl;
																					//	若此牌非赤牌時
					if (reorder.at(i) != 0 && reorder.at(i) != 10 && reorder.at(i) != 20) {
						if (player->ChiDekiruList.at(k).first.first == reorder.at(i) && player->ChiDekiruList.at(k).second == 5) {
							for (int j = 0; j < reorder.size(); ++j) {				//	找另一張牌
								int secondpai = (reorder.at(j) == 0 || reorder.at(j) == 10 || reorder.at(j) == 20) ? reorder.at(j) + 5 : reorder.at(j);
								if (secondpai == player->ChiDekiruList.at(k).first.second) {
									myPai.at(j)->setYPosition(myPai.at(j)->getYPosition() + CEGUI::UDim(-0.01, 0));
									break;
								}
							}
						}
						if (player->ChiDekiruList.at(k).first.first == reorder.at(i) && player->ChiDekiruList.at(k).second == 4) {
							for (int j = 0; j < reorder.size(); ++j) {
								int secondpai = (reorder.at(j) == 0 || reorder.at(j) == 10 || reorder.at(j) == 20) ? reorder.at(j) + 5 : reorder.at(j);
								if (secondpai == player->ChiDekiruList.at(k).first.second) {
									myPai.at(j)->setYPosition(myPai.at(j)->getYPosition() + CEGUI::UDim(-0.01, 0));
									break;
								}
							}
						}
						if (player->ChiDekiruList.at(k).first.second == reorder.at(i) && player->ChiDekiruList.at(k).second == 4) {
							for (int j = 0; j < reorder.size(); ++j) {
								int secondpai = (reorder.at(j) == 0 || reorder.at(j) == 10 || reorder.at(j) == 20) ? reorder.at(j) + 5 : reorder.at(j);
								if (secondpai == player->ChiDekiruList.at(k).first.first) {
									myPai.at(j)->setYPosition(myPai.at(j)->getYPosition() + CEGUI::UDim(-0.01, 0));
									break;
								}
							}
						}
						if (player->ChiDekiruList.at(k).first.second == reorder.at(i) && player->ChiDekiruList.at(k).second == 3) {
							for (int j = 0; j < reorder.size(); ++j) {
								int secondpai = (reorder.at(j) == 0 || reorder.at(j) == 10 || reorder.at(j) == 20) ? reorder.at(j) + 5 : reorder.at(j);
								if (secondpai == player->ChiDekiruList.at(k).first.first) {
									myPai.at(j)->setYPosition(myPai.at(j)->getYPosition() + CEGUI::UDim(-0.01, 0));
									break;
								}
							}
						}
					}																//	若此牌為赤牌時
					else {
						if (player->ChiDekiruList.at(k).first.first == reorder.at(i) + 5 && player->ChiDekiruList.at(k).second == 5) {
							for (int j = 0; j < reorder.size(); ++j) {
								int secondpai = (reorder.at(j) == 0 || reorder.at(j) == 10 || reorder.at(j) == 20) ? reorder.at(j) + 5 : reorder.at(j);
								if (secondpai == player->ChiDekiruList.at(k).first.second) {
									myPai.at(j)->setYPosition(myPai.at(j)->getYPosition() + CEGUI::UDim(-0.01, 0));
									break;
								}
							}
						}
						if (player->ChiDekiruList.at(k).first.first == reorder.at(i) + 5 && player->ChiDekiruList.at(k).second == 4) {
							for (int j = 0; j < reorder.size(); ++j) {
								int secondpai = (reorder.at(j) == 0 || reorder.at(j) == 10 || reorder.at(j) == 20) ? reorder.at(j) + 5 : reorder.at(j);
								if (secondpai == player->ChiDekiruList.at(k).first.second) {
									myPai.at(j)->setYPosition(myPai.at(j)->getYPosition() + CEGUI::UDim(-0.01, 0));
									break;
								}
							}
						}
						if (player->ChiDekiruList.at(k).first.second == reorder.at(i) + 5 && player->ChiDekiruList.at(k).second == 4) {
							for (int j = 0; j < reorder.size(); ++j) {
								int secondpai = (reorder.at(j) == 0 || reorder.at(j) == 10 || reorder.at(j) == 20) ? reorder.at(j) + 5 : reorder.at(j);
								if (secondpai == player->ChiDekiruList.at(k).first.first) {
									myPai.at(j)->setYPosition(myPai.at(j)->getYPosition() + CEGUI::UDim(-0.01, 0));
									break;
								}
							}
						}
						if (player->ChiDekiruList.at(k).first.second == reorder.at(i) + 5 && player->ChiDekiruList.at(k).second == 3) {
							for (int j = 0; j < reorder.size(); ++j) {
								int secondpai = (reorder.at(j) == 0 || reorder.at(j) == 10 || reorder.at(j) == 20) ? reorder.at(j) + 5 : reorder.at(j);
								if (secondpai == player->ChiDekiruList.at(k).first.first) {
									myPai.at(j)->setYPosition(myPai.at(j)->getYPosition() + CEGUI::UDim(-0.01, 0));
									break;
								}
							}
						}
					}
				}
			}
		}));

		//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^			hover in function
		//vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv			hover out function
		tmp->subscribeEvent(CEGUI::PushButton::EventMouseLeavesArea, CEGUI::Event::Subscriber([=]() {
			tmp->setYPosition(tmp->getYPosition() + CEGUI::UDim(0.01, 0));
			if (switchKan&&tmp->isVisible()) {
				for (int k = 0; k < player->KanDekiruList.size(); ++k) {
					int p;
					if (reorder.size() < i) {
						break;
					}
					else if (reorder.size() == i && tsumohai != -1) {
						p = (tsumohai == 0 || tsumohai == 10 || tsumohai == 20) ? tsumohai + 5 : tsumohai;
					}
					else if (reorder.size() > i) {
						p = reorder.at(i);
					}
					if (p == player->KanDekiruList.at(k).first) {
						for (int j = 0; j < reorder.size(); ++j) {
							if (reorder.at(j) == 10 || reorder.at(j) == 20 || reorder.at(j) == 0) {
								if (i != j && reorder.at(j) == p - 5) {
									myPai.at(j)->setYPosition(myPai.at(j)->getYPosition() + CEGUI::UDim(0.01, 0));
								}
							}
							else {
								if (i != j && reorder.at(j) == p) {
									myPai.at(j)->setYPosition(myPai.at(j)->getYPosition() + CEGUI::UDim(0.01, 0));
								}
							}
						}
						if (tsumohai == 10 || tsumohai == 20 || tsumohai == 0) {
							if (i != reorder.size() && tsumohai == p - 5) {
								myPai.at(reorder.size())->setYPosition(myPai.at(reorder.size())->getYPosition() + CEGUI::UDim(0.01, 0));
							}
						}
						else if (tsumohai != -1) {
							if (i != reorder.size() && tsumohai == p) {
								myPai.at(reorder.size())->setYPosition(myPai.at(reorder.size())->getYPosition() + CEGUI::UDim(0.01, 0));
							}
						}
					}
				}
			}
			if (switchChi && tmp->isVisible()) {
				for (int k = 0; k < player->ChiDekiruList.size(); ++k) {
					if (reorder.size() <= i) {
						break;
					}
					if (reorder.at(i) != 0 && reorder.at(i) != 10 && reorder.at(i) != 20) {
						if (player->ChiDekiruList.at(k).first.first == reorder.at(i) && player->ChiDekiruList.at(k).second == 5) {
							for (int j = 0; j < reorder.size(); ++j) {
								int secondpai = (reorder.at(j) == 0 || reorder.at(j) == 10 || reorder.at(j) == 20) ? reorder.at(j) + 5 : reorder.at(j);
								if (secondpai == player->ChiDekiruList.at(k).first.second) {
									myPai.at(j)->setYPosition(myPai.at(j)->getYPosition() + CEGUI::UDim(0.01, 0));
									break;
								}
							}
						}
						if (player->ChiDekiruList.at(k).first.first == reorder.at(i) && player->ChiDekiruList.at(k).second == 4) {
							for (int j = 0; j < reorder.size(); ++j) {
								int secondpai = (reorder.at(j) == 0 || reorder.at(j) == 10 || reorder.at(j) == 20) ? reorder.at(j) + 5 : reorder.at(j);
								if (secondpai == player->ChiDekiruList.at(k).first.second) {
									myPai.at(j)->setYPosition(myPai.at(j)->getYPosition() + CEGUI::UDim(0.01, 0));
									break;
								}
							}
						}
						if (player->ChiDekiruList.at(k).first.second == reorder.at(i) && player->ChiDekiruList.at(k).second == 4) {
							for (int j = 0; j < reorder.size(); ++j) {
								int secondpai = (reorder.at(j) == 0 || reorder.at(j) == 10 || reorder.at(j) == 20) ? reorder.at(j) + 5 : reorder.at(j);
								if (secondpai == player->ChiDekiruList.at(k).first.first) {
									myPai.at(j)->setYPosition(myPai.at(j)->getYPosition() + CEGUI::UDim(0.01, 0));
									break;
								}
							}
						}
						if (player->ChiDekiruList.at(k).first.second == reorder.at(i) && player->ChiDekiruList.at(k).second == 3) {
							for (int j = 0; j < reorder.size(); ++j) {
								int secondpai = (reorder.at(j) == 0 || reorder.at(j) == 10 || reorder.at(j) == 20) ? reorder.at(j) + 5 : reorder.at(j);
								if (secondpai == player->ChiDekiruList.at(k).first.first) {
									myPai.at(j)->setYPosition(myPai.at(j)->getYPosition() + CEGUI::UDim(0.01, 0));
									break;
								}
							}
						}
					}
					else {
						if (player->ChiDekiruList.at(k).first.first == reorder.at(i) + 5 && player->ChiDekiruList.at(k).second == 5) {
							for (int j = 0; j < reorder.size(); ++j) {
								int secondpai = (reorder.at(j) == 0 || reorder.at(j) == 10 || reorder.at(j) == 20) ? reorder.at(j) + 5 : reorder.at(j);
								if (secondpai == player->ChiDekiruList.at(k).first.second) {
									myPai.at(j)->setYPosition(myPai.at(j)->getYPosition() + CEGUI::UDim(0.01, 0));
									break;
								}
							}
						}
						if (player->ChiDekiruList.at(k).first.first == reorder.at(i) + 5 && player->ChiDekiruList.at(k).second == 4) {
							for (int j = 0; j < reorder.size(); ++j) {
								int secondpai = (reorder.at(j) == 0 || reorder.at(j) == 10 || reorder.at(j) == 20) ? reorder.at(j) + 5 : reorder.at(j);
								if (secondpai == player->ChiDekiruList.at(k).first.second) {
									myPai.at(j)->setYPosition(myPai.at(j)->getYPosition() + CEGUI::UDim(0.01, 0));
									break;
								}
							}
						}
						if (player->ChiDekiruList.at(k).first.second == reorder.at(i) + 5 && player->ChiDekiruList.at(k).second == 4) {
							for (int j = 0; j < reorder.size(); ++j) {
								int secondpai = (reorder.at(j) == 0 || reorder.at(j) == 10 || reorder.at(j) == 20) ? reorder.at(j) + 5 : reorder.at(j);
								if (secondpai == player->ChiDekiruList.at(k).first.first) {
									myPai.at(j)->setYPosition(myPai.at(j)->getYPosition() + CEGUI::UDim(0.01, 0));
									break;
								}
							}
						}
						if (player->ChiDekiruList.at(k).first.second == reorder.at(i) + 5 && player->ChiDekiruList.at(k).second == 3) {
							for (int j = 0; j < reorder.size(); ++j) {
								int secondpai = (reorder.at(j) == 0 || reorder.at(j) == 10 || reorder.at(j) == 20) ? reorder.at(j) + 5 : reorder.at(j);
								if (secondpai == player->ChiDekiruList.at(k).first.first) {
									myPai.at(j)->setYPosition(myPai.at(j)->getYPosition() + CEGUI::UDim(0.01, 0));
									break;
								}
							}
						}
					}
				}
			}
		}));

		//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^			hover out function
		//vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv			click function
		tmp->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber([=]() {
			try {
				if (player->WaitForKiru) {							//	捨牌時
					if (switchKan) {
						//		復原浮起的牌
						for (int k = 0; k < player->KanDekiruList.size(); ++k) {
							int p;
							if (reorder.size() < i) {
								break;
							}
							else if (reorder.size() == i && tsumohai != -1) {
								p = (tsumohai == 0 || tsumohai == 10 || tsumohai == 20) ? tsumohai + 5 : tsumohai;
							}
							else if (reorder.size() > i) {
								p = reorder.at(i);
							}
							if (p == player->KanDekiruList.at(k).first) {
								for (int j = 0; j < reorder.size(); ++j) {
									if (reorder.at(j) == 10 || reorder.at(j) == 20 || reorder.at(j) == 0) {
										if (i != j && reorder.at(j) == p - 5) {
											myPai.at(j)->setYPosition(myPai.at(j)->getYPosition() + CEGUI::UDim(0.01, 0));
										}
									}
									else {
										if (i != j && reorder.at(j) == p) {
											myPai.at(j)->setYPosition(myPai.at(j)->getYPosition() + CEGUI::UDim(0.01, 0));
										}
									}
								}
								if (tsumohai == 10 || tsumohai == 20 || tsumohai == 0) {
									if (i != reorder.size() && tsumohai == p - 5) {
										myPai.at(reorder.size())->setYPosition(myPai.at(reorder.size())->getYPosition() + CEGUI::UDim(0.01, 0));
									}
								}
								else if (tsumohai != -1) {
									if (i != reorder.size() && tsumohai == p) {
										myPai.at(reorder.size())->setYPosition(myPai.at(reorder.size())->getYPosition() + CEGUI::UDim(0.01, 0));
									}
								}
							}
						}
						//			選擇槓的 case
						for (int j = 0; j < player->KanDekiruList.size(); ++j) {
							if (tsumohai == 0 || tsumohai==10 || tsumohai == 20) {
								if (player->KanDekiruList.at(j).first == tsumohai + 5) {
									player->KanCase = j;
									switchKan = false;
									break;
								}
							}
							else {
								if (player->KanDekiruList.at(j).first == tsumohai) {
									player->KanCase = j;
									switchKan = false;
									break;
								}
							}
							if (i >= reorder.size()) {
								continue;
							}
							if (reorder.at(i) == 0 || reorder.at(i) == 10 || reorder.at(i) == 20) {
								if (player->KanDekiruList.at(j).first == reorder.at(i) + 5) {
									player->KanCase = j;
									switchKan = false;
									break;
								}
							}
							else {
								if (player->KanDekiruList.at(j).first == reorder.at(i)) {
									player->KanCase = j;
									switchKan = false;
									break;
								}
							}
						}
					}
					else if (switchRichi) {
						if (reorder.size() > i) {
							for (int j = 0; j < richiDekiruPai.size(); ++j) {
								if (reorder.at(i) == richiDekiruPai.at(j)) {
									player->WantToRichi = 1;
									*player->Suteru = reorder.at(i);
									player->WantToTsumo = -1;
									player->WantToKan = -1;
									switchRichi = false;
									break;
								}
							}
						}
						else if (tsumohai != -1) {
							for (int j = 0; j < richiDekiruPai.size(); ++j) {
								player->WantToRichi = 1;
								*player->Suteru = tsumohai;
								player->WantToTsumo = -1;
								player->WantToKan = -1;
								switchRichi = false;
								break;
							}
						}
					}
					else {
						player->WantToTsumo = -1;
						player->WantToKan = -1;
						if (myRichi == 0) {
							if (reorder.size() > i) {
								*player->Suteru = reorder.at(i);
							}
							else if (tsumohai != -1) {
								*player->Suteru = tsumohai;
							}
						}
						else {
							if (reorder.size() == i) {
								*player->Suteru = tsumohai;
							}
						}
					}
				}
				else if (switchChi && tmp->isVisible()) {				//	選擇吃牌時
					for (int k = 0; k < player->ChiDekiruList.size(); ++k) {
						if (reorder.size() <= i) {
							break;
						}
						if (reorder.at(i) != 0 && reorder.at(i) != 10 && reorder.at(i) != 20) {
							if (player->ChiDekiruList.at(k).first.first == reorder.at(i) && player->ChiDekiruList.at(k).second == 5) {
								for (int j = 0; j < reorder.size(); ++j) {
									int secondpai = (reorder.at(j) == 0 || reorder.at(j) == 10 || reorder.at(j) == 20) ? reorder.at(j) + 5 : reorder.at(j);
									if (secondpai == player->ChiDekiruList.at(k).first.second) {
										myPai.at(j)->setYPosition(myPai.at(j)->getYPosition() + CEGUI::UDim(0.01, 0));
										player->ChiCase = k;
										//*player->NakuState = 5;
										switchChi = false;
										break;
									}
								}
							}
							if (player->ChiDekiruList.at(k).first.first == reorder.at(i) && player->ChiDekiruList.at(k).second == 4) {
								for (int j = 0; j < reorder.size(); ++j) {
									int secondpai = (reorder.at(j) == 0 || reorder.at(j) == 10 || reorder.at(j) == 20) ? reorder.at(j) + 5 : reorder.at(j);
									if (secondpai == player->ChiDekiruList.at(k).first.second) {
										myPai.at(j)->setYPosition(myPai.at(j)->getYPosition() + CEGUI::UDim(0.01, 0));
										player->ChiCase = k;
										//*player->NakuState = 4;
										switchChi = false;
										break;
									}
								}
							}
							if (player->ChiDekiruList.at(k).first.second == reorder.at(i) && player->ChiDekiruList.at(k).second == 4) {
								for (int j = 0; j < reorder.size(); ++j) {
									int secondpai = (reorder.at(j) == 0 || reorder.at(j) == 10 || reorder.at(j) == 20) ? reorder.at(j) + 5 : reorder.at(j);
									if (secondpai == player->ChiDekiruList.at(k).first.first) {
										myPai.at(j)->setYPosition(myPai.at(j)->getYPosition() + CEGUI::UDim(0.01, 0));
										player->ChiCase = k;
										//*player->NakuState = 4;
										switchChi = false;
										break;
									}
								}
							}
							if (player->ChiDekiruList.at(k).first.second == reorder.at(i) && player->ChiDekiruList.at(k).second == 3) {
								for (int j = 0; j < reorder.size(); ++j) {
									int secondpai = (reorder.at(j) == 0 || reorder.at(j) == 10 || reorder.at(j) == 20) ? reorder.at(j) + 5 : reorder.at(j);
									if (secondpai == player->ChiDekiruList.at(k).first.first) {
										myPai.at(j)->setYPosition(myPai.at(j)->getYPosition() + CEGUI::UDim(0.01, 0));
										player->ChiCase = k;
										//*player->NakuState = 3;
										switchChi = false;
										break;
									}
								}
							}
						}
						else {
							if (player->ChiDekiruList.at(k).first.first == reorder.at(i) + 5 && player->ChiDekiruList.at(k).second == 5) {
								for (int j = 0; j < reorder.size(); ++j) {
									int secondpai = (reorder.at(j) == 0 || reorder.at(j) == 10 || reorder.at(j) == 20) ? reorder.at(j) + 5 : reorder.at(j);
									if (secondpai == player->ChiDekiruList.at(k).first.second) {
										myPai.at(j)->setYPosition(myPai.at(j)->getYPosition() + CEGUI::UDim(0.01, 0));
										player->ChiCase = k;
										//*player->NakuState = 5;
										switchChi = false;
										break;
									}
								}
							}
							if (player->ChiDekiruList.at(k).first.first == reorder.at(i) + 5 && player->ChiDekiruList.at(k).second == 4) {
								for (int j = 0; j < reorder.size(); ++j) {
									int secondpai = (reorder.at(j) == 0 || reorder.at(j) == 10 || reorder.at(j) == 20) ? reorder.at(j) + 5 : reorder.at(j);
									if (secondpai == player->ChiDekiruList.at(k).first.second) {
										myPai.at(j)->setYPosition(myPai.at(j)->getYPosition() + CEGUI::UDim(0.01, 0));
										player->ChiCase = k;
										//*player->NakuState = 4;
										switchChi = false;
										break;
									}
								}
							}
							if (player->ChiDekiruList.at(k).first.second == reorder.at(i) + 5 && player->ChiDekiruList.at(k).second == 4) {
								for (int j = 0; j < reorder.size(); ++j) {
									int secondpai = (reorder.at(j) == 0 || reorder.at(j) == 10 || reorder.at(j) == 20) ? reorder.at(j) + 5 : reorder.at(j);
									if (secondpai == player->ChiDekiruList.at(k).first.first) {
										myPai.at(j)->setYPosition(myPai.at(j)->getYPosition() + CEGUI::UDim(0.01, 0));
										player->ChiCase = k;
										//*player->NakuState = 4;
										switchChi = false;
										break;
									}
								}
							}
							if (player->ChiDekiruList.at(k).first.second == reorder.at(i) + 5 && player->ChiDekiruList.at(k).second == 3) {
								for (int j = 0; j < reorder.size(); ++j) {
									int secondpai = (reorder.at(j) == 0 || reorder.at(j) == 10 || reorder.at(j) == 20) ? reorder.at(j) + 5 : reorder.at(j);
									if (secondpai == player->ChiDekiruList.at(k).first.first) {
										myPai.at(j)->setYPosition(myPai.at(j)->getYPosition() + CEGUI::UDim(0.01, 0));
										player->ChiCase = k;
										//*player->NakuState = 3;
										switchChi = false;
										break;
									}
								}
							}
						}
					}
				}
			}
			catch (...) {
				cout << "crash situation : pai button click" << endl;
			}
		}));
		//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^			click function
		myPai.at(i) = tmp;
	}
	//^^^^^^^^^^^^^^^^^^^		手牌初始化

	//vvvvvvvvvvvvvvvvvvv						捨牌初始化
	for (int i = 0; i < 4; ++i) {
		for (int j = 6; j > 0; --j) {
			CEGUI::Window *tmp = m_gui->createWidget("MJ_material/Image", glm::vec4(0.574 + 0.032 * i, 0.328 + 0.0423 * j, 0.0238, 0.056406), glm::vec4(), "", background);
			tmp->setProperty("Image", "MJ_material/Nothing");
			tmp->setRotation(CEGUI::Quaternion::axisAngleDegrees(CEGUI::Vector3f(0, 0, 1), 270));
			rightSutehai.push_back(tmp);
		}
	}
	for (int i = 4; i > 0; --i) {
		for (int j = 0; j < 6; ++j) {
			CEGUI::Window *tmp = m_gui->createWidget("MJ_material/Image", glm::vec4(0.2685 + 0.032 * i, 0.367 + 0.0423 * j, 0.0238, 0.056406), glm::vec4(), "", background);
			tmp->setProperty("Image", "MJ_material/Nothing");
			tmp->setRotation(CEGUI::Quaternion::axisAngleDegrees(CEGUI::Vector3f(0, 0, 1), 90));
			leftSutehai.push_back(tmp);
		}
	}
	for (int j = 0; j < 4; ++j) {
		for (int i = 0; i < 6; ++i) {
			CEGUI::Window *tmp = m_gui->createWidget("MJ_material/Image", glm::vec4(0.427 + 0.0238 * i, 0.633 + 0.056406 * j, 0.0238, 0.056406), glm::vec4(), "", background);
			tmp->setProperty("Image", "MJ_material/Nothing");
			mySutehai.push_back(tmp);
		}
	}
	for (int j = 4; j > 0; --j) {
		for (int i = 6; i > 0; --i) {
			CEGUI::Window *tmp = m_gui->createWidget("MJ_material/Image", glm::vec4(0.402 + 0.0238 * i, 0.092 + 0.056406 * j, 0.0238, 0.056406), glm::vec4(), "", background);
			tmp->setProperty("Image", "MJ_material/Nothing");
			tmp->setRotation(CEGUI::Quaternion::axisAngleDegrees(CEGUI::Vector3f(0, 0, 1), 180));
			frontSutehai.push_back(tmp);
		}
	}
	//^^^^^^^^^^^^^^^^^^^						捨牌初始化

	


	//vvvvvvvvvvvvvvvvvvvvvvvvvv		按鈕初始化
	button1 = m_gui->createWidget("AlfiskoSkin/Button", glm::vec4(0.68, 0.6, 0.08, 0.035), glm::vec4(), "", background);
	button2 = m_gui->createWidget("AlfiskoSkin/Button", glm::vec4(0.68, 0.65, 0.08, 0.035), glm::vec4(), "", background);
	button3 = m_gui->createWidget("AlfiskoSkin/Button", glm::vec4(0.68, 0.7, 0.08, 0.035), glm::vec4(), "", background);
	button4 = m_gui->createWidget("AlfiskoSkin/Button", glm::vec4(0.68, 0.75, 0.08, 0.035), glm::vec4(), "", background);
	button5 = m_gui->createWidget("AlfiskoSkin/Button", glm::vec4(0.68, 0.8, 0.08, 0.035), glm::vec4(), "", background);
	button6 = m_gui->createWidget("AlfiskoSkin/Button", glm::vec4(0.68, 0.85, 0.08, 0.035), glm::vec4(), "", background);
	button7 = m_gui->createWidget("AlfiskoSkin/Button", glm::vec4(0.68, 0.9, 0.08, 0.035), glm::vec4(), "", background);
	testbutton = m_gui->createWidget("AlfiskoSkin/Button", glm::vec4(0.9, 0.85, 0.08, 0.035), glm::vec4(), "", background);
	wstring text1 = TString().str2wstr("吃");
	wstring text2 = TString().str2wstr("碰");
	wstring text3 = TString().str2wstr("槓");
	wstring text4 = TString().str2wstr("立直");
	wstring text5 = TString().str2wstr("自摸");
	wstring text6 = TString().str2wstr("和");
	button1->setText("Pass");
	button2->setText(wcharToUTF8(text1));
	button3->setText(wcharToUTF8(text2));
	button4->setText(wcharToUTF8(text3));
	button5->setText(wcharToUTF8(text4));
	button6->setText(wcharToUTF8(text5));
	button7->setText(wcharToUTF8(text6));
	testbutton->setText("print");
	button1->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber([=]() {
		ButtonFunction(1);
	}));
	button2->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber([=]() {
		ButtonFunction(2);
	}));
	button3->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber([=]() {
		ButtonFunction(3);
	}));
	button4->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber([=]() {
		ButtonFunction(4);
	}));
	button5->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber([=]() {
		ButtonFunction(5);
	}));
	button6->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber([=]() {
		ButtonFunction(6);
	}));
	button7->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber([=]() {
		ButtonFunction(7);
	}));
	testbutton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber([=]() {
		for (int i = 0; i < reorder.size(); ++i) {
			cout << reorder.at(i) << " ";
		}
		cout << "\t" << tsumohai << endl;
	}));
	button1->setVisible(false);
	button2->setVisible(false);
	button3->setVisible(false);
	button4->setVisible(false);
	button5->setVisible(false);
	//^^^^^^^^^^^^^^^^^^^^^^^^^^		按鈕初始化

	ShowPaiSan();
	return true;
}

void MahJongRoom::destroy()
{
}

void MahJongRoom::update()
{
}

void MahJongRoom::Act()
{
	//******************							決定按鈕狀態								******************//

	if (player->ChiDekiru) {
		button2->setVisible(true);
	}
	else {
		button2->setVisible(false);
	}
	if (player->PonDekiru) {
		button3->setVisible(true);
	}
	else {
		button3->setVisible(false);
	}
	if (player->KanDekiru || player->AnKanDekiru) {
		button4->setVisible(true);
	}
	else {
		button4->setVisible(false);
	}
	if (player->RichiDekiru) {
		button5->setVisible(true);
	}
	else {
		button5->setVisible(false);
	}
	if (player->TsumoDekiru) {
		button6->setVisible(true);
	}
	else {
		button6->setVisible(false);
	}
	if (player->RonDekiru) {
		button7->setVisible(true);
	}
	else {
		button7->setVisible(false);
	}
	if (player->ChiDekiru || player->PonDekiru || player->KanDekiru || player->AnKanDekiru || player->RichiDekiru || player->TsumoDekiru || player->RonDekiru) {
		button1->setVisible(true);
	}
	else {
		button1->setVisible(false);
	}
}

void MahJongRoom::Reset()
{
	myRichi = 0;
	rightRichi = 0;
	leftRichi = 0;
	frontRichi = 0;
	mySuteNumber = 0;
	rightSuteNumber = 0;
	leftSuteNumber = 0;
	frontSuteNumber = 0;

	myRichiBo->setVisible(false);
	rightRichiBo->setVisible(false);
	frontRichiBo->setVisible(false);
	leftRichiBo->setVisible(false);

	for (int i = 0; i < mySutehai.size(); ++i) {
		mySutehai.at(i)->setProperty("Image", "MJ_material/Nothing");
		mySutehai.at(i)->setRotation(CEGUI::Quaternion::axisAngleDegrees(CEGUI::Vector3f(0, 0, 1), 0));
	}
	for (int i = 0; i < frontSutehai.size(); ++i) {
		frontSutehai.at(i)->setProperty("Image", "MJ_material/Nothing");
		frontSutehai.at(i)->setRotation(CEGUI::Quaternion::axisAngleDegrees(CEGUI::Vector3f(0, 0, 1), 180));
	}
	for (int i = 0; i < leftSutehai.size(); ++i) {
		leftSutehai.at(i)->setProperty("Image", "MJ_material/Nothing");
		leftSutehai.at(i)->setRotation(CEGUI::Quaternion::axisAngleDegrees(CEGUI::Vector3f(0, 0, 1), 90));
	}
	for (int i = 0; i < rightSutehai.size(); ++i) {
		rightSutehai.at(i)->setProperty("Image", "MJ_material/Nothing");
		rightSutehai.at(i)->setRotation(CEGUI::Quaternion::axisAngleDegrees(CEGUI::Vector3f(0, 0, 1), 270));
	}

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			myFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Nothing");
			rightFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Nothing");
			frontFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Nothing");
			leftFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Nothing");
		}
	}
	myFuRouPai.clear();
	rightFuRouPai.clear();
	frontFuRouPai.clear();
	leftFuRouPai.clear();
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

void MahJongRoom::GetInfo(const Player * pai1, const Player * pai2, const Player * pai3, const Player * pai4)
{
	

	reorder = pai1->tehai->tehai;
	if (reorder.size() > 1) {
		for (int i = 0; i < reorder.size() - 1; ++i) {
			if ((reorder.at(i) == 0 && reorder.at(i + 1) < 5) || (reorder.at(i) == 10 && reorder.at(i + 1) < 15) || (reorder.at(i) == 20 && reorder.at(i + 1) < 25)) {
				int tmp = reorder.at(i);
				reorder.at(i) = reorder.at(i + 1);
				reorder.at(i + 1) = tmp;
			}
		}
		//		處理第二張赤五餅
		if (reorder.at(0) == 0) {
			for (int i = 0; i < reorder.size() - 1; ++i) {
				if ((reorder.at(i) == 0 && reorder.at(i + 1) < 5) || (reorder.at(i) == 10 && reorder.at(i + 1) < 15) || (reorder.at(i) == 20 && reorder.at(i + 1) < 25)) {
					int tmp = reorder.at(i);
					reorder.at(i) = reorder.at(i + 1);
					reorder.at(i + 1) = tmp;
				}
			}
		}
	}

	//vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv		手牌情報
	tsumohai = -1;
	for (int i = myPai.size() - 1; i > reorder.size(); --i) {
		myPai.at(i)->setProperty("NormalImage", "MJ_material/Nothing");
		myPai.at(i)->setProperty("HoverImage", "MJ_material/Nothing");
		myPai.at(i)->setProperty("PushedImage", "MJ_material/Nothing");
	}
		if (pai1->tehai->tsumohai != -1) {
			tsumohai = pai1->tehai->tsumohai;
			
			switch (pai1->tehai->tsumohai)
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
				myPai.at(reorder.size())->setProperty("NormalImage", "MJ_material/Sou5R");
				myPai.at(reorder.size())->setProperty("HoverImage", "MJ_material/Sou5R");
				myPai.at(reorder.size())->setProperty("PushedImage", "MJ_material/Sou5R");
				break;
			case 21:
				myPai.at(reorder.size())->setProperty("NormalImage", "MJ_material/Sou1");
				myPai.at(reorder.size())->setProperty("HoverImage", "MJ_material/Sou1");
				myPai.at(reorder.size())->setProperty("PushedImage", "MJ_material/Sou1");
				break;
			case 22:
				myPai.at(reorder.size())->setProperty("NormalImage", "MJ_material/Sou2");
				myPai.at(reorder.size())->setProperty("HoverImage", "MJ_material/Sou2");
				myPai.at(reorder.size())->setProperty("PushedImage", "MJ_material/Sou2");
				break;
			case 23:
				myPai.at(reorder.size())->setProperty("NormalImage", "MJ_material/Sou3");
				myPai.at(reorder.size())->setProperty("HoverImage", "MJ_material/Sou3");
				myPai.at(reorder.size())->setProperty("PushedImage", "MJ_material/Sou3");
				break;
			case 24:
				myPai.at(reorder.size())->setProperty("NormalImage", "MJ_material/Sou4");
				myPai.at(reorder.size())->setProperty("HoverImage", "MJ_material/Sou4");
				myPai.at(reorder.size())->setProperty("PushedImage", "MJ_material/Sou4");
				break;
			case 25:
				myPai.at(reorder.size())->setProperty("NormalImage", "MJ_material/Sou5");
				myPai.at(reorder.size())->setProperty("HoverImage", "MJ_material/Sou5");
				myPai.at(reorder.size())->setProperty("PushedImage", "MJ_material/Sou5");
				break;
			case 26:
				myPai.at(reorder.size())->setProperty("NormalImage", "MJ_material/Sou6");
				myPai.at(reorder.size())->setProperty("HoverImage", "MJ_material/Sou6");
				myPai.at(reorder.size())->setProperty("PushedImage", "MJ_material/Sou6");
				break;
			case 27:
				myPai.at(reorder.size())->setProperty("NormalImage", "MJ_material/Sou7");
				myPai.at(reorder.size())->setProperty("HoverImage", "MJ_material/Sou7");
				myPai.at(reorder.size())->setProperty("PushedImage", "MJ_material/Sou7");
				break;
			case 28:
				myPai.at(reorder.size())->setProperty("NormalImage", "MJ_material/Sou8");
				myPai.at(reorder.size())->setProperty("HoverImage", "MJ_material/Sou8");
				myPai.at(reorder.size())->setProperty("PushedImage", "MJ_material/Sou8");
				break;
			case 29:
				myPai.at(reorder.size())->setProperty("NormalImage", "MJ_material/Sou9");
				myPai.at(reorder.size())->setProperty("HoverImage", "MJ_material/Sou9");
				myPai.at(reorder.size())->setProperty("PushedImage", "MJ_material/Sou9");
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
		for (int i = 0; i < reorder.size(); ++i) {
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
				myPai.at(i)->setProperty("NormalImage", "MJ_material/Sou5R");
				myPai.at(i)->setProperty("HoverImage", "MJ_material/Sou5R");
				myPai.at(i)->setProperty("PushedImage", "MJ_material/Sou5R");
				break;
			case 21:
				myPai.at(i)->setProperty("NormalImage", "MJ_material/Sou1");
				myPai.at(i)->setProperty("HoverImage", "MJ_material/Sou1");
				myPai.at(i)->setProperty("PushedImage", "MJ_material/Sou1");
				break;
			case 22:
				myPai.at(i)->setProperty("NormalImage", "MJ_material/Sou2");
				myPai.at(i)->setProperty("HoverImage", "MJ_material/Sou2");
				myPai.at(i)->setProperty("PushedImage", "MJ_material/Sou2");
				break;
			case 23:
				myPai.at(i)->setProperty("NormalImage", "MJ_material/Sou3");
				myPai.at(i)->setProperty("HoverImage", "MJ_material/Sou3");
				myPai.at(i)->setProperty("PushedImage", "MJ_material/Sou3");
				break;
			case 24:
				myPai.at(i)->setProperty("NormalImage", "MJ_material/Sou4");
				myPai.at(i)->setProperty("HoverImage", "MJ_material/Sou4");
				myPai.at(i)->setProperty("PushedImage", "MJ_material/Sou4");
				break;
			case 25:
				myPai.at(i)->setProperty("NormalImage", "MJ_material/Sou5");
				myPai.at(i)->setProperty("HoverImage", "MJ_material/Sou5");
				myPai.at(i)->setProperty("PushedImage", "MJ_material/Sou5");
				break;
			case 26:
				myPai.at(i)->setProperty("NormalImage", "MJ_material/Sou6");
				myPai.at(i)->setProperty("HoverImage", "MJ_material/Sou6");
				myPai.at(i)->setProperty("PushedImage", "MJ_material/Sou6");
				break;
			case 27:
				myPai.at(i)->setProperty("NormalImage", "MJ_material/Sou7");
				myPai.at(i)->setProperty("HoverImage", "MJ_material/Sou7");
				myPai.at(i)->setProperty("PushedImage", "MJ_material/Sou7");
				break;
			case 28:
				myPai.at(i)->setProperty("NormalImage", "MJ_material/Sou8");
				myPai.at(i)->setProperty("HoverImage", "MJ_material/Sou8");
				myPai.at(i)->setProperty("PushedImage", "MJ_material/Sou8");
				break;
			case 29:
				myPai.at(i)->setProperty("NormalImage", "MJ_material/Sou9");
				myPai.at(i)->setProperty("HoverImage", "MJ_material/Sou9");
				myPai.at(i)->setProperty("PushedImage", "MJ_material/Sou9");
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

		{
		int p2number = pai2->tehai->tehai.size() + (pai2->tehai->tsumohai != -1 ? 1 : 0);	//手牌數量
		int p3number = pai3->tehai->tehai.size() + (pai3->tehai->tsumohai != -1 ? 1 : 0);
		int p4number = pai4->tehai->tehai.size() + (pai4->tehai->tsumohai != -1 ? 1 : 0);
		if (p2number <= 14 && p2number >= 1 && p3number <= 14 && p3number >= 1 && p4number <= 14 && p4number >= 1) {
			for (int i = 14; i > 14 - p2number; --i) {
				rightPlayer.at(i - 1)->setProperty("Image", "MJ_material/PaiSide");
			}
			for (int i = 0; i < 14 - p2number; ++i) {
				rightPlayer.at(i)->setProperty("Image", "MJ_material/Nothing");
			}
			for (int i = 14; i > 14 - p3number; --i) {
				frontPlayer.at(i - 1)->setProperty("Image", "MJ_material/PaiSide");
			}
			for (int i = 0; i < 14 - p3number; ++i) {
				frontPlayer.at(i)->setProperty("Image", "MJ_material/Nothing");
			}
			for (int i = 14; i > p4number; --i) {
				leftPlayer.at(i - 1)->setProperty("Image", "MJ_material/Nothing");
			}
			for (int i = 0; i < p4number; ++i) {
				leftPlayer.at(i)->setProperty("Image", "MJ_material/PaiSide");
			}
		}
		}
		//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^		手牌情報
		//vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv		捨牌情報
		if (pai1->Sutehai.size() < mySuteNumber) {
			mySutehai.at(mySuteNumber - 1)->setProperty("Image", "MJ_material/Nothing");
			--mySuteNumber;
		}
		if (pai2->Sutehai.size() < rightSuteNumber) {
			rightSutehai.at(rightSuteNumber - 1)->setProperty("Image", "MJ_material/Nothing");
			--rightSuteNumber;
		}
		if (pai3->Sutehai.size() < frontSuteNumber) {
			frontSutehai.at(frontSuteNumber - 1)->setProperty("Image", "MJ_material/Nothing");
			--frontSuteNumber;
		}
		if (pai4->Sutehai.size() < leftSuteNumber) {
			leftSutehai.at(leftSuteNumber - 1)->setProperty("Image", "MJ_material/Nothing");
			--leftSuteNumber;
		}

		richiDekiruPai.clear();
		for (int i = 0; i < pai1->agent->WhatToTenPai.size(); ++i) {
			richiDekiruPai.push_back(pai1->agent->WhatToTenPai.at(i).first);
		}
		if (pai1->tehai->richi&&myRichi == 0) {
			myRichi = mySuteNumber;
			myRichiBo->setVisible(true);
			mySutehai.at(myRichi - 1)->setRotation(CEGUI::Quaternion::axisAngleDegrees(CEGUI::Vector3f(0, 0, 1), 90));
		}
		if (pai2->tehai->richi && rightRichi == 0) {
			rightRichi = rightSuteNumber;
			rightRichiBo->setVisible(true);
			rightSutehai.at(myRichi - 1)->setRotation(CEGUI::Quaternion::axisAngleDegrees(CEGUI::Vector3f(0, 0, 1), 180));
		}
		if (pai3->tehai->richi && frontRichi == 0) {
			frontRichi = frontSuteNumber;
			rightRichiBo->setVisible(true);
			frontSutehai.at(myRichi - 1)->setRotation(CEGUI::Quaternion::axisAngleDegrees(CEGUI::Vector3f(0, 0, 1), 270));
		}
		if (pai4->tehai->richi && leftRichi == 0) {
			leftRichi = leftSuteNumber;
			rightRichiBo->setVisible(true);
			leftSutehai.at(myRichi - 1)->setRotation(CEGUI::Quaternion::axisAngleDegrees(CEGUI::Vector3f(0, 0, 1), 0));
		}


		if (pai1->Sutehai.size() > mySuteNumber) {
			++mySuteNumber;
			int i = mySuteNumber - 1;
			switch (pai1->Sutehai.back())
			{
			case 0:
				mySutehai.at(i)->setProperty("Image", "MJ_material/Pin5R");
				break;
			case 1:
				mySutehai.at(i)->setProperty("Image", "MJ_material/Pin1");
				break;
			case 2:
				mySutehai.at(i)->setProperty("Image", "MJ_material/Pin2");
				break;
			case 3:
				mySutehai.at(i)->setProperty("Image", "MJ_material/Pin3");
				break;
			case 4:
				mySutehai.at(i)->setProperty("Image", "MJ_material/Pin4");
				break;
			case 5:
				mySutehai.at(i)->setProperty("Image", "MJ_material/Pin5");
				break;
			case 6:
				mySutehai.at(i)->setProperty("Image", "MJ_material/Pin6");
				break;
			case 7:
				mySutehai.at(i)->setProperty("Image", "MJ_material/Pin7");
				break;
			case 8:
				mySutehai.at(i)->setProperty("Image", "MJ_material/Pin8");
				break;
			case 9:
				mySutehai.at(i)->setProperty("Image", "MJ_material/Pin9");
				break;
			case 10:
				mySutehai.at(i)->setProperty("Image", "MJ_material/Man5R");
				break;
			case 11:
				mySutehai.at(i)->setProperty("Image", "MJ_material/Man1");
				break;
			case 12:
				mySutehai.at(i)->setProperty("Image", "MJ_material/Man2");
				break;
			case 13:
				mySutehai.at(i)->setProperty("Image", "MJ_material/Man3");
				break;
			case 14:
				mySutehai.at(i)->setProperty("Image", "MJ_material/Man4");
				break;
			case 15:
				mySutehai.at(i)->setProperty("Image", "MJ_material/Man5");
				break;
			case 16:
				mySutehai.at(i)->setProperty("Image", "MJ_material/Man6");
				break;
			case 17:
				mySutehai.at(i)->setProperty("Image", "MJ_material/Man7");
				break;
			case 18:
				mySutehai.at(i)->setProperty("Image", "MJ_material/Man8");
				break;
			case 19:
				mySutehai.at(i)->setProperty("Image", "MJ_material/Man9");
				break;
			case 20:
				mySutehai.at(i)->setProperty("Image", "MJ_material/Sou5R");
				break;
			case 21:
				mySutehai.at(i)->setProperty("Image", "MJ_material/Sou1");
				break;
			case 22:
				mySutehai.at(i)->setProperty("Image", "MJ_material/Sou2");
				break;
			case 23:
				mySutehai.at(i)->setProperty("Image", "MJ_material/Sou3");
				break;
			case 24:
				mySutehai.at(i)->setProperty("Image", "MJ_material/Sou4");
				break;
			case 25:
				mySutehai.at(i)->setProperty("Image", "MJ_material/Sou5");
				break;
			case 26:
				mySutehai.at(i)->setProperty("Image", "MJ_material/Sou6");
				break;
			case 27:
				mySutehai.at(i)->setProperty("Image", "MJ_material/Sou7");
				break;
			case 28:
				mySutehai.at(i)->setProperty("Image", "MJ_material/Sou8");
				break;
			case 29:
				mySutehai.at(i)->setProperty("Image", "MJ_material/Sou9");
				break;
			case 30:
				mySutehai.at(i)->setProperty("Image", "MJ_material/Ton");
				break;
			case 31:
				mySutehai.at(i)->setProperty("Image", "MJ_material/Nan");
				break;
			case 32:
				mySutehai.at(i)->setProperty("Image", "MJ_material/Sha");
				break;
			case 33:
				mySutehai.at(i)->setProperty("Image", "MJ_material/Pei");
				break;
			case 34:
				mySutehai.at(i)->setProperty("Image", "MJ_material/Haku");
				break;
			case 35:
				mySutehai.at(i)->setProperty("Image", "MJ_material/Fa");
				break;
			case 36:
				mySutehai.at(i)->setProperty("Image", "MJ_material/Chun");
				break;
			}
		}
		if (pai2->Sutehai.size() > rightSuteNumber) {
			++rightSuteNumber;
			int i = rightSuteNumber - 1;
			switch (pai2->Sutehai.back())
			{
			case 0:
				rightSutehai.at(i)->setProperty("Image", "MJ_material/Pin5R");
				break;
			case 1:
				rightSutehai.at(i)->setProperty("Image", "MJ_material/Pin1");
				break;
			case 2:
				rightSutehai.at(i)->setProperty("Image", "MJ_material/Pin2");
				break;
			case 3:
				rightSutehai.at(i)->setProperty("Image", "MJ_material/Pin3");
				break;
			case 4:
				rightSutehai.at(i)->setProperty("Image", "MJ_material/Pin4");
				break;
			case 5:
				rightSutehai.at(i)->setProperty("Image", "MJ_material/Pin5");
				break;
			case 6:
				rightSutehai.at(i)->setProperty("Image", "MJ_material/Pin6");
				break;
			case 7:
				rightSutehai.at(i)->setProperty("Image", "MJ_material/Pin7");
				break;
			case 8:
				rightSutehai.at(i)->setProperty("Image", "MJ_material/Pin8");
				break;
			case 9:
				rightSutehai.at(i)->setProperty("Image", "MJ_material/Pin9");
				break;
			case 10:
				rightSutehai.at(i)->setProperty("Image", "MJ_material/Man5R");
				break;
			case 11:
				rightSutehai.at(i)->setProperty("Image", "MJ_material/Man1");
				break;
			case 12:
				rightSutehai.at(i)->setProperty("Image", "MJ_material/Man2");
				break;
			case 13:
				rightSutehai.at(i)->setProperty("Image", "MJ_material/Man3");
				break;
			case 14:
				rightSutehai.at(i)->setProperty("Image", "MJ_material/Man4");
				break;
			case 15:
				rightSutehai.at(i)->setProperty("Image", "MJ_material/Man5");
				break;
			case 16:
				rightSutehai.at(i)->setProperty("Image", "MJ_material/Man6");
				break;
			case 17:
				rightSutehai.at(i)->setProperty("Image", "MJ_material/Man7");
				break;
			case 18:
				rightSutehai.at(i)->setProperty("Image", "MJ_material/Man8");
				break;
			case 19:
				rightSutehai.at(i)->setProperty("Image", "MJ_material/Man9");
				break;
			case 20:
				rightSutehai.at(i)->setProperty("Image", "MJ_material/Sou5R");
				break;
			case 21:
				rightSutehai.at(i)->setProperty("Image", "MJ_material/Sou1");
				break;
			case 22:
				rightSutehai.at(i)->setProperty("Image", "MJ_material/Sou2");
				break;
			case 23:
				rightSutehai.at(i)->setProperty("Image", "MJ_material/Sou3");
				break;
			case 24:
				rightSutehai.at(i)->setProperty("Image", "MJ_material/Sou4");
				break;
			case 25:
				rightSutehai.at(i)->setProperty("Image", "MJ_material/Sou5");
				break;
			case 26:
				rightSutehai.at(i)->setProperty("Image", "MJ_material/Sou6");
				break;
			case 27:
				rightSutehai.at(i)->setProperty("Image", "MJ_material/Sou7");
				break;
			case 28:
				rightSutehai.at(i)->setProperty("Image", "MJ_material/Sou8");
				break;
			case 29:
				rightSutehai.at(i)->setProperty("Image", "MJ_material/Sou9");
				break;
			case 30:
				rightSutehai.at(i)->setProperty("Image", "MJ_material/Ton");
				break;
			case 31:
				rightSutehai.at(i)->setProperty("Image", "MJ_material/Nan");
				break;
			case 32:
				rightSutehai.at(i)->setProperty("Image", "MJ_material/Sha");
				break;
			case 33:
				rightSutehai.at(i)->setProperty("Image", "MJ_material/Pei");
				break;
			case 34:
				rightSutehai.at(i)->setProperty("Image", "MJ_material/Haku");
				break;
			case 35:
				rightSutehai.at(i)->setProperty("Image", "MJ_material/Fa");
				break;
			case 36:
				rightSutehai.at(i)->setProperty("Image", "MJ_material/Chun");
				break;
			}
		}
		if (pai3->Sutehai.size() > frontSuteNumber) {
			++frontSuteNumber;
			int i = frontSuteNumber - 1;
			switch (pai3->Sutehai.back())
			{
			case 0:
				frontSutehai.at(i)->setProperty("Image", "MJ_material/Pin5R");
				break;
			case 1:
				frontSutehai.at(i)->setProperty("Image", "MJ_material/Pin1");
				break;
			case 2:
				frontSutehai.at(i)->setProperty("Image", "MJ_material/Pin2");
				break;
			case 3:
				frontSutehai.at(i)->setProperty("Image", "MJ_material/Pin3");
				break;
			case 4:
				frontSutehai.at(i)->setProperty("Image", "MJ_material/Pin4");
				break;
			case 5:
				frontSutehai.at(i)->setProperty("Image", "MJ_material/Pin5");
				break;
			case 6:
				frontSutehai.at(i)->setProperty("Image", "MJ_material/Pin6");
				break;
			case 7:
				frontSutehai.at(i)->setProperty("Image", "MJ_material/Pin7");
				break;
			case 8:
				frontSutehai.at(i)->setProperty("Image", "MJ_material/Pin8");
				break;
			case 9:
				frontSutehai.at(i)->setProperty("Image", "MJ_material/Pin9");
				break;
			case 10:
				frontSutehai.at(i)->setProperty("Image", "MJ_material/Man5R");
				break;
			case 11:
				frontSutehai.at(i)->setProperty("Image", "MJ_material/Man1");
				break;
			case 12:
				frontSutehai.at(i)->setProperty("Image", "MJ_material/Man2");
				break;
			case 13:
				frontSutehai.at(i)->setProperty("Image", "MJ_material/Man3");
				break;
			case 14:
				frontSutehai.at(i)->setProperty("Image", "MJ_material/Man4");
				break;
			case 15:
				frontSutehai.at(i)->setProperty("Image", "MJ_material/Man5");
				break;
			case 16:
				frontSutehai.at(i)->setProperty("Image", "MJ_material/Man6");
				break;
			case 17:
				frontSutehai.at(i)->setProperty("Image", "MJ_material/Man7");
				break;
			case 18:
				frontSutehai.at(i)->setProperty("Image", "MJ_material/Man8");
				break;
			case 19:
				frontSutehai.at(i)->setProperty("Image", "MJ_material/Man9");
				break;
			case 20:
				frontSutehai.at(i)->setProperty("Image", "MJ_material/Sou5R");
				break;
			case 21:
				frontSutehai.at(i)->setProperty("Image", "MJ_material/Sou1");
				break;
			case 22:
				frontSutehai.at(i)->setProperty("Image", "MJ_material/Sou2");
				break;
			case 23:
				frontSutehai.at(i)->setProperty("Image", "MJ_material/Sou3");
				break;
			case 24:
				frontSutehai.at(i)->setProperty("Image", "MJ_material/Sou4");
				break;
			case 25:
				frontSutehai.at(i)->setProperty("Image", "MJ_material/Sou5");
				break;
			case 26:
				frontSutehai.at(i)->setProperty("Image", "MJ_material/Sou6");
				break;
			case 27:
				frontSutehai.at(i)->setProperty("Image", "MJ_material/Sou7");
				break;
			case 28:
				frontSutehai.at(i)->setProperty("Image", "MJ_material/Sou8");
				break;
			case 29:
				frontSutehai.at(i)->setProperty("Image", "MJ_material/Sou9");
				break;
			case 30:
				frontSutehai.at(i)->setProperty("Image", "MJ_material/Ton");
				break;
			case 31:
				frontSutehai.at(i)->setProperty("Image", "MJ_material/Nan");
				break;
			case 32:
				frontSutehai.at(i)->setProperty("Image", "MJ_material/Sha");
				break;
			case 33:
				frontSutehai.at(i)->setProperty("Image", "MJ_material/Pei");
				break;
			case 34:
				frontSutehai.at(i)->setProperty("Image", "MJ_material/Haku");
				break;
			case 35:
				frontSutehai.at(i)->setProperty("Image", "MJ_material/Fa");
				break;
			case 36:
				frontSutehai.at(i)->setProperty("Image", "MJ_material/Chun");
				break;
			}
		}
		if (pai4->Sutehai.size() > leftSuteNumber) {
			++leftSuteNumber;
			int i = leftSuteNumber - 1;
			switch (pai4->Sutehai.back())
			{
			case 0:
				leftSutehai.at(i)->setProperty("Image", "MJ_material/Pin5R");
				break;
			case 1:
				leftSutehai.at(i)->setProperty("Image", "MJ_material/Pin1");
				break;
			case 2:
				leftSutehai.at(i)->setProperty("Image", "MJ_material/Pin2");
				break;
			case 3:
				leftSutehai.at(i)->setProperty("Image", "MJ_material/Pin3");
				break;
			case 4:
				leftSutehai.at(i)->setProperty("Image", "MJ_material/Pin4");
				break;
			case 5:
				leftSutehai.at(i)->setProperty("Image", "MJ_material/Pin5");
				break;
			case 6:
				leftSutehai.at(i)->setProperty("Image", "MJ_material/Pin6");
				break;
			case 7:
				leftSutehai.at(i)->setProperty("Image", "MJ_material/Pin7");
				break;
			case 8:
				leftSutehai.at(i)->setProperty("Image", "MJ_material/Pin8");
				break;
			case 9:
				leftSutehai.at(i)->setProperty("Image", "MJ_material/Pin9");
				break;
			case 10:
				leftSutehai.at(i)->setProperty("Image", "MJ_material/Man5R");
				break;
			case 11:
				leftSutehai.at(i)->setProperty("Image", "MJ_material/Man1");
				break;
			case 12:
				leftSutehai.at(i)->setProperty("Image", "MJ_material/Man2");
				break;
			case 13:
				leftSutehai.at(i)->setProperty("Image", "MJ_material/Man3");
				break;
			case 14:
				leftSutehai.at(i)->setProperty("Image", "MJ_material/Man4");
				break;
			case 15:
				leftSutehai.at(i)->setProperty("Image", "MJ_material/Man5");
				break;
			case 16:
				leftSutehai.at(i)->setProperty("Image", "MJ_material/Man6");
				break;
			case 17:
				leftSutehai.at(i)->setProperty("Image", "MJ_material/Man7");
				break;
			case 18:
				leftSutehai.at(i)->setProperty("Image", "MJ_material/Man8");
				break;
			case 19:
				leftSutehai.at(i)->setProperty("Image", "MJ_material/Man9");
				break;
			case 20:
				leftSutehai.at(i)->setProperty("Image", "MJ_material/Sou5R");
				break;
			case 21:
				leftSutehai.at(i)->setProperty("Image", "MJ_material/Sou1");
				break;
			case 22:
				leftSutehai.at(i)->setProperty("Image", "MJ_material/Sou2");
				break;
			case 23:
				leftSutehai.at(i)->setProperty("Image", "MJ_material/Sou3");
				break;
			case 24:
				leftSutehai.at(i)->setProperty("Image", "MJ_material/Sou4");
				break;
			case 25:
				leftSutehai.at(i)->setProperty("Image", "MJ_material/Sou5");
				break;
			case 26:
				leftSutehai.at(i)->setProperty("Image", "MJ_material/Sou6");
				break;
			case 27:
				leftSutehai.at(i)->setProperty("Image", "MJ_material/Sou7");
				break;
			case 28:
				leftSutehai.at(i)->setProperty("Image", "MJ_material/Sou8");
				break;
			case 29:
				leftSutehai.at(i)->setProperty("Image", "MJ_material/Sou9");
				break;
			case 30:
				leftSutehai.at(i)->setProperty("Image", "MJ_material/Ton");
				break;
			case 31:
				leftSutehai.at(i)->setProperty("Image", "MJ_material/Nan");
				break;
			case 32:
				leftSutehai.at(i)->setProperty("Image", "MJ_material/Sha");
				break;
			case 33:
				leftSutehai.at(i)->setProperty("Image", "MJ_material/Pei");
				break;
			case 34:
				leftSutehai.at(i)->setProperty("Image", "MJ_material/Haku");
				break;
			case 35:
				leftSutehai.at(i)->setProperty("Image", "MJ_material/Fa");
				break;
			case 36:
				leftSutehai.at(i)->setProperty("Image", "MJ_material/Chun");
				break;
			}
		}
		//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^		捨牌情報
		//vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv		副露情報更新
		int ChiNumber = 0;
		int PonNumber = 0;
		int MinKanNumber = 0;
		int AnKanNumber = 0;
		//vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv		自家
			for (int i = 0; i < pai1->FuRouOrder.size(); ++i) {										//		設定副露牌及橫倒方向
				if (pai1->FuRouOrder.at(i) == Chi && pai1->tehai->chi.size() > ChiNumber) {
					std::vector<int> furou;
					furou.push_back(pai1->tehai->chi.at(ChiNumber).at(0));
					furou.push_back(-1);
					furou.push_back(pai1->tehai->chi.at(ChiNumber).at(1));
					furou.push_back(pai1->tehai->chi.at(ChiNumber).at(2));
					++ChiNumber;
					if (myFuRouPai.size() < pai1->FuRouOrder.size() && myFuRouPai.size() <= i) {
						myFuRouPai.push_back(furou);
					}
					else {
						myFuRouPai.at(i) = furou;
					}
					myFuRou.at(i).at(0)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.729 + 0.115 * -i, 0), CEGUI::UDim(0.928, 0)));
					myFuRou.at(i).at(1)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.729 + 0.115 * -i, 0), CEGUI::UDim(0.865, 0)));
					myFuRou.at(i).at(2)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.768 + 0.115 * -i, 0), CEGUI::UDim(0.92, 0)));
					myFuRou.at(i).at(3)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.802 + 0.115 * -i, 0), CEGUI::UDim(0.92, 0)));
				}
				else if (pai1->FuRouOrder.at(i) == Pon && pai1->tehai->pon.size() > PonNumber) {
					std::vector<int> furou;
					furou.push_back(pai1->tehai->pon.at(PonNumber).at(0));
					furou.push_back(-1);
					furou.push_back(pai1->tehai->pon.at(PonNumber).at(1));
					furou.push_back(pai1->tehai->pon.at(PonNumber).at(2));
					++PonNumber;
					if (myFuRouPai.size() < pai1->FuRouOrder.size() && myFuRouPai.size() <= i) {
						myFuRouPai.push_back(furou);
					}
					else {
						myFuRouPai.at(i) = furou;
					}
					switch (pai1->tehai->pon.at(PonNumber - 1).at(3))
					{
					case 0:
						myFuRou.at(i).at(0)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.798 + 0.115 * -i, 0), CEGUI::UDim(0.928, 0)));
						myFuRou.at(i).at(1)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.798 + 0.115 * -i, 0), CEGUI::UDim(0.865, 0)));
						myFuRou.at(i).at(2)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.723 + 0.115 * -i, 0), CEGUI::UDim(0.92, 0)));
						myFuRou.at(i).at(3)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.758 + 0.115 * -i, 0), CEGUI::UDim(0.92, 0)));
						break;
					case 1:
						myFuRou.at(i).at(0)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.763 + 0.115 * -i, 0), CEGUI::UDim(0.928, 0)));
						myFuRou.at(i).at(1)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.763 + 0.115 * -i, 0), CEGUI::UDim(0.865, 0)));
						myFuRou.at(i).at(2)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.723 + 0.115 * -i, 0), CEGUI::UDim(0.92, 0)));
						myFuRou.at(i).at(3)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.802 + 0.115 * -i, 0), CEGUI::UDim(0.92, 0)));
						break;
					case 2:
						myFuRou.at(i).at(0)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.729 + 0.115 * -i, 0), CEGUI::UDim(0.928, 0)));
						myFuRou.at(i).at(1)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.729 + 0.115 * -i, 0), CEGUI::UDim(0.865, 0)));
						myFuRou.at(i).at(2)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.768 + 0.115 * -i, 0), CEGUI::UDim(0.92, 0)));
						myFuRou.at(i).at(3)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.802 + 0.115 * -i, 0), CEGUI::UDim(0.92, 0)));
						break;
					}
				}
				else if (pai1->FuRouOrder.at(i) == MinKan && pai1->tehai->minkan.size() > MinKanNumber) {
					std::vector<int> furou;
					furou.push_back(pai1->tehai->minkan.at(MinKanNumber).at(0));
					furou.push_back(pai1->tehai->minkan.at(MinKanNumber).at(0));
					furou.push_back(pai1->tehai->minkan.at(MinKanNumber).at(0));
					furou.push_back(pai1->tehai->minkan.at(MinKanNumber).at(0));
					++MinKanNumber;
					if (myFuRouPai.size() < pai1->FuRouOrder.size() && myFuRouPai.size() <= i) {
						myFuRouPai.push_back(furou);
					}
					else {
						myFuRouPai.at(i) = furou;
					}
					switch (pai1->tehai->minkan.at(MinKanNumber - 1).at(1))
					{
					case 0:
						myFuRou.at(i).at(0)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.798 + 0.115 * -i, 0), CEGUI::UDim(0.928, 0)));
						myFuRou.at(i).at(1)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.798 + 0.115 * -i, 0), CEGUI::UDim(0.865, 0)));
						myFuRou.at(i).at(2)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.723 + 0.115 * -i, 0), CEGUI::UDim(0.92, 0)));
						myFuRou.at(i).at(3)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.758 + 0.115 * -i, 0), CEGUI::UDim(0.92, 0)));
						break;
					case 1:
						myFuRou.at(i).at(0)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.763 + 0.115 * -i, 0), CEGUI::UDim(0.928, 0)));
						myFuRou.at(i).at(1)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.763 + 0.115 * -i, 0), CEGUI::UDim(0.865, 0)));
						myFuRou.at(i).at(2)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.723 + 0.115 * -i, 0), CEGUI::UDim(0.92, 0)));
						myFuRou.at(i).at(3)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.802 + 0.115 * -i, 0), CEGUI::UDim(0.92, 0)));
						break;
					case 2:
						myFuRou.at(i).at(0)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.729 + 0.115 * -i, 0), CEGUI::UDim(0.928, 0)));
						myFuRou.at(i).at(1)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.729 + 0.115 * -i, 0), CEGUI::UDim(0.865, 0)));
						myFuRou.at(i).at(2)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.768 + 0.115 * -i, 0), CEGUI::UDim(0.92, 0)));
						myFuRou.at(i).at(3)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.802 + 0.115 * -i, 0), CEGUI::UDim(0.92, 0)));
						break;
					}
				}
				else if (pai1->FuRouOrder.at(i) == AnKan && pai1->tehai->ankan.size() > AnKanNumber) {
					std::vector<int> furou;
					furou.push_back(pai1->tehai->ankan.at(AnKanNumber));
					furou.push_back(pai1->tehai->ankan.at(AnKanNumber));
					furou.push_back(37);
					furou.push_back(37);
					++AnKanNumber;
					if (myFuRouPai.size() < pai1->FuRouOrder.size() && myFuRouPai.size() <= i) {
						myFuRouPai.push_back(furou);
					}
					else {
						myFuRouPai.at(i) = furou;
					}
					myFuRou.at(i).at(0)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.763 + 0.115 * -i, 0), CEGUI::UDim(0.928, 0)));
					myFuRou.at(i).at(1)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.763 + 0.115 * -i, 0), CEGUI::UDim(0.865, 0)));
					myFuRou.at(i).at(2)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.723 + 0.115 * -i, 0), CEGUI::UDim(0.92, 0)));
					myFuRou.at(i).at(3)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.802 + 0.115 * -i, 0), CEGUI::UDim(0.92, 0)));
				}
			}
		//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^		自家
		ChiNumber = 0;
		PonNumber = 0;
		MinKanNumber = 0;
		AnKanNumber = 0;
		//vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv		下家
			for (int i = 0; i < pai2->FuRouOrder.size(); ++i) {										//		設定副露牌及橫倒方向
				if (pai2->FuRouOrder.at(i) == Chi && pai2->tehai->chi.size() > ChiNumber) {
					std::vector<int> furou;
					furou.push_back(pai2->tehai->chi.at(ChiNumber).at(0));
					furou.push_back(-1);
					furou.push_back(pai2->tehai->chi.at(ChiNumber).at(1));
					furou.push_back(pai2->tehai->chi.at(ChiNumber).at(2));
					++ChiNumber;
					if (rightFuRouPai.size() < pai2->FuRouOrder.size() && rightFuRouPai.size() <= i) {
						rightFuRouPai.push_back(furou);
					}
					else {
						rightFuRouPai.at(i) = furou;
					}
					rightFuRou.at(i).at(0)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.802, 0), CEGUI::UDim(0.13 + 0.207 * i, 0)));
					rightFuRou.at(i).at(1)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.768, 0), CEGUI::UDim(0.13 + 0.207 * i, 0)));
					rightFuRou.at(i).at(2)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.798, 0), CEGUI::UDim(0.058 + 0.207 * i, 0)));
					rightFuRou.at(i).at(3)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.798, 0), CEGUI::UDim(-0.005 + 0.207 * i, 0)));
				}
				else if (pai2->FuRouOrder.at(i) == Pon && pai2->tehai->pon.size() > PonNumber) {
					std::vector<int> furou;
					furou.push_back(pai2->tehai->pon.at(PonNumber).at(0));
					furou.push_back(-1);
					furou.push_back(pai2->tehai->pon.at(PonNumber).at(1));
					furou.push_back(pai2->tehai->pon.at(PonNumber).at(2));
					++PonNumber;
					if (rightFuRouPai.size() < pai2->FuRouOrder.size() && rightFuRouPai.size() <= i) {
						rightFuRouPai.push_back(furou);
					}
					else {
						rightFuRouPai.at(i) = furou;
					}
					switch (pai2->tehai->pon.at(PonNumber - 1).at(3))
					{
					case 0:
						rightFuRou.at(i).at(0)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.802, 0), CEGUI::UDim(0.005 + 0.207 * i, 0)));
						rightFuRou.at(i).at(1)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.768, 0), CEGUI::UDim(0.005 + 0.207 * i, 0)));
						rightFuRou.at(i).at(2)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.798, 0), CEGUI::UDim(0.138 + 0.207 * i, 0)));
						rightFuRou.at(i).at(3)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.798, 0), CEGUI::UDim(0.0755 + 0.207 * i, 0)));
						break;
					case 1:
						rightFuRou.at(i).at(0)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.802, 0), CEGUI::UDim(0.065 + 0.207 * i, 0)));
						rightFuRou.at(i).at(1)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.768, 0), CEGUI::UDim(0.065 + 0.207 * i, 0)));
						rightFuRou.at(i).at(2)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.798, 0), CEGUI::UDim(0.138 + 0.207 * i, 0)));
						rightFuRou.at(i).at(3)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.798, 0), CEGUI::UDim(-0.005 + 0.207 * i, 0)));
						break;
					case 2:
						rightFuRou.at(i).at(0)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.802, 0), CEGUI::UDim(0.13 + 0.207 * i, 0)));
						rightFuRou.at(i).at(1)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.768, 0), CEGUI::UDim(0.13 + 0.207 * i, 0)));
						rightFuRou.at(i).at(2)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.798, 0), CEGUI::UDim(0.058 + 0.207 * i, 0)));
						rightFuRou.at(i).at(3)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.798, 0), CEGUI::UDim(-0.005 + 0.207 * i, 0)));
						break;
					}
				}
				else if (pai2->FuRouOrder.at(i) == MinKan && pai2->tehai->minkan.size() > MinKanNumber) {
					std::vector<int> furou;
					furou.push_back(pai2->tehai->minkan.at(MinKanNumber).at(0));
					furou.push_back(pai2->tehai->minkan.at(MinKanNumber).at(0));
					furou.push_back(pai2->tehai->minkan.at(MinKanNumber).at(0));
					furou.push_back(pai2->tehai->minkan.at(MinKanNumber).at(0));
					++MinKanNumber;
					if (rightFuRouPai.size() < pai2->FuRouOrder.size() && rightFuRouPai.size() <= i) {
						rightFuRouPai.push_back(furou);
					}
					else {
						rightFuRouPai.at(i) = furou;
					}
					switch (pai2->tehai->minkan.at(MinKanNumber - 1).at(1))
					{
					case 0:
						rightFuRou.at(i).at(0)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.802, 0), CEGUI::UDim(0.005 + 0.207 * i, 0)));
						rightFuRou.at(i).at(1)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.768, 0), CEGUI::UDim(0.005 + 0.207 * i, 0)));
						rightFuRou.at(i).at(2)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.798, 0), CEGUI::UDim(0.138 + 0.207 * i, 0)));
						rightFuRou.at(i).at(3)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.798, 0), CEGUI::UDim(0.0755 + 0.207 * i, 0)));
						break;
					case 1:
						rightFuRou.at(i).at(0)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.802, 0), CEGUI::UDim(0.065 + 0.207 * i, 0)));
						rightFuRou.at(i).at(1)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.768, 0), CEGUI::UDim(0.065 + 0.207 * i, 0)));
						rightFuRou.at(i).at(2)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.798, 0), CEGUI::UDim(0.138 + 0.207 * i, 0)));
						rightFuRou.at(i).at(3)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.798, 0), CEGUI::UDim(-0.005 + 0.207 * i, 0)));
						break;
					case 2:
						rightFuRou.at(i).at(0)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.802, 0), CEGUI::UDim(0.13 + 0.207 * i, 0)));
						rightFuRou.at(i).at(1)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.768, 0), CEGUI::UDim(0.13 + 0.207 * i, 0)));
						rightFuRou.at(i).at(2)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.798, 0), CEGUI::UDim(0.058 + 0.207 * i, 0)));
						rightFuRou.at(i).at(3)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.798, 0), CEGUI::UDim(-0.005 + 0.207 * i, 0)));
						break;
					}
				}
				else if (pai2->FuRouOrder.at(i) == AnKan && pai2->tehai->ankan.size() > AnKanNumber) {
					std::vector<int> furou;
					furou.push_back(pai2->tehai->ankan.at(AnKanNumber));
					furou.push_back(pai2->tehai->ankan.at(AnKanNumber));
					furou.push_back(37);
					furou.push_back(37);
					++AnKanNumber;
					if (rightFuRouPai.size() < pai2->FuRouOrder.size() && rightFuRouPai.size() <= i) {
						rightFuRouPai.push_back(furou);
					}
					else {
						rightFuRouPai.at(i) = furou;
					}
					rightFuRou.at(i).at(0)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.802, 0), CEGUI::UDim(0.065 + 0.207 * i, 0)));
					rightFuRou.at(i).at(1)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.768, 0), CEGUI::UDim(0.065 + 0.207 * i, 0)));
					rightFuRou.at(i).at(2)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.798, 0), CEGUI::UDim(0.138 + 0.207 * i, 0)));
					rightFuRou.at(i).at(3)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.798, 0), CEGUI::UDim(-0.005 + 0.207 * i, 0)));
				}
			}
			//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^		下家
			ChiNumber = 0;
			PonNumber = 0;
			MinKanNumber = 0;
			AnKanNumber = 0;
			//vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv		對家
			for (int i = 0; i < pai3->FuRouOrder.size(); ++i) {										//		設定副露牌及橫倒方向
				if (pai3->FuRouOrder.at(i) == Chi && pai3->tehai->chi.size() > ChiNumber) {
					std::vector<int> furou;
					furou.push_back(pai3->tehai->chi.at(ChiNumber).at(0));
					furou.push_back(-1);
					furou.push_back(pai3->tehai->chi.at(ChiNumber).at(1));
					furou.push_back(pai3->tehai->chi.at(ChiNumber).at(2));
					++ChiNumber;
					if (frontFuRouPai.size() < pai3->FuRouOrder.size() && frontFuRouPai.size() <= i) {
						frontFuRouPai.push_back(furou);
					}
					else {
						frontFuRouPai.at(i) = furou;
					}
					frontFuRou.at(i).at(0)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.239 + 0.115 * i, 0), CEGUI::UDim(-0.005, 0)));
					frontFuRou.at(i).at(1)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.239 + 0.115 * i, 0), CEGUI::UDim(0.057, 0)));
					frontFuRou.at(i).at(2)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.199 + 0.115 * i, 0), CEGUI::UDim(0.005, 0)));
					frontFuRou.at(i).at(3)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.164 + 0.115 * i, 0), CEGUI::UDim(0.005, 0)));
				}
				else if (pai3->FuRouOrder.at(i) == Pon && pai3->tehai->pon.size() > PonNumber) {
					std::vector<int> furou;
					furou.push_back(pai3->tehai->pon.at(PonNumber).at(0));
					furou.push_back(-1);
					furou.push_back(pai3->tehai->pon.at(PonNumber).at(1));
					furou.push_back(pai3->tehai->pon.at(PonNumber).at(2));
					++PonNumber;
					if (frontFuRouPai.size() < pai3->FuRouOrder.size() && frontFuRouPai.size() <= i) {
						frontFuRouPai.push_back(furou);
					}
					else {
						frontFuRouPai.at(i) = furou;
					}
					switch (pai3->tehai->pon.at(PonNumber - 1).at(3))
					{
					case 0:
						frontFuRou.at(i).at(0)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.17 + 0.115 * i, 0), CEGUI::UDim(-0.005, 0)));
						frontFuRou.at(i).at(1)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.17 + 0.115 * i, 0), CEGUI::UDim(0.057, 0)));
						frontFuRou.at(i).at(2)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.245 + 0.115 * i, 0), CEGUI::UDim(0.005, 0)));
						frontFuRou.at(i).at(3)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.21 + 0.115 * i, 0), CEGUI::UDim(0.005, 0)));
						break;
					case 1:
						frontFuRou.at(i).at(0)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.204 + 0.115 * i, 0), CEGUI::UDim(-0.005, 0)));
						frontFuRou.at(i).at(1)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.204 + 0.115 * i, 0), CEGUI::UDim(0.057, 0)));
						frontFuRou.at(i).at(2)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.244 + 0.115 * i, 0), CEGUI::UDim(0.005, 0)));
						frontFuRou.at(i).at(3)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.164 + 0.115 * i, 0), CEGUI::UDim(0.005, 0)));
						break;
					case 2:
						frontFuRou.at(i).at(0)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.239 + 0.115 * i, 0), CEGUI::UDim(-0.005, 0)));
						frontFuRou.at(i).at(1)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.239 + 0.115 * i, 0), CEGUI::UDim(0.057, 0)));
						frontFuRou.at(i).at(2)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.199 + 0.115 * i, 0), CEGUI::UDim(0.005, 0)));
						frontFuRou.at(i).at(3)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.164 + 0.115 * i, 0), CEGUI::UDim(0.005, 0)));
						break;
					}
				}
				else if (pai3->FuRouOrder.at(i) == MinKan && pai3->tehai->minkan.size() > MinKanNumber) {
					std::vector<int> furou;
					furou.push_back(pai3->tehai->minkan.at(MinKanNumber).at(0));
					furou.push_back(pai3->tehai->minkan.at(MinKanNumber).at(0));
					furou.push_back(pai3->tehai->minkan.at(MinKanNumber).at(0));
					furou.push_back(pai3->tehai->minkan.at(MinKanNumber).at(0));
					++MinKanNumber;
					if (frontFuRouPai.size() < pai3->FuRouOrder.size() && frontFuRouPai.size() <= i) {
						frontFuRouPai.push_back(furou);
					}
					else {
						frontFuRouPai.at(i) = furou;
					}
					switch (pai3->tehai->minkan.at(MinKanNumber - 1).at(1))
					{
					case 0:
						frontFuRou.at(i).at(0)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.17 + 0.115 * i, 0), CEGUI::UDim(-0.005, 0)));
						frontFuRou.at(i).at(1)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.17 + 0.115 * i, 0), CEGUI::UDim(0.057, 0)));
						frontFuRou.at(i).at(2)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.245 + 0.115 * i, 0), CEGUI::UDim(0.005, 0)));
						frontFuRou.at(i).at(3)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.21 + 0.115 * i, 0), CEGUI::UDim(0.005, 0)));
						break;
					case 1:
						frontFuRou.at(i).at(0)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.204 + 0.115 * i, 0), CEGUI::UDim(-0.005, 0)));
						frontFuRou.at(i).at(1)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.204 + 0.115 * i, 0), CEGUI::UDim(0.057, 0)));
						frontFuRou.at(i).at(2)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.244 + 0.115 * i, 0), CEGUI::UDim(0.005, 0)));
						frontFuRou.at(i).at(3)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.164 + 0.115 * i, 0), CEGUI::UDim(0.005, 0)));
						break;
					case 2:
						frontFuRou.at(i).at(0)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.239 + 0.115 * i, 0), CEGUI::UDim(-0.005, 0)));
						frontFuRou.at(i).at(1)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.239 + 0.115 * i, 0), CEGUI::UDim(0.057, 0)));
						frontFuRou.at(i).at(2)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.199 + 0.115 * i, 0), CEGUI::UDim(0.005, 0)));
						frontFuRou.at(i).at(3)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.164 + 0.115 * i, 0), CEGUI::UDim(0.005, 0)));
						break;
					}
				}
				else if (pai3->FuRouOrder.at(i) == AnKan && pai3->tehai->ankan.size() > AnKanNumber) {
					std::vector<int> furou;
					furou.push_back(pai3->tehai->ankan.at(AnKanNumber));
					furou.push_back(pai3->tehai->ankan.at(AnKanNumber));
					furou.push_back(37);
					furou.push_back(37);
					++AnKanNumber;
					if (frontFuRouPai.size() < pai3->FuRouOrder.size() && frontFuRouPai.size() <= i) {
						frontFuRouPai.push_back(furou);
					}
					else {
						frontFuRouPai.at(i) = furou;
					}
					frontFuRou.at(i).at(0)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.204 + 0.115 * i, 0), CEGUI::UDim(-0.005, 0)));
					frontFuRou.at(i).at(1)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.204 + 0.115 * i, 0), CEGUI::UDim(0.057, 0)));
					frontFuRou.at(i).at(2)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.244 + 0.115 * i, 0), CEGUI::UDim(0.005, 0)));
					frontFuRou.at(i).at(3)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.164 + 0.115 * i, 0), CEGUI::UDim(0.005, 0)));
				}
			}
			//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^		對家
			ChiNumber = 0;
			PonNumber = 0;
			MinKanNumber = 0;
			AnKanNumber = 0;
			//vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv		上家
			for (int i = 0; i < pai4->FuRouOrder.size(); ++i) {										//		設定副露牌及橫倒方向
				if (pai4->FuRouOrder.at(i) == Chi && pai4->tehai->chi.size() > ChiNumber) {
					std::vector<int> furou;
					furou.push_back(pai4->tehai->chi.at(ChiNumber).at(0));
					furou.push_back(-1);
					furou.push_back(pai4->tehai->chi.at(ChiNumber).at(1));
					furou.push_back(pai4->tehai->chi.at(ChiNumber).at(2));
					++ChiNumber;
					if (leftFuRouPai.size() < pai4->FuRouOrder.size() && leftFuRouPai.size() <= i) {
						leftFuRouPai.push_back(furou);
					}
					else {
						leftFuRouPai.at(i) = furou;
					}
					leftFuRou.at(i).at(0)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.164, 0), CEGUI::UDim(0.792 + 0.207 * -i, 0)));
					leftFuRou.at(i).at(1)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.198, 0), CEGUI::UDim(0.792 + 0.207 * -i, 0)));
					leftFuRou.at(i).at(2)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.17, 0), CEGUI::UDim(0.865 + 0.207 * -i, 0)));
					leftFuRou.at(i).at(3)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.17, 0), CEGUI::UDim(0.928 + 0.207 * -i, 0)));
				}
				else if (pai4->FuRouOrder.at(i) == Pon && pai4->tehai->pon.size() > PonNumber) {
					std::vector<int> furou;
					furou.push_back(pai4->tehai->pon.at(PonNumber).at(0));
					furou.push_back(-1);
					furou.push_back(pai4->tehai->pon.at(PonNumber).at(1));
					furou.push_back(pai4->tehai->pon.at(PonNumber).at(2));
					++PonNumber;
					if (leftFuRouPai.size() < pai4->FuRouOrder.size() && leftFuRouPai.size() <= i) {
						leftFuRouPai.push_back(furou);
					}
					else {
						leftFuRouPai.at(i) = furou;
					}
					switch (pai4->tehai->pon.at(PonNumber - 1).at(3))
					{
					case 0:
						leftFuRou.at(i).at(0)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.164, 0), CEGUI::UDim(0.918 + 0.207 * -i, 0)));
						leftFuRou.at(i).at(1)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.198, 0), CEGUI::UDim(0.918 + 0.207 * -i, 0)));
						leftFuRou.at(i).at(2)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.17, 0), CEGUI::UDim(0.785 + 0.207 * -i, 0)));
						leftFuRou.at(i).at(3)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.17, 0), CEGUI::UDim(0.847 + 0.207 * -i, 0)));
						break;
					case 1:
						leftFuRou.at(i).at(0)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.164, 0), CEGUI::UDim(0.855 + 0.207 * -i, 0)));
						leftFuRou.at(i).at(1)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.198, 0), CEGUI::UDim(0.855 + 0.207 * -i, 0)));
						leftFuRou.at(i).at(2)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.17, 0), CEGUI::UDim(0.785 + 0.207 * -i, 0)));
						leftFuRou.at(i).at(3)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.17, 0), CEGUI::UDim(0.928 + 0.207 * -i, 0)));
						break;
					case 2:
						leftFuRou.at(i).at(0)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.164, 0), CEGUI::UDim(0.792 + 0.207 * -i, 0)));
						leftFuRou.at(i).at(1)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.198, 0), CEGUI::UDim(0.792 + 0.207 * -i, 0)));
						leftFuRou.at(i).at(2)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.17, 0), CEGUI::UDim(0.865 + 0.207 * -i, 0)));
						leftFuRou.at(i).at(3)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.17, 0), CEGUI::UDim(0.928 + 0.207 * -i, 0)));
						break;
					}
				}
				else if (pai4->FuRouOrder.at(i) == MinKan && pai4->tehai->minkan.size() > MinKanNumber) {
					std::vector<int> furou;
					furou.push_back(pai4->tehai->minkan.at(MinKanNumber).at(0));
					furou.push_back(pai4->tehai->minkan.at(MinKanNumber).at(0));
					furou.push_back(pai4->tehai->minkan.at(MinKanNumber).at(0));
					furou.push_back(pai4->tehai->minkan.at(MinKanNumber).at(0));
					++MinKanNumber;
					if (leftFuRouPai.size() < pai4->FuRouOrder.size() && leftFuRouPai.size() <= i) {
						leftFuRouPai.push_back(furou);
					}
					else {
						leftFuRouPai.at(i) = furou;
					}
					switch (pai4->tehai->minkan.at(MinKanNumber - 1).at(1))
					{
					case 0:
						leftFuRou.at(i).at(0)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.164, 0), CEGUI::UDim(0.918 + 0.207 * -i, 0)));
						leftFuRou.at(i).at(1)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.198, 0), CEGUI::UDim(0.918 + 0.207 * -i, 0)));
						leftFuRou.at(i).at(2)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.17, 0), CEGUI::UDim(0.785 + 0.207 * -i, 0)));
						leftFuRou.at(i).at(3)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.17, 0), CEGUI::UDim(0.847 + 0.207 * -i, 0)));
						break;
					case 1:
						leftFuRou.at(i).at(0)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.164, 0), CEGUI::UDim(0.855 + 0.207 * -i, 0)));
						leftFuRou.at(i).at(1)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.198, 0), CEGUI::UDim(0.855 + 0.207 * -i, 0)));
						leftFuRou.at(i).at(2)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.17, 0), CEGUI::UDim(0.785 + 0.207 * -i, 0)));
						leftFuRou.at(i).at(3)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.17, 0), CEGUI::UDim(0.928 + 0.207 * -i, 0)));
						break;
					case 2:
						leftFuRou.at(i).at(0)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.164, 0), CEGUI::UDim(0.792 + 0.207 * -i, 0)));
						leftFuRou.at(i).at(1)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.198, 0), CEGUI::UDim(0.792 + 0.207 * -i, 0)));
						leftFuRou.at(i).at(2)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.17, 0), CEGUI::UDim(0.865 + 0.207 * -i, 0)));
						leftFuRou.at(i).at(3)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.17, 0), CEGUI::UDim(0.928 + 0.207 * -i, 0)));
						break;
					}
				}
				else if (pai4->FuRouOrder.at(i) == AnKan && pai4->tehai->ankan.size() > AnKanNumber) {
					std::vector<int> furou;
					furou.push_back(pai4->tehai->ankan.at(AnKanNumber));
					furou.push_back(pai4->tehai->ankan.at(AnKanNumber));
					furou.push_back(37);
					furou.push_back(37);
					++AnKanNumber;
					if (leftFuRouPai.size() < pai4->FuRouOrder.size() && leftFuRouPai.size() <= i) {
						leftFuRouPai.push_back(furou);
					}
					else {
						leftFuRouPai.at(i) = furou;
					}
					leftFuRou.at(i).at(0)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.164, 0), CEGUI::UDim(0.855 + 0.207 * -i, 0)));
					leftFuRou.at(i).at(1)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.198, 0), CEGUI::UDim(0.855 + 0.207 * -i, 0)));
					leftFuRou.at(i).at(2)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.17, 0), CEGUI::UDim(0.785 + 0.207 * -i, 0)));
					leftFuRou.at(i).at(3)->setPosition(CEGUI::UVector2(CEGUI::UDim(0.17, 0), CEGUI::UDim(0.928 + 0.207 * -i, 0)));
				}
			}
		//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^		上家
		//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^		副露情報更新
		//vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv		副露情報顯示
		for (int i = 0; i < myFuRouPai.size(); ++i) {
			for (int j = 0; j < 4; ++j) {
				switch (myFuRouPai.at(i).at(j))
				{
				case -1:
					myFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Nothing");
					break;
				case 0:
					myFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Pin5R");
					break;
				case 1:
					myFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Pin1");
					break;
				case 2:
					myFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Pin2");
					break;
				case 3:
					myFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Pin3");
					break;
				case 4:
					myFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Pin4");
					break;
				case 5:
					myFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Pin5");
					break;
				case 6:
					myFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Pin6");
					break;
				case 7:
					myFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Pin7");
					break;
				case 8:
					myFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Pin8");
					break;
				case 9:
					myFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Pin9");
					break;
				case 10:
					myFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Man5R");
					break;
				case 11:
					myFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Man1");
					break;
				case 12:
					myFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Man2");
					break;
				case 13:
					myFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Man3");
					break;
				case 14:
					myFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Man4");
					break;
				case 15:
					myFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Man5");
					break;
				case 16:
					myFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Man6");
					break;
				case 17:
					myFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Man7");
					break;
				case 18:
					myFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Man8");
					break;
				case 19:
					myFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Man9");
					break;
				case 20:
					myFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Sou5R");
					break;
				case 21:
					myFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Sou1");
					break;
				case 22:
					myFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Sou2");
					break;
				case 23:
					myFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Sou3");
					break;
				case 24:
					myFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Sou4");
					break;
				case 25:
					myFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Sou5");
					break;
				case 26:
					myFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Sou6");
					break;
				case 27:
					myFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Sou7");
					break;
				case 28:
					myFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Sou8");
					break;
				case 29:
					myFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Sou9");
					break;
				case 30:
					myFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Ton");
					break;
				case 31:
					myFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Nan");
					break;
				case 32:
					myFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Sha");
					break;
				case 33:
					myFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Pei");
					break;
				case 34:
					myFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Haku");
					break;
				case 35:
					myFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Fa");
					break;
				case 36:
					myFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Chun");
					break;
				case 37:
					myFuRou.at(i).at(j)->setProperty("Image", "MJ_material/PaiBack");
					break;
				}
			}
		}
		for (int i = 0; i < rightFuRouPai.size(); ++i) {
			for (int j = 0; j < 4; ++j) {
				switch (rightFuRouPai.at(i).at(j))
				{
				case -1:
					rightFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Nothing");
					break;
				case 0:
					rightFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Pin5R");
					break;
				case 1:
					rightFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Pin1");
					break;
				case 2:
					rightFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Pin2");
					break;
				case 3:
					rightFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Pin3");
					break;
				case 4:
					rightFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Pin4");
					break;
				case 5:
					rightFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Pin5");
					break;
				case 6:
					rightFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Pin6");
					break;
				case 7:
					rightFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Pin7");
					break;
				case 8:
					rightFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Pin8");
					break;
				case 9:
					rightFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Pin9");
					break;
				case 10:
					rightFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Man5R");
					break;
				case 11:
					rightFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Man1");
					break;
				case 12:
					rightFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Man2");
					break;
				case 13:
					rightFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Man3");
					break;
				case 14:
					rightFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Man4");
					break;
				case 15:
					rightFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Man5");
					break;
				case 16:
					rightFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Man6");
					break;
				case 17:
					rightFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Man7");
					break;
				case 18:
					rightFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Man8");
					break;
				case 19:
					rightFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Man9");
					break;
				case 20:
					rightFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Sou5R");
					break;
				case 21:
					rightFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Sou1");
					break;
				case 22:
					rightFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Sou2");
					break;
				case 23:
					rightFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Sou3");
					break;
				case 24:
					rightFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Sou4");
					break;
				case 25:
					rightFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Sou5");
					break;
				case 26:
					rightFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Sou6");
					break;
				case 27:
					rightFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Sou7");
					break;
				case 28:
					rightFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Sou8");
					break;
				case 29:
					rightFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Sou9");
					break;
				case 30:
					rightFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Ton");
					break;
				case 31:
					rightFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Nan");
					break;
				case 32:
					rightFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Sha");
					break;
				case 33:
					rightFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Pei");
					break;
				case 34:
					rightFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Haku");
					break;
				case 35:
					rightFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Fa");
					break;
				case 36:
					rightFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Chun");
					break;
				case 37:
					rightFuRou.at(i).at(j)->setProperty("Image", "MJ_material/PaiBack");
					break;
				}
			}
		}
		for (int i = 0; i < frontFuRouPai.size(); ++i) {
			for (int j = 0; j < 4; ++j) {
				switch (frontFuRouPai.at(i).at(j))
				{
				case -1:
					frontFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Nothing");
					break;
				case 0:
					frontFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Pin5R");
					break;
				case 1:
					frontFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Pin1");
					break;
				case 2:
					frontFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Pin2");
					break;
				case 3:
					frontFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Pin3");
					break;
				case 4:
					frontFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Pin4");
					break;
				case 5:
					frontFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Pin5");
					break;
				case 6:
					frontFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Pin6");
					break;
				case 7:
					frontFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Pin7");
					break;
				case 8:
					frontFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Pin8");
					break;
				case 9:
					frontFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Pin9");
					break;
				case 10:
					frontFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Man5R");
					break;
				case 11:
					frontFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Man1");
					break;
				case 12:
					frontFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Man2");
					break;
				case 13:
					frontFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Man3");
					break;
				case 14:
					frontFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Man4");
					break;
				case 15:
					frontFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Man5");
					break;
				case 16:
					frontFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Man6");
					break;
				case 17:
					frontFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Man7");
					break;
				case 18:
					frontFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Man8");
					break;
				case 19:
					frontFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Man9");
					break;
				case 20:
					frontFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Sou5R");
					break;
				case 21:
					frontFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Sou1");
					break;
				case 22:
					frontFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Sou2");
					break;
				case 23:
					frontFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Sou3");
					break;
				case 24:
					frontFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Sou4");
					break;
				case 25:
					frontFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Sou5");
					break;
				case 26:
					frontFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Sou6");
					break;
				case 27:
					frontFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Sou7");
					break;
				case 28:
					frontFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Sou8");
					break;
				case 29:
					frontFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Sou9");
					break;
				case 30:
					frontFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Ton");
					break;
				case 31:
					frontFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Nan");
					break;
				case 32:
					frontFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Sha");
					break;
				case 33:
					frontFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Pei");
					break;
				case 34:
					frontFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Haku");
					break;
				case 35:
					frontFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Fa");
					break;
				case 36:
					frontFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Chun");
					break;
				case 37:
					frontFuRou.at(i).at(j)->setProperty("Image", "MJ_material/PaiBack");
					break;
				}
			}
		}
		for (int i = 0; i < leftFuRouPai.size(); ++i) {
			for (int j = 0; j < 4; ++j) {
				switch (leftFuRouPai.at(i).at(j))
				{
				case -1:
					leftFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Nothing");
					break;
				case 0:
					leftFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Pin5R");
					break;
				case 1:
					leftFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Pin1");
					break;
				case 2:
					leftFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Pin2");
					break;
				case 3:
					leftFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Pin3");
					break;
				case 4:
					leftFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Pin4");
					break;
				case 5:
					leftFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Pin5");
					break;
				case 6:
					leftFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Pin6");
					break;
				case 7:
					leftFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Pin7");
					break;
				case 8:
					leftFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Pin8");
					break;
				case 9:
					leftFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Pin9");
					break;
				case 10:
					leftFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Man5R");
					break;
				case 11:
					leftFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Man1");
					break;
				case 12:
					leftFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Man2");
					break;
				case 13:
					leftFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Man3");
					break;
				case 14:
					leftFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Man4");
					break;
				case 15:
					leftFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Man5");
					break;
				case 16:
					leftFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Man6");
					break;
				case 17:
					leftFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Man7");
					break;
				case 18:
					leftFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Man8");
					break;
				case 19:
					leftFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Man9");
					break;
				case 20:
					leftFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Sou5R");
					break;
				case 21:
					leftFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Sou1");
					break;
				case 22:
					leftFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Sou2");
					break;
				case 23:
					leftFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Sou3");
					break;
				case 24:
					leftFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Sou4");
					break;
				case 25:
					leftFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Sou5");
					break;
				case 26:
					leftFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Sou6");
					break;
				case 27:
					leftFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Sou7");
					break;
				case 28:
					leftFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Sou8");
					break;
				case 29:
					leftFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Sou9");
					break;
				case 30:
					leftFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Ton");
					break;
				case 31:
					leftFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Nan");
					break;
				case 32:
					leftFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Sha");
					break;
				case 33:
					leftFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Pei");
					break;
				case 34:
					leftFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Haku");
					break;
				case 35:
					leftFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Fa");
					break;
				case 36:
					leftFuRou.at(i).at(j)->setProperty("Image", "MJ_material/Chun");
					break;
				case 37:
					leftFuRou.at(i).at(j)->setProperty("Image", "MJ_material/PaiBack");
					break;
				}
			}
		}
		//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^		副露情報顯示
}

void MahJongRoom::SetAgent(Agent * p)
{
	player = p;
}

void MahJongRoom::ButtonFunction(int n)
{
	button1->setVisible(false);
	button2->setVisible(false);
	button3->setVisible(false);
	button4->setVisible(false);
	button5->setVisible(false);
	button6->setVisible(false);
	button7->setVisible(false);
	switch (n)
	{
	case 1:
		player->WantToChi = -1;
		player->WantToKan = -1;
		player->WantToPon = -1;
		player->WantToRon = -1;
		player->WantToTsumo = -1;
		player->WantToRichi = -1;
		switchChi = false;
		switchKan = false;
		switchRichi = false;
		break;
	case 2:
		player->WantToChi = 1;
		switchChi = true;
		break;
	case 3:
		player->WantToPon = 1;
		break;
	case 4:
		player->WantToKan = 1;
		if (player->AnKanDekiru) {
			switchKan = true;
		}
		break;
	case 5:
		player->WantToRichi = 1;
		switchRichi = true;
		break;
	case 6:
		player->WantToTsumo = 1;
		break;
	case 7:
		player->WantToRon = 1;
		break;
	}
}
