#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class BitmapRenderer
{
public:
	BitmapRenderer(const std::string& filePath, const sf::Vector2f& position);

	bool loadBitmap(const std::string& filePath);
	BitmapRenderer& setPosition(const sf::Vector2f& position);
	BitmapRenderer& setScale(float sx, float sy);
	BitmapRenderer& setRotation(float radians);
	BitmapRenderer& setTranslation(float dx, float dy);
	void draw(sf::RenderWindow& window);

private:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f scale;
	float rotation;
	sf::Vector2f translation;
	const double PI = 3.14159265358979323846;
};

