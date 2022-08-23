#include "SmartEnemy.h"


SmartEnemy::SmartEnemy(sf::Vector2f location, Image img, sf::Vector2u imageCount,
	float switchTime, Player* player)
	: Enemy(location, img, imageCount, switchTime, SMRT_SPD), m_player(player)
{
	m_row = 0;
	m_dir = Direction::RightUp;
	changeDir();
}

// ------------------------------------

void SmartEnemy::update(float deltaTime)
{
	move(deltaTime);

	Object::update(m_row, deltaTime);
	m_sprite.move(toVector(m_dir) * deltaTime * m_speed);

}

// ------------------------------------
void SmartEnemy::setScale(float size)
{
	Object::setScale(size, 6, 1);
}
// ------------------------------------

void SmartEnemy::move(float deltaTime)
{
	auto pX = m_player->getPos().x, pY = m_player->getPos().y,
		eX = this->getPos().x, eY = this->getPos().y;

	if (pX < eX) // need to move left

		if (pY < eY) // player is above
			m_dir = Direction::LeftUp;
		else 
			m_dir = Direction::LeftDown;

	else // need to move right
		if (pY < eY) 
			m_dir = Direction::RightUp;
		else
			m_dir = Direction::RightDown;
}