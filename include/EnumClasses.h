#pragma once

#include "Consts.h"

enum class Action
{
    NewGame,
    Instructions,
    Exit,
    GotIt,
    NoAction,
};


enum class Mode
{
    InGame,
    Opening,
    Help,
    GameOver,
    Win,
    Pause,
};

enum class Image
{
    Buttons,
    Player,
    Tile,
    Regular,
    Smart,
    Hungry,
    Occupied,
    Rewards,
};
