#include "Controller.h"
#include "Textures.h"
Controller::Controller()
	: m_isGame(false), m_isOnMenu(true), m_windowMode(Mode::Opening)
{
}
// ------------------------------------

void Controller::runGame()
{
	Audio::instance().playBackgroundMusic();
	
	auto window = sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT),
		"Talia and Matan's Project", sf::Style::Close);
	
	m_board.setBoardOfRectangles();

	auto clock = sf::Clock();
	float deltaTime = 0.0f, counterTime = 0.0f;

	bool pause = false;

	sf::Vector2f mousePos;
	while (window.isOpen())
	{
		if (auto event = sf::Event{}; window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyReleased:
				if (m_isGame && event.key.code == sf::Keyboard::Space) // pause/unpause
				{
					m_windowMode = pause ? Mode::Pause : Mode::InGame;
					pause = !pause;
				}
				break;
			case sf::Event::MouseButtonReleased:
				auto mousePos = window.mapPixelToCoords(
					{ event.mouseButton.x, event.mouseButton.y });
				manageClick(mousePos, window);
				break;
			} // end of switch
		} // end of if
		
		
		window.clear(sf::Color::White);
		
		int percent = 0;

		m_board.updateObjects(deltaTime, m_windowMode);

		if (m_isGame && m_windowMode != Mode::Pause)
		{
			if (!m_board.handleCollisions(deltaTime)) // returns false when player loses hp
			{
				if (m_board.getPlayerHP() == 0) // lost all hp, end game
				{
					Audio::instance().playSound("gameOver");
					m_windowMode = Mode::GameOver;
				}
				m_board.resetBoard();
			}
			
			percent = getOccupiedAreaPercent();
			if (percent >= NEEDED_PRCNT) // 80+
			{
				if (!setNewLevel()) // fail ==> there are no more stages!
				{
					m_windowMode = Mode::Win;
					m_isGame = false;
				}
				Audio::instance().playSound("clearStage");
				
			}
		}

		if (m_windowMode == Mode::GameOver || m_windowMode == Mode::Win) // need to return to main menu
		{
			counterTime += deltaTime;
			if (counterTime > SHOW_TIME) // show msg for 2 seconds
			{
				m_windowMode = Mode::Opening;
				m_isGame = false;
				counterTime = 0.0f;
			}
		}

		deltaTime = clock.restart().asSeconds();
		drawObjects(window, percent);
		window.display();
	}
}


// ------------------------------------


void Controller::manageClick(const sf::Vector2f& mousePos, sf::RenderWindow& window)
{
	if (!m_isGame) // ==> must be in opening screen or help screen
	{
		auto action = m_board.whereClicked(mousePos);
		switch (action)
		{
			case Action::Exit:
				if (m_isOnMenu) //  do not exit if not in main menu (like if in instructions)
					window.close();
				break;

			case Action::NewGame:
				m_isGame = true;
				m_windowMode = Mode::InGame;
				m_board.openStagesFile();
				setNewLevel();
				break;
			case Action::Instructions:
				m_isOnMenu = false;
				m_windowMode = Mode::Help;
				break;
			case Action::GotIt:
				if (!m_isOnMenu)
				{
					m_windowMode = Mode::Opening;
					m_isOnMenu = true;
				}
				break;
		}// end of switch
		
	} // end of if in menu/help screen
}


// ------------------------------------


void Controller::drawObjects(sf::RenderWindow& window, int percent)
{
	m_board.drawScreen(window, m_windowMode);

	if (m_windowMode == Mode::InGame)
		m_info.printTexts(window, m_board.getPlayerHP(), percent );
}

// ------------------------------------


int Controller::getOccupiedAreaPercent()
{
	return m_board.updateOccupiedArea();
}
// ------------------------------------


bool Controller::setNewLevel()
{
	if (!m_board.isNewLevel()) // file ended, don't continue. else, set things up
		return false; // false == >> no more stages
	
	m_board.allocateObjects();
	m_board.scaleObjects();

	return true; // otherwise
	
}