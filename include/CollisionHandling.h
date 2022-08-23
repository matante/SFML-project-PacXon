#pragma once

#include "Object.h"

#include <iostream>
#include <typeinfo>
#include "Occupation.h"
#include "Audio.h"
#include "Player.h"
#include "Tile.h"
#include "RegularEnemy.h"
#include "SmartEnemy.h"
#include "HungryEnemy.h"
#include "OccupiedAreaEnemy.h"
#include "SpeedBoost.h"
#include "SlowEnemies.h"
#include "LifeReward.h"
#include "EatableEnemies.h"

struct UnknownCollision : public std::runtime_error
{
    UnknownCollision(Object& a, Object& b)
        : std::runtime_error(std::string("Unknown collision of ") + typeid(a).name() + " and " + typeid(b).name())
    {
    }
};

void processCollision(Object& object1, Object& object2);
