#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>

class MovingCircle : public GameObject
{
public:
	MovingCircle(float x, float y, float radius, sf::Color color);

	virtual void update(float deltaTime) override;
	virtual void render() override;

	float getRadius() const;
	sf::Color getColor() const;

private:
	float radius;
	sf::Color color;
};

