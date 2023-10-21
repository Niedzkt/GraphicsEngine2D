#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Point2D.h"

class Point2D;

class PrimitiveRenderer
{
private:
	sf::RenderWindow& window;

public:
	PrimitiveRenderer(sf::RenderWindow& window);
	void drawLine(const sf::Vector2f& startPoint, const sf::Vector2f& endPoint, const sf::Color& color, float thickness = 1.0f);
	void drawRectangle(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color);
	void drawCircle(const sf::Vector2f& center, float radius, const sf::Color& color);
	void drawLineByBresenham(const sf::Vector2f& startPoint, const sf::Vector2f& endPoint, const sf::Color& color, float thickness);
	void drawPolyline(const std::vector<Point2D>& points, const sf::Color& color, float thickness = 2.0f, bool useBresenham = false);
	void drawClosedPolyline(const std::vector<Point2D>& points, const sf::Color& color, float thickness = 2.0f, bool useBresenham = false);
};

