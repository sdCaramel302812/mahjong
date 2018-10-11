#include "stdafx.h"
#include "GUI.h"
#include "GUI.h"
#include "SDL/SDL_timer.h"

CEGUI::OpenGL3Renderer* GUI::m_renderer = nullptr;

bool GUI::ChnInjectChar(CEGUI::utf32 code_point)
{
#ifndef UNICODE
	static char s_tempChar[3] = "";
	static wchar_t s_tempWchar[2] = L"";
	static bool s_flag = false;
	unsigned char uch = (unsigned char)code_point;
	/*	if (uch >= 0xA1)
	{
	if (!s_flag)
	{
	s_tempChar[0] = (char)uch; //第一个字?
	s_flag = true;
	return true;
	}
	else if (uch >= 0xA1)
	{
	s_tempChar[1] = (char)uch; //第二个字?
	s_flag = false;
	MultiByteToWideChar(0, 0, s_tempChar, 2, s_tempWchar, 1); //?成?字?
	s_tempWchar[1] = L'\0';
	CEGUI::utf32 code = (CEGUI::utf32)s_tempWchar[0];
	return m_context->injectChar(code);
	}
	else
	{
	return m_context->injectChar(code_point);
	}
	}
	else
	{*/
	s_flag = false;
	return m_context->injectChar(code_point);
	//	}
#else
	return m_context->injectChar(code_point);
#endif
}

void GUI::init(const std::string& resourceDirectory) {
	// Check if the renderer and system were not already initialized
	if (m_renderer == nullptr) {
		m_renderer = &CEGUI::OpenGL3Renderer::bootstrapSystem();

		CEGUI::DefaultResourceProvider* rp = static_cast<CEGUI::DefaultResourceProvider*>(CEGUI::System::getSingleton().getResourceProvider());
		
		rp->setResourceGroupDirectory("imagesets", resourceDirectory + "/imagesets/");
		rp->setResourceGroupDirectory("schemes", resourceDirectory + "/schemes/");
		rp->setResourceGroupDirectory("fonts", resourceDirectory + "/fonts/");
		rp->setResourceGroupDirectory("layouts", resourceDirectory + "/layouts/");
		rp->setResourceGroupDirectory("looknfeels", resourceDirectory + "/looknfeel/");
		rp->setResourceGroupDirectory("lua_scripts", resourceDirectory + "/lua_scripts/");
		

		CEGUI::ImageManager::setImagesetDefaultResourceGroup("imagesets");
		CEGUI::Scheme::setDefaultResourceGroup("schemes");
		CEGUI::Font::setDefaultResourceGroup("fonts");
		CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");
		CEGUI::WindowManager::setDefaultResourceGroup("layouts");
		CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts");
	}

	m_context = &CEGUI::System::getSingleton().createGUIContext(m_renderer->getDefaultRenderTarget());
	m_root = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow", "root");
	m_context->setRootWindow(m_root);
}

void GUI::destroy() {
	CEGUI::System::getSingleton().destroyGUIContext(*m_context);
}

void GUI::draw() {
	m_renderer->beginRendering();
	m_context->draw();
	m_renderer->endRendering();
	glDisable(GL_SCISSOR_TEST);
}

void GUI::update() {
	unsigned int elapsed;
	if (m_lastTime == 0) {
		elapsed = 0;
		m_lastTime = clock();
	}
	else {
		unsigned int nextTime = clock();
		elapsed = nextTime - m_lastTime;
		m_lastTime = nextTime;
	}
	m_context->injectTimePulse((float)elapsed / 1000.0f);
}

void GUI::setMouseCursor(const std::string& imageFile) {
	m_context->getMouseCursor().setDefaultImage(imageFile);
}

void GUI::showMouseCursor() {
	m_context->getMouseCursor().show();
}

void GUI::hideMouseCursor() {
	m_context->getMouseCursor().hide();
}

CEGUI::Key::Scan glfwToCEGUIKey(int key) {
	using namespace CEGUI;
	switch (key) {
	case GLFW_KEY_BACKSPACE:    return Key::Backspace;
	case GLFW_KEY_TAB:          return Key::Tab;
	case GLFW_KEY_ENTER:       return Key::Return;
	case GLFW_KEY_PAUSE:        return Key::Pause;
	case GLFW_KEY_ESCAPE:       return Key::Escape;
	case GLFW_KEY_SPACE:        return Key::Space;
	case GLFW_KEY_COMMA:        return Key::Comma;
	case GLFW_KEY_MINUS:        return Key::Minus;
	case GLFW_KEY_PERIOD:       return Key::Period;
	case GLFW_KEY_SLASH:        return Key::Slash;
	case GLFW_KEY_0:            return Key::Zero;
	case GLFW_KEY_1:            return Key::One;
	case GLFW_KEY_2:            return Key::Two;
	case GLFW_KEY_3:            return Key::Three;
	case GLFW_KEY_4:            return Key::Four;
	case GLFW_KEY_5:            return Key::Five;
	case GLFW_KEY_6:            return Key::Six;
	case GLFW_KEY_7:            return Key::Seven;
	case GLFW_KEY_8:            return Key::Eight;
	case GLFW_KEY_9:            return Key::Nine;
		//case GLFW_KEY:        return Key::Colon;
	case GLFW_KEY_SEMICOLON:    return Key::Semicolon;
		//case GLFW_KEY_EQUALS:       return Key::Equals;
		//case GLFW_KEY_BRACKET:  return Key::LeftBracket;
	case GLFW_KEY_BACKSLASH:    return Key::Backslash;
		//case GLFW_KEY_RIGHTBRACKET: return Key::RightBracket;
	case GLFW_KEY_A:            return Key::A;
	case GLFW_KEY_B:            return Key::B;
	case GLFW_KEY_C:            return Key::C;
	case GLFW_KEY_D:            return Key::D;
	case GLFW_KEY_E:            return Key::E;
	case GLFW_KEY_F:            return Key::F;
	case GLFW_KEY_G:            return Key::G;
	case GLFW_KEY_H:            return Key::H;
	case GLFW_KEY_I:            return Key::I;
	case GLFW_KEY_J:            return Key::J;
	case GLFW_KEY_K:            return Key::K;
	case GLFW_KEY_L:            return Key::L;
	case GLFW_KEY_M:            return Key::M;
	case GLFW_KEY_N:            return Key::N;
	case GLFW_KEY_O:            return Key::O;
	case GLFW_KEY_P:            return Key::P;
	case GLFW_KEY_Q:            return Key::Q;
	case GLFW_KEY_R:            return Key::R;
	case GLFW_KEY_S:            return Key::S;
	case GLFW_KEY_T:            return Key::T;
	case GLFW_KEY_U:            return Key::U;
	case GLFW_KEY_V:            return Key::V;
	case GLFW_KEY_W:            return Key::W;
	case GLFW_KEY_X:            return Key::X;
	case GLFW_KEY_Y:            return Key::Y;
	case GLFW_KEY_Z:            return Key::Z;
	case GLFW_KEY_DELETE:       return Key::Delete;
		//case GLFW_KEY_PERIOD:    return Key::Decimal;
	case GLFW_KEY_KP_DIVIDE:    return Key::Divide;
	case GLFW_KEY_KP_MULTIPLY:  return Key::Multiply;
		//case GLFW_KEY_MINUS:     return Key::Subtract;
		//case GLFW_KEY_KP_PLUS:      return Key::Add;
	case GLFW_KEY_KP_ENTER:     return Key::NumpadEnter;
		//case GLFW_KEY_KP_EQUALS:    return Key::NumpadEquals;
	case GLFW_KEY_UP:           return Key::ArrowUp;
	case GLFW_KEY_DOWN:         return Key::ArrowDown;
	case GLFW_KEY_RIGHT:        return Key::ArrowRight;
	case GLFW_KEY_LEFT:         return Key::ArrowLeft;
	case GLFW_KEY_INSERT:       return Key::Insert;
	case GLFW_KEY_HOME:         return Key::Home;
	case GLFW_KEY_END:          return Key::End;
	case GLFW_KEY_PAGE_UP:       return Key::PageUp;
	case GLFW_KEY_PAGE_DOWN:     return Key::PageDown;
	case GLFW_KEY_F1:           return Key::F1;
	case GLFW_KEY_F2:           return Key::F2;
	case GLFW_KEY_F3:           return Key::F3;
	case GLFW_KEY_F4:           return Key::F4;
	case GLFW_KEY_F5:           return Key::F5;
	case GLFW_KEY_F6:           return Key::F6;
	case GLFW_KEY_F7:           return Key::F7;
	case GLFW_KEY_F8:           return Key::F8;
	case GLFW_KEY_F9:           return Key::F9;
	case GLFW_KEY_F10:          return Key::F10;
	case GLFW_KEY_F11:          return Key::F11;
	case GLFW_KEY_F12:          return Key::F12;
	case GLFW_KEY_F13:          return Key::F13;
	case GLFW_KEY_F14:          return Key::F14;
	case GLFW_KEY_F15:          return Key::F15;
	case GLFW_KEY_RIGHT_SHIFT:       return Key::RightShift;
	case GLFW_KEY_LEFT_SHIFT:       return Key::LeftShift;
	case GLFW_KEY_RIGHT_CONTROL:        return Key::RightControl;
	case GLFW_KEY_LEFT_CONTROL:        return Key::LeftControl;
	case GLFW_KEY_RIGHT_ALT:         return Key::RightAlt;
	case GLFW_KEY_LEFT_ALT:         return Key::LeftAlt;
		//case GLFW_KEY_:       return Key::SysRq;
		//case SDLK_MENU:         return Key::AppMenu;
		//case SDLK_POWER:        return Key::Power;
	default:                return Key::Unknown;
	}
}


CEGUI::MouseButton glfwButtonToCEGUIButton(int glfwButton) {
	switch (glfwButton) {
	case GLFW_MOUSE_BUTTON_LEFT: return CEGUI::MouseButton::LeftButton;
	case GLFW_MOUSE_BUTTON_MIDDLE: return CEGUI::MouseButton::MiddleButton;
	case GLFW_MOUSE_BUTTON_RIGHT: return CEGUI::MouseButton::RightButton;
		//case SDL_BUTTON_X1: return CEGUI::MouseButton::X1Button;
		//case SDL_BUTTON_X2: return CEGUI::MouseButton::X2Button;
	}
	return CEGUI::MouseButton::NoButton;
}


void GUI::glfwEvent(GLFW_Event & event, GLFWwindow * window)
{
	if (event.mouse_action == GLFW_PRESS) {
		m_context->injectMouseButtonDown(glfwButtonToCEGUIButton(event.mouse_button));
	}
	if (event.mouse_action == GLFW_RELEASE) {
		m_context->injectMouseButtonUp(glfwButtonToCEGUIButton(event.mouse_button));
	}
	m_context->injectMousePosition(event.mouse_x_pos, event.mouse_y_pos);
}

void GUI::glfwKeyEvent(Scene *sc) {
	int current_press = clock();
	if (current_press - last_press > 70) {

		if (glfwGetKey(sc->window, GLFW_KEY_BACKSPACE) == GLFW_PRESS) {
			m_context->injectKeyDown(CEGUI::Key::Backspace);
			last_press = current_press;
		}
		if (glfwGetKey(sc->window, GLFW_KEY_LEFT) == GLFW_PRESS) {
			last_press = current_press;
			m_context->injectKeyDown(CEGUI::Key::ArrowLeft);
		}
		if (glfwGetKey(sc->window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
			last_press = current_press;
			m_context->injectKeyDown(CEGUI::Key::ArrowRight);
		}
		if (glfwGetKey(sc->window, GLFW_KEY_UP) == GLFW_PRESS) {
			last_press = current_press;
			m_context->injectKeyDown(CEGUI::Key::ArrowUp);
		}
		if (glfwGetKey(sc->window, GLFW_KEY_DOWN) == GLFW_PRESS) {
			last_press = current_press;
			m_context->injectKeyDown(CEGUI::Key::ArrowDown);
		}
		if (glfwGetKey(sc->window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
			m_context->injectKeyDown(CEGUI::Key::LeftShift);
			last_press = current_press;
		}
		if (glfwGetKey(sc->window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) {
			m_context->injectKeyUp(CEGUI::Key::LeftShift);
			last_press = current_press;
		}

	}
}

void GUI::loadScheme(const std::string& schemeFile) {
	CEGUI::SchemeManager::getSingleton().createFromFile(schemeFile);
}

CEGUI::Window* GUI::createWidget(const std::string& type, const glm::vec4& destRectPerc, const glm::vec4& destRectPix, const std::string& name , CEGUI::Window* root) {
	CEGUI::Window* newWindow = CEGUI::WindowManager::getSingleton().createWindow(type, name);
	if(root == nullptr) {
		m_root->addChild(newWindow);
	}
	else {
		root->addChild(newWindow);
	}
	setWidgetDestRect(newWindow, destRectPerc, destRectPix);
	return newWindow;
}

void GUI::setWidgetDestRect(CEGUI::Window* widget, const glm::vec4& destRectPerc, const glm::vec4& destRectPix) {
	widget->setPosition(CEGUI::UVector2(CEGUI::UDim(destRectPerc.x, destRectPix.x), CEGUI::UDim(destRectPerc.y, destRectPix.y)));
	widget->setSize(CEGUI::USize(CEGUI::UDim(destRectPerc.z, destRectPix.z), CEGUI::UDim(destRectPerc.w, destRectPix.w)));
}

void GUI::setFont(const std::string& fontFile) {
	CEGUI::FontManager::getSingleton().createFromFile(fontFile + ".font");
	m_context->setDefaultFont(fontFile);
}
