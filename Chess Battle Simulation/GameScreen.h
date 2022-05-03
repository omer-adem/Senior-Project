#pragma once
#include "Screen.h"
#include "GamePanel.h"
#include "GameInput.h"
#include "ShopPanel.h"
#include "ShopInput.h"
#include "UnitTeam.h"
#include "Fighter.h"
#include "TeamStates.h"
#include "FighterStates.h"
#include <thread>

class GameScreen : public Screen
{
private:
	unique_ptr<Panel> m_panels[2];
	unique_ptr<InputHandler> m_inputHandler[2];
	Text m_Info;
	bool m_GameFirstStart = true;
	int round = 1;
	float waitTime = 15;
	bool cpuChose = false;
	int m_poolIndexesOpponent[3];
	bool game;
	void prepareGameObjects();
	void gameLogic(float seconds);
	void endFight(char winner);
	void opponentChoices();
public:
	bool isFrozen = false;
	bool inFight = false;
	shared_ptr<UnitTeam> m_PlayerTeam;
	shared_ptr<UnitTeam> m_OpponentTeam;
	vector<unique_ptr<BaseCharacter>> m_Pool;
	int m_poolIndexesPlayer[3];
	GameScreen(Vector2i resolution,RemoteManager* sm);
	int findPanel();
	void resetGame();
	void generateTroops(char c);
	void backgroundTask();
	void finishGame();
	virtual void init();
	virtual void input(RenderWindow& window);
	virtual void draw(RenderWindow& window);
	virtual void update(float seconds);
	void virtual changePanel(string name);
};