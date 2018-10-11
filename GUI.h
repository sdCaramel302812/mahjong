#pragma once
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>
#include <glm/glm.hpp>
#include "SDL/SDL_events.h"
#include "GLFW_Event.h"
#include "Scene.h"
#include <ctime>


class GUI {
public:
	void init(const std::string& resourceDirectory);
	void destroy();

	void draw();
	void update();

	void setMouseCursor(const std::string& imageFile);
	void showMouseCursor();
	void hideMouseCursor();

	void glfwEvent(GLFW_Event &event, GLFWwindow *window);
	void glfwKeyEvent(Scene *scene);
	bool ChnInjectChar(CEGUI::utf32 code_point);

	void loadScheme(const std::string& schemeFile);
	void setFont(const std::string& fontFile);
	CEGUI::Window* createWidget(const std::string& type, const glm::vec4& destRectPerc, const glm::vec4& destRectPix, const std::string& name = "", CEGUI::Window* root = nullptr);
	void setWidgetDestRect(CEGUI::Window* widget, const glm::vec4& destRectPerc, const glm::vec4& destRectPix);

	// Getters
	CEGUI::OpenGL3Renderer* getRenderer() { return m_renderer; }
	const CEGUI::GUIContext* getContext() { return m_context; }
private:
	int last_press = 0;
	static CEGUI::OpenGL3Renderer* m_renderer;
	CEGUI::GUIContext* m_context = nullptr;
	CEGUI::Window* m_root = nullptr;
	unsigned int m_lastTime = 0;
};