#pragma once
#include "RemoteManager.h"
#include "MainMenuScreen.h"
#include "GameScreen.h"

class ScreenManager : public RemoteManager
{
private:
	string currentScreen = "MainMenuScreen";
	unique_ptr<Screen> screens[2];
	void initMenuScreen(Vector2i& resolution);
public:
	ScreenManager(Vector2i resolution);
	virtual void input(RenderWindow& window);
	virtual void update(float seconds);
	virtual void draw(RenderWindow& window);
	virtual void changeScreen(string name);
	virtual int findScreen();
};