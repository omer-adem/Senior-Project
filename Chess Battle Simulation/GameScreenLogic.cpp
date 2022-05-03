#include "GameScreen.h"
#include "GameSettings.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>

int getMax(int n1, int n2, int n3)
{
	if (n1 > n2 && n1 > n3)
		return 0;
	if (n2 > n1 && n2 > n3)
		return 1;
	if (n3 > n1 && n3 > n2)
		return 2;
	return 0;
}

void GameScreen::opponentChoices()
{
	if (GameSettings::CPU_MONEY >= 3 && m_OpponentTeam->getFieldSize()!=0)
	{
		m_OpponentTeam->getXP()++;
		GameSettings::CPU_MONEY -= 3;
		if (m_OpponentTeam->getXP() >= m_OpponentTeam->requiredXP[m_OpponentTeam->getLevel() - 1])
		{
			m_OpponentTeam->getXP() = 0;
			m_OpponentTeam->getLevel()++;
			m_OpponentTeam->getFieldCapacity()++;
		}
	}
	if (GameSettings::CPU_MONEY >= 1 && (m_OpponentTeam->getSubSize() + m_OpponentTeam->getFieldSize()) <= m_OpponentTeam->getFieldCapacity())
	{
		int score[3];
		for (int i = 0; i < 3; i++)
			score[i] = (m_Pool[m_poolIndexesOpponent[i]]->getMaxHP() + m_Pool[m_poolIndexesOpponent[i]]->getATK()) / m_Pool[m_poolIndexesOpponent[i]]->getATKSPEED();
		
		int indx = getMax(score[0], score[1], score[2]);
		auto it = m_Pool.begin() + m_poolIndexesOpponent[indx];
		BaseCharacter* troop = (*it).get();
		if (m_OpponentTeam->addTroop(it))
		{
			for (int j = 0; j < 3; j++)
			if (m_poolIndexesOpponent[indx] < m_poolIndexesPlayer[j])
				m_poolIndexesPlayer[j]--;
			
			troop->getBar().setFillColor(Color::Red);
			troop->getInfo().setFillColor(Color::Black);
			troop->setEnemyTeam(m_PlayerTeam);
			troop->setTeam(m_OpponentTeam);
			troop->setActive(false);
			m_Pool.erase(it);
			GameSettings::CPU_MONEY--;
			m_poolIndexesOpponent[indx] = -1;
		}
		troop = nullptr;
	}
	srand(time(NULL));
	if (m_OpponentTeam->getFieldCapacity() > m_OpponentTeam->getFieldSize())
	{
		if (m_OpponentTeam->getSubSize() > 0)
		{
			auto it = m_OpponentTeam->SubUnits().begin();
			int x = rand() % 8;
			int y = rand() % 4;
			if ((*it)->getMaxHP() >= 480)
				y = y % 2 + 2;
			else
				y = y % 2;
			m_OpponentTeam->moveTroop(it, x, y);
		}
	}
}

void GameScreen::generateTroops(char c)
{
	srand(time(NULL) * GameSettings::POOLSEED);
	
	if (c == 'P')
	{
		Sprite s_temp[3];
		string t_name[3];
		string t_info[3];
		for (int i = 0; i < 3; i++)
		{
			if ((m_poolIndexesPlayer[i] == -1 && isFrozen) || !isFrozen)
			{
				m_poolIndexesPlayer[i] = rand() % m_Pool.size();
				s_temp[i].setTexture(*m_Pool[m_poolIndexesPlayer[i]]->getSprite().getTexture());
				t_name[i] = (m_Pool[m_poolIndexesPlayer[i]]->getName());
				t_info[i] = ("Attack : " + to_string(m_Pool[m_poolIndexesPlayer[i]]->getATK()) +
					"\nHealth : " + to_string(m_Pool[m_poolIndexesPlayer[i]]->getMaxHP()) +
					"\nAttack Speed : " + to_string(m_Pool[m_poolIndexesPlayer[i]]->getATKSPEED()).substr(0,3) +
					"\nClass : " + m_Pool[m_poolIndexesPlayer[i]]->getClass());
			}
		}
		((ShopPanel*)(m_panels[1].get()))->setTroops(s_temp, t_name, t_info);
	}
	else if (c == 'C')
	{
		for (int i = 0; i < 3; i++)
		{
			m_poolIndexesOpponent[i] = rand() % m_Pool.size();
			int temp = m_poolIndexesOpponent[i];
			if (temp == m_poolIndexesPlayer[0] || temp == m_poolIndexesPlayer[1] || temp == m_poolIndexesPlayer[2])
				i--;
		}
	}
}

void GameScreen::backgroundTask()
{
	sleep(seconds(2));
	m_Info.setString("");
}

void GameScreen::endFight(char winner)
{
	if (winner == 'p')
	{
		GameSettings::CPU_HEALTH -= m_PlayerTeam->Alive * (m_PlayerTeam->getLevel() + 3);
		GameSettings::CPU_MONEY += 2;
		GameSettings::PLAYER_MONEY += 5;
		m_Info.setString("Player wins!!");
		th1 = new thread(&GameScreen::backgroundTask,ref(*this));
		th1->detach();
	}
	else if (winner == 'c')
	{
		GameSettings::PLAYER_HEALTH -= m_OpponentTeam->Alive * (m_OpponentTeam->getLevel() + 3);
		GameSettings::CPU_MONEY += 5;
		GameSettings::PLAYER_MONEY += 2;
		m_Info.setString("CPU wins!!");
		th1 = new thread(&GameScreen::backgroundTask, ref(*this));
		th1->detach();
	}
	else
	{
		GameSettings::PLAYER_MONEY += 2;
		GameSettings::CPU_MONEY += 2;
		GameSettings::PLAYER_HEALTH -= (m_OpponentTeam->Alive) * (m_OpponentTeam->getLevel()+3);
		GameSettings::CPU_HEALTH -= (m_PlayerTeam->Alive) * (m_PlayerTeam->getLevel() + 3);
		m_Info.setString("Draw!!");
		th1 = new thread(&GameScreen::backgroundTask, ref(*this));
		th1->detach();
	}
	m_PlayerTeam->getStateManager()->ChangeState(WaitTeam::Instance());
	m_OpponentTeam->getStateManager()->ChangeState(WaitTeam::Instance());
	waitTime = 15;
	m_panels[0]->timeValue = 15;
	((GamePanel*)m_panels[0].get())->setTimer();
	((GamePanel*)m_panels[0].get())->setRound(++round, "Strategy");
	inFight = false;
	generateTroops('P');
	generateTroops('C');
	cpuChose = false;
	isFrozen = false;
	m_panels[1]->getButtons()[2].getShape().setOutlineThickness(0);
	((GamePanel*)m_panels[0].get())->setExpLevel(m_PlayerTeam->getXP(), m_PlayerTeam->requiredXP[m_PlayerTeam->getLevel() - 1], m_PlayerTeam->getLevel());
	((GamePanel*)m_panels[0].get())->setMoney();
	((GamePanel*)m_panels[0].get())->setHealth();
}

void GameScreen::gameLogic(float seconds)
{
	if (GameSettings::CPU_HEALTH > 0 && GameSettings::PLAYER_HEALTH > 0)
	{
		waitTime -= seconds;
		if (!inFight)
		{
			if (waitTime <= 0)
			{
				changePanel("GamePanel");
				m_PlayerTeam->Alive = m_PlayerTeam->FieldUnits().size();
				m_OpponentTeam->Alive = m_OpponentTeam->FieldUnits().size();
				m_PlayerTeam->getStateManager()->ChangeState(Fight::Instance());
				m_OpponentTeam->getStateManager()->ChangeState(Fight::Instance());
				waitTime = 30;
				m_panels[0]->timeValue = 30;
				((GamePanel*)m_panels[0].get())->setTimer();
				((GamePanel*)m_panels[0].get())->setRound(round, "Battle");
				inFight = true;
				
			}
			else if (!cpuChose)
			{
				opponentChoices();
				cpuChose = true;
			}
		}
		else
		{
			if (!m_PlayerTeam->active && !m_OpponentTeam->active)
			{
				endFight('n');
			}

			else if (!m_PlayerTeam->active)
			{
				endFight('c');
			}

			else if (!m_OpponentTeam->active)
			{
				endFight('p');
			}

			else if (waitTime <= 0)
			{			
				endFight('n');
			}
		}
	}
	else
	{
		if (GameSettings::CPU_HEALTH <= 0)
		{
			m_Info.setString("Player won the game!!");
			th1 = new thread(&GameScreen::backgroundTask, ref(*this));
			th1->detach();
			GameSettings::CPU_HEALTH = 0;
		}
		else if (GameSettings::PLAYER_HEALTH <= 0)
		{
			m_Info.setString("CPU won the game!!");
			th1 = new thread(&GameScreen::backgroundTask, ref(*this));
			th1->detach();
			GameSettings::PLAYER_HEALTH = 0;
		}
		else
		{
			m_Info.setString("Draw Game!!");
			th1 = new thread(&GameScreen::backgroundTask, ref(*this));
			th1->detach();
			GameSettings::PLAYER_HEALTH = 0;
			GameSettings::CPU_HEALTH = 0;
		}
		game = false;
		((GamePanel*)m_panels[0].get())->setHealth();
		th2 = new thread(&GameScreen::finishGame, ref(*this));
		th2->detach();
	}
}

void GameScreen::finishGame()
{
	sf::sleep(seconds(2.5f));
	m_Info.setString("Thanks for playing the game!");
	sf::sleep(seconds(3));
	m_Info.setString("");
	m_inputHandler[0]->pointerToManager->changeScreen("MainMenuScreen");
}