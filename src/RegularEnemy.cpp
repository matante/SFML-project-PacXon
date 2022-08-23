#include "RegularEnemy.h"


RegularEnemy::RegularEnemy(sf::Vector2f location, Image img, sf::Vector2u imageCount,
	float switchTime)
	: Enemy(location, img, imageCount, switchTime, RGLR_SPD)

{
	m_dir = Direction::LeftUp;
}

// ------------------------------------


void RegularEnemy::update(float deltaTime)
{
	move(deltaTime);
}

// ------------------------------------

void RegularEnemy::setScale(float size)
{
	Object::setScale(size, 4, 5);
}


// ------------------------------------

