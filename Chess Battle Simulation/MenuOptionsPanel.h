#pragma once
#include "Panel.h"
class MenuOptionsPanel : public Panel
{
private:
	Button buttons[8];
	Text header;
	Text t_texts[4];
	RectangleShape r_settings;
	Sprite tick;
public:
	MenuOptionsPanel(Vector2i resolution);
	void virtual draw(RenderWindow& window);
	virtual void update(float seconds) {}
	virtual Button* getButtons();
	RectangleShape r_volumelevel;
};