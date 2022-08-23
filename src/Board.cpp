#include "Board.h"


Board::Board()
	: m_h(ROWS), m_w(COLS), m_tileSize(0), m_isOCCreated(false)
{

	m_backgrounds[Mode::Opening].setTexture(&Textures::instance().getBackgroundTexture(Mode::Opening));
	m_backgrounds[Mode::Opening].setSize(sf::Vector2f(WIDTH, HEIGHT));

	m_backgrounds[Mode::Help].setTexture(&Textures::instance().getBackgroundTexture(Mode::Help));
	m_backgrounds[Mode::Help].setSize(sf::Vector2f(WIDTH, HEIGHT));

	m_backgrounds[Mode::GameOver].setTexture(&Textures::instance().getBackgroundTexture(Mode::GameOver));
	m_backgrounds[Mode::GameOver].setSize(sf::Vector2f(WIDTH, HEIGHT));

	m_backgrounds[Mode::Win].setTexture(&Textures::instance().getBackgroundTexture(Mode::Win));
	m_backgrounds[Mode::Win].setSize(sf::Vector2f(WIDTH, HEIGHT));

	m_backgrounds[Mode::InGame].setTexture(&Textures::instance().getBackgroundTexture(Mode::InGame));
	m_backgrounds[Mode::InGame].setSize(sf::Vector2f(WIDTH, HEIGHT));
	m_backgrounds[Mode::InGame].setFillColor(sf::Color(255, 255, 255, 128)); // half trasnparent

	m_backgrounds[Mode::Pause].setTexture(&Textures::instance().getBackgroundTexture(Mode::Pause));
	m_backgrounds[Mode::Pause].setSize(sf::Vector2f(WIDTH, HEIGHT));

	auto btn_size = sf::Vector2u(
		Textures::instance().getIconTexture(Image::Buttons).getSize().x,
		Textures::instance().getIconTexture(Image::Buttons).getSize().y / NUM_OF_BTNS);


	for (int row = 0, gap = 0; row < NUM_OF_BTNS; row++, gap += btn_size.y)
		m_buttons.push_back(
			sf::Sprite(Textures::instance().getIconTexture(Image::Buttons),
			sf::IntRect(0, gap, btn_size.x, btn_size.y))
		);


	float gap = HEIGHT / 5;
	for (auto& button : m_buttons)
	{
		button.setOrigin(sf::Vector2f(
			button.getLocalBounds().width / 2,
			button.getLocalBounds().height / 2));

		button.setScale(sf::Vector2f(0.75, 0.75));

		button.setPosition(sf::Vector2f(WIDTH / 2, gap));
		gap += HEIGHT / 5;
	}

	m_buttons[GOT_IT_BTN].setPosition(sf::Vector2f((float)WIDTH / 2, (float)(7 * (HEIGHT / 7.75))));
}

// ------------------------------------

bool Board::isANum(const std::string& word) const
{
	// used to verify input from file
	for (auto i : word)
		if (!isdigit(i))
			return false;

	return true;
}
// ------------------------------------

void Board::setBoardOfRectangles() {
	/*set empty grid of rectangles. this is used to place the objects on right spot*/

	sf::RectangleShape myRectangle; // a basic rectangle
	myRectangle.setOutlineColor(sf::Color::Black);
	myRectangle.setOutlineThickness(3.f);
	float size = std::min(((HEIGHT - INFO_BAR) / m_h), (float)(WIDTH / m_w));
	// it will be squared rectangle

	myRectangle.setSize(sf::Vector2f(size, size)); //sqaured 

	for (unsigned row = 0; row < m_h; row++)
	{
		m_map.push_back(std::vector<sf::RectangleShape>()); // each line is a vector of rectangles
		for (unsigned col = 0; col < m_w; col++)
		{
			myRectangle.setPosition((float)(col * size + size * 0.85),
				(float)(INFO_BAR + row * size - size / 4));
			m_map[row].push_back(myRectangle);
		}
	}
	m_tileSize = size;
}
// ------------------------------------


void Board::makeTiles()
{
	for (int i = 0; i < ROWS; i++) // make a 2d vector of Occupation, used for the dynamic programming algorith,
	{
		m_grid.push_back(std::vector<Occupation>());
		for (int j = 0; j < COLS; j++)
		{
			m_grid[i].push_back(Occupation::Free);

			if (i == 0 || j == 0 || i == ROWS - 1 || j == COLS - 1)
				m_grid[i][j] = Occupation::Occupied;
		}
	}

	// based on the 2d, make the vector that contains the Tiles themselves (as objects)
	for (int row = 0; row < m_map.size(); row++)
	{
		for (int col = 0; col < m_map[row].size(); col++)
		{
			sf::Vector2f pos = m_map[row][col].getPosition();

			m_tiles.push_back(std::move(std::make_unique<Tile>(pos,
				Image::Tile, sf::Vector2u(1, 4), 0.0f)));

			if (m_grid[row][col] == Occupation::Occupied)
				m_tiles[m_tiles.size() - 1]->setOccupied(Occupation::Occupied);
		}
	}
}

// ------------------------------------


void Board::drawScreen(sf::RenderWindow& window, Mode type)
{
	window.draw(m_backgrounds[type]);

	switch (type)
	{
	case Mode::InGame:
		for (const auto& tile : m_tiles)
			tile->draw(window);

		for (auto& reward : m_rewards)
			if (reward.second->shouldBeDrawn())
				reward.second->draw(window);

		m_player->draw(window);

		for (auto& enemy : m_enemies)
			if (enemy->shouldBeDrawn())
				enemy->draw(window);
		break;

	case Mode::Opening:
		window.draw(m_buttons[NEW_GAME_BTN]);
		window.draw(m_buttons[INSTRUCTIONS_BTN]);
		window.draw(m_buttons[EXIT_BTN]);
		break;
	case Mode::Help:
		window.draw(m_buttons[GOT_IT_BTN]);
		break;
	case Mode::GameOver:
	case Mode::Win:
	case Mode::Pause:
		break;
	default:
		throw std::runtime_error("Unknown Mode");
	}

}
// ------------------------------------

Action Board::whereClicked(const sf::Vector2f& mousePos) const
{
	if (m_buttons[NEW_GAME_BTN].getGlobalBounds().contains(mousePos))
		return Action::NewGame;
	else if (m_buttons[INSTRUCTIONS_BTN].getGlobalBounds().contains(mousePos))
		return Action::Instructions;
	else if (m_buttons[EXIT_BTN].getGlobalBounds().contains(mousePos))
		return Action::Exit;
	else if (m_buttons[GOT_IT_BTN].getGlobalBounds().contains(mousePos))
		return Action::GotIt;

	return Action::NoAction;
}
// ------------------------------------

void Board::scaleObjects()
{
	// make the objects fit to the size of the window
	for (auto& tile : m_tiles)
	{
		tile->setScale(m_tileSize);
		tile->setOrigin();
	}

	for (auto& enemy : m_enemies)
	{
		enemy->setScale(m_tileSize);
		enemy->setOrigin();
	}
}
// ------------------------------------

bool Board::outOfBounds(const MovingObject& obj) const
{
	auto isLower = [](float obj1, float obj2) {return obj1 < obj2; };
	auto pos = obj.getPos(),
		topLeft = m_tiles[0]->getPos(),
		bottomRight = m_tiles[m_tiles.size() - 1]->getPos();

	switch (obj.getDirection())
	{
	case Direction::Left:
		return isLower(pos.x, topLeft.x);

	case Direction::Right:
		return isLower(bottomRight.x, pos.x);

	case Direction::Up:
		return isLower(pos.y, topLeft.y);

	case Direction::Down:
		return isLower(bottomRight.y, pos.y);

	case Direction::LeftDown:
		return isLower(pos.x, topLeft.x) || isLower(bottomRight.y, pos.y);

	case Direction::LeftUp:
		return isLower(pos.x, topLeft.x) || isLower(pos.y, topLeft.y);

	case Direction::RightDown:
		return isLower(bottomRight.x, pos.x) || isLower(bottomRight.y, pos.y);

	case Direction::RightUp:
		return isLower(bottomRight.x, pos.x) || isLower(pos.y, topLeft.y);

	default:
		return false;
	}
}
// ------------------------------------

void Board::updateObjects(float deltaTime, Mode type)
{
	if (type == Mode::Pause) // no need to update if in pause, duh
		return;
	// also no need if in help or in menu

	if (type == Mode::InGame)
	{
		m_player->update(deltaTime);
		if (outOfBounds(*m_player)) // need to reverse
			m_player->update(-deltaTime);

		for (auto& enemy : m_enemies)
		{
			enemy->update(deltaTime);

			if (outOfBounds(*enemy))
			{
				enemy->update(-deltaTime);
				enemy->changeDir();
			}
		}
		auto oldSize = m_enemies.size();

		std::experimental::erase_if(m_enemies, [](auto& e)
			{
				return !e->shouldBeDrawn(); // if not needed to be drawn
			});

		if (oldSize > m_enemies.size()) // enemy removed
			updateRewardsVectors();

		for (auto& tile : m_tiles)
			tile->update(deltaTime);

		for (auto& reward : m_rewards)
		{
			reward.second->update(deltaTime);
			reward.second->useReward(deltaTime); // m_reward is a map
		}
	}
}
// ------------------------------------
void Board::updateRewardsVectors()
{
	auto enemies = getEnemiesPointers();
	for (auto& r : m_rewards) // update reward's "targets"
		r.second->updateObjects(enemies);
}
// ------------------------------------
std::vector<Object*> Board::getEnemiesPointers()const
{
	std::vector<Object*> enemiesTemp;
	for (auto& e : m_enemies)
		enemiesTemp.push_back(e.get()); // get a regular pointer
	return enemiesTemp;
}

// ------------------------------------

bool Board::handleCollisions(float deltaTime)
{
	// we first check if there is a collison, and then handling it

	int currHP = m_player->getPlayerHP();

	for (auto& tile : m_tiles)
		tile->setContainEnemy(false); // by default

	for (auto& enemy : m_enemies)
		for (auto& tile : m_tiles)
			if (Object::collides(*enemy, *tile))
				processCollision(*enemy, *tile);

	//after the collisions, need to
	updateGrid(); // because we changed the tiles

	static float countingTime = sf::Time::Zero.asSeconds();
	countingTime += deltaTime;
	
	if (countingTime > DNG_CHS_SPD) // make the dangerous tiles procceed slowly
	{
		for (int loc = 0; loc < m_tiles.size(); loc++)
			if (m_tiles[loc]->getOccupationStatus() == Occupation::Dangerous)
				infectPotential(loc);

		countingTime = 0; //reset

	}
	//after we infected the grid, need to 
	updateTiles();


	for (auto& enemy : m_enemies)
		if (Object::collides(*m_player, *enemy))
		{
			processCollision(*m_player, *enemy);
			if (m_player->getPlayerHP() < currHP) // if lost hp because of enemy
				return false;
		}

	for (auto& tile : m_tiles)
		if (Object::contains(*m_player, *tile))
		{
			processCollision(*m_player, *tile);
			if (m_player->getPlayerHP() < currHP) // if lost hp because of dangerous
				return false;
		}

	for (auto& reward : m_rewards)
		if (Object::collides(*m_player, *reward.second)) // if player picked reward
			processCollision(*m_player, *reward.second);

	return true; // player didn't lose hp
}

// ------------------------------------

void Board::infectPotential(int location)
{

	// we won't overflow, because there is a frame which 
	//is occupied and therefore can't be potential
	int row = location / COLS, col = location % COLS;

	makeDangerous(row + 1, col);
	makeDangerous(row - 1, col);
	makeDangerous(row, col + 1);
	makeDangerous(row, col - 1);

}
// ------------------------------------
void Board::makeDangerous(int row, int col)
{
	if (m_grid[row][col] == Occupation::Potential)
		m_grid[row][col] = Occupation::Dangerous;
}

// ------------------------------------

void Board::updateGrid()//based on tiles
{

	for (int tile = 0; tile < m_tiles.size(); tile++)
	{
		int row = tile / COLS, col = tile % COLS;

		if (row == 0 || col == 0 || row == ROWS - 1 || col == COLS - 1)
			m_grid[row][col] = Occupation::Occupied;
		else
			m_grid[row][col] = m_tiles[tile]->getOccupationStatus();
	}

}

// ------------------------------------

void Board::infectEnemyArea()
{
	// area containing enemy cannot be occupied
	for (int tile = 0; tile < m_tiles.size(); tile++)
	{
		int row = tile / COLS, col = tile % COLS;
		if (m_tiles[tile]->isContainEnemy())
			OccupationSolver::floodFill(m_grid, row, col, Occupation::EnemyArea);
	}
}
// ------------------------------------

void Board::updateTiles() // based on grid
{
	int location = 0;
	for (int row = 0; row < m_grid.size(); row++)
		for (int col = 0; col < m_grid[row].size(); col++, location++)
			m_tiles[location]->setOccupied(m_grid[row][col]);
}
// ------------------------------------

int Board::updateOccupiedArea()
{
	/* We reach this function after we changed tiles according to the collision.*/
	updateGrid(); 	// we update the 2d vector

	infectEnemyArea(); // we infect free areas in the grid with enemy plague

	updateTiles(); // after the grid changed, we update the tiles

	int location = 0;
	for (int row = 0; row < m_grid.size(); row++)
		for (int col = 0; col < m_grid[row].size(); col++, location++)
			if (m_grid[row][col] != Occupation::EnemyArea) // so it's free/potential/occupied/danger
				occupy(location, row, col); // change both grid and vector to Occupy
			else // cure enemy's infection, reset EnemyArea to Free
			{
				m_tiles[location]->setOccupied(Occupation::Free);
				m_grid[row][col] = Occupation::Free;
			}

	auto res = calculateOccupiedPercent(); // tell how many of the area is occ
	if (res < NEEDED_PRCNT && res > OCC_SPAWN && !m_isOCCreated)
		// not finished, more than 10, and not created yet
	{
		m_enemies.push_back(std::move(std::make_unique<OccupiedAreaEnemy>(
			sf::Vector2f(700, 200), Image::Occupied, sf::Vector2u(3, 4), 0.1f)));

		m_isOCCreated = true;
		m_enemies[m_enemies.size() - 1]->setScale(m_tileSize);
		m_enemies[m_enemies.size() - 1]->setPos(findOccupied());
		m_enemies[m_enemies.size() - 1]->setOrigin();
		updateRewardsVectors();

	}


	// clear all unactive rewards
	// we used itreators because we delete from the data structure while iterating, need to be careful
	for (auto it = m_rewards.cbegin(); it != m_rewards.cend(); /*empty*/)
	{
		if (res < NEEDED_PRCNT && res > it->second->whenAppears())
			//under 80% and above % needed to spawn reward
		{
			if (!it->second->isActive()) // if it was not active
				it->second->setDrawStatus(true); // make it appear

			if (it->second->isTimeUp()) // effect is more than X
				it = m_rewards.erase(it); // remove it 
			else
				++it; // not removed, move to the next itr
		}

		else // no need to spawn at all, move to the next itr
			++it;
	}

	return res; // the % calculated earlier 
}
// ------------------------------------


void Board::occupy(int location, int row, int col)
{

	if (m_player->isOnSafeGround()) // player reached back to safe ground (Occupied, blue)
	{
		m_tiles[location]->setOccupied(Occupation::Occupied);
		m_grid[row][col] = Occupation::Occupied;
	}

}
// ------------------------------------

int Board::calculateOccupiedPercent()const
{
	double counter = 0;
	//  we don't consider the frame as part of the game
	for (int row = 1; row < m_grid.size() - 1; row++)
		for (int col = 1; col < m_grid[row].size() - 1; col++)
			if (m_grid[row][col] == Occupation::Occupied)
				counter++;
	
	// static cast to long long int to make the compiler shut up about Arithmetic overflow
	double areaSize = (static_cast<__int64>(ROWS - 2)) * (static_cast<__int64>(COLS - 2)); // ignore first and last row/col
	return (int)((counter / areaSize) * 100); // percent

}
// ------------------------------------

sf::Vector2f Board::findOccupied()const
{
	//used to tell where can the Occ enemy be spawned at
	for (int loc = 0; loc < m_tiles.size(); loc++)
	{
		int row = loc / COLS, col = loc % COLS;

		if (row == 0 || col == 0 || row == ROWS - 1 || col == COLS - 1) // ignore frame
			continue;

		if (m_tiles[loc]->getOccupationStatus() == Occupation::Occupied)
		{
			// make sure there is enough space for the Occ enemy to spawn
			if (m_grid[row][col + 1] == Occupation::Occupied &&  // to the right
				m_grid[row + 1][col] == Occupation::Occupied &&  // to the down
				m_grid[row + 1][col + 1] == Occupation::Occupied) // to the right down

				return m_tiles[loc]->getPos();
		}
	}
	return m_tiles[0]->getPos();
	// will not reach here, to calm down compiler (if reached, will be spawn in top left)
}
// ------------------------------------


void Board::resetBoard()
{
	// we reach here when the player loses hp but didn't lose the game 
	m_player->setPos(m_player->getOriginalPos());

	for (auto& e : m_enemies)
		e->resetSpeed();

	//leave frame untouched
	for (int row = 1; row < m_grid.size() - 1; row++)
		for (int col = 1; col < m_grid[row].size() - 1; col++)
			if (m_grid[row][col] != Occupation::Occupied)
				m_grid[row][col] = Occupation::Free;

	for (auto& reward : m_rewards)
		reward.second->useReward(reward.second->howLong() + 1.f); 
	// force rewards to stop

	updateTiles(); // according to grid

}

// ------------------------------------


void Board::openStagesFile()
{
	m_stagesFile.open("stages.txt", std::fstream::in);
	m_stagesFile.clear();
	m_stagesFile.seekg(0); // jump to top of file

	if (m_player)
		m_player = nullptr;
}
// ------------------------------------

void Board::clearOldData()
{

	for (int i = 0; i < m_grid.size(); i++)
		m_grid[i].clear();
	m_grid.clear();

	m_tiles.clear();
	m_rewards.clear();
	m_enemies.clear();
}

void Board::makePlayer()
{
	m_player = std::move(std::make_unique<Player>(
		sf::Vector2f(50, 150),
		Image::Player, sf::Vector2u(3, 4), 0.1f, P_SPD));
	m_player->setScale(m_tileSize);
	m_player->setOrigin();
	m_player->setPos(m_tiles[0]->getPos());
	m_player->setOriginalPos(m_player->getPos());
}

// ------------------------------------


bool Board::isNewLevel()
{
	auto level = std::string(); // set new string and read into it

	if (std::getline(m_stagesFile, level))
		return true; // if could read
	return false;

}
// ------------------------------------

void Board::allocateObjects()
{
	// we know this is a "long" function. but we need somewhere to read the data.
	// it is long mostly because of the constructors, rather than the checks themselves

	m_isOCCreated = false; // used for the occ enemy, so it can be spawned in every stage

	clearOldData();

	makeTiles();

	if (!m_player) // not exits, because if exits no need to change hp and such
		makePlayer();
	else // already alive and need to move to the next stage
		m_player->setPos(m_player->getOriginalPos());

	auto checkIfPositive = [&](int num) {if (num < 0) invalidFile(); };

	std::string word;
	m_stagesFile >> word;

	while (word.compare("END")) // while didn't read "END"
	{
		int amount = 0;
		if (!(m_stagesFile >> amount)) // check if valid, same for all the next
			invalidFile();
		checkIfPositive(amount);

		for (int i = 0; i < amount; i++) // how many of the next object need to make
		{
			float x = 0, y = 0;
			if (!(m_stagesFile >> x >> y))
				invalidFile();
			checkIfPositive((int)x);
			checkIfPositive((int)y);

			if (!word.compare("RegularEnemy")) // if we read RegularEnemy, same for all the next
				m_enemies.push_back(std::move(std::make_unique<RegularEnemy>(
					sf::Vector2f(x, y), Image::Regular, sf::Vector2u(3, 4), 0.1f)));

			else if (!word.compare("SmartEnemy"))
				m_enemies.push_back(std::move(std::make_unique<SmartEnemy>(
					sf::Vector2f(x, y), Image::Smart, sf::Vector2u(6, 1), 0.2f,
					m_player.get())));

			else if (!word.compare("HungryEnemy"))
				m_enemies.push_back(std::move(std::make_unique<HungryEnemy>(
					sf::Vector2f(x, y), Image::Hungry, sf::Vector2u(3, 4), 0.2f)));

			else // reached here, ==> reward
			{
				float whenAppears = 0.0f; // after % of the area is occupied
				if (!(m_stagesFile >> whenAppears))
					invalidFile();
				checkIfPositive((int)whenAppears);

				if (!word.compare("SpeedBoost"))
					m_rewards[word] = std::move(std::make_unique<SpeedBoost>(
						sf::Vector2f(x, y), Image::Rewards, sf::Vector2u(1, 5), 0.0f,
						m_player.get(), whenAppears));

				else if (!word.compare("LifeReward"))
					m_rewards[word] = std::move(std::make_unique<LifeReward>(
						sf::Vector2f(x, y), Image::Rewards, sf::Vector2u(1, 5),
						0.0f, m_player.get(), whenAppears));

				else // eatable / slow, need the enemeies pointers
				{
					auto enemies = getEnemiesPointers();
					if (!word.compare("EatableEnemies"))
						m_rewards[word] = std::move(std::make_unique<EatableEnemies>(
							sf::Vector2f(x, y), Image::Rewards, sf::Vector2u(1, 5),
							0.0f, enemies, whenAppears));
					else // slow reward
					{
						float speed = 0.0f;
						if (!(m_stagesFile >> speed))
							invalidFile();
						checkIfPositive((int)speed);

						int row = speed > 0 ? 2 : 3;
						if (!word.compare("SlowEnemies"))
							m_rewards[word] = std::move(std::make_unique<SlowEnemies>(
								sf::Vector2f(x, y), Image::Rewards, sf::Vector2u(1, 5),
								speed, enemies, row, whenAppears));
					} // end of slow reward
				}// end of rewards with enemy vector 
			}// end of reward
		} // end of for (how many to make)
		m_stagesFile >> word; // read next
	}// end of compare

	m_stagesFile.get(); // eat the "\n" in the end of the END line

}

// ------------------------------------

void Board::invalidFile()const
{
	throw std::invalid_argument("Stages file is not in format!!!!\n");
}