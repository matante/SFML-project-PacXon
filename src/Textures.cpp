#include "Textures.h"


Textures::Textures()
{
	loadTextures();
};
// --------------------------------------------------------------

Textures::~Textures() {}
// --------------------------------------------------------------

Textures& Textures::instance() {
	static Textures inst;
	return inst;
}
// --------------------------------------------------------------



void Textures::loadTextures()
{	
	sf::Texture myTexture;
	

	if (!myTexture.loadFromFile("buttons.png"))
		throw std::runtime_error("Could not load buttons image!");
	m_textures[Image::Buttons] = myTexture;

	if (!myTexture.loadFromFile("Player.png"))
		throw std::runtime_error("Could not load image ");
	m_textures[Image::Player] = myTexture;

	if (!myTexture.loadFromFile("tiles.png"))
		throw std::runtime_error("Could not load image ");
	m_textures[Image::Tile] = myTexture;

	if (!myTexture.loadFromFile("RegularEnemy.png"))
		throw std::runtime_error("Could not load image ");
	m_textures[Image::Regular] = myTexture;

	if (!myTexture.loadFromFile("SmartEnemy.png"))
		throw std::runtime_error("Could not load image ");
	m_textures[Image::Smart] = myTexture;

	if (!myTexture.loadFromFile("HungryEnemy.png"))
		throw std::runtime_error("Could not load image ");
	m_textures[Image::Hungry] = myTexture;

	if (!myTexture.loadFromFile("OccupiedAreaEnemy.png"))
		throw std::runtime_error("Could not load image ");
	m_textures[Image::Occupied] = myTexture;

	if (!myTexture.loadFromFile("rewards.png"))
		throw std::runtime_error("Could not load image ");
	m_textures[Image::Rewards] = myTexture;

	

	if (!myTexture.loadFromFile("openingScreen.jpg"))
		throw std::runtime_error("Could not load openingScreen image!");
	m_background[Mode::Opening] = myTexture;

	if (!myTexture.loadFromFile("helpScreen.png"))
		throw std::runtime_error("Could not load helpScreen image!");
	m_background[Mode::Help] = myTexture;

	if (!myTexture.loadFromFile("background.jpg"))
		throw std::runtime_error("Could not load background image!");
	m_background[Mode::InGame] = myTexture;

	if (!myTexture.loadFromFile("gameover.png"))
		throw std::runtime_error("Could not load background image!");
	m_background[Mode::GameOver] = myTexture;

	if (!myTexture.loadFromFile("win.png"))
		throw std::runtime_error("Could not load background image!");
	m_background[Mode::Win] = myTexture;

	if (!myTexture.loadFromFile("pause.png"))
		throw std::runtime_error("Could not load background image!");
	m_background[Mode::Pause] = myTexture;

	for (auto& t : m_textures)
		t.second.setSmooth(true);
	for (auto& b : m_background)
		b.second.setSmooth(true);
		
}
// --------------------------------------------------------------

sf::Texture& Textures::getIconTexture(Image img)
{
	
	if (m_textures.find(img) != m_textures.end()) {
		// found
		return m_textures[img];
	}
}
// --------------------------------------------------------------

sf::Texture& Textures::getBackgroundTexture(Mode type)
{
	if (m_background.find(type) != m_background.end()) {
		// found
		return m_background[type];
	}
}



// --------------------------------------------------------------

