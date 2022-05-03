#include "GamePanel.h"
#include "TextureHolder.h"
#include "GameSettings.h"

GamePanel::GamePanel(Vector2i resolution)
{
	money.setTexture(TextureHolder::GetTexture("graphics/Money.png"));
	money.setPosition(Vector2f(resolution.x / 2 + 620, 20.0f));
	moneyAmount.setFont(TextureHolder::GetFont());
	moneyAmount.setCharacterSize(60);
	moneyAmount.setFillColor(Color::White);
	moneyAmount.setString("5");
	moneyAmount.setStyle(Text::Bold);
	moneyAmount.setPosition(Vector2f(resolution.x / 2 + 630 + money.getGlobalBounds().width, 5.0f));

	roundInfo.setFont(TextureHolder::GetFont());
	roundInfo.setCharacterSize(40);
	roundInfo.setFillColor(Color::White);
	roundInfo.setStyle(Text::Bold);
	roundInfo.setString("Round 1\nStrategy Phase");
	roundInfo.setPosition(Vector2f(resolution.x / 8 - 200, 7.5f));

	timeInfo.setFont(TextureHolder::GetFont());
	timeInfo.setCharacterSize(60);
	timeInfo.setFillColor(Color::White);
	timeInfo.setStyle(Text::Bold);
	timeInfo.setString("15");
	timeInfo.setPosition(Vector2f(resolution.x / 2 + 880, 5.0f));

	expInfo.setFont(TextureHolder::GetFont());
	expInfo.setCharacterSize(50);
	expInfo.setFillColor(Color::White);
	expInfo.setString("0 / 4 XP\nLevel 1");
	expInfo.setPosition(Vector2f(resolution.x / 8 - 190, resolution.y - 300));

	r_player = RectangleShape(Vector2f(200, 100));
	r_player.setFillColor(Color(128, 128, 128,255));
	r_cpu = r_player;
	r_player.setPosition(Vector2f(resolution.x / 8 - 200, 140.0f));
	r_cpu.setPosition(Vector2f(resolution.x / 8 - 200, 270.0f));

	playerInfo.setFont(TextureHolder::GetFont());
	playerInfo.setFillColor(Color::White);
	cpuInfo = playerInfo;
	playerInfo.setString("You\t\t\t\t " + to_string(GameSettings::PLAYER_HEALTH));
	playerInfo.setPosition(Vector2f(resolution.x / 8 - 190, 142.5f));
	cpuInfo.setString("Cpu\t\t\t\t" + to_string(GameSettings::CPU_HEALTH));
	cpuInfo.setPosition(Vector2f(resolution.x / 8 - 190, 272.5f));

	playerLife.setTexture(TextureHolder::GetTexture("graphics/Life.png"));
	cpuLife.setTexture(TextureHolder::GetTexture("graphics/Life.png"));
	playerLife.setPosition(Vector2f(resolution.x / 8 - 90, 152.5f));
	cpuLife.setPosition(Vector2f(resolution.x / 8 - 90, 282.5f));

	playerLifeBar.setTexture(&TextureHolder::GetTexture("graphics/LifeBar.png"));
	playerLifeBar.setSize(Vector2f(GameSettings::PLAYER_HEALTH * 1.4f, 30));

	cpuLifeBar.setTexture(&TextureHolder::GetTexture("graphics/LifeBar.png"));
	cpuLifeBar.setSize(Vector2f(GameSettings::CPU_HEALTH * 1.4f, 30));

	playerLifeBar.setPosition(Vector2f(resolution.x / 8 - 190, 200.0f));
	cpuLifeBar.setPosition(Vector2f(resolution.x / 8 - 190, 330.0f));

	buttons[0] = Button(Vector2f(resolution.x / 8 - 180, resolution.y - 180), 120, 120, "", "ExpButton.png");
	buttons[1] = Button(Vector2f(resolution.x / 2 + 640, resolution.y - 160), 180, 90, "", "GameShop.png");
}

void GamePanel::draw(RenderWindow& window)
{
	window.draw(money);
	window.draw(moneyAmount);
	window.draw(timeInfo);
	window.draw(roundInfo);
	window.draw(expInfo);
	window.draw(r_player);
	window.draw(r_cpu);
	window.draw(playerInfo);
	window.draw(cpuInfo);
	window.draw(playerLife);
	window.draw(cpuLife);
	window.draw(playerLifeBar);
	window.draw(cpuLifeBar);
	buttons[0].draw(window);
	buttons[1].draw(window);
}

void GamePanel::update(float seconds)
{
	timer += seconds;
	if (timer >= 1)
	{
		timeValue--;
		timeInfo.setString(to_string(timeValue));
		timer = 0;
	}
}

void GamePanel::reset()
{
	timeValue = 15;
	timer = 0;
	timeInfo.setString(to_string(timeValue));
	setMoney();
	setRound(1, "Strategy");
	setHealth();
	setExpLevel(0, 4, 1);
}

void GamePanel::setTimer()
{
	timeInfo.setString(to_string(timeValue));
	timer = 0;
}

void GamePanel::setRound(int r,string phase)
{
	roundInfo.setString("Round " + to_string(r) + "\n" + phase + " Phase");
}

void GamePanel::setMoney()
{
	moneyAmount.setString(to_string(GameSettings::PLAYER_MONEY));
}

void GamePanel::setExpLevel(int xp, int req, int lvl)
{
	expInfo.setString(to_string(xp) + " / " + to_string(req) + " XP\nLevel " + to_string(lvl));
}

void GamePanel::setHealth()
{
	playerLifeBar.setSize(Vector2f(GameSettings::PLAYER_HEALTH * 1.4f, 30));
	cpuLifeBar.setSize(Vector2f(GameSettings::CPU_HEALTH * 1.4f, 30));
	playerInfo.setString("You\t\t\t\t " + to_string(GameSettings::PLAYER_HEALTH));
	cpuInfo.setString("Cpu\t\t\t\t" + to_string(GameSettings::CPU_HEALTH));
}

Button* GamePanel::getButtons()
{
	return buttons;
}
