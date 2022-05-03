#pragma once
#include "InputHandler.h"

class MainMenuInput : public InputHandler
{
public:
	MainMenuInput(Panel* mp, Screen* ms,RemoteManager* sm);
	void virtual input(RenderWindow& window,Event& event);
};
