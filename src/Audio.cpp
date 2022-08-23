#include "Audio.h"


Audio::Audio()
{
	loadMusicFiles();
};
// --------------------------------------------------------------

Audio& Audio::instance() {
	static Audio inst;
	return inst;
}
// --------------------------------------------------------------

void Audio::playBackgroundMusic()
{
	m_backgroundMusic.play();
}
// --------------------------------------------------------------

void Audio::playSound(const std::string& name)
{	
	if (m_sounds.find(name) != m_sounds.end()) {
		// found
		m_sounds[name].play();
	}
	
}
// --------------------------------------------------------------


void Audio::loadSound(std::string name)
{
	
	if (!m_buffers[name].loadFromFile(name + ".wav"))
		throw std::runtime_error("Could not load music file!");
	
	m_sounds[name] = sf::Sound(m_buffers[name]);

}
// ------------------------------------

void Audio::loadMusicFiles()
{
	loadSound("clearStage");
	loadSound("gameOver");
	loadSound("lose");
	loadSound("reward");

	for (auto& s : m_sounds)
		s.second.setVolume(10.0f);

	if (!m_backgroundMusic.openFromFile("backgroundMusic.ogg"))
		throw std::runtime_error("Could not load background music file!");
	
	m_backgroundMusic.setVolume(10.0f);
	m_backgroundMusic.setLoop(true);
}

