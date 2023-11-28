#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>

class MovingLine : public GameObject
{
private:
	sf::Vector2f direction;
public:
	// Konstruktor klasy `MovingLine` inicjalizuje lini� jako `GameObject` z podan� pozycj� startow�
	// i wektorem kierunku. Dodatkowo, ustawia przyspieszenie w osi Y na warto�� odpowiadaj�c� grawitacji (9.81).
	MovingLine(float x, float y, float dirX, float dirY) : GameObject(x,y), direction(dirX, dirY) {
		this->ax = 0;
		this->ay = 9.81;
	}

	// Metoda `render` (wirtualna i przes�oni�ta) s�u�y do rysowania linii na ekranie.
	// Aktualnie jest pusta i wymaga implementacji.
	virtual void render() override {
	}
};

