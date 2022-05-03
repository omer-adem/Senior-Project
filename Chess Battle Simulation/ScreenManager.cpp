#include "ScreenManager.h"
#include <iostream>

ScreenManager::ScreenManager(Vector2i resolution)
{
	screens[0] = make_unique<MainMenuScreen>(resolution, this);
	screens[1] = make_unique<GameScreen>(resolution, this);
}

void ScreenManager::initMenuScreen(Vector2i& resolution)
{
	screens[0] = make_unique<MainMenuScreen>(resolution, this);
}

void ScreenManager::changeScreen(string name)
{
	currentScreen = name;
	screens[findScreen()]->init();
}

int ScreenManager::findScreen()
{
	if (currentScreen == "MainMenuScreen")
		return 0;
	else if (currentScreen == "GameScreen")
		return 1;
}

void ScreenManager::draw(RenderWindow& window)
{
	screens[findScreen()]->draw(window);
}

void ScreenManager::input(RenderWindow& window)
{
	screens[findScreen()]->input(window);
}

void ScreenManager::update(float seconds)
{
	screens[findScreen()]->update(seconds);
}