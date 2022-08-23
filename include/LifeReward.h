#pragma once
#include "Reward.h"
#include "Animation.h"
#include "Consts.h"
#include <SFML/Graphics.hpp>
#include "Player.h"

class LifeReward : public Reward
{
public:
    LifeReward(sf::Vector2f, Image , sf::Vector2u, float, Player*, float );
    virtual void update(float)override;
    virtual void setScale(float) override;

    virtual void useReward(float) override;
private:
    Player* m_player;


};
