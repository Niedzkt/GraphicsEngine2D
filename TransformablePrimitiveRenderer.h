#pragma once
#include "PrimitiveRenderer.h"
#include <iostream>
class TransformablePrimitiveRenderer : public PrimitiveRenderer
{
public:
	TransformablePrimitiveRenderer(sf::RenderWindow& renderWindow);

	void translate(float x, float y);
	void rotate(float angle);
	void scale(float scaleX, float scaleY);
	void setPosition(float x, float y);
	void resetTransform();

	void drawLine(const sf::Vector2f& startPoint, const sf::Vector2f& endPoint, const sf::Color& color, float thickness);
	void drawRectangle(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color);
	void drawCircle(const sf::Vector2f& center, float radius, const sf::Color& color);
	void drawPolyline(const std::vector<Point2D>& points, const sf::Color& color, float thickness, bool useBresenham);
	void drawClosedPolyline(const std::vector<Point2D>& points, const sf::Color& color, float thickness, bool useBresenham);
	void fillRectangle(float x, float y, float width, float height, const sf::Color& color);
	void fillCircle(float x_center, float y_center, float radius, const sf::Color& color);
	void fillPolygon(const std::vector<Point2D>& points, const sf::Color& color);

private:
	sf::Transform currentTransform;
};

