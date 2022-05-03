#pragma once
#include "InputHandler.h"
#include "UnitTeam.h"

class ShopInput : public InputHandler
{
private:
	Panel* pointerToGamePanel;

public:
	void virtual input(RenderWindow& window, Event& event);
	ShopInput(Panel* mp, Screen* ms,Panel* gp);
	~ShopInput() { delete pointerToGamePanel; }
};