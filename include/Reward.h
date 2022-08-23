#pragma once
#include "StaticObject.h"
#include "Animation.h"
#include <SFML/Graphics.hpp>

class Reward : public StaticObject
{
public:
    Reward(sf::Vector2f, Image , sf::Vector2u, float, float);
    virtual void useReward(float) = 0;

    bool isActive()const { return m_isActive; };
    void activate(bool status) { m_isActive = status; };
    bool isTimeUp()const { return m_timeUp; };
    float whenAppears()const { return m_whenAppears; };
    virtual void updateObjects(std::vector<Object*>) {/*empty, done by yorshot if needed*/ };
    float howLong()const { return m_howLong; };
protected:
    bool m_isActive;
    float m_howLong;
    bool m_timeUp;
    float m_whenAppears;

};
