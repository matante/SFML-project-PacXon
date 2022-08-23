#include "SpeedBoost.h"
 


SpeedBoost::SpeedBoost(sf::Vector2f location, Image img, sf::Vector2u imageCount,
	float switchTime, Player* player, float when)
	: Reward(location, img, imageCount, switchTime, when), m_player(player)
	
{
	m_row = 0;
	m_howLong = 5.f;

}


// ------------------------------------
void SpeedBoost::update(float deltaTime)
{
	Object::update(m_row, deltaTime);
}

// ------------------------------------
void SpeedBoost::setScale(float size)
{
	Object::setScale(size, 1, 5);
}
// ------------------------------------
void SpeedBoost::useReward(float deltaTime)
{
	if (!m_isActive)
		return;

	static float delay = 0;
	
	delay += deltaTime;

	if (delay > m_howLong) // need to reset
	{
		m_player->setSpeed(m_player->getSpeed() - BONUS);
		delay = 0;
		m_isActive = false;
		m_timeUp = true;
	}

}

// ------------------------------------