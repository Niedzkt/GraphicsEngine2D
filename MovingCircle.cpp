#include "MovingCircle.h"

// Konstruktor klasy `MovingCircle` inicjalizuje obiekt jako `GameObject` z podan� pozycj�, a tak�e ustawia
// promie� i kolor ko�a. Dodatkowo, inicjalizuje pr�dko�ci i przyspieszenia, gdzie przyspieszenie w osi Y
// jest zazwyczaj ustawione na warto�� odpowiadaj�c� grawitacji (9.81).
MovingCircle::MovingCircle(float x, float y, float radius, sf::Color color)
	:GameObject(x,y), radius(radius), color(color)
{
	vx = vy = 0;
	ax = 0;
	ay = 9.81;
}
// Metoda `update` aktualizuje stan ruchomego ko�a na podstawie up�ywu czasu. Obejmuje to obliczanie
// nowej pozycji na podstawie pr�dko�ci i przyspieszenia oraz sprawdzanie kolizji z granicami okna,
// powoduj�c odbicie, je�li ko�o dotknie kraw�dzi okna.
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
// Metoda `render` (obecnie pusta) prawdopodobnie ma za zadanie rysowa� ko�o na ekranie,
// ale wymaga implementacji.
void MovingCircle::render()
{
}
// Metoda `getRadius` zwraca promie� ko�a.
float MovingCircle::getRadius() const
{
	return radius;
}
// Metoda `getColor` zwraca kolor ko�a.
sf::Color MovingCircle::getColor() const
{
	return color;
}
