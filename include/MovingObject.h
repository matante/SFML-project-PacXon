#pragma once
#include "Object.h"
#include "Consts.h"
#include "Animation.h"
#include "Direction.h"

class MovingObject : public Object
{
public:
	MovingObject(sf::Vector2f, Image, sf::Vector2u, float, float);
	sf::Vector2f getOriginalPos()const { return m_originalPos; };
	void setSpeed(float newSpeed) { m_speed = newSpeed; };
	void resetSpeed() { m_speed = m_originalSpeed; };
	Direction getDirection() const { return m_dir; };
	float getSpeed()const { return m_speed; };
	virtual void setScale(float) = 0;
	virtual void update(float) = 0;

protected:
	float m_speed;
	float m_originalSpeed;

	Direction m_dir;
	sf::Vector2f m_originalPos;

};