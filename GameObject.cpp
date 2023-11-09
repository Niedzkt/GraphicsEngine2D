#include "GameObject.h"

GameObject::GameObject(float x = 0, float y = 0) 
	:x(x),y(y),vx(0),vy(0),ax(0),ay(0)
{
}

void GameObject::update(float deltaTime)
{
	vx += ax * deltaTime;
	vy += ay * deltaTime;
	x += vx * deltaTime;
	y += vy * deltaTime;
}

GameObject::~GameObject()
{
}
