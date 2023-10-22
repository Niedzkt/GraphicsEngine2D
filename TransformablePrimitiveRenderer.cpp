#include "TransformablePrimitiveRenderer.h"

TransformablePrimitiveRenderer::TransformablePrimitiveRenderer(sf::RenderWindow& renderWindow)
	:PrimitiveRenderer(renderWindow),
	currentTransform(sf::Transform::Identity)
{
}

void TransformablePrimitiveRenderer::translate(float x, float y)
{
	currentTransform.translate(x, y);
}

void TransformablePrimitiveRenderer::rotate(float angle)
{
	currentTransform.rotate(angle);
}

void TransformablePrimitiveRenderer::scale(float scaleX, float scaleY)
{
	currentTransform.scale(scaleX, scaleY);
}

void TransformablePrimitiveRenderer::setPosition(float x, float y)
{
	sf::Transform translation;
	translation.translate(x, y);
	currentTransform = translation * currentTransform;
}

void TransformablePrimitiveRenderer::resetTransform()
{
	currentTransform = sf::Transform::Identity;
}

void TransformablePrimitiveRenderer::drawLine(const sf::Vector2f& startPoint, const sf::Vector2f& endPoint, const sf::Color& color, float thickness)
{
    sf::Vector2f transformedStart = currentTransform.transformPoint(startPoint);
    sf::Vector2f transformedEnd = currentTransform.transformPoint(endPoint);
    PrimitiveRenderer::drawLine(transformedStart, transformedEnd, color, thickness);
}

void TransformablePrimitiveRenderer::drawRectangle(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color)
{
    sf::Vector2f transformedPos = currentTransform.transformPoint(position);
    PrimitiveRenderer::drawRectangle(transformedPos, size, color);
}

void TransformablePrimitiveRenderer::drawCircle(const sf::Vector2f& center, float radius, const sf::Color& color)
{
    sf::Vector2f transformedCenter = currentTransform.transformPoint(center);
    PrimitiveRenderer::drawCircle(transformedCenter, radius, color);
}

void TransformablePrimitiveRenderer::drawPolyline(const std::vector<Point2D>& points, const sf::Color& color, float thickness, bool useBresenham)
{
    std::vector<Point2D> transformedPoints;
    for (const auto& point : points)
    {
        sf::Vector2f transformed = currentTransform.transformPoint(sf::Vector2f(point.getX(), point.getY()));
        transformedPoints.push_back(Point2D(transformed.x, transformed.y));
    }
    PrimitiveRenderer::drawPolyline(transformedPoints, color, thickness, useBresenham);
}

void TransformablePrimitiveRenderer::drawClosedPolyline(const std::vector<Point2D>& points, const sf::Color& color, float thickness, bool useBresenham)
{
    std::vector<Point2D> transformedPoints;
    for (const auto& point : points)
    {
        sf::Vector2f transformed = currentTransform.transformPoint(sf::Vector2f(point.getX(), point.getY()));
        transformedPoints.push_back(Point2D(transformed.x, transformed.y));
    }
    PrimitiveRenderer::drawClosedPolyline(transformedPoints, color, thickness, useBresenham);
}

void TransformablePrimitiveRenderer::fillPolygon(const std::vector<Point2D>& points, const sf::Color& color)
{
    std::vector<Point2D> transformedPoints;
    for (const auto& point : points)
    {
        sf::Vector2f transformed = currentTransform.transformPoint(sf::Vector2f(point.getX(), point.getY()));
        transformedPoints.push_back(Point2D(transformed.x, transformed.y));
    }
    PrimitiveRenderer::fillPolygon(transformedPoints, color);
}

void TransformablePrimitiveRenderer::fillRectangle(float x, float y, float width, float height, const sf::Color& color)
{
    sf::Vector2f transformedPos = currentTransform.transformPoint(sf::Vector2f(x, y));
    sf::Vector2f transformedSize = currentTransform.transformPoint(sf::Vector2f(x + width, y + height)) - transformedPos;

    PrimitiveRenderer::fillRectangle(transformedPos.x, transformedPos.y, transformedSize.x, transformedSize.y, color);
}

void TransformablePrimitiveRenderer::fillCircle(float x_center, float y_center, float radius, const sf::Color& color)
{
    sf::Vector2f transformedCenter = currentTransform.transformPoint(sf::Vector2f(x_center, y_center));
    sf::Vector2f transformedRadiusPoint = currentTransform.transformPoint(sf::Vector2f(x_center + radius, y_center));
    float transformedRadius = std::sqrt(std::pow(transformedRadiusPoint.x - transformedCenter.x, 2) + std::pow(transformedRadiusPoint.y - transformedCenter.y, 2));

    PrimitiveRenderer::fillCircle(transformedCenter.x, transformedCenter.y, transformedRadius, color);
}