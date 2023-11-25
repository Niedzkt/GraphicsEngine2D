#include "PrimitiveRenderer.h"

PrimitiveRenderer::PrimitiveRenderer(sf::RenderWindow& renderWindow)
    :window(renderWindow),
    scale(1.0f, 1.0f),
    useScaleTransform(true),
    useRotationTransform(true)
{
}

PrimitiveRenderer& PrimitiveRenderer::setScale(float sx, float sy)
{
    this->scale.x = sx;
    this->scale.y = sy;
    return *this;
}

PrimitiveRenderer& PrimitiveRenderer::setRotation(float radians)
{
    rotation = radians;
    return *this;
}

PrimitiveRenderer& PrimitiveRenderer::setTranslation(float dx, float dy)
{
    translation.x = dx;
    translation.y = dy;
    return *this;
}

void PrimitiveRenderer::drawLine(const sf::Vector2f& startPoint, const sf::Vector2f& endPoint, const sf::Color& color, float thickness)
{
    sf::Vector2f center = (startPoint + endPoint) * 0.5f;

    sf::Vector2f finalStartPoint = startPoint - center;
    sf::Vector2f finalEndPoint = endPoint - center;

    if (useRotationTransform) {
        float s = sin(rotation);
        float c = cos(rotation);

        sf::Vector2f rotatedStartPoint(finalStartPoint.x * c - finalStartPoint.y * s,
            finalStartPoint.x * s + finalStartPoint.y * c);
        sf::Vector2f rotatedEndPoint(finalEndPoint.x * c - finalEndPoint.y * s,
            finalEndPoint.x * s + finalEndPoint.y * c);

        finalStartPoint = rotatedStartPoint;
        finalEndPoint = rotatedEndPoint;
    }

    if (useScaleTransform) {
        finalStartPoint = sf::Vector2f(finalStartPoint.x * scale.x, finalStartPoint.y * scale.y);
        finalEndPoint = sf::Vector2f(finalEndPoint.x * scale.x, finalEndPoint.y * scale.y);
    }
    else {
        finalStartPoint = startPoint;
        finalEndPoint = endPoint;
    }

    if (useTranslationTransform)
    {
        finalStartPoint += translation;
        finalEndPoint += translation;
    }
    else
    {
        finalStartPoint += center;
        finalEndPoint += center;
    }

    sf::VertexArray line(sf::Lines, 2);
    line[0].position = finalStartPoint;
    line[0].color = color;
    line[1].position = finalEndPoint;
    line[1].color = color;
	window.draw(line);

    resetTransformation();
}

void PrimitiveRenderer::drawLine(const GameObject& object, const sf::Color& color, float thickness, float lenght)
{
    sf::Vector2f startPoint(object.x, object.y);
    sf::Vector2f endPoint(startPoint.x + lenght, startPoint.y);

    sf::Vector2f center = (startPoint + endPoint) * 0.5f;

    sf::Vector2f finalStartPoint = startPoint - center;
    sf::Vector2f finalEndPoint = endPoint - center;
    
    if (useScaleTransform)
    {
        finalStartPoint = sf::Vector2f(finalStartPoint.x * scale.x, finalStartPoint.y * scale.y);
        finalStartPoint = sf::Vector2f(finalEndPoint.x * scale.x, finalEndPoint.y * scale.y);
    }

    finalStartPoint += center;
    finalEndPoint += center;

    drawLine(startPoint, endPoint, color, thickness);
}

void PrimitiveRenderer::drawRectangle(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color)
{
    sf::RectangleShape rectangle(size);

    if (useScaleTransform) {
        rectangle.setScale(scale.x, scale.y);
    }
    
    if (useRotationTransform)
    {
        rectangle.setRotation(rotation * 180 / PI);
        rectangle.setOrigin(size.x / 2, size.y / 2);
    }
    if (useTranslationTransform)
    {
        rectangle.setPosition(position + translation);
    }
    else
    {
        rectangle.setPosition(position);
    }

    rectangle.setFillColor(color);
    window.draw(rectangle);

    resetTransformation();
}

void PrimitiveRenderer::drawPhysicsRectangle(const MovingRectangle& rectangle)
{
    sf::RectangleShape shape(sf::Vector2f(rectangle.getWidth(), rectangle.getHeight()));

    shape.setPosition(rectangle.x, rectangle.y);
    shape.setFillColor(rectangle.getColor());

    if (useScaleTransform) {
        shape.setScale(scale.x, scale.y);
    }

    if (useRotationTransform) {
        shape.setRotation(rotation * 180 / PI);
        shape.setOrigin(rectangle.getWidth() / 2, rectangle.getHeight() / 2);
    }

    if (useTranslationTransform) {
        shape.setPosition(shape.getPosition() + translation);
    }

    window.draw(shape);

    resetTransformation();
}

void PrimitiveRenderer::drawCircle(const sf::Vector2f& center, float radius, const sf::Color& color)
{
    sf::CircleShape circle(radius);

    if (useScaleTransform) {
        circle.setScale(scale.x, scale.y);
    }

    if (useRotationTransform)
    {
        circle.setRotation(rotation * 180 / PI);
        circle.setOrigin(radius * scale.x, radius * scale.y);
    }

    if (useTranslationTransform) {
        circle.setPosition(center + translation - sf::Vector2f(radius * scale.x, radius * scale.y));

    }
    else
    {
        circle.setPosition(center);
    }

    circle.setFillColor(color);
    window.draw(circle);

    resetTransformation();
}

void PrimitiveRenderer::drawPhysicsCircle(const MovingCircle& circle)
{
    sf::CircleShape shape(circle.getRadius());

    shape.setPosition(circle.x, circle.y);
    shape.setFillColor(circle.getColor());

    if (useScaleTransform) {
        shape.setScale(scale.x, scale.y);
    }

    if (useRotationTransform) {
        shape.setRotation(rotation * 180 / PI);
        shape.setOrigin(circle.getRadius() * scale.x, circle.getRadius() * scale.y);
    }

    if (useTranslationTransform) {
        shape.setPosition(shape.getPosition() + translation);
    }

    window.draw(shape);

    resetTransformation();
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

void PrimitiveRenderer::drawEllipse(const GameObject& object, float x0, float y0, float RX, float RY, const sf::Color& color)
{
    /*TODO*/
    drawEllipse(x0, y0, RX, RY, color);
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

void PrimitiveRenderer::fillRectangle(float x, float y, float width, float height, const sf::Color& color)
{
    sf::RectangleShape rectangle(sf::Vector2f(width, height));
    rectangle.setPosition(x, y);
    rectangle.setFillColor(color);
    window.draw(rectangle);
}

void PrimitiveRenderer::fillCircle(float x_center, float y_center, float radius, const sf::Color& color)
{
    sf::CircleShape circle(radius);
    circle.setPosition(x_center - radius, y_center - radius);
    circle.setFillColor(color);
    window.draw(circle);
}

void PrimitiveRenderer::fillPolygon(const std::vector<Point2D>& points, const sf::Color& color)
{
    sf::ConvexShape polygon;
    polygon.setPointCount(points.size());
    for (size_t i = 0; i < points.size(); i++)
    {
        polygon.setPoint(i, sf::Vector2f(points[i].getX(), points[i].getY()));
    }
    polygon.setFillColor(color);
    window.draw(polygon);
}

sf::Vector2f PrimitiveRenderer::applyTransform(const sf::Vector2f& point)
{
    sf::Vector2f transformed = point;

    transformed.x = std::cos(rotation) * point.x - std::sin(rotation) * point.y;
    transformed.x = std::sin(rotation) * point.x + std::cos(rotation) * point.y;

    transformed.x *= scale.x;
    transformed.y *= scale.y;

    return transformed;
}

void PrimitiveRenderer::resetTransformation()
{
    scale = sf::Vector2f(1.0f, 1.0f);
    rotation = 0.0f;
    translation = sf::Vector2f(0.0f, 0.0f);
}

void PrimitiveRenderer::enableScaleTransform()
{
    useScaleTransform = true;
}

void PrimitiveRenderer::disableScaleTransform()
{
    useScaleTransform = false;
}

void PrimitiveRenderer::enableRotationTransform()
{
    useRotationTransform = true;
}

void PrimitiveRenderer::disableRotationTransform()
{
    useRotationTransform = false;
}

void PrimitiveRenderer::enableTranslationTransform()
{
    useTranslationTransform = true;
}

void PrimitiveRenderer::disableTranslationTransform()
{
    useTranslationTransform = false;
}
