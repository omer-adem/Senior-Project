#include "GameInput.h"
#include "GameSettings.h"
#include "GamePanel.h"
#include "GameScreen.h"

GameInput::GameInput(Panel* mp, Screen* ms, RemoteManager* sm,shared_ptr<UnitTeam> team)
{
	pointerToPanel = mp;
	pointerToScreen = ms;
	pointerToManager = sm;
	pointerToTeam = team;
}

void GameInput::input(RenderWindow& window, Event& event)
{
	if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
		pointerToManager->changeScreen("MainMenuScreen");

	if (event.type == Event::MouseButtonPressed && event.key.code == Mouse::Left)
	{
		mouse = (Vector2i)window.mapPixelToCoords(Mouse::getPosition(window));
		
		if (!((GameScreen*)(pointerToScreen))->inFight && GameSettings::MAP_BOUNDS.intersects(FloatRect(mouse.x, mouse.y, 2, 2)))
		{
			troopWhichSide = false;
			if (!movingTroop && (pointToTroop = pointerToTeam->troopClicked(mouse, troopWhichSide)))
			{
				movingTroop = true;
				mousePrev = mouse;
				troopPrev = pointToTroop->getPosition();
			}
		}
		else if (GameSettings::SUB_BOUNDS.intersects(FloatRect(mouse.x, mouse.y, 2, 2)))
		{
			troopWhichSide = true;
			if (!movingTroop && (pointToTroop = pointerToTeam->troopClicked(mouse,troopWhichSide)))
			{
				movingTroop = true;
				mousePrev = mouse;
				troopPrev = pointToTroop->getPosition();
			}
		}

		else if (pointerToPanel->getButtons()[1].getShape().getGlobalBounds().intersects(FloatRect(mouse.x, mouse.y, 2, 2)))
		{
			pointerToScreen->changePanel("ShopPanel");
		}

		else if (pointerToPanel->getButtons()[0].getShape().getGlobalBounds().intersects(FloatRect(mouse.x, mouse.y, 2, 2)))
		{
			if (GameSettings::PLAYER_MONEY >= 3)
			{
				pointerToTeam->getXP()++;
				GameSettings::PLAYER_MONEY -= 3;
				if (pointerToTeam->getXP() >= pointerToTeam->requiredXP[pointerToTeam->getLevel() - 1])
				{
					pointerToTeam->getXP() = 0;
					pointerToTeam->getLevel()++;
					pointerToTeam->getFieldCapacity()++;
				}
				((GamePanel*)pointerToPanel)->setExpLevel(pointerToTeam->getXP(), pointerToTeam->requiredXP[pointerToTeam->getLevel() - 1], pointerToTeam->getLevel());
				((GamePanel*)pointerToPanel)->setMoney();
			}
		}
		
	}
	if (event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
	{
		if (movingTroop && pointToTroop)
		{
			bool result = false;
			if (!((GameScreen*)(pointerToScreen))->inFight && GameSettings::MAP_BOUNDS.intersects(FloatRect(mouse.x, mouse.y, 2, 2)))
			{
				result = pointerToTeam->moveTroop(pointToTroop, troopWhichSide,false);          // False means troop is going to fieldMap
			}
			else if (GameSettings::SUB_BOUNDS.intersects(FloatRect(mouse.x, mouse.y, 2, 2)))
			{
				result = pointerToTeam->moveTroop(pointToTroop, troopWhichSide,true);          // True means troop is going to subMap
			}
			else if (pointerToPanel->getButtons()[1].getShape().getGlobalBounds().intersects(FloatRect(mouse.x, mouse.y, 2, 2)))
			{
				pointerToTeam->discardTroop(pointToTroop, troopWhichSide);
				GameSettings::PLAYER_MONEY++;
				((GamePanel*)(pointerToPanel))->setMoney();
				result = true;
			}
			if(!result)
			{
				pointToTroop->getPosition() = troopPrev;
			}
			movingTroop = false;
			pointToTroop = nullptr;
			troopPrev = Vector2f(0, 0);
		}
	}
	if (movingTroop)
	{
		mouse = (Vector2i)window.mapPixelToCoords(Mouse::getPosition(window));
		pointToTroop->getPosition() += Vector2f(mouse - mousePrev);
		mousePrev = mouse;
	}
	
}
