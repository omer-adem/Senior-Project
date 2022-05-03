#pragma once
#include <vector>
#include "StateManager.h"
#include "BaseCharacter.h"
using namespace sf;
using namespace std;
class BaseCharacter;
class UnitTeam
{
private:
	vector<unique_ptr<BaseCharacter>> fieldUnits;
	vector<unique_ptr<BaseCharacter>> subUnits;
	StateManager<UnitTeam>* stateManager;
	const int subCapacity = 8;
	int fieldCapacity;
	int XP;
	int Level;
	char type;

public:
	typedef vector<unique_ptr<BaseCharacter>>::iterator Iterator;
	const int requiredXP[5] = { 4, 8, 16, 24, 30 };
	bool active;
	UnitTeam(State<UnitTeam>* start,char tp);
	~UnitTeam();
	bool addTroop(Iterator unit);
	bool moveTroop(BaseCharacter* unit,bool which,bool toWhere);
	bool moveTroop(Iterator unit, int x, int y);
	bool isTeamAlive();
	BaseCharacter* troopClicked(Vector2i mouse,bool which);
	StateManager<UnitTeam>* getStateManager()const { return stateManager; }
	vector<unique_ptr<BaseCharacter>>& FieldUnits() { return fieldUnits; }
	vector<unique_ptr<BaseCharacter>>& SubUnits() { return subUnits; }
	void discardTroop(BaseCharacter* unit, bool which);
	void update(float seconds);
	void draw(RenderWindow& window);
	void reviveUnits();
	void toTheBattle();
	int& getFieldCapacity() { return fieldCapacity; }
	int getFieldSize() { return fieldUnits.size(); }
	int getSubSize() { return subUnits.size(); }
	char getType() { return type; }
	int& getLevel() { return Level; }
	int Alive;
	void clear(State<UnitTeam>* start) { 
		fieldUnits.clear(); subUnits.clear(); active = true; 
	stateManager->setCurrentState(start);
	XP = 0;
	fieldCapacity = 1;
	Alive = 0;
	Level = 1;
	}
	BaseCharacter* findTarget(shared_ptr<UnitTeam> enemy);
	void setUnitsActiveness(bool value);
	int& getXP() { return XP; }
};