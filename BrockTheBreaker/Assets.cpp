#include "Assets.h"

void Assets::LoadSprites()
{
	// A small lambda function to load the sprites from textures
	auto load = [&](std::string&& name, std::string&& fileName)
	{
		// Loading the texture
		sf::Texture texture;
		texture.loadFromFile(fileName);

		// Setting the indexed name to the loaded texture
		m_spriteMap[name] = texture;
	};

	// Loading all of the sprites and giving them friendly names
	load("brock", "assets/Sprites/brock.png");
	load("ball", "assets/Sprites/ball.png");
	load("brick", "assets/Sprites/brick.png");
	load("side_wall", "assets/Sprites/side_wall.png");
	load("top_wall", "assets/Sprites/top_wall.png");
}

void Assets::LoadAudio()
{
	auto load = [&](std::string&& name, std::string&& fileName)
	{
		// Creating the sound buffer
		m_buffer.loadFromFile(fileName);

		// Loading the audio from the sound buffer
		sf::Sound sound(m_buffer);
		m_audioMap[name] = sound;
	};

	// Loading all of the audio files
	load("hitBrick", "assets/Audio/hit_brick.wav");
	load("wallHit", "assets/Audio/wall_hit.wav");
	load("stageClear", "assets/Audio/stage_clear.wav");
	load("lose", "assets/Audio/lose.wav");
}

void Assets::LoadFont()
{
	sf::Font font;
	font.loadFromFile("assets/Font/bit5x3.ttf");
	
	m_font = font;
}

Assets::Assets()
{

}

Assets::~Assets()
{

}
