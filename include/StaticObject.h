#pragma once
#include "Object.h"
#include "Consts.h"
#include "Animation.h"
#include "Direction.h"
#include "Occupation.h"
class StaticObject : public Object
{
public:
	StaticObject(sf::Vector2f, Image, sf::Vector2u, float);
	virtual void update(float) = 0;
	virtual void setScale(float) = 0;
	
};