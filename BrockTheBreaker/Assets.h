#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>

class Assets
{
private:
	std::map<std::string, sf::Texture> m_spriteMap;
	std::map<std::string, sf::Sound> m_audioMap;
	sf::Font m_font;
	sf::SoundBuffer m_buffer;

public:
	static Assets& GetInstance()
	{
		static Assets instatnce;
		return instatnce;
	}

	Assets(Assets const&) = delete;
	void operator=(Assets const&) = delete;

	sf::Texture& GetSprite(std::string&& name) { return m_spriteMap[name]; }
	sf::Sound& GetAudio(std::string&& name) { return m_audioMap[name]; }
	sf::Font& GetFont() { return m_font; }

	void LoadSprites();
	void LoadAudio();
	void LoadFont();

private:
	Assets();
	~Assets();
};

