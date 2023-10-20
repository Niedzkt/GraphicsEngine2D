#include "GameObject.h"
#include <iostream>

GameObject::GameObject(const std::string& texturePath)
{
	if (!texture.loadFromFile(texturePath))
	{
		std::cout << "ERROR::TEXTURE OF GAMEOBJECT DID NOT LOAD!" << std::endl;
	}
	sprite.setTexture(texture);
}

GameObject::~GameObject()
{
}

void GameObject::setPosition(const sf::Vector2f& position)
{
	sprite.setPosition(position);
}

const sf::Vector2f& GameObject::getPosition() const
{
	return sprite.getPosition();
}

void GameObject::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}
