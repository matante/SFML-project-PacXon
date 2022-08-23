#pragma once
#include "StaticObject.h"
#include "Animation.h"

#include "Occupation.h"

#include <SFML/Graphics.hpp>

class Tile : public StaticObject
{
public:
	Tile(sf::Vector2f, Image, sf::Vector2u, float);
	virtual void update(float)override;
	virtual void setScale(float) override;
	void setOccupied(Occupation);
	Occupation getOccupationStatus()const { return m_occupation; };
	void setContainEnemy(bool status) { m_containEnemy = status; };
	bool isContainEnemy()const { return m_containEnemy; };


private:
    Occupation m_occupation;
    bool m_containEnemy;

};
