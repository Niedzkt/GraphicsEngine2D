#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>

class MovingLine : public GameObject
{
private:
	sf::Vector2f direction;
public:
	// Konstruktor klasy `MovingLine` inicjalizuje liniê jako `GameObject` z podan¹ pozycj¹ startow¹
	// i wektorem kierunku. Dodatkowo, ustawia przyspieszenie w osi Y na wartoœæ odpowiadaj¹c¹ grawitacji (9.81).
	MovingLine(float x, float y, float dirX, float dirY) : GameObject(x,y), direction(dirX, dirY) {
		this->ax = 0;
		this->ay = 9.81;
	}

	// Metoda `render` (wirtualna i przes³oniêta) s³u¿y do rysowania linii na ekranie.
	// Aktualnie jest pusta i wymaga implementacji.
	virtual void render() override {
	}
};

