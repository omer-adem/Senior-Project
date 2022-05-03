#pragma once
#include "BaseCharacter.h"
#include "FighterStates.h"
#include "StateManager.h"

class Fighter : public BaseCharacter
{
private:
	StateManager<Fighter>* stateManager;
public:
	Fighter(State<Fighter>* start,int id,int atk,string name, int hp, float atkspeed, Sprite spr);
	~Fighter();
	float timer;
	virtual void update(float seconds);
	virtual void draw(RenderWindow& window);
	StateManager<Fighter>* getStateManager()const { return stateManager; }
};