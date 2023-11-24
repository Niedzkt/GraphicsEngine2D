#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>

class MovingRectangle : public GameObject {
public:
    MovingRectangle(float x, float y, float width, float height, sf::Color color, sf::Vector2f velocity)
        : GameObject(x, y), width(width), height(height), color(color), velocity(velocity) {
        this->ax = 0; 
        this->ay = 9.81; 
        rectangle.setSize(sf::Vector2f(width, height));
        rectangle.setFillColor(color);
        rectangle.setPosition(x, y);
    }

    void update(float deltaTime) {
        velocity.x += ax * deltaTime;
        velocity.y += ay * deltaTime;


        position.x += velocity.x * deltaTime;
        position.y += velocity.y * deltaTime;


        rectangle.setPosition(position);
    }

    virtual void render() override {
    }


private:
    float width, height;
    sf::Color color;
    sf::Vector2f velocity;
    float ax, ay; 
    sf::RectangleShape rectangle;
    sf::Vector2f position;
};
