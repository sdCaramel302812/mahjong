// mahjong.cpp: 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include "tenpai.h"
#include "Tehai.h"
#include <iostream>
#include "Scene.h"
#include "GUI.h"
#include "nstdlib.h"
#include "Manager.h"
#include "MahJongRoom.h"
#include "Player.h"
using std::cout;
using std::endl;

GLFW_Event glfw_input;

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void char_callback(GLFWwindow* window, unsigned int codepoint);


int main()
{
	glfwWindowHint(GLFW_SAMPLES, 4);
	Scene *scene = new Scene(1920, 1080);

	glfwSetCursorPosCallback(scene->window, mouse_callback);
	glfwSetMouseButtonCallback(scene->window, mouse_button_callback);
	glfwSetScrollCallback(scene->window, scroll_callback);
	glfwSetCharCallback(scene->window, char_callback);

	Yaku::SetTable();

	int tehai[] = {
		TON,
		TON,
		TON,
		NAN,
		NAN,
		NAN,
		SHA,
		SHA,
		SHA,
		PEI,
		PEI,
		FA,
		FA
	};
	int tehai2[]{
		MAN2,
		MAN3,
		MAN3,
		MAN3,
		MAN3,
		MAN4,
		MAN4,
		R5MAN,
		MAN6,
		MAN7,
		MAN8,
		MAN8,
		MAN8
	};
	Player *player = new Player();
	player->tehai->Peipai(tehai2);
	player->Tsumo(MAN2);

	//cout << "agari " << AgariCheck(p1) << endl;
	Yaku yaku;
	yaku = YakuCheck(player->tehai, TON, TON);


	player->tehai->ShowTehai();
	yaku.ShowYaku();

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//									記得考慮三色一杯口的雀頭(完成)											   //
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//vvvvvvvvvvvvvvvv	test for cegui
	MahJongRoom *mjr = new MahJongRoom();
	Manager::LayoutList.push_back(mjr);

	mjr->SetAgent(player->agent);
	mjr->GetInfo(player->tehai, player->tehai, player->tehai, player->tehai);


	//CEGUI::PushButton *testbtn = static_cast<CEGUI::PushButton *>(m_ui->createWidget("AlfiskoSkin/Button", glm::vec4(0.83f, 0.9f, 0.17f, 0.1f), glm::vec4(), "testButton", background));
	//wstring ws = TString().str2wstr("full screen");
	//testbtn->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber([=]() {
	//	if (scene->isFullScreen()) {
	//		scene->setFullScreen(false);
	//	}
	//	else {
	//		scene->setFullScreen(true);
	//	}
	//}));
	//testbtn->setText(wcharToUTF8(ws));

	
	//^^^^^^^^^^^^^^^^	test for cegui
	
	while (!glfwWindowShouldClose(scene->window)) {
		//float current_frame = glfwGetTime();
		//dt = current_frame - last_frame;
		//last_frame = current_frame;

		glClearColor(0.2, 0.2, 0.2, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// start to rending

		player->Kiru();
		mjr->GetInfo(player->tehai, player->tehai, player->tehai, player->tehai);

		//vvvvvvvvvvvvvvvv	test for cegui
		glDisable(GL_DEPTH_TEST);
		for (int i = 0; i < Manager::LayoutList.size(); ++i) {
			if (Manager::LayoutList.at(i)->active) {
				Manager::LayoutList.at(i)->m_gui->update();
				Manager::LayoutList.at(i)->m_gui->glfwKeyEvent(scene);
				Manager::LayoutList.at(i)->m_gui->glfwEvent(glfw_input, scene->window);
				Manager::LayoutList.at(i)->m_gui->draw();
			}
		}
		glEnable(GL_DEPTH_TEST);
		//^^^^^^^^^^^^^^^^	test for cegui
		

		// end of loop

		//////////////////////////////////////	end of the main loop	//////////////////////////////////////
		glfwSwapBuffers(scene->window);
		glfwPollEvents();
	}

	
	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
    return 0;
}


void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	glfw_input.mouse_x_pos = xpos;
	glfw_input.mouse_y_pos = ypos;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	glfw_input.mouse_button = button;
	glfw_input.mouse_action = action;
	glfw_input.mouse_mods = mods;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	glfw_input.wheel_xoffset = xoffset;
	glfw_input.wheel_yoffset = yoffset;

}

void char_callback(GLFWwindow* window, unsigned int codepoint) {
	for (int i = 0; i < Manager::LayoutList.size(); ++i) {
		Manager::LayoutList.at(i)->m_gui->ChnInjectChar(codepoint);
	};
}
