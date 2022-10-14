#pragma once

#include <SFML/System/Vector2.hpp>

class Movement
{
protected:
	sf::Vector2f m_speed;
	bool m_isMoving;

public:
	void SetSpeed(const float speedX, const float speedY) { m_speed = sf::Vector2f(speedX, speedY); }
	void SetSpeed(const sf::Vector2f& speed) { m_speed = speed; }
	const sf::Vector2f& GetSpeed() const { return m_speed; }

	void SetMoving(const bool& moving) { m_isMoving = moving; }
	const bool& IsMoving() const { return m_isMoving; }

	virtual void Move(const float& deltaTime) {}
};

