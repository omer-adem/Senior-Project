#pragma once
#include <SFML/Graphics.hpp>
#include "UnitTeam.h"
#include "Movement.h"
#include "TextureHolder.h"
#define DEFAULT_SPEED 150
using namespace sf;
using namespace std;

class Movement;
class UnitTeam;
class BaseCharacter
{
protected:
	int m_ID;
	int m_ATK;
	string m_Name;
	string m_Class;
	int m_HP;
	int m_MAX_HP;
	float m_ATK_SPEED;
	Sprite m_sprite;
	Text m_info;
	RectangleShape m_bar;
	Vector2f m_velocity;
	Vector2f m_position;
	float m_Last_Attacked = 0.f;
	shared_ptr<UnitTeam> pointerToTeam;
	shared_ptr<UnitTeam> pointerToEnemyTeam;
	unique_ptr<Movement> pointerToMovement;
	BaseCharacter* m_target;
	int m_X;
	int m_Y;
	int prev_X;
	int prev_Y;
	bool isActive = true;
public:
	BaseCharacter(int id,int atk, string name, string Class, int hp, float atkspeed, Sprite spr) 
		:m_ID(id), m_ATK(atk), m_Name(name), m_Class(Class), m_HP(hp), m_ATK_SPEED(atkspeed), m_sprite(spr),m_MAX_HP(hp) {
		m_X = -1; m_Y = -1;
		prev_X = -1; prev_Y = -1;
		pointerToMovement = make_unique<Movement>(this);
		m_info.setFont(TextureHolder::GetFont());
		m_info.setCharacterSize(35);
		m_info.setString(name);
		m_bar.setSize(Vector2f(m_MAX_HP * 0.8, 15));
	}

	int getID() { return m_ID; }
	int getATK() { return m_ATK; }
	int& getX() { return m_X; }
	int& getY() { return m_Y; }
	int& getPrevX() { return prev_X; }
	int& getPrevY() { return prev_Y; }
	void setPrevX(int x) { prev_X = x; }
	void setPrevY(int y) { prev_Y = y; }
	string getName() { return m_Name; }
	string getClass() { return m_Class; }
	Text& getInfo() { return m_info; }
	RectangleShape& getBar() { return m_bar; }
	BaseCharacter* getTarget() { return m_target; }
	void setTarget(BaseCharacter* target) { m_target = target; }
	int& getHP() { return m_HP; }
	int getMaxHP() { return m_MAX_HP; }
	float getATKSPEED() { return m_ATK_SPEED; }
	Sprite& getSprite() { return m_sprite; }
	Vector2f& getVelocity() { return m_velocity; }
	Vector2f& getPosition() { return m_position; }
	FloatRect getBox() { return m_sprite.getGlobalBounds(); }
	float& getLastAttacked() { return m_Last_Attacked; }
	void setTeam(shared_ptr<UnitTeam> team) { pointerToTeam = team; }
	void setEnemyTeam(shared_ptr<UnitTeam> team) { pointerToEnemyTeam = team; }
	shared_ptr<UnitTeam> getTeam() { return pointerToTeam; }
	shared_ptr<UnitTeam> getEnemyTeam() { return pointerToEnemyTeam; }
	unique_ptr<Movement>& getMovement() { return pointerToMovement; }
	void setActive(bool val) { isActive = val; }
	bool Active() { return isActive; }
	virtual void update(float seconds) = 0;
	virtual void draw(RenderWindow& window) = 0;
};