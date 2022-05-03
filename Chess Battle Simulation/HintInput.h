#pragma once
#include "InputHandler.h"

class HintInput : public InputHandler
{
public:
	void virtual input(RenderWindow& window, Event& event);
	HintInput(Panel* mp, Screen* ms);
};
