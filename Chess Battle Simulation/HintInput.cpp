#include "HintInput.h"

HintInput::HintInput(Panel* mp, Screen* ms)
{
	pointerToPanel = mp;
	pointerToScreen = ms;
}

void HintInput::input(RenderWindow& window, Event& event)
{
	if (event.type == Event::MouseButtonPressed && event.key.code == Mouse::Left)
	{
		mouse = (Vector2i)window.mapPixelToCoords(Mouse::getPosition(window));
		if (pointerToPanel->getButtons()[0].getShape().getGlobalBounds().intersects(FloatRect(mouse.x, mouse.y, 1, 1)))
		{
			pointerToScreen->changePanel("MainMenuPanel");
		}
	}
}
