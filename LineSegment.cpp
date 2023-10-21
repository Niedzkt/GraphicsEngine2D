#include "LineSegment.h"

LineSegment::LineSegment()
{
}

LineSegment::LineSegment(const Point2D& start, const Point2D& end) : start(start), end(end)
{
}

Point2D LineSegment::getStart() const
{
	return start;
}

Point2D LineSegment::getEnd() const
{
	return end;
}

void LineSegment::setStart(const Point2D& start)
{
	this->start = start;
}

void LineSegment::setEnd(const Point2D& end)
{
	this->end = end;
}

void LineSegment::draw(PrimitiveRenderer& renderer, const sf::Color& color, float thickness, bool useBresenham) const
{
	if (useBresenham)
	{
		renderer.drawLineByBresenham({ start.getX(), start.getY()}, {end.getX(), end.getY()}, color, thickness);
	}
	else
	{
		renderer.drawLine({ start.getX(), start.getY() }, { end.getX(), end.getY() }, color, thickness);
	}
}
