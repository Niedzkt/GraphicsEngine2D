#pragma once
#include "PrimitiveRenderer.h"

class PrimitiveRenderer;

class Point2D
{
private:
	float x, y;
public:
	Point2D();
	Point2D(float x, float y);

	float getX() const;
	float getY() const;

	void setX(float x);
	void setY(float y);
	void setPosition(float x, float y);

	void draw(PrimitiveRenderer& renderer, const sf::Color& color = sf::Color::White, float size = 2.0f) const;
};

