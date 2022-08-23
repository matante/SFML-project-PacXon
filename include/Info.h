#pragma once
#include "Consts.h"
#include "Textures.h"

class Info
{
public:
	Info();
	~Info() = default;
	void loadTexts();
	void printTexts(sf::RenderWindow&, int, int);

private:
	sf::Font m_PokemonFont;
	std::vector<sf::Text> m_titles;
	sf::Text m_lives;
	sf::Text m_percent;
	std::vector<sf::Sprite> m_sprites;
};