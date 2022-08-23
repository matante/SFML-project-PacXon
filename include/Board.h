#pragma once
#include "Consts.h"
#include "Object.h"
#include "MovingObject.h"
#include "StaticObject.h"
#include "CollisionHandling.h"
#include "Occupation.h"
#include "Player.h"
#include "Tile.h"
#include "RegularEnemy.h"
#include "SmartEnemy.h"
#include "HungryEnemy.h"
#include "Reward.h"
#include "SpeedBoost.h"
#include "SlowEnemies.h"
#include "OccupiedAreaEnemy.h"
#include "LifeReward.h"
#include "EatableEnemies.h"
#include "EnumClasses.h"


class Board
{
public:
	Board();

public: //funcs
	void setBoardOfRectangles();
	void scaleObjects();
	void updateObjects(float, Mode);
	void makeTiles();
	void drawScreen(sf::RenderWindow&, Mode);
	void resetBoard();
	Action whereClicked(const sf::Vector2f&)const;
	bool handleCollisions(float);
	int getPlayerHP()const { return m_player->getPlayerHP(); };
	int updateOccupiedArea();
	void openStagesFile();
	bool isNewLevel();
	void allocateObjects();

	bool isANum(const std::string&) const;

private: // members
	std::fstream m_stagesFile; // file
	unsigned m_w, m_h;
	std::vector<std::vector<sf::RectangleShape>> m_map;
	float m_tileSize;
	std::vector<std::vector<Occupation>> m_grid;
	bool m_isOCCreated; // used for occupied area enemy 

private: // drawables
	std::map <Mode, sf::RectangleShape> m_backgrounds;
	std::vector<sf::Sprite> m_buttons;
	std::unique_ptr<Player> m_player;
	std::vector<std::unique_ptr<Enemy>> m_enemies;
	std::vector<std::unique_ptr<Tile>> m_tiles; 
	std::map<std::string, std::unique_ptr<Reward>> m_rewards;


private: // funcs
	void updateGrid();
	void updateTiles();
	void infectEnemyArea();
	void occupy(int, int, int);
	int calculateOccupiedPercent()const;
	bool outOfBounds(const MovingObject&)const;
	void infectPotential(int);
	void makeDangerous(int, int);
	sf::Vector2f findOccupied()const;
	void updateRewardsVectors();
	std::vector<Object*> getEnemiesPointers()const;
	void clearOldData();
	void makePlayer();
	void invalidFile()const;
};