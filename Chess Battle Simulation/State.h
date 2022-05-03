#ifndef STATE_H
#define STATE_H

#include <string>

enum Message
{
	Revive = 0,
	Fighting
};

using namespace std;

template <class type>
class State
{
public:
	virtual ~State(){}

	virtual void Enter(type*) = 0;

	virtual void Execute(type*) = 0;
	
	virtual void Exit(type*) = 0;

	virtual void Evolve(type*,const Message) = 0;

};

#endif