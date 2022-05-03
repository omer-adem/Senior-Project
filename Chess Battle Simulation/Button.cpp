#include "Button.h"
#include "TextureHolder.h"
Button::Button()
{

}

Button::Button(Vector2f position,
	float width, float height,
	std::string text, std::string filename)
{
	m_Button.setSize(Vector2f(width, height));
	m_Button.setPosition(position);
	m_Button.setTexture(&TextureHolder::GetTexture("graphics/" + filename));
	if (text != "")
	{
		m_Text = "" + text;
		float textPaddingX = width / 10;
		float textPaddingY = height / 10;
		m_ButtonText.setFont(TextureHolder::GetFont());
		m_ButtonText.setCharacterSize(height * .65f);
		m_ButtonText.setFillColor(Color::Black);
		m_ButtonText.setString(text);
		m_ButtonText.setPosition(Vector2f((position.x + textPaddingX),
			(position.y + textPaddingY)));
	}
}

void Button::draw(RenderWindow& window)
{
	window.draw(m_Button);
	if (m_Text != "")
		window.draw(m_ButtonText);
}


RectangleShape& Button::getShape()
{
	return m_Button;
}

Text& Button::getText()
{
	return m_ButtonText;
}