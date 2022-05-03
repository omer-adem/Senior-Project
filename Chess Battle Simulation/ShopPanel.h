#pragma once
#include "Panel.h"

class ShopPanel : public Panel
{
private:
	Button buttons[3];
	Text header;
	RectangleShape r_shop;
	Sprite troops[3];
	Text t_names[3];
	RectangleShape r_stats[3];
	Text t_stats[3];
public:
	ShopPanel(Vector2i resolution);
	void virtual draw(RenderWindow& window);
	virtual void update(float seconds) {}
	virtual Button* getButtons();
	Sprite* getTroops();
	void setTroops(Sprite units[3], string names[3], string stats[3]);
	bool clearTroop(int ID);
};