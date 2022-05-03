#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;
class RemoteManager
{
public:
	virtual void input(RenderWindow& window) = 0;
	virtual void update(float seconds) = 0;
	virtual void draw(RenderWindow& window) = 0;
	virtual void changeScreen(string name) = 0;
	virtual int findScreen() = 0;
};