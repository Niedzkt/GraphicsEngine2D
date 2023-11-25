#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>

class AnimatedBitmap
{
public:
	AnimatedBitmap(const std::string& filePath, const sf::Vector2i& frameSize, int frameCount, float FrameDuration, const sf::Vector2f& position);

	bool loadAnimation(const std::string& filePath, const sf::Vector2i& frameSize, int frameCount, float frameDuration);
	void update(float deltaTime);
	AnimatedBitmap& setPosition(const sf::Vector2f& position);
	AnimatedBitmap& setScale(float sx, float sy);
	AnimatedBitmap& setRotation(float radians);
	AnimatedBitmap& setTranslation(float dx, float dy);
	void draw(sf::RenderWindow& window);

private:
	sf::Texture texture;
	std::vector<sf::IntRect> frames;
	sf::Sprite sprite;
	sf::Vector2f scale;
	float rotation;
	sf::Vector2f translation;
	float frameDuration;
	float elapsedTime;
	size_t currentFrame;
	const double PI = 3.14159265358979323846;
};

