#include "Player.h"
 


Player::Player(sf::Vector2f location, Image img, sf::Vector2u imageCount,
	float switchTime, float speed)
	: MovingObject(location, img, imageCount, switchTime, speed),
	m_hp(LIFE), m_size(0), m_onSafeGround(true)
{
}

// ------------------------------------

void Player::update(float deltaTime)
{
	sf::Vector2f movement(0.0f, 0.0f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		movement.x -= m_speed * deltaTime;
		m_row = 0;
		m_dir = Direction::Left;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		movement.x += m_speed * deltaTime;
		m_row = 1;
		m_dir = Direction::Right;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		movement.y += m_speed * deltaTime;
		m_row = 2;
		m_dir = Direction::Down;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		movement.y -= m_speed * deltaTime;
		m_row = 3;
		m_dir = Direction::Up;
	}
	else // stay in place. 
	{
		m_row = 2;
		m_dir = Direction::Stay;
	}


	Object::update(m_row, deltaTime);
	
	m_sprite.move(movement);

}


// ------------------------------------


void Player::setScale(float size)
{
	Object::setScale(size, 3, 4);
	m_size = size;
}
