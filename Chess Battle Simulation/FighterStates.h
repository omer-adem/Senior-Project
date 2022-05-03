#pragma once
#include "State.h"

class Fighter;

class GlobalFighter : public State<Fighter>
{
private:
	GlobalFighter() {}

public:

	static GlobalFighter* Instance();

	virtual void Enter(Fighter* fighter) {}

	virtual void Execute(Fighter* fighter);

	virtual void Exit(Fighter* fighter) {}
	
	virtual void Evolve(Fighter* fighter, const Message);

};

class WaitTroop : public State<Fighter>
{
private:
	WaitTroop() {}

public:

	static WaitTroop* Instance();

	virtual void Enter(Fighter* fighter);

	virtual void Execute(Fighter* fighter);

	virtual void Exit(Fighter* fighter);

	virtual void Evolve(Fighter* fighter, const Message) {}

};

class ChaseTarget : public State<Fighter>
{
private:
	ChaseTarget() {}

public:

	static ChaseTarget* Instance();

	virtual void Enter(Fighter* fighter);

	virtual void Execute(Fighter* fighter);

	virtual void Exit(Fighter* fighter);

	virtual void Evolve(Fighter* fighter, const Message) {}

};

class Attack : public State<Fighter>
{
private:
	Attack() {}

public:

	static Attack* Instance();

	virtual void Enter(Fighter* fighter);

	virtual void Execute(Fighter* fighter);

	virtual void Exit(Fighter* fighter);

	virtual void Evolve(Fighter* fighter, const Message) {}

};

class Dead : public State<Fighter>
{
private:
	Dead() {}

public:

	static Dead* Instance();

	virtual void Enter(Fighter* fighter);

	virtual void Execute(Fighter* fighter);

	virtual void Exit(Fighter* fighter);

	virtual void Evolve(Fighter* fighter, const Message) {}

};