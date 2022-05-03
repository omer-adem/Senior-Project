#pragma once
#include "Screen.h"
#include "MainMenuPanel.h"
#include "MenuOptionsPanel.h"
#include "HintPanel.h"
#include "MainMenuInput.h"
#include "MenuOptionsInput.h"
#include "HintInput.h"

class MainMenuScreen : public Screen
{
private:
	Text header;
	unique_ptr<Panel> m_panels[3];
	unique_ptr<InputHandler> m_inputhandlers[3];
public:
	MainMenuScreen(Vector2i resolution,RemoteManager* sm);
	int findPanel();
	void virtual input(RenderWindow& window);
	void virtual draw(RenderWindow& window);
	void virtual update(float seconds);
	void virtual changePanel(string name);
	void virtual init();
};