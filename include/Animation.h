#pragma once
#include "Consts.h"
#include "Direction.h"
class Animation
{
public:
	Animation() = default;
	Animation(sf::Texture &, sf::Vector2u, float );
	~Animation() = default;

public:
	void update(int, float);
	sf::IntRect getUVRect()const {return m_uvRect;};
private:
	sf::IntRect m_uvRect;

	sf::Vector2u m_imageCount;
	sf::Vector2u m_currentImage;
	float m_totalTime;
	float m_switchTime;
};