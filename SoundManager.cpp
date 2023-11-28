#include "SoundManager.h"
// Metoda do ³adowania dŸwiêku z pliku do mened¿era dŸwiêków
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
// Metoda do odtwarzania dŸwiêku o podanej nazwie
void SoundManager::playSound(const std::string& name)
{
	auto it = sounds.find(name);
	if (it != sounds.end())
	{
		it->second.play();
	}
}
// Metoda do ustawiania g³oœnoœci dla wszystkich dŸwiêków w mened¿erze
void SoundManager::setVolume(float volume)
{
	this->volume = volume;
	for (auto& sound : sounds)
	{
		sound.second.setVolume(volume);
	}
}
// Metoda do zatrzymywania dŸwiêku o podanej nazwie
void SoundManager::stopSound(const std::string& name)
{
	auto it = sounds.find(name);
	if (it != sounds.end()) {
		it->second.stop();
	}
}
