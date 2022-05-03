#pragma once
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;
class BaseCharacter;
class Movement
{
private:
	BaseCharacter* m_Target;
	Vector2f m_Velocity;
	BaseCharacter* m_Owner;
	bool m_Chasing = false;
	bool m_ChaseCompleted = false;
	bool isChasing() { return m_Chasing; }
	void Chase();
	void Watch();
	float m_ExactDistance;
	int m_NextX;
	int m_NextY;
public:
	Movement(BaseCharacter* owner);
	~Movement() { m_Target = nullptr; m_Owner = nullptr; }
	bool isWithinRange() { return m_ExactDistance <= 1.5f; }
	bool isChasingDone() { return m_ChaseCompleted; }
	void setTarget(BaseCharacter* target) { m_Target = target; }
	void chasingOn() { m_Chasing = true; m_ExactDistance = 999; m_NextX = -1;
	m_NextY = -1;
	}
	void chasingOff() { m_Chasing = false; m_ChaseCompleted = false; }
	Vector2f Calculate();
};