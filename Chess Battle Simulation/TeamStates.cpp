#include "TeamStates.h"
#include "GameSettings.h"


// WaitTeam Part
WaitTeam* WaitTeam::Instance()
{
	static WaitTeam member;
	
	return &member;
}

void WaitTeam::Enter(UnitTeam* team)
{
	team->getXP()++;
	if (team->getXP() >= team->requiredXP[team->getLevel() - 1])
	{
		team->getXP() = 0;
		team->getLevel()++;
		team->getFieldCapacity()++;
	}
	team->reviveUnits();
}

void WaitTeam::Execute(UnitTeam* team)
{

}

void WaitTeam::Exit(UnitTeam* team)
{
	if(team->getType() == 'c')
		team->setUnitsActiveness(true);
	team->active = true;
}

// ------------------------------------------


// Fight Part
Fight* Fight::Instance()
{
	static Fight member;

	return &member;
}

void Fight::Enter(UnitTeam* team)
{
	team->toTheBattle();
}

void Fight::Execute(UnitTeam* team)
{
	if (!team->isTeamAlive())
	{
		team->active = false;
	}
}

void Fight::Exit(UnitTeam* team)
{
	if (team->getType() == 'p')
		team->setUnitsActiveness(true);
	else
		team->setUnitsActiveness(false);
}

// ------------------------------------------