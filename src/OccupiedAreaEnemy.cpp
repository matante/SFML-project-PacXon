#include "OccupiedAreaEnemy.h"



OccupiedAreaEnemy::OccupiedAreaEnemy(sf::Vector2f location, Image img, sf::Vector2u imageCount,
	float switchTime)
	: Enemy(location, img, imageCount, switchTime, OCC_SPD)

{
	m_dir = Direction::RightDown;
}

// ------------------------------------


void OccupiedAreaEnemy::update(float deltaTime)
{
	move(deltaTime);
}

// ------------------------------------

void OccupiedAreaEnemy::setScale(float size)
{
	Object::setScale(size, 3, 4);
}



