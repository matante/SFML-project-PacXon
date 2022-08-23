#pragma once
#include "Enemy.h"
#include "Animation.h"
#include "Direction.h"
#include "Consts.h"

class HungryEnemy : public Enemy
{
public:
    HungryEnemy(sf::Vector2f, Image, sf::Vector2u, float);
    virtual void update(float)override;
    void setScale(float);
    
private:
};
