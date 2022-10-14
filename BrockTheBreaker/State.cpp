#include "State.h"
#include "Assets.h"
#include "Game.h"
#include "Utilities.h"
#include "Score.h"
#include "GameObject.h"

#include <SFML/System.hpp>

// Extern variables init
State state;

// Global variables
Game game;
float menuTitleSway = 0;
float menuUnderlineSway = 0;

void State::Init()
{
	m_isPaused = false;
	m_isGameOver = false;
	m_gameState = MENU;
}

void State::Update(sf::RenderWindow& window)
{
	// Pausing when P is pressed
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) && m_gameState == GAME)
		m_isPaused = !m_isPaused;

	// Menu to game
	if (m_gameState == MENU && sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		m_gameState = GAME;
		game.Reset();
	}
	// Menu to help
	if (m_gameState == MENU && sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		m_gameState = HELP;
	// Help to menu
	if (m_gameState == HELP && sf::Keyboard::isKeyPressed(sf::Keyboard::M))
		m_gameState = MENU;
	// Pause to menu
	if (m_isPaused && sf::Keyboard::isKeyPressed(sf::Keyboard::M))
		m_gameState = MENU;
	// Game to over
	if (m_gameState == GAME && m_isGameOver)
		m_gameState = OVER;
	// Over to game
	if (m_gameState == OVER && sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		game.Reset();
		m_gameState = GAME;
	}

	// Death handaling
	if (ball.GetPos().y > window.getSize().y)
		state.SetOver(true);
}

void State::MenuScreen(sf::RenderWindow& window)
{	
	// Clamping the values
	menuTitleSway = utl::Clamp(menuTitleSway, 0, 190.5f);
	menuUnderlineSway = utl::Clamp(menuUnderlineSway, 7, 200);

	// Menu title
	sf::Text menuTitle("Brock The Breaker", Assets::GetInstance().GetFont(), 50);
	menuTitle.setPosition(menuTitleSway, 10);
	menuTitle.setFillColor(sf::Color::Blue);
	// Menu underline
	sf::RectangleShape underline;
	underline.setSize(sf::Vector2f(423, 7));
	underline.setPosition(menuUnderlineSway, 65);
	underline.setFillColor(sf::Color::Blue);

	// Play text
	sf::Text playText("1.Play", Assets::GetInstance().GetFont(), 30);
	playText.setPosition(window.getSize().x / 2.0f - playText.getGlobalBounds().width / 2.0f, 215);
	playText.setFillColor(sf::Color::Blue);
	
	// Help text
	sf::Text helpText("2.Help", Assets::GetInstance().GetFont(), 30);
	helpText.setPosition(window.getSize().x / 2.0f - helpText.getGlobalBounds().width / 2.0f, 268);
	helpText.setFillColor(sf::Color::Blue);

	// Exit text
	sf::Text exitText("[ESC] Exit", Assets::GetInstance().GetFont(), 20);
	exitText.setPosition(5, 574);
	exitText.setFillColor(sf::Color::Red);

	// Drawing the texts
	window.draw(menuTitle);
	window.draw(playText);
	window.draw(helpText);
	window.draw(exitText);
	window.draw(underline);

	// Moving the menu title and its underline to the right
	menuTitleSway++;
	menuUnderlineSway++;

	// Deactivating pause in case it is still on
	m_isPaused = false;
}

void State::HelpScreen(sf::RenderWindow& window)
{
	// Help title 
	sf::Text helpTitle("Help", Assets::GetInstance().GetFont(), 50);
	helpTitle.setPosition(window.getSize().x / 2.0f - helpTitle.getGlobalBounds().width / 2.0f, 10.0f);
	helpTitle.setFillColor(sf::Color::Blue);

	/* Help texts */
	// Player control
	sf::Text help1("Move with A and D keys or LEFT and RIGHT arrow keys", Assets::GetInstance().GetFont(), 30);
	help1.setPosition(30.0f, 200.0f);
	help1.setFillColor(sf::Color::Green);
	
	// Pause control
	sf::Text help2("Press P to pause the game", Assets::GetInstance().GetFont(), 30);
	help2.setPosition(30.0f, 250.0f);
	help2.setFillColor(sf::Color::Green);
	
	// Start control
	sf::Text help3("Press SPACE to start the game", Assets::GetInstance().GetFont(), 30);
	help3.setPosition(30.0f, 300.0f);
	help3.setFillColor(sf::Color::Green);

	// To menu text
	sf::Text menuText("[M] Menu", Assets::GetInstance().GetFont(), 20);
	menuText.setPosition(5, 574);
	menuText.setFillColor(sf::Color::Blue);

	window.draw(helpTitle);
	window.draw(help1);
	window.draw(help2);
	window.draw(help3);
	window.draw(menuText);
}

void State::PauseScreen(sf::RenderWindow& window)
{
	// Pause title
	sf::Text pauseTitle("PAUSED", Assets::GetInstance().GetFont(), 40);
	pauseTitle.setPosition(window.getSize().x / 2.0f - pauseTitle.getGlobalBounds().width / 2.0f, 177);
	pauseTitle.setFillColor(sf::Color::Red);

	// Resume text
	sf::Text resumeText("[P] Resume", Assets::GetInstance().GetFont(), 25);
	resumeText.setPosition(window.getSize().x / 2.0f - resumeText.getGlobalBounds().width / 2.0f, 234);
	resumeText.setFillColor(sf::Color::Red);

	// To menu text
	sf::Text menuText("[M] Menu", Assets::GetInstance().GetFont(), 20);
	menuText.setPosition(5, 574);
	menuText.setFillColor(sf::Color::Blue);

	// Drawing the texts
	window.draw(pauseTitle);
	window.draw(resumeText);
	window.draw(menuText);
}

void State::GameOverScreen(sf::RenderWindow& window)
{
	// Game over title
	sf::Text overTitle("Game Over!", Assets::GetInstance().GetFont(), 50);
	overTitle.setPosition(window.getSize().x / 2.0f - overTitle.getGlobalBounds().width / 2.0f, 10);
	overTitle.setFillColor(sf::Color::Blue);

	// Score text
	sf::Text scoreText("Score: " + std::to_string(score.GetScore()), Assets::GetInstance().GetFont(), 30);
	scoreText.setPosition(window.getSize().x / 2.0f - scoreText.getGlobalBounds().width / 2.0f, 206);
	scoreText.setFillColor(sf::Color::Blue);

	// High score text
	sf::Text highScoreText("High score: " + std::to_string(score.GetHighScore()), Assets::GetInstance().GetFont(), 30);
	highScoreText.setPosition(window.getSize().x / 2.0f - highScoreText.getGlobalBounds().width / 2.0f, 248);
	highScoreText.setFillColor(sf::Color::Blue); 

	// Wave text
	sf::Text waveText("Wave: " + std::to_string(score.GetWave()), Assets::GetInstance().GetFont(), 30);
	waveText.setPosition(window.getSize().x / 2.0f - waveText.getGlobalBounds().width / 2.0f, 292.0f);
	waveText.setFillColor(sf::Color::Blue);

	// Replay text
	sf::Text replayText("[R] Replay", Assets::GetInstance().GetFont(), 20);
	replayText.setPosition(5, 574);
	replayText.setFillColor(sf::Color::Red);

	// Drawing the texts
	window.draw(overTitle);
	window.draw(scoreText);
	window.draw(highScoreText);
	window.draw(waveText);
	window.draw(replayText);

	// Deactivating pause in case it is still on
	m_isPaused = false;
}
