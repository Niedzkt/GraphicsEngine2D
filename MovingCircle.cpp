#include "MovingCircle.h"

// Konstruktor klasy `MovingCircle` inicjalizuje obiekt jako `GameObject` z podan¹ pozycj¹, a tak¿e ustawia
// promieñ i kolor ko³a. Dodatkowo, inicjalizuje prêdkoœci i przyspieszenia, gdzie przyspieszenie w osi Y
// jest zazwyczaj ustawione na wartoœæ odpowiadaj¹c¹ grawitacji (9.81).
MovingCircle::MovingCircle(float x, float y, float radius, sf::Color color)
	:GameObject(x,y), radius(radius), color(color)
{
	vx = vy = 0;
	ax = 0;
	ay = 9.81;
}
// Metoda `update` aktualizuje stan ruchomego ko³a na podstawie up³ywu czasu. Obejmuje to obliczanie
// nowej pozycji na podstawie prêdkoœci i przyspieszenia oraz sprawdzanie kolizji z granicami okna,
// powoduj¹c odbicie, jeœli ko³o dotknie krawêdzi okna.
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
// Metoda `render` (obecnie pusta) prawdopodobnie ma za zadanie rysowaæ ko³o na ekranie,
// ale wymaga implementacji.
void MovingCircle::render()
{
}
// Metoda `getRadius` zwraca promieñ ko³a.
float MovingCircle::getRadius() const
{
	return radius;
}
// Metoda `getColor` zwraca kolor ko³a.
sf::Color MovingCircle::getColor() const
{
	return color;
}
