#include "Direction.h"

#include <stdexcept>

Direction opposite(Direction dir)
{
    switch (dir)
    {
        case Direction::Up:
            return Direction::Down;
        case Direction::Down:
            return Direction::Up;
        case Direction::Right:
            return Direction::Left;
        case Direction::Left:
            return Direction::Right;
        case Direction::Stay:
            return Direction::Stay;


        case Direction::RightUp:
            return Direction::LeftUp;
        case Direction::RightDown:
            return Direction::RightUp;
        case Direction::LeftDown:
            return Direction::RightDown;
        case Direction::LeftUp:
            return Direction::LeftDown;



        default:
            throw std::runtime_error("Unknown direction");
    }
}

// ------------------------------------


sf::Vector2f toVector(Direction dir)
{
    switch (dir)
    {
        case Direction::Up:
            return { 0, -1 };
        case Direction::Down:
            return { 0, 1 };
        case Direction::Right:
            return { 1, 0 };
        case Direction::Left:
            return { -1, 0 };
        case Direction::Stay:
            return { 0, 0 };

        case Direction::RightUp:
            return { 1, -1 };
        case Direction::RightDown:
            return { 1, 1 };
        case Direction::LeftDown:
            return { -1, 1 };
        case Direction::LeftUp:
            return { -1, -1 };



        default:
            throw std::runtime_error("Unknown direction");
    }
}

