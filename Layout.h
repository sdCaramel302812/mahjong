#pragma once
#include "GUI.h"

class Layout
{
public:
	Layout();
	~Layout();

	virtual bool init() = 0;
	virtual void destroy() = 0;
	virtual void update(float dt){}

	GUI *m_gui;
	bool active = true;
};

