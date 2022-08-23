#pragma once
#include "Reward.h"
#include "Animation.h"
#include "Consts.h"
#include <SFML/Graphics.hpp>
#include "Enemy.h"

class EatableEnemies : public Reward
{
public:
    EatableEnemies(sf::Vector2f, Image, sf::Vector2u, float, std::vector<Object*>, float );
    virtual void update(float)override;
    virtual void setScale(float) override;

    virtual void useReward(float) override;


    virtual void updateObjects(std::vector<Object*>)override;

   
private:
    std::vector<Enemy*> m_enemies;
    float m_delay = sf::Time::Zero.asSeconds();
    bool m_used = false;
};
