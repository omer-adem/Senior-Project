#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class Button
{
private:
	RectangleShape m_Button;
	Text m_ButtonText;

public:
	std::string m_Text;
	Button(Vector2f position,
		float width, float height,
		std::string text, std::string filename);
	Button();
	void draw(RenderWindow& window);
	RectangleShape& getShape();
	Text& getText();
};