#pragma once
#include "MovingObject.h"
#include "Animation.h"
#include "Consts.h"
#include <SFML/Graphics.hpp>

class Player : public MovingObject
{
public:
    Player(sf::Vector2f, Image, sf::Vector2u, float, float);
    virtual void update(float)override;
    void setScale(float);
    int getPlayerHP()const { return m_hp; };

    void incPlayerHPBy(int amount) { m_hp += amount; };

    bool isOnSafeGround() const{ return m_onSafeGround; };
    void setGroundSafety(bool status) { m_onSafeGround = status; };
    void setOriginalPos(sf::Vector2f orgPos) { m_originalPos = orgPos; };
    
private:
    int m_hp;
    float m_size;
    bool m_onSafeGround ;
};
