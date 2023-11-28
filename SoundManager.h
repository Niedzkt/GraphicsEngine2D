#pragma once
#include <SFML/Audio.hpp>
#include <string>
#include <unordered_map>

class SoundManager
{
public:
	bool loadSound(const std::string& name, const std::string& filePath);
	void playSound(const std::string& name);
	void setVolume(float volume);
	void stopSound(const std::string& name);


private:
	std::unordered_map<std::string, sf::SoundBuffer> soundBuffers;
	std::unordered_map<std::string, sf::Sound> sounds;
	float volume;
};

