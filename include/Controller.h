#pragma once
#include "Consts.h"
#include "Object.h"
#include "Board.h"
#include "Audio.h"
#include "Player.h"
#include "Enemy.h"
#include "RegularEnemy.h"
#include "Animation.h"
#include "Info.h"
#include "EnumClasses.h"


class Controller
{
public:
	Controller();
	void runGame();

private: // funcs
	void manageClick(const sf::Vector2f&, sf::RenderWindow&);
	void drawObjects(sf::RenderWindow&, int);
	int getOccupiedAreaPercent();
	bool setNewLevel();


private: // members
	Board m_board;
	Info m_info;
	bool m_isGame;
	bool m_isOnMenu;
	Mode m_windowMode;
};

