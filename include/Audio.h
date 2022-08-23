#pragma once
#include "Consts.h"

class Audio
{
public: /*Functions:*/

	static Audio& instance();
	void playBackgroundMusic();
	void playSound(const std::string&);

private: /*Functions:*/
	Audio();
	Audio(const Audio&) = default;
	Audio& operator=(const Audio&) = default;
	void loadMusicFiles();
	void loadSound(std::string);
private: /*Members:*/
	
	std::unordered_map <std::string, sf::SoundBuffer> m_buffers;
	std::unordered_map <std::string, sf::Sound> m_sounds;
	sf::Music m_backgroundMusic;

};