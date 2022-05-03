#pragma once
#include "InputHandler.h"
#include "UnitTeam.h"

class GameInput : public InputHandler
{
private:
	shared_ptr<UnitTeam> pointerToTeam;
	BaseCharacter* pointToTroop;
	Vector2f troopPrev;
	bool troopWhichSide = false;
	bool movingTroop = false;
	Vector2i mousePrev;
public:
	void virtual input(RenderWindow& window, Event& event);
	GameInput(Panel* mp, Screen* ms, RemoteManager* sm,shared_ptr<UnitTeam> team);
	~GameInput() { delete pointToTroop; }
};