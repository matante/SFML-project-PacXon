#include "MovingObject.h"

MovingObject::MovingObject(sf::Vector2f location, Image img, sf::Vector2u imageCount,
		float switchTime, float speed)
	: Object(location, img, imageCount, switchTime),
	m_speed(speed),m_originalSpeed(speed), m_dir (Direction::Left),
	m_originalPos(location)

{
	
}
