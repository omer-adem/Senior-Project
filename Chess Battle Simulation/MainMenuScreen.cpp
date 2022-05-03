#include "MainMenuScreen.h"
#include "TextureHolder.h"
#include <iostream>
using namespace std;
MainMenuScreen::MainMenuScreen(Vector2i resolution,RemoteManager* sm)
{
    m_currentPanel = "MainMenuPanel";
    m_panels[0] = make_unique<MainMenuPanel>( resolution );
    m_panels[1] = make_unique<MenuOptionsPanel>( resolution );
    m_panels[2] = make_unique<HintPanel>( resolution );
    header.setFont(TextureHolder::GetFont());
    header.setCharacterSize(75);
    header.setFillColor(Color::Black);
    header.setString("Chess Battle Simulation");
    header.setPosition((resolution.x / 2) - header.getGlobalBounds().width / 2, 30.0f);
    m_View = View(FloatRect(0, 0, resolution.x,resolution.y));
    background.setTexture(TextureHolder::GetTexture("graphics/MenuBackground.png"));
    m_inputhandlers[0] = make_unique<MainMenuInput>( m_panels[0].get(), this,sm );
    m_inputhandlers[1] = make_unique<MenuOptionsInput>( m_panels[1].get(), this);
    m_inputhandlers[2] = make_unique<HintInput>( m_panels[2].get(), this );
}

int MainMenuScreen::findPanel()
{
    if (m_currentPanel == "MainMenuPanel")
        return 0;
    else if (m_currentPanel == "MenuOptionsPanel")
        return 1;
    else if (m_currentPanel == "HintPanel")
        return 2;
}

void MainMenuScreen::changePanel(string name)
{
    m_currentPanel = name;
}


void MainMenuScreen::draw(RenderWindow& window)
{
    window.setView(m_View);
    window.draw(background);
    window.draw(header);
    m_panels[findPanel()]->draw(window);
}

void MainMenuScreen::input(RenderWindow& window)
{
    Event event;
    while (window.pollEvent(event))
    {
        if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
            window.close();
        if (event.type == Event::Closed)
            window.close();
        m_inputhandlers[findPanel()]->input(window, event);
    }
}

void MainMenuScreen::update(float seconds){}

void MainMenuScreen::init(){}
