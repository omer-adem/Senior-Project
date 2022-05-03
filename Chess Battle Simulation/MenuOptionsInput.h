#pragma once
#include "InputHandler.h"
#include "MenuOptionsPanel.h"

class MenuOptionsInput : public InputHandler
{

public:
	MenuOptionsInput(Panel* mp, Screen* ms);
	void virtual input(RenderWindow& window, Event& event);
};
