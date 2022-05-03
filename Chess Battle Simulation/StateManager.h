#pragma once
#include "State.h"

template <class type>
class StateManager
{
private:
	State<type>* currentState;
	State<type>* globalState;
	type* m_Owner;
public:
	StateManager(type* owner) : m_Owner(owner) {};
	void setCurrentState(State<type>* state) { currentState = state; }
	void setGlobalState(State<type>* state) { globalState = state; }
	
	State<type>* CurrentState() { return currentState; }
	State<type>* GlobalState() { return globalState; }

	void update(float seconds)const
	{
		if (globalState) globalState->Execute(m_Owner);
		if (currentState) currentState->Execute(m_Owner);
	}

	void ChangeState(State<type>* state)
	{
		if (!isInState(*state))
			currentState->Exit(m_Owner);
		currentState = state;
		currentState->Enter(m_Owner);
	}

	bool isInState(State<type>& state)const
	{
		if (typeid(*currentState) == typeid(state)) return true;
		return false;
	}
};