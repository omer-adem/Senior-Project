#pragma once
#include "State.h"
#include "UnitTeam.h"

class UnitTeam;

class WaitTeam : public State<UnitTeam>
{
private:
	WaitTeam() {}

public:

	static WaitTeam* Instance();

	virtual void Enter(UnitTeam* team);

	virtual void Execute(UnitTeam* team);

	virtual void Exit(UnitTeam* team);

	virtual void Evolve(UnitTeam* team, const Message) {}
};

class Fight : public State<UnitTeam>
{
private:
	Fight() {}

public:

	static Fight* Instance();

	virtual void Enter(UnitTeam* team);
	
	virtual void Execute(UnitTeam* team);

	virtual void Exit(UnitTeam* team);

	virtual void Evolve(UnitTeam* team, const Message) {}
};
