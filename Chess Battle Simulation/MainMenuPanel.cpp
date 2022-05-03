#include "MainMenuPanel.h"

MainMenuPanel::MainMenuPanel(Vector2i resolution)
{
    string labels[4] = { "Start Game","Hints","Settings","Exit" };
    for (int i = 0; i < 4; i++)
        buttons[i] = Button(Vector2f(resolution.x / 2 - buttonWidth / 2, 400.0f + TxtOffset * i), buttonWidth, buttonHeight, labels[i], "MenuButton.png");
}


void MainMenuPanel::draw(RenderWindow& window)
{
    for (int i = 0; i < 4; i++)
        buttons[i].draw(window);
}


Button* MainMenuPanel::getButtons()
{
    return buttons;
}