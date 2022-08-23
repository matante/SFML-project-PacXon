#pragma once
#include "Consts.h"
#include "EnumClasses.h"
class Textures
{
public:
	//static class stuff
	~Textures();
	static Textures& instance();


	/*get funcs*/
	sf::Texture& getIconTexture(Image);
	sf::Texture& getBackgroundTexture(Mode);

private://static class stuff
	Textures();
	Textures(const Textures&) = default;
	Textures& operator=(const Textures&) = default;


private: //functions
	void loadTextures();

private: //members
	std::unordered_map<Mode, sf::Texture> m_background;
	std::unordered_map<Image, sf::Texture> m_textures;
	
};