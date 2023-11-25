#pragma once
#include "GameObject.h"
#include "PrimitiveRenderer.h"
#include <SFML/Graphics.hpp>

class MovingRectangle : public GameObject
{
public:
	MovingRectangle(float x, float y, float width, float height, sf::Color color);

	virtual void update(float deltaTime) override;
	virtual void render() override;

	float getWidth() const;
	float getHeight() const;
	sf::Color getColor() const;

private:
	float width, height;
	sf::Color color;
};

