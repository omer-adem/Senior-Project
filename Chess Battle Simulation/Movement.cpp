#include "Movement.h"
#include "GameSettings.h"
#include "BaseCharacter.h"

int Manhattan(int ax, int ay, int bx, int by)
{
	return (abs(bx - ax) + abs(by - ay));
}

float Exact(int ax, int ay, int bx, int by)
{
	return sqrt(pow(bx - ax, 2) + pow(by - ay, 2));
}

float Length(Vector2f val)
{
    return float(sqrt(pow(val.x, 2) + pow(val.y, 2)));
}

Movement::Movement(BaseCharacter* owner)
{
	m_Owner = owner;
}

Vector2f Movement::Calculate()
{
    if (!isChasing() || m_ChaseCompleted)
    {
        m_Velocity = Vector2f(0, 0);
        Watch();
    }
	else
		Chase();
	return m_Velocity;
}

bool isValid(int x, int y)
{
	return (x >= 0 && x <= 7 && y >= 0 && y <= 7 && !GameSettings::MOVEMENT_MAP[y][x].selected);
}

void Movement::Watch()
{
	if (m_Target && Manhattan(m_Owner->getX(), m_Owner->getY(), m_Target->getX(), m_Target->getY()) <= 3)
	{
		m_ExactDistance = Exact(m_Owner->getX(), m_Owner->getY(), m_Target->getX(), m_Target->getY());
	}
}

void Movement::Chase()
{
	if (m_NextX == -1 && m_NextY == -1)
	{
		int minimum = 999;
		int X = 0;
		int Y = 0;
        int dist;
        if (isValid(m_Owner->getX(), m_Owner->getY() - 1))
        {
            dist = Manhattan(m_Owner->getX(), m_Owner->getY() - 1, m_Target->getX(), m_Target->getY());
            if (dist < minimum)
            {
                minimum = dist;
                X = m_Owner->getX();
                Y = m_Owner->getY() - 1;
            }
        }
        if (isValid(m_Owner->getX() - 1, m_Owner->getY() - 1))
        {
            dist = Manhattan(m_Owner->getX() - 1, m_Owner->getY() - 1, m_Target->getX(), m_Target->getY());
            if (dist < minimum)
            {
                minimum = dist;
                X = m_Owner->getX() - 1;
                Y = m_Owner->getY() - 1;
            }
        }
        if (isValid(m_Owner->getX() - 1, m_Owner->getY()))
        {
            dist = Manhattan(m_Owner->getX() - 1, m_Owner->getY(), m_Target->getX(), m_Target->getY());
            if (dist < minimum)
            {
                minimum = dist;
                X = m_Owner->getX() - 1;
                Y = m_Owner->getY();
            }
        }
        if (isValid(m_Owner->getX() - 1, m_Owner->getY() + 1))
        {
            dist = Manhattan(m_Owner->getX() - 1, m_Owner->getY() + 1, m_Target->getX(), m_Target->getY());
            if (dist < minimum)
            {
                minimum = dist;
                X = m_Owner->getX() - 1;
                Y = m_Owner->getY() + 1;
            }
        }
        if (isValid(m_Owner->getX(), m_Owner->getY() + 1))
        {
            dist = Manhattan(m_Owner->getX(), m_Owner->getY() + 1, m_Target->getX(), m_Target->getY());
            if (dist < minimum)
            {
                minimum = dist;
                X = m_Owner->getX();
                Y = m_Owner->getY() + 1;
            }
        }

        if (isValid(m_Owner->getX() + 1, m_Owner->getY() + 1))
        {
            dist = Manhattan(m_Owner->getX() + 1, m_Owner->getY() + 1, m_Target->getX(), m_Target->getY());
            if (dist < minimum)
            {
                minimum = dist;
                X = m_Owner->getX() + 1;
                Y = m_Owner->getY() + 1;
            }
        }

        if (isValid(m_Owner->getX() + 1, m_Owner->getY()))
        {
            dist = Manhattan(m_Owner->getX() + 1, m_Owner->getY(), m_Target->getX(), m_Target->getY());
            if (dist < minimum)
            {
                minimum = dist;
                X = m_Owner->getX() + 1;
                Y = m_Owner->getY();
            }
        }
        m_NextX = X;
        m_NextY = Y;
        GameSettings::MOVEMENT_MAP[Y][X].parent = &GameSettings::MOVEMENT_MAP[m_Owner->getY()][m_Owner->getX()];
        GameSettings::MOVEMENT_MAP[Y][X].selected = true;
        m_Velocity = GameSettings::MAP[Y][X] - m_Owner->getPosition();
        float length = Length(m_Velocity);
        m_Velocity = Vector2f((m_Velocity.x / length) * DEFAULT_SPEED, (m_Velocity.y / length) * DEFAULT_SPEED);
	}
	if(m_NextX!=-1 && m_NextY!=-1)
	{
		Vector2f temp = GameSettings::MAP[m_NextY][m_NextX];
		if (abs(m_Owner->getPosition().x - temp.x) <= 10.0f && abs(m_Owner->getPosition().y - temp.y) <= 10.0f)
		{
			m_Owner->getPosition() = temp;
			m_Owner->getX() = m_NextX;
			m_Owner->getY() = m_NextY;
            GameSettings::MOVEMENT_MAP[m_Owner->getY()][m_Owner->getX()].parent->selected = false;
            GameSettings::MOVEMENT_MAP[m_Owner->getY()][m_Owner->getX()].parent = nullptr;
			m_NextX = -1; m_NextY = -1;
			m_Velocity = Vector2f(0, 0);

            Watch();

            if (m_NextX == -1 && m_NextY == -1 && isWithinRange())
            {
                m_ChaseCompleted = true;
            }
		}
	}
}