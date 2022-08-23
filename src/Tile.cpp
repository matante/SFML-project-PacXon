#include "Tile.h"
 


Tile::Tile(sf::Vector2f location, Image img, sf::Vector2u imageCount,
	float switchTime)
	: StaticObject(location, img, imageCount, switchTime),
	m_occupation (Occupation::Free), m_containEnemy(false)
	
{
	
}

// ------------------------------------


void Tile::update(float deltaTime)
{
	Object::update(m_row, deltaTime);
}
// ------------------------------------


void Tile::setScale(float size)
{
	Object::setScale(size, 1, 4);
}
// ------------------------------------

void Tile::setOccupied(Occupation status)
{

	m_occupation = status;

	switch (status)
	{
	case Occupation::Occupied:

		m_row = 1;// make blue
		break;
	
	case Occupation::Free: 
	case Occupation::EnemyArea:
		m_row = 0; // make clear
		break;
	case Occupation::Potential:
		m_row = 2;
		break;
	case Occupation::Dangerous:
		m_row = 3;
		break;
	}

}


