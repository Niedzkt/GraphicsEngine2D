#include "TextDisplay.h"

TextDisplay::TextDisplay() {
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::White);
	text.setStyle(sf::Text::Regular);
}

bool TextDisplay::loadFont(const std::string& fontPath)
{
	return font.loadFromFile(fontPath);
}

void TextDisplay::setText(const std::string& str)
{
	text.setString(str);
}

void TextDisplay::setPosition(float x, float y)
{
	text.setPosition(x, y);
}

void TextDisplay::setCharacterSize(unsigned int size)
{
	text.setCharacterSize(size);
}

void TextDisplay::setColor(const sf::Color& color)
{
	text.setFillColor(color);
}

void TextDisplay::draw(sf::RenderWindow& window)
{
	window.draw(text);
}
