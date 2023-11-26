#include "SoundManager.h"

bool SoundManager::loadSound(const std::string& name, const std::string& filePath)
{
    sf::SoundBuffer buffer;
	if (!buffer.loadFromFile(filePath))
	{
		return false;
	}
	soundBuffers[name] = buffer;
	sounds[name].setBuffer(soundBuffers[name]);
	return true;
}

void SoundManager::playSound(const std::string& name)
{
	auto it = sounds.find(name);
	if (it != sounds.end())
	{
		it->second.play();
	}
}

void SoundManager::setVolume(float volume)
{
	this->volume = volume;
	for (auto& sound : sounds)
	{
		sound.second.setVolume(volume);
	}
}
