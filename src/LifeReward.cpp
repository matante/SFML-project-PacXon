#include "LifeReward.h"
 


LifeReward::LifeReward(sf::Vector2f location, Image img, sf::Vector2u imageCount,
	float switchTime, Player* player, float when)
	: Reward(location, img, imageCount, switchTime, when), m_player(player)
	
{
	m_row =4;
	m_howLong = 5.f;
}
// ------------------------------------

void LifeReward::update(float deltaTime)
{
	Object::update(m_row, deltaTime);
}
// ------------------------------------


void LifeReward::setScale(float size)
{
	Object::setScale(size, 1, 5);
}
// ------------------------------------

void LifeReward::useReward(float )
{
	if (m_isActive)
	{
		m_timeUp = true;
		m_isActive = false;
	}
}