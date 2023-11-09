#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include "Point2D.h"
#include "GameObject.h"

class Point2D;

class PrimitiveRenderer
{
private:
	sf::RenderWindow& window;
	const double PI = 3.14159265358979323846;

	sf::Vector2f scale;
	float rotation;
	sf::Vector2f translation;
	bool useScaleTransform = true;

public:
	PrimitiveRenderer(sf::RenderWindow& window);
	PrimitiveRenderer& setScale(float sx, float sy);
	PrimitiveRenderer& setRotation(float radians);
	PrimitiveRenderer& setTranslation(float dx, float dy);

	void drawLine(const sf::Vector2f& startPoint, const sf::Vector2f& endPoint, const sf::Color& color, float thickness = 1.0f);
	void drawLine(const GameObject& object, const sf::Color& color, float thickness = 1.0f, float lenght = 70.0f);
	void drawRectangle(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color);
	void drawRectangle(const GameObject& object, const sf::Vector2f& size, const sf::Color& color);
	void drawCircle(const sf::Vector2f& center, float radius, const sf::Color& color);
	void drawCircle(const GameObject& object, float radius, const sf::Color& color);
	void drawLineByBresenham(const sf::Vector2f& startPoint, const sf::Vector2f& endPoint, const sf::Color& color, float thickness);
	void drawPolyline(const std::vector<Point2D>& points, const sf::Color& color, float thickness = 2.0f, bool useBresenham = false);
	void drawPolyline(const std::vector<sf::Vector2f>& points, const sf::Color& color, float thickness = 2.0f, bool useBresenham = false);
	void drawClosedPolyline(const std::vector<Point2D>& points, const sf::Color& color, float thickness = 2.0f, bool useBresenham = false);
	void drawCircleAlgorithm(int x_center, int y_center, int r, const sf::Color& color);
	void putPixel(int x, int y, const sf::Color& color);
	void drawEllipse(float x0, float y0, float RX, float RY, const sf::Color& color);
	void drawEllipse(const GameObject& object, float x0, float y0, float RX, float RY, const sf::Color& color);
	void drawPolygon(const std::vector<Point2D>& points, const sf::Color& color);
	void drawPolygon(const GameObject& object, const std::vector<Point2D>& points, const sf::Color& color);
	void fillRectangle(float x, float y, float width, float height, const sf::Color& color);
	void fillRectangle(const GameObject& object, float x, float y, float width, float height, const sf::Color& color);
	void fillCircle(float x_center, float y_center, float radius, const sf::Color& color);
	void fillCircle(const GameObject& object, float x_center, float y_center, float radius, const sf::Color& color);
	void fillPolygon(const std::vector<Point2D>& points, const sf::Color& color);
	void fillPolygon(const GameObject& object, const std::vector<Point2D>& points, const sf::Color& color);

	sf::Vector2f applyTransform(const sf::Vector2f& point);
	void resetTransformation();
	void enableScaleTransform();
	void disableScaleTransform();
};

