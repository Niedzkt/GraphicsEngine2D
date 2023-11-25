#include "MovingRectangle.h"

MovingRectangle::MovingRectangle(float x, float y, float width, float height, sf::Color color)
	:GameObject(x,y), width(width), height(height), color(color)
{
	vx = vy = 0;
	ax = 0;
	ay = 9.81;
}

void MovingRectangle::update(float deltaTime)
{
	vx += ax * deltaTime;
	vy += ay * deltaTime;

	x += vx * deltaTime;
	y += vy * deltaTime;
}

void MovingRectangle::render()
{
}

float MovingRectangle::getWidth() const
{
	return width;
}

float MovingRectangle::getHeight() const
{
	return height;
}

sf::Color MovingRectangle::getColor() const
{
	return color;
}
