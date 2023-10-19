#include "Engine.h"

Engine::Engine(int width, int height, const std::string& title):window(sf::VideoMode(width, height), title), isRunning(true)
{
	init();
}

Engine::~Engine()
{
}

void Engine::init()
{
}

void Engine::handleEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed) {
			isRunning = false;
		}
	}
}

void Engine::update(float deltaTime)
{
}

void Engine::render()
{
	window.clear();


	window.display();
}

void Engine::run()
{
	sf::Clock clock;
	while (isRunning)
	{
		float deltaTime = clock.restart().asSeconds();
		handleEvents();
		update(deltaTime);
		render();
	}

	window.close();
}
