#include "GameScreen.h"
#include "TextureHolder.h"
#include "GameSettings.h"

int GameSettings::CPU_HEALTH = 100;
int GameSettings::PLAYER_HEALTH = 100;
int GameSettings::PLAYER_MONEY = 5;
int GameSettings::CPU_MONEY = 5;
int GameSettings::POOLSEED = 19;
int GameSettings::POOLSIZE = 80;
int GameSettings::AVAILABLE_ID = 0;

GameScreen::GameScreen(Vector2i resolution, RemoteManager* sm)
{
	m_currentPanel = "GamePanel";
	m_View = View(FloatRect(0, 0, resolution.x, resolution.y));
	background.setTexture(TextureHolder::GetTexture("graphics/Environment.png"));
	m_PlayerTeam = make_shared<UnitTeam>(WaitTeam::Instance(),'p');
	m_OpponentTeam = make_shared<UnitTeam>(WaitTeam::Instance(),'c');
	m_panels[0] = make_unique<GamePanel>( resolution );
	m_panels[1] = make_unique<ShopPanel>( resolution );
	m_inputHandler[0] = make_unique<GameInput>( m_panels[0].get(),this,sm,m_PlayerTeam);
	m_inputHandler[1] = make_unique<ShopInput>(m_panels[1].get(), this,m_panels[0].get());
	m_Info.setFont(TextureHolder::GetFont());
	m_Info.setCharacterSize(60);
	m_Info.setFillColor(Color::Cyan);
	m_Info.setStyle(Text::Italic);
	m_Info.setPosition(resolution.x / 2 - 200, 20.0f);
	game = true;
}

int GameScreen::findPanel()
{
	if (m_currentPanel == "GamePanel")
		return 0;
	else if (m_currentPanel == "ShopPanel")
		return 1;
	return -1;
}

void GameScreen::changePanel(string name)
{
	m_currentPanel = name;
}

void GameScreen::draw(RenderWindow& window)
{
	window.setView(m_View);
	window.draw(background);
	window.draw(m_Info);
	m_panels[0]->draw(window);
	m_PlayerTeam->draw(window);
	m_OpponentTeam->draw(window);
	if (findPanel())
		m_panels[1]->draw(window);
}

void GameScreen::input(RenderWindow& window)
{
	Event event;
	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
			window.close();
		m_inputHandler[findPanel()]->input(window, event);
	}
}

void GameScreen::update(float seconds)
{
	if (game)
	{
		gameLogic(seconds);
		m_PlayerTeam->update(seconds);
		m_OpponentTeam->update(seconds);
		m_panels[0]->update(seconds);
	}
}

void GameScreen::resetGame()
{
	game = true;
	GameSettings::CPU_HEALTH = 100;
	GameSettings::PLAYER_HEALTH = 100;
	GameSettings::AVAILABLE_ID = 0;
	GameSettings::PLAYER_MONEY = 4;
	GameSettings::CPU_MONEY = 4;
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			GameSettings::MOVEMENT_MAP[i][j] = Node(i, j);
	round = 1;
	inFight = false;
	isFrozen = false;
	waitTime = 15;
	cpuChose = false;
	((GamePanel*)(m_panels[0].get()))->reset();
	m_panels[1]->getButtons()[2].getShape().setOutlineThickness(0);
	m_Pool.clear();
	m_PlayerTeam->clear(WaitTeam::Instance());
	m_OpponentTeam->clear(WaitTeam::Instance());
}