#include "Engine.h"

int GameSettings::FPS = 60;
bool GameSettings::DAMAGE_ENABLE = true;
int GameSettings::RESOLUTION;
int GameSettings::VOLUME = 10;

Engine::Engine()
{
	m_resolution = Vector2f(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height);
	GameSettings::RESOLUTION = m_resolution.y;
	m_window.create(VideoMode(m_resolution.x, m_resolution.y), "Chess Battle Simulation", Style::Fullscreen);
	m_Manager = make_unique<ScreenManager>(Vector2i(m_resolution.x,m_resolution.y));
	m_text.setFont(TextureHolder::GetFont());
	m_text.setCharacterSize(50);
	m_text.setFillColor(Color::White);
	m_text.setString("Fps: 60");
	m_text.setPosition(Vector2f(m_resolution.x / 8 - 200, 380.0f));
}


void Engine::run()
{
	m_window.setFramerateLimit(GameSettings::FPS);
	Clock clock;
	Time frametotal;
	int framecount = 0;
	while (m_window.isOpen())
	{
		Time dt = clock.restart();
		frametotal += dt;
		framecount++;
		input();
		if (frametotal.asSeconds() >= 0.4f)
		{
			int fps = framecount / frametotal.asSeconds();
			framecount = 0;
			frametotal = frametotal.Zero;
			m_text.setString("Fps: " + to_string(fps));
		}
		update(dt.asSeconds());
		draw();
	}
}

void Engine::update(float seconds)
{
	m_Manager->update(seconds);
}

void Engine::input()
{
	m_Manager->input(m_window);
}

void Engine::draw()
{
	m_window.clear(Color::Black);
	m_Manager->draw(m_window);
	m_window.draw(m_text);
	m_window.display();
}

