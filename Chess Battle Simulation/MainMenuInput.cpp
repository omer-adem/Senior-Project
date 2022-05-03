#include "MainMenuInput.h"


MainMenuInput::MainMenuInput(Panel* mp, Screen* ms, RemoteManager* sm)
{
    pointerToScreen = ms;
	pointerToPanel = mp;
    pointerToManager = sm;
}

void MainMenuInput::input(RenderWindow& window,Event& event)
{
	if (event.type == Event::MouseButtonPressed && event.key.code == Mouse::Left)
	{
        mouse = (Vector2i)window.mapPixelToCoords(Mouse::getPosition(window));
        if (pointerToPanel->getButtons()[0].getShape().getGlobalBounds().intersects(FloatRect(mouse.x, mouse.y, 1, 1)))
        {
            pointerToManager->changeScreen("GameScreen");
        }
        else if (pointerToPanel->getButtons()[1].getShape().getGlobalBounds().intersects(FloatRect(mouse.x, mouse.y, 1, 1)))
        {
            pointerToScreen->changePanel("HintPanel");
        }
        else if (pointerToPanel->getButtons()[2].getShape().getGlobalBounds().intersects(FloatRect(mouse.x, mouse.y, 1, 1)))
        {
            pointerToScreen->changePanel("MenuOptionsPanel");
        }
        else if (pointerToPanel->getButtons()[3].getShape().getGlobalBounds().intersects(FloatRect(mouse.x, mouse.y, 1, 1)))
        {
            window.close();
        }
	}
}
