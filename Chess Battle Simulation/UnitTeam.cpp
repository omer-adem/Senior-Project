#include "UnitTeam.h"
#include "GameSettings.h"
#include "Fighter.h"

UnitTeam::UnitTeam(State<UnitTeam>* start,char tp)
{
	Alive = 0;
	fieldCapacity = 1;
	XP = 0;
	Level = 1;
	stateManager = new StateManager<UnitTeam>(this);
	stateManager->setCurrentState(start);
	type = tp;
	active = true;
}

UnitTeam::~UnitTeam()
{
	delete stateManager;
}

bool UnitTeam::addTroop(Iterator unit)
{
	if (subUnits.size() == subCapacity)
		return false;

	vector<int> temp = { 0,1,2,3,4,5,6,7 };
	for (auto it = subUnits.begin(); it != subUnits.end(); it++)
	{
		int val = (*it)->getX();
		for(auto iter = temp.begin(); iter != temp.end(); iter++)
			if (val == (*iter))
			{
				temp.erase(iter);
				break;
			}
	}
	(*unit)->getX() = temp[0];
	(*unit)->getPosition() = GameSettings::SUBMAP[temp[0]];
	subUnits.push_back(move(*unit));
	return true;
}

bool UnitTeam::moveTroop(BaseCharacter* unit,bool which,bool toWhere)    // If which == true then troop is from SubUnits, If not troop is from FieldUnits.  77'e 71 for SUB,  50'e 30 for Field
{
	if (which)
	{
		auto itUnit = subUnits.begin();
		for (itUnit; itUnit != subUnits.end(); itUnit++)
		{
			if (unit == (*itUnit).get())
				break;
		}

		if (toWhere)
		{
			for (auto it = subUnits.begin(); it != subUnits.end(); it++)
			{
				if (unit != (*it).get() && unit->getBox().intersects(FloatRect(GameSettings::SUBMAP[(*it)->getX()].x - 65, GameSettings::SUBMAP[(*it)->getX()].y - 60, 65, 60)))
					return false;
			}

			for (int j = 0; j < 8; j++)
			{
				if (unit->getBox().intersects(FloatRect(GameSettings::SUBMAP[j].x - 65, GameSettings::SUBMAP[j].y - 60, 65, 60)))
				{
					unit->getPosition() = GameSettings::SUBMAP[j];
					unit->getX() = j;
					return true;
				}
			}
		}
		else
		{
			if (fieldUnits.size() == fieldCapacity)
				return false;
	
			for (auto it = fieldUnits.begin(); it != fieldUnits.end(); it++)
			{
				if (unit->getBox().intersects(FloatRect(GameSettings::MAP[(*it)->getY()][(*it)->getX()].x - 45, GameSettings::MAP[(*it)->getY()][(*it)->getX()].y - 20, 45, 20)))
					return false;
			}

			for (int i = 4; i < 8; i++)
			{
				for (int j = 0; j < 8; j++)
					if (unit->getBox().intersects(FloatRect(GameSettings::MAP[i][j].x - 45, GameSettings::MAP[i][j].y - 20, 45, 20)))
					{
						unit->getPosition() = GameSettings::MAP[i][j];
						unit->getX() = j;
						unit->getY() = i;
						unit->setPrevX(j);
						unit->setPrevY(i);
						fieldUnits.push_back(move(*itUnit));
						subUnits.erase(itUnit);
						GameSettings::MOVEMENT_MAP[i][j].selected = true;
						return true;
					}
			}

		}
	}
	else
	{
		auto itUnit = fieldUnits.begin();
		for (itUnit; itUnit != fieldUnits.end(); itUnit++)
		{
			if (unit == (*itUnit).get())
				break;
		}

		if (toWhere)
		{
			for (auto it = subUnits.begin(); it != subUnits.end(); it++)
			{
				if (unit != (*it).get() && unit->getBox().intersects(FloatRect(GameSettings::SUBMAP[(*it)->getX()].x - 65, GameSettings::SUBMAP[(*it)->getX()].y - 60, 65, 60)))
					return false;
			}

			for (int j = 0; j < 8; j++)
			{
				if (unit->getBox().intersects(FloatRect(GameSettings::SUBMAP[j].x - 65, GameSettings::SUBMAP[j].y - 60, 65, 60)))
				{
					GameSettings::MOVEMENT_MAP[unit->getY()][unit->getX()].selected = false;
					unit->getPosition() = GameSettings::SUBMAP[j];
					unit->getX() = j;		
					subUnits.push_back(move(*itUnit));
					fieldUnits.erase(itUnit);
					return true;
				}
			}
		}
		else
		{
			for (auto it = fieldUnits.begin(); it != fieldUnits.end(); it++)
			{
				if (unit != (*it).get() && unit->getBox().intersects(FloatRect(GameSettings::MAP[(*it)->getY()][(*it)->getX()].x - 45, GameSettings::MAP[(*it)->getY()][(*it)->getX()].y - 20, 45, 20)))
					return false;
			}

			for (int i = 4; i < 8; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					if (unit->getBox().intersects(FloatRect(GameSettings::MAP[i][j].x - 45, GameSettings::MAP[i][j].y - 20, 45, 20)))
					{
						GameSettings::MOVEMENT_MAP[unit->getY()][unit->getY()].selected = false;
						unit->getPosition() = GameSettings::MAP[i][j];
						unit->getX() = j;
						unit->getY() = i;
						unit->setPrevX(j);
						unit->setPrevY(i);
						GameSettings::MOVEMENT_MAP[i][j].selected = true;
						return true;
					}
				}
			}
		}
	}
	return false;
}

BaseCharacter* UnitTeam::findTarget(shared_ptr<UnitTeam> enemy)
{
	if (enemy->FieldUnits().size() == 0 || !enemy->isTeamAlive())
		return nullptr;
	else
	{
		float* score = new float[static_cast<int>(enemy->FieldUnits().size())];
		float max = -1;
		int indx = -1;
		int i = 0;
		for(auto it = enemy->FieldUnits().begin(); it != enemy->FieldUnits().end(); it++)
		{
			if (i < enemy->FieldUnits().size() && !((Fighter*)(*it).get())->getStateManager()->isInState(*Dead::Instance()))
			{
				score[i] = (float)enemy->FieldUnits()[i]->getATK() / enemy->FieldUnits()[i]->getATKSPEED();
				if (score[i] > max)
				{
					max = score[i];
					indx = i;
				}
			}
			i++;
		}
		delete[] score;
		return enemy->FieldUnits()[indx].get();
	}
}

bool UnitTeam::moveTroop(Iterator unit, int x, int y)
{
	if (fieldUnits.size() == fieldCapacity)
		return false;

	bool control = true;
	for (auto it = fieldUnits.begin(); it != fieldUnits.end(); it++)
	{
		if (x == (*it)->getX() && y == (*it)->getY())
		{
			control = false;
			break;
		}
	}

	if (!control)
	{
		for (int j = 0; j < 8; j++)
			if (!GameSettings::MOVEMENT_MAP[y][j].selected)
			{
				x = j;
				break;
			}
	}

	(*unit)->getPosition() = GameSettings::MAP[y][x];
	(*unit)->getX() = x;
	(*unit)->getY() = y;
	(*unit)->setPrevX(x);
	(*unit)->setPrevY(y);
	fieldUnits.push_back(move(*unit));
	subUnits.erase(unit);
	GameSettings::MOVEMENT_MAP[y][x].selected = true;
	return true;
		
}

bool UnitTeam::isTeamAlive()
{
	if (Alive == 0)
		return false;
	else
		return true;
}

BaseCharacter* UnitTeam::troopClicked(Vector2i mouse,bool which)
{
	if (which)
	{
		for (auto it = subUnits.begin(); it != subUnits.end(); it++)
		{
			if ((*it)->getBox().intersects(FloatRect(mouse.x, mouse.y, 2, 2)))
				return (*it).get();
		}
	}
	else
	{
		for (auto it = fieldUnits.begin(); it != fieldUnits.end(); it++)
		{
			if ((*it)->getBox().intersects(FloatRect(mouse.x, mouse.y, 2, 2)))
				return (*it).get();
		}
	}
	return nullptr;
}

void UnitTeam::discardTroop(BaseCharacter* unit,bool which)
{

	if (which)
	{
		for (auto it = subUnits.begin(); it != subUnits.end(); it++)
		{
			if ((*it).get() == unit)
			{
				subUnits.erase(it);
				break;
			}
		}
	}
	else
	{
		for (auto it = fieldUnits.begin(); it != fieldUnits.end(); it++)
		{
			if ((*it).get() == unit)
			{
				fieldUnits.erase(it);
				break;
			}
		}
	}
}

void UnitTeam::reviveUnits()
{
	for (auto it = fieldUnits.begin(); it != fieldUnits.end(); it++)
	{
		if ((*it)->getClass() == "Fighter")
			((Fighter*)(*it).get())->getStateManager()->GlobalState()->Evolve(((Fighter*)(*it).get()), Revive);
	}
}

void UnitTeam::toTheBattle()
{
	for (auto it = fieldUnits.begin(); it != fieldUnits.end(); it++)
		if ((*it)->getClass() == "Fighter")
			((Fighter*)(*it).get())->getStateManager()->GlobalState()->Evolve(((Fighter*)(*it).get()),Fighting);
}


void UnitTeam::setUnitsActiveness(bool value)
{
	for (auto it = fieldUnits.begin(); it != fieldUnits.end(); it++)
		(*it)->setActive(value);
}


void UnitTeam::update(float seconds)
{
	stateManager->update(seconds);

	for (auto it = subUnits.begin(); it != subUnits.end(); it++)
		(*it)->update(seconds);

	for (auto it = fieldUnits.begin(); it != fieldUnits.end(); it++)
		(*it)->update(seconds);
}

void UnitTeam::draw(RenderWindow& window)
{
	for (auto it = subUnits.begin(); it != subUnits.end(); it++)
		(*it)->draw(window);

	for (int i = 0; i < 8; i++)
	{
		for (auto it = fieldUnits.begin(); it != fieldUnits.end(); it++)
			if ((*it)->getY() == i)
				(*it)->draw(window);
	}
}