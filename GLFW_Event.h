#pragma once
class GLFW_Event
{
public:
	GLFW_Event();
	~GLFW_Event();
	int mouse_button;
	int mouse_action;
	int mouse_mods;
	double mouse_x_pos;
	double mouse_y_pos;
	double wheel_xoffset;
	double wheel_yoffset;
};

