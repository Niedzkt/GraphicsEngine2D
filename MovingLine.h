#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>
class MovingLine : public GameObject
{
private:
	sf::Vector2f direction;
public:
	MovingLine(float x, float y, float dirX, float dirY) : GameObject(x,y), direction(dirX, dirY) {
		this->ax = 0;
		this->ay = 9.81;
	}

	virtual void render() override {
	}
};

