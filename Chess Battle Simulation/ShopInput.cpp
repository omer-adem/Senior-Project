#include "ShopInput.h"
#include "GameSettings.h"
#include "GameScreen.h"

#define pointToScreen ((GameScreen*)(pointerToScreen))
#define pointToGame ((GamePanel*)(pointerToGamePanel))
#define pointToShop ((ShopPanel*)(pointerToPanel))

ShopInput::ShopInput(Panel* mp, Screen* sm, Panel* gp)
{
	pointerToPanel = mp;
	pointerToScreen = sm;
	pointerToGamePanel = gp;
}

void ShopInput::input(RenderWindow& window, Event& event)
{
	if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
		pointerToScreen->changePanel("GamePanel");

	if (event.type == Event::MouseButtonPressed && event.key.code == Mouse::Left)
	{
		mouse = (Vector2i)window.mapPixelToCoords(Mouse::getPosition(window));

		if (pointerToPanel->getButtons()[0].getShape().getGlobalBounds().intersects(FloatRect(mouse.x,mouse.y,2,2)))
			pointerToScreen->changePanel("GamePanel");

		else if (pointerToPanel->getButtons()[1].getShape().getGlobalBounds().intersects(FloatRect(mouse.x, mouse.y, 2, 2)))
		{
			if (GameSettings::PLAYER_MONEY > 0)
			{
				pointToScreen->isFrozen = false;
				pointToScreen->generateTroops('P');
				GameSettings::PLAYER_MONEY--;
				pointToGame->setMoney();
			}
		}

		else if (pointerToPanel->getButtons()[2].getShape().getGlobalBounds().intersects(FloatRect(mouse.x, mouse.y, 2, 2)))
		{
			if (pointToScreen->isFrozen)
			{
				pointToScreen->isFrozen = false;
				pointerToPanel->getButtons()[2].getShape().setOutlineThickness(0);
			}
			else
			{
				pointToScreen->isFrozen = true;
				pointerToPanel->getButtons()[2].getShape().setOutlineThickness(5);
			}
		}

		for (int i = 0; i < 3; i++)
		{
			if (pointToShop->getTroops()[i].getGlobalBounds().intersects(FloatRect(mouse.x, mouse.y, 2, 2)))
			{
				int indx = pointToScreen->m_poolIndexesPlayer[i];
				if (GameSettings::PLAYER_MONEY > 0 && pointToShop->clearTroop(i))
				{
					auto it = pointToScreen->m_Pool.begin() + indx;
					BaseCharacter* troop = (*it).get();
					if (pointToScreen->m_PlayerTeam->addTroop(it))
					{
						troop->getBar().setFillColor(Color::Green);
						troop->getInfo().setFillColor(Color::White);
						troop->setTeam(pointToScreen->m_PlayerTeam);
						troop->setEnemyTeam(pointToScreen->m_OpponentTeam);
						pointToScreen->m_Pool.erase(it);
						GameSettings::PLAYER_MONEY--;
						pointToGame->setMoney();

						if (pointToScreen->m_poolIndexesPlayer[i] < pointToScreen->m_poolIndexesPlayer[0])
							pointToScreen->m_poolIndexesPlayer[0]--;

						if (pointToScreen->m_poolIndexesPlayer[i] < pointToScreen->m_poolIndexesPlayer[1])
							pointToScreen->m_poolIndexesPlayer[1]--;

						if (pointToScreen->m_poolIndexesPlayer[i] < pointToScreen->m_poolIndexesPlayer[2])
							pointToScreen->m_poolIndexesPlayer[2]--;

						pointToScreen->m_poolIndexesPlayer[i] = -1;
					}
					troop = nullptr;
				}
			}
		}
	}
}