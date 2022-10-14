#include "GameObject.h"

// Extern variables init
std::array<GameObject, 3> walls;
std::array<std::array<GameObject, COLOMN>, ROW> bricks;
Player player;
Ball ball;

// Game object funtions
GameObject::GameObject()
{
	m_isActive = false;
}

GameObject::~GameObject()
{

}

void GameObject::Init(const sf::Texture& texture, const sf::Vector2f& pos, const bool& active)
{
	m_sprite.setTexture(texture);
	m_sprite.setPosition(pos);
	m_isActive = active;
}

void GameObject::DrawSprite(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

sf::FloatRect GameObject::GetCollider()
{
	if (m_isActive) return sf::FloatRect(m_sprite.getGlobalBounds());
	else return sf::FloatRect();
}

// Player functions
void Player::Move(const float& deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		m_sprite.move(-m_speed.x * deltaTime, 0.0f);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		m_sprite.move(m_speed.x * deltaTime, 0.0f);
}

// Ball functions
void Ball::Move(const float& deltaTime)
{
	m_sprite.move(m_speed * deltaTime);
}