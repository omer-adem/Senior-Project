#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"

using namespace sf;
using namespace std;
class Panel
{
public:
	const int TxtOffset = 105;
	const int buttonWidth = 200;
	const int buttonHeight = 50;
	int timeValue;
	void virtual draw(RenderWindow& window) = 0;
	virtual void update(float seconds) = 0;
	virtual Button* getButtons() = 0;
};