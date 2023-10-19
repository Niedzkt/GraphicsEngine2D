#pragma once
#include <SFML/Graphics.hpp>

class Engine
{
private:
	sf::RenderWindow window;
	bool isRunning;

public:
	Engine(int width, int height, const std::string& title);
	~Engine();
	void run();

private:
	void init();
	void handleEvents();
	void update(float deltaTime);
	void render();
};

