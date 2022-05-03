#pragma once
#include "Panel.h"

class GamePanel : public Panel
{
private:
	Button buttons[2];
	Sprite money;
	Text moneyAmount;
	Text roundInfo;
	Text timeInfo;
	Text expInfo;
	RectangleShape r_player;
	RectangleShape r_cpu;
	Text playerInfo;
	Text cpuInfo;
	Sprite playerLife;
	Sprite cpuLife;
	RectangleShape cpuLifeBar;
	RectangleShape playerLifeBar;
	float timer = 0;
public:
	GamePanel(Vector2i resolution);
	virtual void draw(RenderWindow& window);
	virtual void update(float seconds);
	void setRound(int r,string phase);
	void setMoney();
	void setTimer();
	void setExpLevel(int xp, int req, int lvl);
	void setHealth();
	void reset();
	virtual Button* getButtons();
};