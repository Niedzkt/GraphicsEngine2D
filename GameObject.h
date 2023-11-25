#pragma once
#include <SFML/System/Vector2.hpp>
class GameObject
{
public:
	float x, y;
	float vx, vy;
	float ax, ay;

	static void setWindowSize(const sf::Vector2u& size);
	static sf::Vector2u getWindowSize();
	GameObject(float x, float y);

	virtual void update(float deltaTime);
	virtual void render()=0;
	virtual ~GameObject();

protected:
	static sf::Vector2u windowSize;
};

