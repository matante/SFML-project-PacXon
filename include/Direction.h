#pragma once

#include "Consts.h"

enum class Direction
{
    Up,
    Down,
    Right,
    Left,
    Stay,
    RightUp,
    RightDown,
    LeftDown,
    LeftUp,
};


Direction opposite(Direction dir);
sf::Vector2f toVector(Direction dir);
