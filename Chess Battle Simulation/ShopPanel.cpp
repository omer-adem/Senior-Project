#include "ShopPanel.h"
#include "TextureHolder.h"

ShopPanel::ShopPanel(Vector2i resolution)
{
	header.setFont(TextureHolder::GetFont());
	header.setCharacterSize(60);
	header.setFillColor(Color::Black);
	header.setString("Shop");
	header.setPosition((resolution.x / 2) - header.getGlobalBounds().width / 2, 305.0f);
	header.setStyle(Text::Bold);

	buttons[0] = Button(Vector2f(resolution.x / 2 + 360, 300.0f), 40, 40, "  X  ", "SettingsButton.png");
	buttons[1] = Button(Vector2f(resolution.x / 2 - 200-50, 830.0f), 100, 40, "Shuffle", "SettingsButton.png");
	buttons[2] = Button(Vector2f(resolution.x / 2 + 200-50, 830.0f), 100, 40, "Freeze", "SettingsButton.png");

	for (int i = 0; i < 3; i++)
	{
		troops[i].setPosition(resolution.x/2 - 300.0f + (i * 250.f), 370.f + TxtOffset);
		t_names[i].setFont(TextureHolder::GetFont());
		t_names[i].setCharacterSize(30);
		t_names[i].setFillColor(Color::Black);
		t_names[i].setPosition(resolution.x/2 - 300.0f + troops[i].getGlobalBounds().width/2 + (i * 250.0f), 300.f + TxtOffset);
		t_names[i].setStyle(Text::Italic);
		r_stats[i] = RectangleShape(Vector2f(200, 120));
		r_stats[i].setFillColor(Color::Color(52, 235, 161));
		r_stats[i].setPosition(Vector2f(resolution.x / 2 - 350.0f + (i * 250.f), 560.0f + TxtOffset));
		t_stats[i].setFont(TextureHolder::GetFont());
		t_stats[i].setCharacterSize(23);
		t_stats[i].setFillColor(Color::Black);
		t_stats[i].setPosition(Vector2f(r_stats[i].getPosition().x + 10.0f, r_stats[i].getPosition().y + 10.0f));
		t_stats[i].setStyle(Text::Italic);
	}

	r_shop = RectangleShape(Vector2f(800, 600));
	r_shop.setFillColor(Color::Color(160, 146, 173, 200));
	r_shop.setPosition(Vector2f(resolution.x / 2 - 400, 300.0f));
}

void ShopPanel::draw(RenderWindow& window)
{
	window.draw(r_shop);
	window.draw(header);
	for (int i = 0; i < 3; i++)
	{
		buttons[i].draw(window);
		if (t_names[i].getString().isEmpty())
			continue;
		window.draw(t_names[i]);
		window.draw(troops[i]);
		window.draw(r_stats[i]);
		window.draw(t_stats[i]);
	}
}

Button* ShopPanel::getButtons()
{
	return buttons;
}

Sprite* ShopPanel::getTroops()
{
	return troops;
}

void ShopPanel::setTroops(Sprite units[3], string names[3], string stats[3])
{
	for (int i = 0; i < 3; i++)
	{
		if (!names[i].empty())
		{
			troops[i].setTexture(*units[i].getTexture());
			troops[i].setScale(0.35f, 0.35f);
			t_names[i].setString(names[i]);
			t_stats[i].setString(stats[i]);
		}
	}
}

bool ShopPanel::clearTroop(int id)
{
	if (!t_names[id].getString().isEmpty())
	{
		troops[id].setTexture(Texture());
		t_stats[id].setString("");
		t_names[id].setString("");
		return true;
	}
	return false;
}