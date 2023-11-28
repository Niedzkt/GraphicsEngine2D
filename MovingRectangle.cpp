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

	sf::Vector2u windowSize = GameObject::getWindowSize();

    if (x < 0) {
        x = 0;  
        vx = -vx; 
    }
    else if (x + width > windowSize.x) {
        x = windowSize.x - width;  
        vx = -vx;
    }

    if (y < 0) {
        y = 0; 
        vy = -vy; 
    }
    else if (y + height > windowSize.y) {
        y = windowSize.y - height; 
        vy = -vy;
    }
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
