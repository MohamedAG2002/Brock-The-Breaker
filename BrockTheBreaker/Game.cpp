#include "Game.h"
#include "GameObject.h"
#include "Utilities.h"
#include "Assets.h"
#include "State.h"
#include "Score.h"
#include "Collision.h"

// PROBLEMS:
// Resetting the bricks after they were cleared does not work properly, the stage clear audio keeps screeching as well
// Fix all of the audio

// TO-DO:
// Put all of the objects in the game into a vector and go through the vector to initialize, update and render the objects
// Create a UI namespace that will make adding and controling buttons easier
// Add a filesystem that remebers you high score

Game::Game()
{
	m_dt = 0;
}

Game::~Game()
{

}

void Game::Init()
{
	// Creating the window and setting the fps limit to 60
	m_window.create(sf::VideoMode(800, 600), "Brock The Breaker", sf::Style::Titlebar | sf::Style::Close);
	m_window.setFramerateLimit(60);

	// Loading the sprites
	Assets::GetInstance().LoadSprites();

	// Loading the audio
	Assets::GetInstance().LoadAudio();

	// Loading the font
	Assets::GetInstance().LoadFont();

	// State init
	state.Init();
	
	/* Objects init */
	// Player init
	player.Init(Assets::GetInstance().GetSprite("brock"), // Texture
				sf::Vector2f(m_window.getSize().x / 2.0f - 50.0f / 2.0f, m_window.getSize().y - 40.0f), // Position
				true); // Active state
	player.SetMoving(false);
	player.SetSpeed(400.0f, 0.0f);
	
	// Ball init
	ball.Init(Assets::GetInstance().GetSprite("ball"), // Texture
			  sf::Vector2f(player.GetPos().x + 21.0f, player.GetPos().y - 20.0f), // Position
			  true); // Active state
	ball.SetMoving(false);
	ball.SetSpeed(350, 350.0f);

	// Left wall init
	walls.at(0).Init(Assets::GetInstance().GetSprite("side_wall"), sf::Vector2f(20.0f, 50.0f), true);
	
	// Top wall init
	walls.at(1).Init(Assets::GetInstance().GetSprite("top_wall"), sf::Vector2f(20.0f, 20.0f), true);
	// Resizing the sprite scale because I can't be bothered to redraw it
	walls.at(1).GetSprite().setScale(walls.at(1).GetSprite().getScale().x + 0.462f, walls.at(1).GetSprite().getScale().y);

	// Right wall init
	walls.at(2).Init(Assets::GetInstance().GetSprite("side_wall"), sf::Vector2f(m_window.getSize().x - 50.0f, 50.0f), true);
	
	// Bricks init
	for (int i = 0; i < bricks.size(); i++)
	{
		for (int j = 0; j < bricks.at(i).size(); j++)
		{
			bricks.at(i).at(j).Init(Assets::GetInstance().GetSprite("brick"), // Texture
								    sf::Vector2f((BRICK_SIZE.x + 30) * j + 80, (BRICK_SIZE.y - 40) * i + 70), // Position
									true); // Active state
		}
	}
}

void Game::Update()
{
	// Getting the delta time
	m_dt = m_deltaClock.restart().asSeconds();

	// Staring the movement when the SPACE bar is pressed
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		player.SetMoving(true);
		ball.SetMoving(true);
	}

	/* Movement handaling */
	// Only when the current state is the gameplay
	if (state.GetState() == 2)
	{
		if (!state.IsPaused())
		{
			if (player.IsMoving()) player.Move(m_dt);
			if (ball.IsMoving()) ball.Move(m_dt);
		}
	}

	// Clamping movements
	float cX = utl::Clamp(player.GetPos().x, walls.at(0).GetPos().x + player.GetSize().x / 2, walls.at(2).GetPos().x - player.GetSize().x);
	player.SetPos(cX, player.GetPos().y);

	/* Collision handaling */
	collision.Update();

	/* Score handaling */
	score.Update();

	/* States handaling */
	state.Update(m_window);
}

void Game::Render()
{
	// Drawing stuff
	m_window.clear(sf::Color::White);

	switch (state.GetState())
	{
		// Menu
		case 0: state.MenuScreen(m_window); break;
		// Help
		case 1: state.HelpScreen(m_window); break;
		// Game 
		case 2:
		{
			// Player
			if (player.IsActive()) player.DrawSprite(m_window);
			// Ball
			if (ball.IsActive()) ball.DrawSprite(m_window);
			// Walls
			for (int i = 0; i < walls.size(); i++)
			{
				if (walls.at(i).IsActive()) walls.at(i).DrawSprite(m_window);
			}
			// Bricks
			for (int i = 0; i < bricks.size(); i++)
			{
				for (int j = 0; j < bricks.at(i).size(); j++)
				{
					if (bricks.at(i).at(j).IsActive()) bricks.at(i).at(j).DrawSprite(m_window);
				}
			}

			// Setting up the score's text
			sf::Text scoreText(std::to_string(score.GetScore()), Assets::GetInstance().GetFont(), 30);
			scoreText.setPosition(m_window.getSize().x / 2.0f, 15.0f);
			scoreText.setFillColor(sf::Color::Black);

			// Setting up the wave's text
			sf::Text waveText("Wave: " + std::to_string(score.GetWave()), Assets::GetInstance().GetFont(), 30);
			waveText.setPosition(30.0f, 15);
			waveText.setFillColor(sf::Color::Black);

			// Drawing the texts
			m_window.draw(scoreText);
			m_window.draw(waveText);

		} break;
		// Game over
		case 3: state.GameOverScreen(m_window); break;
	}

	// Pause
	if (state.IsPaused()) state.PauseScreen(m_window);
	
	m_window.display();
}

void Game::Reset()
{
	// Resetting the player
	player.SetPos(375, 560);
	player.SetMoving(false);

	// Resetting the ball
	ball.SetPos(player.GetPos().x + 21.0f, player.GetPos().y - 20.0f);
	ball.SetMoving(false);

	// Resetting the bricks
	for (int i = 0; i < bricks.size(); i++)
	{
		for (int j = 0; j < bricks.at(i).size(); j++)
		{
			if (!bricks.at(i).at(j).IsActive()) 
				bricks.at(i).at(j).SetActive(true);
		}
	}

	// Resetting variables
	score.SetScore(0);
	score.SetWave(0);
	state.SetPause(false);
	state.SetOver(false);
}

void Game::ProcessEvents()
{
	while (m_window.pollEvent(m_event))
	{
		switch (m_event.type)
		{
			case sf::Event::Closed: m_window.close(); break;
			case sf::Event::KeyPressed:
			{
				if (m_event.key.code == sf::Keyboard::Escape)
					m_window.close();
			} break;
		}
	}
}

void Game::Run()
{
	Init();

	// Main game loop
	while (m_window.isOpen())
	{
		ProcessEvents();

		Update();

		Render();
	}
}