#pragma once
#include <SFML/Graphics.hpp>
#include "Panel.h"
#include "RemoteManager.h"
#include "Screen.h"
using namespace sf;
class RemoteManager;
class Screen;
class Panel;
class InputHandler
{
private:
public:
	Vector2i mouse;
	virtual void input(RenderWindow& window, Event& event) = 0;
	~InputHandler() { 
		if(pointerToManager)
			delete pointerToManager; 
		if(pointerToScreen)
			delete pointerToScreen;
		if(pointerToPanel)
		    delete pointerToPanel;
	}
	RemoteManager* pointerToManager = nullptr;
	Screen* pointerToScreen = nullptr;
	Panel* pointerToPanel = nullptr;
};
