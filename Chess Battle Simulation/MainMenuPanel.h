#pragma once
#include "Panel.h"

class MainMenuPanel : public Panel
{
private:
	Button buttons[4];
public:
	MainMenuPanel(Vector2i resolution);
	void virtual draw(RenderWindow& window);
	virtual void update(float seconds) {}
	virtual Button* getButtons();
};