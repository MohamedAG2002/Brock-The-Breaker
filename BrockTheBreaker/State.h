#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

class State
{
private:
	bool m_isPaused, m_isGameOver;
	enum GameState{ MENU = 0, HELP, GAME, OVER } m_gameState;

public:
	void Init();
	void Update(sf::RenderWindow& window);
	void MenuScreen(sf::RenderWindow& window);
	void HelpScreen(sf::RenderWindow& window);
	void PauseScreen(sf::RenderWindow& window);
	void GameOverScreen(sf::RenderWindow& window);

	/* Getters and setters */
	const GameState& GetState() const { return m_gameState; }

	// Pause
	void SetPause(const bool& paused) { m_isPaused = paused; }
	const bool& IsPaused() const { return m_isPaused; }

	// Game Over
	void SetOver(const bool& over) { m_isGameOver = over; }
	const bool& IsGameOver() const { return m_isPaused; }
};
extern State state;