#include "SoundManager.h"
// Metoda do �adowania d�wi�ku z pliku do mened�era d�wi�k�w
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
// Metoda do odtwarzania d�wi�ku o podanej nazwie
void SoundManager::playSound(const std::string& name)
{
	auto it = sounds.find(name);
	if (it != sounds.end())
	{
		it->second.play();
	}
}
// Metoda do ustawiania g�o�no�ci dla wszystkich d�wi�k�w w mened�erze
void SoundManager::setVolume(float volume)
{
	this->volume = volume;
	for (auto& sound : sounds)
	{
		sound.second.setVolume(volume);
	}
}
// Metoda do zatrzymywania d�wi�ku o podanej nazwie
void SoundManager::stopSound(const std::string& name)
{
	auto it = sounds.find(name);
	if (it != sounds.end()) {
		it->second.stop();
	}
}
