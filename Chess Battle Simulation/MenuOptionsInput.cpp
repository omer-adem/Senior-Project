#include "MenuOptionsInput.h"
#include "GameSettings.h"

MenuOptionsInput::MenuOptionsInput(Panel* mp, Screen* ms)
{
    pointerToScreen = ms;
    pointerToPanel = mp;
}

void MenuOptionsInput::input(RenderWindow& window, Event& event)
{
    if (event.type == Event::MouseButtonPressed && event.key.code == Mouse::Left)
    {
        mouse = (Vector2i)window.mapPixelToCoords(Mouse::getPosition(window));
        if (pointerToPanel->getButtons()[0].getShape().getGlobalBounds().intersects(FloatRect(mouse.x, mouse.y, 1, 1)))
        {
            pointerToScreen->changePanel("MainMenuPanel");
        }
        else if (pointerToPanel->getButtons()[5].getShape().getGlobalBounds().intersects(FloatRect(mouse.x, mouse.y, 1, 1)))
        {
            if (GameSettings::VOLUME != 0)
            {
                GameSettings::VOLUME--;
                ((MenuOptionsPanel*)(pointerToPanel))->r_volumelevel.setSize(Vector2f(GameSettings::VOLUME * 50, 30));
            }
        }
        else if (pointerToPanel->getButtons()[6].getShape().getGlobalBounds().intersects(FloatRect(mouse.x, mouse.y, 1, 1)))
        {
            if (GameSettings::VOLUME != 10)
            {
                GameSettings::VOLUME++;
                ((MenuOptionsPanel*)(pointerToPanel))->r_volumelevel.setSize(Vector2f(GameSettings::VOLUME * 50, 30));
            }
        }
        else if (pointerToPanel->getButtons()[1].getShape().getGlobalBounds().intersects(FloatRect(mouse.x, mouse.y, 1, 1)))
        {
            if (GameSettings::RESOLUTION == 1080)
            {
                pointerToPanel->getButtons()[2].getShape().setOutlineThickness(0);
                pointerToPanel->getButtons()[1].getShape().setOutlineThickness(3);
                Vector2f resolution = Vector2f(960.0f, 540.0f);
                GameSettings::RESOLUTION = resolution.y;
                window.create(VideoMode(resolution.x, resolution.y), "Chess Battle Simulation");
                window.setFramerateLimit(GameSettings::FPS);
            }
        }
        else if (pointerToPanel->getButtons()[2].getShape().getGlobalBounds().intersects(FloatRect(mouse.x, mouse.y, 1, 1)))
        {
            if (GameSettings::RESOLUTION == 540)
            {
                pointerToPanel->getButtons()[1].getShape().setOutlineThickness(0);
                pointerToPanel->getButtons()[2].getShape().setOutlineThickness(3);
                Vector2f resolution = Vector2f(1920.0f, 1080.0f);
                GameSettings::RESOLUTION = resolution.y;
                window.create(VideoMode(resolution.x, resolution.y), "Chess Battle Simulation", Style::Fullscreen);
                window.setFramerateLimit(GameSettings::FPS);
            }
        }
        else if (pointerToPanel->getButtons()[3].getShape().getGlobalBounds().intersects(FloatRect(mouse.x, mouse.y, 1, 1)))
        {
            if (GameSettings::FPS == 60)
            {
                GameSettings::FPS = 30;
                window.setFramerateLimit(GameSettings::FPS);
                pointerToPanel->getButtons()[3].getShape().setOutlineThickness(3);
                pointerToPanel->getButtons()[4].getShape().setOutlineThickness(0);
            }
        }
        else if (pointerToPanel->getButtons()[4].getShape().getGlobalBounds().intersects(FloatRect(mouse.x, mouse.y, 1, 1)))
        {
            if (GameSettings::FPS == 30)
            {
                GameSettings::FPS = 60;
                window.setFramerateLimit(GameSettings::FPS);
                pointerToPanel->getButtons()[3].getShape().setOutlineThickness(0);
                pointerToPanel->getButtons()[4].getShape().setOutlineThickness(3);
            }
        }
        else if (pointerToPanel->getButtons()[7].getShape().getGlobalBounds().intersects(FloatRect(mouse.x, mouse.y, 1, 1)))
        {
            GameSettings::DAMAGE_ENABLE = !GameSettings::DAMAGE_ENABLE;
        }
    }
}
