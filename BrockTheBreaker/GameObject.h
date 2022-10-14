#pragma once

#include <SFML/Graphics.hpp>

#include <array>

#include "Movement.h"

// Consts 
static const int COLOMN = 16;
static const int ROW = 8;
static const sf::Vector2f BRICK_SIZE(10, 60);

class GameObject
{
protected:
	sf::Sprite m_sprite;
	bool m_isActive;

public:
	GameObject();
	~GameObject();

public:
	void Init(const sf::Texture& texture, const sf::Vector2f& pos, const bool& active);
	void DrawSprite(sf::RenderWindow& window);

	/* Getters and setters */
	// Position
	void SetPos(const float& x, const float& y) { m_sprite.setPosition(x, y); }
	void SetPos(const sf::Vector2f& pos) { m_sprite.setPosition(pos); }
	const sf::Vector2f& GetPos() const { return m_sprite.getPosition(); }

	// Size
	void SetSize(const sf::Vector2f& size) { m_sprite.setScale(size); }
	const sf::Vector2f& GetSize() const { return (sf::Vector2f)m_sprite.getTexture()->getSize(); }

	// Active state
	void SetActive(const bool& active) { m_isActive = active; }
	const bool& IsActive() const { return m_isActive; }

	// Collider
	sf::FloatRect GetCollider();

	// Sprite
	sf::Sprite& GetSprite() { return m_sprite; }
};
extern std::array<GameObject, 3> walls;
extern std::array<std::array<GameObject, COLOMN>, ROW> bricks;

class Player : public GameObject, public Movement
{
public:
	void Move(const float& deltaTime) override;
};
extern Player player;

class Ball : public GameObject, public Movement
{
public:
	void Move(const float& deltaTime) override;
};
extern Ball ball;