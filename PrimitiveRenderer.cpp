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

void PrimitiveRenderer::drawCircleBresenham(int x_center, int y_center, int r, const sf::Color& color)
{
    int x = 0, y = r;
    int d = 3 - 2 * r;

    putPixel(x_center + x, y_center - y, color);
    putPixel(x_center - x, y_center - y, color);
    putPixel(x_center + x, y_center + y, color);
    putPixel(x_center - x, y_center + y, color);
    putPixel(x_center + y, y_center - x, color);
    putPixel(x_center - y, y_center - x, color);
    putPixel(x_center + y, y_center + x, color);
    putPixel(x_center - y, y_center + x, color);

    while (y>=x)
    {
        x++;

        if (d>0)
        {
            y--;
            d = d + 4 * (x - y) + 10;
        }
        else
        {
            d = d + 4 * x + 6;

            putPixel(x_center + x, y_center - y, color);
            putPixel(x_center - x, y_center - y, color);
            putPixel(x_center + x, y_center + y, color);
            putPixel(x_center - x, y_center + y, color);
            putPixel(x_center + y, y_center - x, color);
            putPixel(x_center - y, y_center - x, color);
            putPixel(x_center + y, y_center + x, color);
            putPixel(x_center - y, y_center + x, color);
        }
    }
}

void PrimitiveRenderer::putPixel(int x, int y, const sf::Color& color)
{
    sf::Vertex point(sf::Vector2f(static_cast<float>(x), static_cast<float>(y)), color);
    window.draw(&point, 1, sf::Points);
}


