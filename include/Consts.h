#pragma once
/* this file used for all the consts, includes for other libraries and unsing*/

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdlib>    // exit prototype
#include <cstring>    // strcpy and strcat prototypes
#include <ctime>
#include <experimental/vector>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <thread>
#include <typeinfo>
#include <string>
#include <sstream>
#include <list>
#include <unordered_set>
#include <set>
#include <exception>
#include <map>
#include <unordered_map>

const int ROWS = 25, COLS = 35;
const int WIDTH = 1000, HEIGHT = 800;

const float X_DISTANCE = 80, Y_DISTANCE = 20;



//
//const int BUTTONS = 0,
//PLAYER = 1,
//TILE = 2,
//RGLR_ENEMY = 3,
//SMART_ENEMY = 4,
//HUNGRY_ENEMY = 5,
//OC_ENEMY = 6,
//RWRDS = 7;


const float INFO_BAR = 100.f;


const int NEW_GAME_BTN = 0,
INSTRUCTIONS_BTN = 1,
EXIT_BTN = 2,
GOT_IT_BTN = 3,
NUM_OF_BTNS = 4;


// ~~~~ Player consts ~~~~
const int LIFE = 3;

const int NEEDED_PRCNT = 80, OCC_SPAWN = 10;
const float SHOW_TIME = 2.0f;


// ~~~ speed ~~~
const float P_SPD = 90.f,
BONUS = 100.0f,
HNGRY_SPD = 40.0f,
OCC_SPD = 80.0f,
RGLR_SPD = 70.0f,
SMRT_SPD = 30.0f,
DNG_CHS_SPD = 0.3f;
