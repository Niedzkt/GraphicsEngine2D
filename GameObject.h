#pragma once
#include <SFML/Graphics.hpp>
class GameObject
{
private:
	sf::Sprite sprite;
	sf::Texture texture;

public:
	GameObject(const std::string& texturePath);
	~GameObject();

	void setPosition(const sf::Vector2f& position);
	const sf::Vector2f& getPosition() const;

	void draw(sf::RenderWindow& window);
};

