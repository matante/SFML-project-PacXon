#include "EatableEnemies.h"
 


EatableEnemies::EatableEnemies(sf::Vector2f location, Image img, sf::Vector2u imageCount,
	float speed, std::vector<Object*> enemies, float when)
	: Reward(location, img, imageCount, 0.f, when) 
{
	updateObjects(enemies);

	m_row = 1;
	m_howLong = 8.f;
	
}



void EatableEnemies::update(float deltaTime)
{

	Object::update(m_row, deltaTime);
}


void EatableEnemies::setScale(float size)
{
	

	Object::setScale(size, 1, 5);
}


void EatableEnemies::useReward(float deltaTime)
{


	if (!m_isActive)
	{
		m_delay = 0.f;
		m_used = false;
		return;
	}
	m_delay += deltaTime;
	
	for (auto& e : m_enemies)
		if (m_delay > m_howLong) // reached end of gift
		{
			e->setEatable(false);
			e->setTransparency(255);
			m_isActive = false;
			m_timeUp = true;

		}
		else if (!m_used)
		{// statement here, so this scope won't make the enemy slower and slower, lim speed -> inf = 0
			e->setEatable(true);
			e->setTransparency(128);
		}

	m_used = true;
}


void EatableEnemies::updateObjects(std::vector<Object*> objs)
{
	std::vector<Enemy*> enemiesTemp;
	for (auto& e : objs)
		enemiesTemp.push_back(static_cast<Enemy*>(e));

	m_enemies.clear();
	m_enemies = enemiesTemp;

}
