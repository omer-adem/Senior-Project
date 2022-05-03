#include "Fighter.h"

Fighter::Fighter(State<Fighter>* start,int id,int atk, string name, int hp, float atkspeed, Sprite spr):
	BaseCharacter(id,atk,name,"Fighter",hp,atkspeed,spr)
{
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height/1.4f);
	m_sprite.scale(0.3f, 0.3f);
	stateManager = new StateManager<Fighter>(this);
	m_target = nullptr;
	stateManager->setCurrentState(start);
	stateManager->setGlobalState(GlobalFighter::Instance());
	timer = 0.f;
}

Fighter::~Fighter()
{
	delete stateManager;

	delete m_target;
}

void Fighter::update(float seconds)
{
	timer = seconds;
	stateManager->update(seconds);
	m_velocity = pointerToMovement->Calculate();
	m_position += m_velocity*seconds;
	m_sprite.setPosition(m_position);
	m_bar.setPosition(m_position.x-getBox().width+35, m_position.y - 30 - getBox().height/2);
	m_info.setPosition(m_position.x-getBox().width+35, m_position.y - 75 - getBox().height/2);
	m_bar.setSize(Vector2f(m_HP * 0.25f, 15));
}

void Fighter::draw(RenderWindow& window)
{
	if (isActive)
	{
		window.draw(m_sprite);
		window.draw(m_bar);
		window.draw(m_info);
	}
}