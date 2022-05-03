#pragma once
#include <SFML/Graphics.hpp>
#include "TextureHolder.h"
#include <SFML/Audio.hpp>
#include "ScreenManager.h"
#include "GameSettings.h"
using namespace sf;


class Engine
{
private:
    TextureHolder TH;
    Vector2f m_resolution;
    RenderWindow m_window;
    unique_ptr<ScreenManager> m_Manager;
    Text m_text;

    void input();
    void update(float seconds);
    void draw();

public:
    Engine();
    void run();
};