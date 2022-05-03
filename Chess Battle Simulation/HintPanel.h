#pragma once
#include "Panel.h"

class HintPanel : public Panel
{
private:
	Button button;
	Text header;
	Text hints[3];
	Text hint1Info;
	Text hint2Info;
	Text hint3Info;
	RectangleShape r_hints;
	Sprite shop;
	Sprite troopex;


public:
	HintPanel(Vector2i resolution);
	virtual void draw(RenderWindow& window);
	virtual void update(float seconds) {}
	virtual Button* getButtons();
};