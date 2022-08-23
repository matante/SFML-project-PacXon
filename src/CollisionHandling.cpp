#include "CollisionHandling.h"

#include <iostream>
#include <map>
#include <string>
#include <typeinfo>
#include <typeindex>


namespace 
{

	// primary collision-processing functions
	
	void playerTile(Object& player, Object& tile)
	{
		Player& p = static_cast<Player&>(player);
		Tile& t = static_cast<Tile&>(tile);

		p.setGroundSafety(false); // by default 

		switch (t.getOccupationStatus())
		{
		case Occupation::Free:
			t.setOccupied(Occupation::Potential);
			break;

		case Occupation::Occupied:
			p.setGroundSafety(true);
			break;
		
		case Occupation::Potential:
		case Occupation::EnemyArea:
			break;

		case Occupation::Dangerous:
			p.incPlayerHPBy(-1);
			break;
		}
	}
	// ------------------------------------


	void playerEnemy(Object& player, Object& enemy)
	{
		Player& p = static_cast<Player&>(player);
		Enemy& e = static_cast<Enemy&>(enemy);

		if (e.shouldBeDrawn()) // not on board
		{
			if (!e.isEatable()) // on board and not eatable (regular state)
			{
				Audio::instance().playSound("lose");
				p.incPlayerHPBy(-1);
				return;
			}
			e.setDrawStatus(false);// reached here ==> enemy is eatable, remove it
		}		
	}
	// ------------------------------------

	void hungEnemyTile(Object& enemy, Object& tile)
	{
		HungryEnemy& e = static_cast<HungryEnemy&>(enemy);
		Tile& t = static_cast<Tile&>(tile);

		auto status = t.getOccupationStatus();
		if (status == Occupation::Occupied)
		{
			if (!t.isContainEnemy()) // there is no Occ enemy in this tile (because occ can't be in free!)
				t.setOccupied(Occupation::Free);
			e.changeDir();
			t.setContainEnemy(false);
		}

		if (status == Occupation::Potential)
			t.setOccupied(Occupation::Dangerous);
		
		t.setContainEnemy(true);
	}
	// ------------------------------------

	void smartEnemyTile(Object& enemy, Object& tile)
	{
		return; // ignore collision, smart can go anywhere, can't infect area
	}
	// ------------------------------------

	void OCEnemyTile(Object& enemy, Object& tile)
	{
		OccupiedAreaEnemy& e = static_cast<OccupiedAreaEnemy&>(enemy);
		Tile& t = static_cast<Tile&>(tile);

		t.setContainEnemy(true); 

		auto status = t.getOccupationStatus();

		if (status != Occupation::Occupied) // anything but occupied, need to change dir 
			e.changeDir();
	}
	// ------------------------------------


	void regEnemyTile(Object& enemy, Object& tile)
	{
		RegularEnemy& e = static_cast<RegularEnemy&>(enemy);
		Tile& t = static_cast<Tile&>(tile);

		t.setContainEnemy(true); // may be unneeded ---

		auto status = t.getOccupationStatus();

		if (status == Occupation::Potential)
		{
			if (!e.isEatable()) // eatable enemy can't infect
				t.setOccupied(Occupation::Dangerous);
			e.changeDir();
		}
		if (status == Occupation::Dangerous ||  // can't move over dangerous
			status == Occupation::Occupied) // hit a wall
			e.changeDir();
	}
	// ------------------------------------
	void playerEatable(Object& player, Object& eat)
	{
		Player& p = static_cast<Player&>(player);
		EatableEnemies& s = static_cast<EatableEnemies&>(eat);
		if (s.shouldBeDrawn())
		{
			Audio::instance().playSound("reward");
			s.activate(true);// activate for amount of time
			s.setDrawStatus(false); // make it disappear
		}
	}
	// ------------------------------------

	void playerSpeed(Object& player, Object& speed)
	{
		Player& p = static_cast<Player&>(player);
		SpeedBoost& s = static_cast<SpeedBoost&>(speed);
		if (s.shouldBeDrawn())
		{
			Audio::instance().playSound("reward");
			p.setSpeed(p.getSpeed() + BONUS);
			s.setDrawStatus(false); 
			s.activate(true); 
		}
	}
	// ------------------------------------
	void playerLife(Object& player, Object& life)
	{
		Player& p = static_cast<Player&>(player);
		LifeReward& l = static_cast<LifeReward&>(life);
		if (l.shouldBeDrawn())
		{
			Audio::instance().playSound("reward");
			p.incPlayerHPBy(1);
			l.setDrawStatus(false);
			l.activate(true);
		}
	}

	// ------------------------------------
	void playerSlow(Object& player, Object& slow)
	{
		Player& p = static_cast<Player&>(player);
		SlowEnemies& s = static_cast<SlowEnemies&>(slow);
		if (s.shouldBeDrawn())
		{
			Audio::instance().playSound("reward");
			s.activate(true);
			s.setDrawStatus(false);
		}

	}
	// ------------------------------------
	

	// secondary collision-processing functions that just
	// implement symmetry
	void tilePlayer(Object& tile, Object& player)
	{
		playerTile(player, tile);
	}
	// ------------------------------------

	void enemyPlayer(Object& enemy, Object& player)
	{
		playerEnemy(player, enemy);
	}
	// ------------------------------------

	void tileRegEnemy(Object& tile, Object& enemy)
	{
		regEnemyTile(enemy, tile);
	}
	// ------------------------------------

	void tileHungEnemy(Object& tile, Object& enemy)
	{
		hungEnemyTile(enemy, tile);
	}
	// ------------------------------------

	void tileSmartEnemy(Object& tile, Object& enemy)
	{
		smartEnemyTile(enemy, tile);
	}
	// ------------------------------------

	void speedPlayer(Object& speed, Object& player)
	{
		playerSpeed(player, speed);
	}
	// ------------------------------------

	void lifePlayer(Object& life, Object& player)
	{
		playerSpeed(player, life);
	}
	// ------------------------------------

	void slowPlayer(Object& slow, Object& player)
	{
		playerSlow(player, slow);
	}
	// ------------------------------------


	void eatablePlayer(Object& eat, Object& player)
	{
		playerSlow(player, eat);
	}
	// ------------------------------------

	void tileOCEnemy(Object& tile, Object& enemy)
	{
		OCEnemyTile(enemy, tile);
	}
	// ------------------------------------

	using HitFunctionPtr = void (*)(Object&, Object&);
	using Key = std::pair<std::type_index, std::type_index>;
	using HitMap = std::map<Key, HitFunctionPtr>;

	HitMap initializeCollisionMap()
	{
		HitMap phm;
		phm[Key(typeid(Player), typeid(Tile))] = &playerTile;
		phm[Key(typeid(Tile), typeid(Player))] = &tilePlayer;

		phm[Key(typeid(Tile), typeid(RegularEnemy))] = &tileRegEnemy;
		phm[Key(typeid(RegularEnemy), typeid(Tile))] = &regEnemyTile;
		phm[Key(typeid(RegularEnemy), typeid(Player))] = &enemyPlayer;
		phm[Key(typeid(Player), typeid(RegularEnemy))] = &playerEnemy;

		phm[Key(typeid(Tile), typeid(HungryEnemy))] = &tileHungEnemy;
		phm[Key(typeid(HungryEnemy), typeid(Tile))] = &hungEnemyTile;
		phm[Key(typeid(HungryEnemy), typeid(Player))] = &enemyPlayer;
		phm[Key(typeid(Player), typeid(HungryEnemy))] = &playerEnemy;

		phm[Key(typeid(Tile), typeid(SmartEnemy))] = &tileSmartEnemy;
		phm[Key(typeid(SmartEnemy), typeid(Tile))] = &smartEnemyTile;
		phm[Key(typeid(SmartEnemy), typeid(Player))] = &enemyPlayer;
		phm[Key(typeid(Player), typeid(SmartEnemy))] = &playerEnemy;


		phm[Key(typeid(Player), typeid(OccupiedAreaEnemy))] = &playerEnemy;
		phm[Key(typeid(OccupiedAreaEnemy), typeid(Player))] = &enemyPlayer;

		phm[Key(typeid(Tile), typeid(OccupiedAreaEnemy))] = &tileOCEnemy;
		phm[Key(typeid(OccupiedAreaEnemy), typeid(Tile))] = &OCEnemyTile;

		phm[Key(typeid(Player), typeid(SpeedBoost))] = &playerSpeed;
		phm[Key(typeid(SpeedBoost), typeid(Player))] = &speedPlayer;

		phm[Key(typeid(Player), typeid(LifeReward))] = &playerLife;
		phm[Key(typeid(LifeReward), typeid(Player))] = &lifePlayer;

		phm[Key(typeid(Player), typeid(SlowEnemies))] = &playerSlow;
		phm[Key(typeid(SlowEnemies), typeid(Player))] = &slowPlayer;

		phm[Key(typeid(Player), typeid(EatableEnemies))] = &playerEatable;
		phm[Key(typeid(EatableEnemies), typeid(Player))] = &eatablePlayer;

		return phm;
	}
	// ------------------------------------

	HitFunctionPtr lookup(const std::type_index& class1, const std::type_index& class2)
	{
		static HitMap collisionMap = initializeCollisionMap();
		auto mapEntry = collisionMap.find(std::make_pair(class1, class2));
		if (mapEntry == collisionMap.end())
		{
			return nullptr;
		}
		return mapEntry->second;
	}

} // end namespace

void processCollision(Object& object1, Object& object2)
{
	auto phf = lookup(typeid(object1), typeid(object2));
	if (!phf)
	{
		throw UnknownCollision(object1, object2);
	}
	phf(object1, object2);
}
