#include "HintPanel.h"
#include "TextureHolder.h"

HintPanel::HintPanel(Vector2i resolution)
{
    
    header.setFont(TextureHolder::GetFont());
    header.setCharacterSize(60);
    header.setFillColor(Color::Black);
    header.setString("Hints");
    header.setPosition((resolution.x / 2) - header.getGlobalBounds().width / 2, 305.0f);
    header.setStyle(Text::Bold);

    float* vals = new float[3]{ 150.0f,480.0f,790.0f };
    for (int i = 0; i < 3; i++)
    {
        hints[i].setFont(TextureHolder::GetFont());
        hints[i].setCharacterSize(40);
        hints[i].setFillColor(Color::Green);
        hints[i].setString(to_string(i+1)+"");
        hints[i].setStyle(Text::Bold);
        hints[i].setPosition((resolution.x / 2 - 500.0f) + vals[i], 300.0f + TxtOffset);
    }
    delete[] vals;

    hint1Info.setFont(TextureHolder::GetFont());
    hint1Info.setCharacterSize(25);
    hint1Info.setFillColor(Color::Black);
    hint1Info.setString("When the game starts\neach player has 1$.\n You shouldn't forget to\nbuy a troop from the shop!");
    hint1Info.setPosition((resolution.x / 2 - 500.0f) + 140.0f - hint1Info.getGlobalBounds().width / 2 + 50.0f, 430.0f + TxtOffset + 100.0f);

    hint2Info.setFont(TextureHolder::GetFont());
    hint2Info.setCharacterSize(25);
    hint2Info.setFillColor(Color::Black);
    hint2Info.setString("Troop placement is\nvery important!\nThink ahead about\nwhich troop will\nget attacked first!");
    hint2Info.setPosition((resolution.x / 2 - 500.0f) + 445.0f - hint2Info.getGlobalBounds().width / 2 + 50.0f, 430.0f + TxtOffset + 100.0f);

    hint3Info.setFont(TextureHolder::GetFont());
    hint3Info.setCharacterSize(30);
    hint3Info.setFillColor(Color::Black);
    hint3Info.setString("                  Have Fun\nWhile playing the game!!");
    hint3Info.setPosition((resolution.x / 2 - 500.0f) + 820.0f - hint3Info.getGlobalBounds().width / 2, 380.0f + TxtOffset);
    
    button = Button(Vector2f(resolution.x / 2 + 500 - 40, 300.0f), 40, 40, "  X  ", "SettingsButton.png");
    button.getText().setFillColor(Color::Red);
    button.getShape().setOutlineColor(Color::White);

    shop.setTexture(TextureHolder::GetTexture("graphics/Shop.png"));
    shop.setPosition((resolution.x / 2 - 500.0f) + 150.0f - shop.getGlobalBounds().width / 2, 400.0f + TxtOffset);

    troopex.setTexture(TextureHolder::GetTexture("graphics/TroopEx.png"));
    troopex.setPosition((resolution.x / 2 - 500.0f) + 490.0f - troopex.getGlobalBounds().width / 2, 350.0f + TxtOffset);

    r_hints = RectangleShape(Vector2f(1000, 700));
    r_hints.setFillColor(Color::Color(205, 133, 63, 245));
    r_hints.setPosition(Vector2f(resolution.x / 2 - 500, 300.0f));
}

Button* HintPanel::getButtons()
{
    return &button;
}

void HintPanel::draw(RenderWindow& window)
{
    window.draw(r_hints);
    button.draw(window);
    window.draw(header);
    for (int i = 0; i < 3; i++)
        window.draw(hints[i]);
    window.draw(hint1Info);
    window.draw(hint2Info);
    window.draw(hint3Info);
    window.draw(shop);
    window.draw(troopex);
}