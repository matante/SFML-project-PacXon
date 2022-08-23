#include "Reward.h"
 


Reward::Reward(sf::Vector2f location, Image img, sf::Vector2u imageCount,
	float switchTime, float when)
	: StaticObject(location, img, imageCount, switchTime), m_whenAppears(when),
	m_isActive(false), m_timeUp(false)
{
	m_drawMe = false;
	m_howLong = 0.f;
}



