#include "FighterStates.h"
#include "Fighter.h"
#include "GameSettings.h"

#define position GameSettings::MOVEMENT_MAP[fighter->getY()][fighter->getX()]

// Global Part
GlobalFighter* GlobalFighter::Instance()
{
	static GlobalFighter member;

	return &member;
}

void GlobalFighter::Execute(Fighter* fighter)
{
	
}

void GlobalFighter::Evolve(Fighter* fighter,const Message msg)
{
	switch (msg)
	{
	case Revive:
		fighter->getStateManager()->ChangeState(WaitTroop::Instance());
		break;
	case Fighting:
		fighter->getStateManager()->ChangeState(ChaseTarget::Instance());
	}
}

// ------------------------------------------


// WaitTroop Part
WaitTroop* WaitTroop::Instance()
{
	static WaitTroop member;
	
	return &member;
}

void WaitTroop::Enter(Fighter* fighter)
{
	fighter->getHP() = fighter->getMaxHP();
	position.selected = false;
	if (position.parent)
	{
		position.parent->selected = false;
		position.parent = nullptr;
	}
	fighter->getY() = fighter->getPrevY();
	fighter->getX() = fighter->getPrevX();
	fighter->getPosition() = Vector2f(GameSettings::MAP[fighter->getY()][fighter->getX()]);
	fighter->setTarget(nullptr);
	position.selected = true;
}

void WaitTroop::Execute(Fighter* fighter)
{
	// IDLE 
}

void WaitTroop::Exit(Fighter* fighter)
{
	fighter->getHP() = fighter->getMaxHP();
}

// ------------------------------------------


// ChaseTarget Part
ChaseTarget* ChaseTarget::Instance()
{
	static ChaseTarget member;

	return &member;
}

void ChaseTarget::Enter(Fighter* fighter)
{
	fighter->getLastAttacked() = 0.0f;
	BaseCharacter* temp = fighter->getTeam()->findTarget(fighter->getEnemyTeam());
	if (temp!=nullptr)
	{
		fighter->setTarget(temp);
		fighter->getMovement()->setTarget(temp);
		fighter->getMovement()->chasingOn();
	}
	else
	{
		fighter->getStateManager()->setCurrentState(WaitTroop::Instance());
	}
	// Set Animation Name and Index
}

void ChaseTarget::Execute(Fighter* fighter)
{
	// Clean previous position and chase more.
	if (fighter->getMovement()->isChasingDone())
	{
		fighter->getStateManager()->ChangeState(Attack::Instance());
	}

	if (fighter->getTarget()->getHP() <= 0)
	{
		fighter->setTarget(nullptr);
		fighter->getMovement()->setTarget(nullptr);
		fighter->getMovement()->chasingOff();
		fighter->getStateManager()->ChangeState(ChaseTarget::Instance());
	}

}

void ChaseTarget::Exit(Fighter* fighter)
{
	// Stop Moving
	fighter->getMovement()->chasingOff();
}

// ------------------------------------------


// Attack Part
Attack* Attack::Instance()
{
	static Attack member;

	return &member;
}

void Attack::Enter(Fighter* fighter)
{
	// Set animation Name and Index
	fighter->getLastAttacked() = fighter->getATKSPEED();
}

void Attack::Execute(Fighter* fighter)
{
	fighter->getLastAttacked() += fighter->timer;
	if (!fighter->getMovement()->isWithinRange())
	{
		fighter->getStateManager()->ChangeState(ChaseTarget::Instance());
	}

	if (fighter->getMovement()->isWithinRange() && fighter->getLastAttacked() >= fighter->getATKSPEED())
	{
		fighter->getTarget()->getHP() -= fighter->getATK();
		fighter->getLastAttacked() = 0.0f;
	}

	if (fighter->getTarget()->getHP() <= 0)
	{
		if (!((Fighter*)(fighter->getTarget()))->getStateManager()->isInState(*Dead::Instance()))
		{
			((Fighter*)(fighter->getTarget()))->getStateManager()->ChangeState(Dead::Instance());
		}
		fighter->getStateManager()->ChangeState(ChaseTarget::Instance());
	}
}

void Attack::Exit(Fighter* fighter)
{
	fighter->setTarget(nullptr);
	fighter->getMovement()->setTarget(nullptr);
}

// ------------------------------------------


// Dead Part
Dead* Dead::Instance()
{
	static Dead member;

	return &member;
}

void Dead::Enter(Fighter* fighter)
{
	fighter->setActive(false);
	position.selected = false;
	if (position.parent)
	{
		position.parent->selected = false;
		position.parent = nullptr;
	}
	fighter->getTeam()->Alive--;
}

void Dead::Execute(Fighter* fighter)
{

}

void Dead::Exit(Fighter* fighter)
{

}

// -----------------------------------------