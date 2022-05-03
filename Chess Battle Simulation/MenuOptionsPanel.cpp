#include "MenuOptionsPanel.h"
#include "TextureHolder.h"
#include "GameSettings.h"

MenuOptionsPanel::MenuOptionsPanel(Vector2i resolution)
{

    string values[] = { "Resolution","Volume Level","Framerate","Display Damage On Hit" };
    for (int i = 0; i < 4; i++)
    {
        t_texts[i].setFont(TextureHolder::GetFont());
        t_texts[i].setCharacterSize(40);
        t_texts[i].setFillColor(Color::White);
        t_texts[i].setString(values[i]);
        t_texts[i].setPosition((resolution.x / 2 - 500.0f) + 20.0f, 300.0f + TxtOffset*(i+1));
    }

    header.setFont(TextureHolder::GetFont());
    header.setCharacterSize(60);
    header.setFillColor(Color::Black);
    header.setString("Settings");
    header.setPosition((resolution.x / 2) - header.getGlobalBounds().width / 2, 305.0f);
    header.setStyle(Text::Bold);

    buttons[0] = Button(Vector2f(resolution.x / 2 + 500 - 40, 300.0f), 40, 40, "  X  ", "SettingsButton.png");
    buttons[0].getText().setFillColor(Color::Red);
    buttons[0].getShape().setOutlineColor(Color::White);
    buttons[1] = Button(Vector2f(resolution.x / 2 - 120, 300.0f + TxtOffset), 90, 50, "540P", "SettingsButton.png");
    buttons[2] = Button(Vector2f(resolution.x / 2 + 25, 300.0f + TxtOffset), 90, 50, "1080P", "SettingsButton.png");
    buttons[2].getShape().setOutlineThickness(3.0f);
    buttons[3] = Button(Vector2f(resolution.x / 2 - 120, 300.0f + TxtOffset * 3), 90, 50, "30FPS", "SettingsButton.png");
    buttons[4] = Button(Vector2f(resolution.x / 2 + 25, 300.0f + TxtOffset * 3), 90, 50, "60FPS", "SettingsButton.png");
    buttons[4].getShape().setOutlineThickness(3.0f);
    buttons[5] = Button(Vector2f(resolution.x / 2 - 500.0f + 20.0f + t_texts[1].getGlobalBounds().width + 40.0f, 300.0f + TxtOffset * 2), 50, 50, "  -  ", "SettingsButton.png");
    buttons[6] = Button(Vector2f(resolution.x / 2 - 500.0f + 20.0f + t_texts[1].getGlobalBounds().width + 610.0f, 300.0f + TxtOffset * 2), 50, 50, "  +  ", "SettingsButton.png");
    buttons[7] = Button(Vector2f(resolution.x / 2 - 500.0f + 40.0f + t_texts[3].getGlobalBounds().width, 300.0f + TxtOffset * 4), 50, 50, "", "SettingsButton.png");

    r_settings = RectangleShape(Vector2f(1000, 700));
    r_settings.setFillColor(Color::Color(205, 133, 63, 220));
    r_settings.setPosition(Vector2f(resolution.x / 2 - 500, 300.0f));

    r_volumelevel = RectangleShape(Vector2f(GameSettings::VOLUME*50, 30));
    r_volumelevel.setTexture(&TextureHolder::GetTexture("graphics/VolumeLevel.png"));
    r_volumelevel.setPosition(buttons[5].getShape().getGlobalBounds().left + 60, buttons[5].getShape().getGlobalBounds().top + 10.0f);

    tick.setTexture(TextureHolder::GetTexture("graphics/Tick.png"));
    tick.setPosition(Vector2f(resolution.x / 2 - 500.0f + 44.0f + t_texts[3].getGlobalBounds().width, 300.0f + TxtOffset * 4 + 2.0f));
    tick.scale(tick.getScale().x * 1.65f, tick.getScale().y * 1.65f);
}

void MenuOptionsPanel::draw(RenderWindow& window)
{
    window.draw(r_settings);
    window.draw(header);
    for (int i = 0; i < 8; i++)
        buttons[i].draw(window);
    for (int j = 0; j < 4; j++)
        window.draw(t_texts[j]);
    window.draw(r_volumelevel);
    if (GameSettings::DAMAGE_ENABLE)
        window.draw(tick);
}


Button* MenuOptionsPanel::getButtons()
{
    return buttons;
}