#pragma once
class GameObject
{
public:
	float x, y;
	float vx, vy;
	float ax, ay;


	GameObject(float x, float y);

	virtual void update(float deltaTime);
	virtual void render()=0;
	virtual ~GameObject();
};

