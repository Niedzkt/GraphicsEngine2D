#include "LineSegment.h"
// Konstruktor domy�lny klasy `LineSegment` inicjalizuje obiekt bez okre�lonych punkt�w startowego i ko�cowego.
LineSegment::LineSegment()
{
}
// Konstruktor parametryczny klasy `LineSegment` inicjalizuje obiekt z podanymi punktami startowym i ko�cowym.
LineSegment::LineSegment(const Point2D& start, const Point2D& end) : start(start), end(end)
{
}
// Metoda `getStart` zwraca punkt startowy odcinka.
Point2D LineSegment::getStart() const
{
	return start;
}
// Metoda `getEnd` zwraca punkt ko�cowy odcinka.
Point2D LineSegment::getEnd() const
{
	return end;
}
// Metoda `setStart` ustawia nowy punkt startowy odcinka.
void LineSegment::setStart(const Point2D& start)
{
	this->start = start;
}
// Metoda `setEnd` ustawia nowy punkt ko�cowy odcinka.
void LineSegment::setEnd(const Point2D& end)
{
	this->end = end;
}
// Metoda `draw` rysuje odcinek wykorzystuj�c renderer. Umo�liwia wyb�r mi�dzy klasycznym rysowaniem
// a algorytmem Bresenhama do rysowania linii.
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
