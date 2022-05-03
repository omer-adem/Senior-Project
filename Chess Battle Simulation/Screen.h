#pragma once
#include <SFML/Graphics.hpp>
#include "Panel.h"
#include "InputHandler.h"
#include <thread>
using namespace sf;
using namespace std;
class Screen
{
public:
	void virtual input(RenderWindow& window) = 0;
	void virtual draw(RenderWindow& window) = 0;
	void virtual update(float seconds) = 0;
	void virtual changePanel(string name) = 0;
	void virtual init() = 0;
	View m_View;
	string m_currentPanel;
	Sprite background;
	thread* th1;
	thread* th2;
};