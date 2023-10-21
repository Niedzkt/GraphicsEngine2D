#pragma once
#include "Point2D.h"
#include "PrimitiveRenderer.h"

class LineSegment
{
private:
	Point2D start, end;

public:
	LineSegment();
	LineSegment(const Point2D& start, const Point2D& end);

	Point2D getStart() const;
	Point2D getEnd() const;
	void setStart(const Point2D& start);
	void setEnd(const Point2D& end);

	void draw(PrimitiveRenderer& renderer, const sf::Color& color = sf::Color::White, float thickness = 2.0f, bool useBresenham = false) const;
};

