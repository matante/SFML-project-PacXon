#include "SlowEnemies.h"
 
SlowEnemies::SlowEnemies(sf::Vector2f location, Image img, sf::Vector2u imageCount,
	float speed, std::vector<Object*> enemies, int row, float when)
	: Reward(location, img, imageCount, 0.f, when) , m_speed(speed),
	m_delay(sf::Time::Zero.asSeconds()), m_used (false)
{
	updateObjects(enemies);	
	m_row = row;
	m_howLong = 5.0f;
}

// ------------------------------------


void SlowEnemies::update(float deltaTime)
{
	Object::update(m_row, deltaTime);
}

// ------------------------------------

void SlowEnemies::setScale(float size)
{
	Object::setScale(size, 1, 5);
}

// ------------------------------------

void SlowEnemies::useReward(float deltaTime)
{

	if (!m_isActive) // force resetting
	{
		m_delay = 0.f;
		m_used = false;
		return;
	} 

	m_delay += deltaTime;
	
	for (auto& e : m_enemies)
		if (m_delay > m_howLong) // reached end of gift
		{
			e->resetSpeed();
			m_isActive = false;
			m_timeUp = true;

		}
		else if (!m_used) // statement here, so this scope won't make the enemy slower and slower, lim speed -> inf = 0
			e->setSpeed(e->getSpeed() * m_speed);

	m_used = true;
}
// ------------------------------------


void SlowEnemies::updateObjects(std::vector<Object*> objs)
{
	std::vector<Enemy*> enemiesTemp;
	for (auto& e : objs)
		enemiesTemp.push_back(static_cast<Enemy*>(e));

	m_enemies.clear();
	m_enemies = enemiesTemp;

}
