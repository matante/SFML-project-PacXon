#include "Enemy.h"
 


Enemy::Enemy(sf::Vector2f location, Image img, sf::Vector2u imageCount,
	float switchTime, float speed)
	: MovingObject(location, img, imageCount, switchTime, speed),
	m_needToChange(false), m_timeInOccupied(sf::Time::Zero.asSeconds()), m_eatable(false)
	
{
}
// ------------------------------------


void Enemy::move(float deltaTime)
{
	sf::Vector2f movement(0.0f, 0.0f); // by default
	if (m_needToChange)
	{
		m_dir = opposite(m_dir);
		m_needToChange = false;
	}

	switch (m_dir)
	{
	case Direction::LeftUp:
		m_row = 0;
		break;
	case Direction::RightUp:
		m_row = 1;
		break;
	case Direction::LeftDown:
		m_row = 2;
		break;
	case Direction::RightDown:
		m_row = 3;
		break;
	default:
		m_row = 0;

	}

	Object::update(m_row, deltaTime);
	m_sprite.move(toVector(m_dir) * deltaTime * m_speed);
}

