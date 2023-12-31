#pragma once
#include "PrimitiveRenderer.h"
#include "Point2D.h"
#include "LineSegment.h"
#include "MovingLine.h"
#include "BitmapRenderer.h"
#include "AnimatedBitmap.h"
#include "SoundManager.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>


class Engine
{
private:
	sf::RenderWindow window;
	sf::Clock clock;
	sf::Color backgroundColor;
	float deltaTime;
	bool isFullScreen;
	PrimitiveRenderer renderer;
	Point2D point;
	LineSegment segment;
	std::vector<LineSegment> segments;
	std::vector<Point2D> myPoints;
	std::vector<Point2D> polygonPoints;
	std::vector<MovingRectangle> movingRectangles;
	Point2D circleCenter;
	float circleRadius;
	sf::Color circleColor;
	MovingLine movingLine;
	BitmapRenderer bitmapRenderer;
	AnimatedBitmap animatedBitmap;
	MovingRectangle movingRectangle;
	MovingCircle movingCircle;
	SoundManager soundManager;

	void handleEvents();
	void update();
	void draw();
	void logError(const std::string& message);
	void handleKeyboardEvents(const sf::Event& event);
	void handleMouseEvents(const sf::Event& event);

public:
	sf::Vector2u getWindowSize() const;
	Engine(unsigned int width = 800, unsigned height = 600, const std::string& title = "Engine 2D");
	bool initialize();
	void setFullscreen(bool fullscreen);
	void setFramerateLimit(unsigned int limit);
	void mainLoop();
	void setBackgroundColor(const sf::Color& color);
	~Engine();
};

