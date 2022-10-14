#pragma once

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Game
{
public:
	Game();
	~Game();

public:
	void Init();
	void Update();
	void Render();
	void Reset();
	void ProcessEvents();
	void Run();

private:
	sf::RenderWindow m_window;
	sf::Event m_event;
	sf::Clock m_deltaClock;
	float m_dt;
};

