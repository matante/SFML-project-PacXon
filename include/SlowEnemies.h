#pragma once
#include "Reward.h"
#include "Animation.h"
#include "Consts.h"
#include <SFML/Graphics.hpp>
#include "Enemy.h"

class SlowEnemies : public Reward
{
public:
    SlowEnemies(sf::Vector2f, Image , sf::Vector2u, float, std::vector<Object*>,
        int, float );
    virtual void update(float)override;
    virtual void setScale(float) override;

    virtual void useReward(float) override;

    virtual void updateObjects(std::vector<Object*>)override;


   
private:
    std::vector<Enemy*> m_enemies;
    float m_speed;
    float m_delay;
    bool m_used;
};
