#include "Info.h"

Info::Info()
{
	loadTexts();
}

// ------------------------------------

void Info::loadTexts()
{
	if (!m_PokemonFont.loadFromFile("Pokemon Solid.ttf"))
		throw std::runtime_error("Could not load font file!");

	// we didn't want to use consts here because those numbers used here and only here.
	// spamming with "FONT_SIZE", "HP_X", "PRCNT_X" etc is overwhelming

	sf::Text text;
	text.setFont(m_PokemonFont);
	text.setCharacterSize(40);  
	text.setOutlineColor(sf::Color::Black);
	text.setOutlineThickness(1.0f);
	text.setFillColor(sf::Color::Red);
	text.setPosition(sf::Vector2f(100, 20));
	text.setString("HP: ");

	m_titles.push_back(text);
	text.setPosition(sf::Vector2f(550, 20));
	text.setString("Occupied: ");
	m_titles.push_back(text);

	text.setPosition(sf::Vector2f(750, 20));
	text.setString("");
	m_percent = std::move(text);

	text.setPosition(sf::Vector2f(200, 20));
	text.setString("");
	m_lives = std::move(text);
}

// ------------------------------------

void Info::printTexts(sf::RenderWindow& window, int lives, int percent)
{
	for (auto& text : m_titles)
		window.draw(text);

	m_percent.setString(std::to_string(percent) + " / " + std::to_string(NEEDED_PRCNT) + " %");
	window.draw(m_percent);
	m_lives.setString(std::to_string(lives));
	window.draw(m_lives);
}