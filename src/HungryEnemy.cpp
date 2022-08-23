#include "HungryEnemy.h"


HungryEnemy::HungryEnemy(sf::Vector2f location, Image img, sf::Vector2u imageCount,
	float switchTime)
	: Enemy(location, img, imageCount, switchTime, HNGRY_SPD)
{
	m_dir = Direction::LeftDown;
}

// ------------------------------------


void HungryEnemy::update(float deltaTime)
{
	move(deltaTime);
}

// ------------------------------------

void HungryEnemy::setScale(float size)
{
	Object::setScale(size, 3, 4);
}