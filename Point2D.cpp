#include "Point2D.h"

Point2D::Point2D() : x(0.0f), y(0.0f)
{
}

Point2D::Point2D(float x, float y) : x(x), y(y)
{
}

float Point2D::getX() const
{
	return x;
}

float Point2D::getY() const
{
	return y;
}

void Point2D::setX(float x)
{
	this->x = x;
}

void Point2D::setY(float y)
{
	this->y = y;
}

void Point2D::setPosition(float x, float y)
{
	this->x = x;
	this->y = y;
}

void Point2D::draw(PrimitiveRenderer& renderer, const sf::Color& color, float size) const
{
	//renderer.drawRectangle({ x - size / 2, y - size / 2 }, { size, size }, color);
}
