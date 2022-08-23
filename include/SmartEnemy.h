#pragma once
#include "Enemy.h"
#include "Animation.h"
#include "Direction.h"
#include "Consts.h"
#include "Player.h"
class SmartEnemy : public Enemy
{
public:
    SmartEnemy(sf::Vector2f, Image , sf::Vector2u, float, Player*);
    virtual void update(float)override;
    void setScale(float);
    virtual void move(float) override;
private:
    Player* m_player;
};
