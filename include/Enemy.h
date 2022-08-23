#pragma once
#include "MovingObject.h"
#include "Animation.h"


#include <SFML/Graphics.hpp>

class Enemy : public MovingObject
{
public:
    Enemy(sf::Vector2f, Image, sf::Vector2u, float, float);
    virtual void move(float);
    
    void setTransparency(sf::Uint8 amount) { m_sprite.setColor(sf::Color(255, 255, 255, amount)); };
    void addTimeInOcc(float timeToAdd) { m_timeInOccupied += timeToAdd; };
    float resetClock() { return m_clock.restart().asSeconds(); };
    void setEatable(bool status) { m_eatable = status; };
    float timeInOcc()const { return m_timeInOccupied; };
    void changeDir() { m_needToChange = true; };
    bool isEatable()const { return m_eatable; };

private:
    bool m_needToChange;
    float m_timeInOccupied;
    sf::Clock m_clock;
    bool m_eatable;

};
