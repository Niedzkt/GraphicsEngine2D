#include "MovingCircle.h"

MovingCircle::MovingCircle(float x, float y, float radius, sf::Color color)
	:GameObject(x,y), radius(radius), color(color)
{
	vx = vy = 0;
	ax = 0;
	ay = 9.81;
}

void MovingCircle::update(float deltaTime)
{
	vx += ax * deltaTime;
	vy += ay * deltaTime;

	x += vx * deltaTime;
	y += vy * deltaTime;

    sf::Vector2u windowSize = GameObject::getWindowSize();

 
    if (x - radius < 0) {
        x = radius;  
        vx = -vx; 
    }
    else if (x + radius > windowSize.x) {
        x = windowSize.x - radius;  
        vx = -vx;
    }

    
    if (y - radius < 0) {
        y = radius;
        vy = -vy; 
    }
    else if (y + radius > windowSize.y) {
        y = windowSize.y - radius;  
        vy = -vy;
    }
}

void MovingCircle::render()
{
}

float MovingCircle::getRadius() const
{
	return radius;
}

sf::Color MovingCircle::getColor() const
{
	return color;
}
