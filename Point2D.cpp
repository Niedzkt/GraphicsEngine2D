#include "Point2D.h"
// Konstruktor domyœlny `Point2D` inicjalizuje punkt z wartoœciami 0.0f dla x i y.
Point2D::Point2D() : x(0.0f), y(0.0f)
{
}
// Konstruktor parametryczny `Point2D` inicjalizuje punkt z podanymi wartoœciami x i y.
Point2D::Point2D(float x, float y) : x(x), y(y)
{
}
// Metoda `getX` zwraca wartoœæ wspó³rzêdnej x punktu.
float Point2D::getX() const
{
	return x;
}
// Metoda `getY` zwraca wartoœæ wspó³rzêdnej y punktu.
float Point2D::getY() const
{
	return y;
}

// Metoda `setX` ustawia now¹ wartoœæ wspó³rzêdnej x punktu.
void Point2D::setX(float x)
{
	this->x = x;
}
// Metoda `setY` ustawia now¹ wartoœæ wspó³rzêdnej y punktu.
void Point2D::setY(float y)
{
	this->y = y;
}
// Metoda `setPosition` ustawia nowe wspó³rzêdne x i y punktu.
void Point2D::setPosition(float x, float y)
{
	this->x = x;
	this->y = y;
}
// Metoda `draw` (obecnie zakomentowana) prawdopodobnie ma za zadanie rysowaæ reprezentacjê
// punktu na ekranie, ale wymaga implementacji.
void Point2D::draw(PrimitiveRenderer& renderer, const sf::Color& color, float size) const
{
	//renderer.drawRectangle({ x - size / 2, y - size / 2 }, { size, size }, color);
}
