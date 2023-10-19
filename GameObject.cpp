#include "GameObject.h"
#include <iostream>

GameObject::GameObject(const std::string& texturePath)
{
	if (!texture.loadFromFile(texturePath))
	{
		std::cout << "ERROR::TEXTURE OF GAMEOBJECT DID NOT LOAD!" << std::endl;
	}
}

GameObject::~GameObject()
{
}

void GameObject::setPosition(const sf::Vector2f& position)
{
}

const sf::Vector2f& GameObject::getPosition() const
{
	// TODO: tu wstawiæ instrukcjê return
}

void GameObject::draw(sf::RenderWindow& window)
{
}
