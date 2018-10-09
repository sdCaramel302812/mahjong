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

//				牌型測試
int tehai[] = {
	TON,
	TON,
	TON,
	NAN,
	NAN,
	NAN,
	SHA,
	6,
	0,
	PEI,
	PEI,
	7,
	PEI
};
int tehai2[]{
	14,
	15,
	16,
	19,
	19,
	21,
	22,
	23,
	20,
	25,
	25,
	26,
	26
};
//


int main()
{
	srand(time(NULL));

	glfwWindowHint(GLFW_SAMPLES, 4);
	Scene *scene = new Scene(1920, 1080);

	glfwSetCursorPosCallback(scene->window, mouse_callback);
	glfwSetMouseButtonCallback(scene->window, mouse_button_callback);
	glfwSetScrollCallback(scene->window, scroll_callback);
	glfwSetCharCallback(scene->window, char_callback);


	Yaku::SetTable();

	Manager::GameRoom->Init();
	Manager::CurrentLayout = "Game";

	Manager::GameRoom->pl1->tehai->Peipai(tehai2);
	//Manager::GameRoom->pl1->Tsumo(16);
	//Manager::GameRoom->pl1->tehai->ronhai = 30;

//	Manager::GameRoom->pl1->tehai->Pon(33, 0);
//	Manager::GameRoom->pl1->tehai->Kiru(28);
//	Manager::GameRoom->pl1->tehai->Daiminkan(31, 0);
//	Manager::GameRoom->pl1->Tsumo(1);
//	Manager::GameRoom->pl1->tehai->Kiru(1);
//	Manager::GameRoom->pl1->tehai->Pon(30, 0);
//	Manager::GameRoom->pl1->tehai->Kiru(28);
	//Manager::GameRoom->pl1->Tsumo(16);
	Manager::GameRoom->pl1->tehai->ronhai = 19;

	Yaku yaku;
	yaku = YakuCheck(Manager::GameRoom->pl1->tehai, TON, TON);

	Manager::GameRoom->pl1->tehai->ShowTehai();
	yaku.ShowYaku();
	Manager::GameRoom->Init();
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//									記得考慮三色一杯口的雀頭(完成)												//
	//										裸單騎時會 crash(完成)													//
	//									放棄和了後會停在 state 1(完成)												//
	//									 有時候無法自摸 / 和牌(完成)												//
	//											有時候吃會 crash													//
	//										   大概是吃的時候點錯													//
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//vvvvvvvvvvvvvvvv	test for cegui
	MahJongRoom *mjr = new MahJongRoom();
	Manager::LayoutList["GameRoom"]= mjr;

	mjr->SetAgent(Manager::GameRoom->pl1->agent);
	
	//^^^^^^^^^^^^^^^^	test for cegui
	

	float dt = 0;
	float last_frame = glfwGetTime();
	//////////////////////////////////////	start of the main loop	//////////////////////////////////////
	while (!glfwWindowShouldClose(scene->window)) {
		float current_frame = glfwGetTime();
		dt = current_frame - last_frame;
		last_frame = current_frame;

		glClearColor(0.2, 0.2, 0.2, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// start to rending


		


			//vvvvvvvvvvvvvvvv
			if (Manager::CurrentLayout == "Game") {
				Manager::GameRoom->Play();
				mjr->Act();
				if (Manager::GameRoom->UpdateScene) {
					mjr->GetInfo(Manager::GameRoom->pl1, Manager::GameRoom->pl2, Manager::GameRoom->pl3, Manager::GameRoom->pl4);
					Manager::GameRoom->UpdateScene = false;
				}
				if (Manager::GameRoom->kyoukuover) {
					mjr->Reset();
				}
			}
			//^^^^^^^^^^^^^^^^


		//vvvvvvvvvvvvvvvv				cegui
		glDisable(GL_DEPTH_TEST);
		for (std::map<std::string, Layout *>::iterator i = Manager::LayoutList.begin(); i != Manager::LayoutList.end(); ++i) {
			if (i->second->active) {
				i->second->m_gui->update();
				i->second->m_gui->glfwKeyEvent(scene);
				i->second->m_gui->glfwEvent(glfw_input, scene->window);
				i->second->m_gui->draw();
			}
		}
		glEnable(GL_DEPTH_TEST);
		//^^^^^^^^^^^^^^^^				cegui


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
	for (std::map<std::string, Layout *>::iterator i = Manager::LayoutList.begin(); i != Manager::LayoutList.end(); ++i) {
		i->second->m_gui->ChnInjectChar(codepoint);
	};
}
