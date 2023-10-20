#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>

class Engine
{
private:
	sf::RenderWindow window;
	sf::Clock clock;
	sf::Color backgroundColor;
	float deltaTime;
	bool isFullScreen;

	void handleEvents();
	void update();
	void draw();
	void logError(const std::string& message);
	void handleKeyboardEvents(const sf::Event& event);
	void handleMouseEvents(const sf::Event& event);

public:
	Engine(unsigned int width = 800, unsigned height = 600, const std::string& title = "Engine 2D");
	bool initialize();
	void setFullscreen(bool fullscreen);
	void setFramerateLimit(unsigned int limit);
	void mainLoop();
	void setBackgroundColor(const sf::Color& color);
	~Engine();
};

