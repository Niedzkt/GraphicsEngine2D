#include "PrimitiveRenderer.h"

PrimitiveRenderer::PrimitiveRenderer(sf::RenderWindow& renderWindow)
	:window(renderWindow)
{
}

void PrimitiveRenderer::drawLine(const sf::Vector2f& startPoint, const sf::Vector2f& endPoint, const sf::Color& color, float thickness)
{
	sf::VertexArray line(sf::Lines, 2);
	line[0].position = startPoint;
	line[0].color = color;
	line[1].position = endPoint;
	line[1].color = color;
	window.draw(line);
}

void PrimitiveRenderer::drawRectangle(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color)
{
	sf::RectangleShape rectangle(size);
	rectangle.setPosition(position);
	rectangle.setFillColor(color);
	window.draw(rectangle);
}

void PrimitiveRenderer::drawCircle(const sf::Vector2f& center, float radius, const sf::Color& color)
{
	sf::CircleShape circle(radius);
	circle.setPosition(center - sf::Vector2f(radius, radius));
	circle.setFillColor(color);
	window.draw(circle);
}

void PrimitiveRenderer::drawLineByBresenham(const sf::Vector2f& startPoint, const sf::Vector2f& endPoint, const sf::Color& color , float thickness)
{
    int x1 = static_cast<int>(startPoint.x);
    int y1 = static_cast<int>(startPoint.y);
    int x2 = static_cast<int>(endPoint.x);
    int y2 = static_cast<int>(endPoint.y);

    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;

    int err = dx - dy;

    while (true) {
        sf::RectangleShape pixel({ thickness, thickness });
        pixel.setPosition(x1, y1);
        pixel.setFillColor(color);
        window.draw(pixel);

        if (x1 == x2 && y1 == y2) break;

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}
void PrimitiveRenderer::drawPolyline(const std::vector<Point2D>& points, const sf::Color& color, float thickness, bool useBresenham)
{
    for (size_t i = 0; i < points.size() - 1; i++)
    {
        if (useBresenham) {
            drawLineByBresenham({ points[i].getX(), points[i].getY() }, { points[i + 1].getX(), points[i + 1].getY() }, color, thickness);
        }
        else
        {
            drawLine({ points[i].getX(), points[i].getY() }, { points[i + 1].getX(), points[i + 1].getY() }, color, thickness);
        }
    }
}

void PrimitiveRenderer::drawPolyline(const std::vector<sf::Vector2f>& points, const sf::Color& color, float thickness, bool useBresenham)
{
    for (size_t i = 0; i < points.size() - 1; i++)
    {
        if (useBresenham) {
            drawLineByBresenham(points[i], points[i + 1], color, thickness);
        }
        else
        {
            drawLine(points[i], points[i + 1], color, thickness);
        }
    }
}


void PrimitiveRenderer::drawClosedPolyline(const std::vector<Point2D>& points, const sf::Color& color, float thickness, bool useBresenham)
{
    drawPolyline(points, color, thickness, useBresenham);
    if (points.size() >= 2)
    {
        if (useBresenham) {
            drawLineByBresenham({ points.back().getX(), points.back().getY() }, { points[0].getX(), points[0].getY() }, color, thickness);
        }
        else
        {
            drawLine({ points.back().getX(), points.back().getY() }, { points[0].getX(), points[0].getY() }, color, thickness);
        }
    }
}

void PrimitiveRenderer::drawCircleAlgorithm(int x_center, int y_center, int r, const sf::Color& color)
{
    const float dTheta = 0.01;

    for (float theta = 0;theta<= 2*PI;theta +=dTheta)
    {
        int x = x_center + r * std::cos(theta);
        int y = y_center + r * std::sin(theta);
        putPixel(x, y, color);
    }
}


void PrimitiveRenderer::putPixel(int x, int y, const sf::Color& color)
{
    sf::Vertex point(sf::Vector2f(static_cast<float>(x), static_cast<float>(y)), color);
    window.draw(&point, 1, sf::Points);
}

void PrimitiveRenderer::drawEllipse(float x0, float y0, float RX, float RY, const sf::Color& color)
{
    const float dTheta = 0.001;

    for (float alpha = 0; alpha <= 2* PI; alpha+=dTheta)
    {
        float x = x0 + RX * cos(alpha);
        float y = y0 + RY * sin(alpha);

        putPixel(round(x), round(y), color);
    }
}

void PrimitiveRenderer::drawPolygon(const std::vector<Point2D>& points, const sf::Color& color)
{
    if (points.size() < 3)
    {
        return;
    }
    std::vector<sf::Vector2f> sfPoints;
    for (const auto& point : points)
    {
        sfPoints.push_back({ point.getX(), point.getY() });
    }

    sfPoints.push_back({ points[0].getX(), points[0].getY() });
    drawPolyline(sfPoints, color);
}
