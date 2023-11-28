#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class TextDisplay
{
public:
	TextDisplay();
	bool loadFont(const std::string& fontPath);
	void setText(const std::string& text);
	void setPosition(float x, float y);
	void setCharacterSize(unsigned int size);
	void setColor(const sf::Color& color);
	void draw(sf::RenderWindow& window);

private:
	sf::Font font;
	sf::Text text;
};

