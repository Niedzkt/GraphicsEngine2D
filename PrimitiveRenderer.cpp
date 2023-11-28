#include "PrimitiveRenderer.h"
// Konstruktor klasy `PrimitiveRenderer` inicjalizuje obiekt z podanym oknem renderowania oraz domyœlnymi
// wartoœciami transformacji (skala, rotacja, translacja).
PrimitiveRenderer::PrimitiveRenderer(sf::RenderWindow& renderWindow)
    :window(renderWindow),
    scale(1.0f, 1.0f),
    useScaleTransform(true),
    useRotationTransform(true)
{
}
// Metoda `setScale` klasy `PrimitiveRenderer` ustawia skalê dla przysz³ych operacji rysowania.
// Przyjmuje wartoœci skali w osiach x i y, co pozwala na skalowanie rysowanych obiektów.
PrimitiveRenderer& PrimitiveRenderer::setScale(float sx, float sy)
{
    this->scale.x = sx;
    this->scale.y = sy;
    return *this;
}

// Metoda `setRotation` ustawia k¹t rotacji dla przysz³ych operacji rysowania.
// K¹t jest podany w radianach, co pozwala na obracanie rysowanych obiektów.
PrimitiveRenderer& PrimitiveRenderer::setRotation(float radians)
{
    rotation = radians;
    return *this;
}

// Metoda `setTranslation` ustawia translacjê (przesuniêcie) dla przysz³ych operacji rysowania.
// Przyjmuje wartoœci przesuniêcia w osiach x i y, co pozwala na przesuwanie rysowanych obiektów.
PrimitiveRenderer& PrimitiveRenderer::setTranslation(float dx, float dy)
{
    translation.x = dx;
    translation.y = dy;
    return *this;
}

// Metoda `drawLine` rysuje liniê miêdzy dwoma punktami. Wykorzystuje wczeœniej ustawione transformacje
// (skala, rotacja, translacja) do modyfikacji wygl¹du linii.
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

// Metoda `drawLine` rysuje liniê zwi¹zane z podanym obiektem `GameObject`. Wykorzystuje obecne
// transformacje i pozycjê obiektu do okreœlenia pocz¹tku i koñca linii.
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

// Metoda `drawRectangle` rysuje prostok¹t o podanej pozycji, rozmiarze i kolorze.
// Tak jak w innych metodach, wykorzystuje wczeœniej ustawione transformacje.
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

// Metoda `drawPhysicsRectangle` rysuje prostok¹t reprezentowany przez obiekt `MovingRectangle`.
// Wykorzystuje informacje o pozycji, wymiarach i kolorze prostok¹ta oraz stosuje ustawione wczeœniej transformacje.
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

// Metoda `drawCircle` rysuje ko³o o podanym œrodku, promieniu i kolorze. Tak jak w poprzednich metodach,
// stosuje wczeœniej ustawione transformacje.
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

// Metoda `drawPhysicsCircle` rysuje ko³o reprezentowane przez obiekt `MovingCircle`.
// Wykorzystuje informacje o pozycji, promieniu i kolorze ko³a oraz stosuje ustawione wczeœniej transformacje.
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

// Metoda `drawLineByBresenham` implementuje algorytm Bresenhama do rysowania linii piksel po pikselu.
// Jest to szczególnie przydatne w sytuacjach, gdy potrzebna jest wiêksza kontrola nad rysowaniem linii,
// np. w grafice pikselowej.
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

// Metoda `drawPolyline` rysuje liniê ³aman¹ (poliliniê) na podstawie serii punktów.
// Mo¿na wybraæ, czy linia ma byæ rysowana za pomoc¹ klasycznego rysowania linii, czy algorytmem Bresenhama.
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

// Analogicznie, ta wersja metody `drawPolyline` akceptuje punkty w formacie `sf::Vector2f`.
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

// Metoda `drawClosedPolyline` rysuje zamkniêt¹ liniê ³aman¹ (poliliniê) na podstawie serii punktów Point2D.
// Linia jest zamkniêta poprzez po³¹czenie ostatniego punktu z pierwszym. Pozwala na wybór miêdzy
// klasycznym rysowaniem linii a algorytmem Bresenhama.
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

// Metoda `drawCircleAlgorithm` rysuje ko³o, wykorzystuj¹c algorytm rysowania ko³a oparty na równaniu parametrycznym.
// Ko³o jest rysowane poprzez obliczanie punktów na jego obwodzie i umieszczanie pojedynczych pikseli w tych miejscach.
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

// Metoda `putPixel` rysuje pojedynczy piksel w okreœlonym miejscu. Jest u¿ywana do rysowania bardziej z³o¿onych
// kszta³tów poprzez umieszczanie wielu pojedynczych pikseli.
void PrimitiveRenderer::putPixel(int x, int y, const sf::Color& color)
{
    sf::Vertex point(sf::Vector2f(static_cast<float>(x), static_cast<float>(y)), color);
    window.draw(&point, 1, sf::Points);
}

// Metoda `drawEllipse` rysuje elipsê na podstawie zadanych parametrów: œrodka, promieni w osi X i Y oraz koloru.
// Podobnie jak w przypadku ko³a, elipsa jest rysowana poprzez obliczanie i rysowanie pojedynczych pikseli.
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

// Metoda `drawPolygon` rysuje wielok¹t na podstawie serii punktów Point2D. Wielok¹t jest automatycznie zamkniêty,
// ³¹cz¹c ostatni punkt z pierwszym, a linie s¹ rysowane miêdzy kolejnymi punktami.
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

// Metoda `fillRectangle` rysuje wype³niony prostok¹t o okreœlonej pozycji, rozmiarze i kolorze.
void PrimitiveRenderer::fillRectangle(float x, float y, float width, float height, const sf::Color& color)
{
    sf::RectangleShape rectangle(sf::Vector2f(width, height));
    rectangle.setPosition(x, y);
    rectangle.setFillColor(color);
    window.draw(rectangle);
}

// Metoda `fillCircle` rysuje wype³nione ko³o o okreœlonym œrodku, promieniu i kolorze.
void PrimitiveRenderer::fillCircle(float x_center, float y_center, float radius, const sf::Color& color)
{
    sf::CircleShape circle(radius);
    circle.setPosition(x_center - radius, y_center - radius);
    circle.setFillColor(color);
    window.draw(circle);
}

// Metoda `fillPolygon` rysuje wype³niony wielok¹t na podstawie serii punktów Point2D. Wype³nienie odbywa siê
// poprzez rysowanie spójnej, wewnêtrznej przestrzeni wielok¹ta.
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

// Metoda `applyTransform` stosuje zdefiniowane transformacje (skala, rotacja) do danego punktu.
// Umo¿liwia modyfikacjê po³o¿enia punktu zgodnie z aktualnymi ustawieniami transformacji obiektu.
sf::Vector2f PrimitiveRenderer::applyTransform(const sf::Vector2f& point)
{
    sf::Vector2f transformed = point;

    transformed.x = std::cos(rotation) * point.x - std::sin(rotation) * point.y;
    transformed.x = std::sin(rotation) * point.x + std::cos(rotation) * point.y;

    transformed.x *= scale.x;
    transformed.y *= scale.y;

    return transformed;
}

// Metoda `resetTransformation` resetuje wszystkie transformacje (skala, rotacja, translacja) do ich wartoœci domyœlnych.
// Jest to przydatne do przywrócenia stanu domyœlnego przed kolejnymi operacjami rysowania.
void PrimitiveRenderer::resetTransformation()
{
    scale = sf::Vector2f(1.0f, 1.0f);
    rotation = 0.0f;
    translation = sf::Vector2f(0.0f, 0.0f);
}

// Metoda `enableScaleTransform` w³¹cza stosowanie transformacji skali dla kolejnych operacji rysowania.
// Pozwala to na skalowanie rysowanych obiektów.
void PrimitiveRenderer::enableScaleTransform()
{
    useScaleTransform = true;
}

// Metoda `disableScaleTransform` wy³¹cza stosowanie transformacji skali dla kolejnych operacji rysowania.
// Dzia³a przeciwnie do metody `enableScaleTransform`, powracaj¹c do rysowania bez skalowania.
void PrimitiveRenderer::disableScaleTransform()
{
    useScaleTransform = false;
}

// Metoda `enableRotationTransform` w³¹cza stosowanie transformacji rotacji dla kolejnych operacji rysowania.
// Pozwala to na obracanie rysowanych obiektów.
void PrimitiveRenderer::enableRotationTransform()
{
    useRotationTransform = true;
}

// Metoda `disableRotationTransform` wy³¹cza stosowanie transformacji rotacji dla kolejnych operacji rysowania.
// Dzia³a przeciwnie do metody `enableRotationTransform`, powracaj¹c do rysowania bez obracania.
void PrimitiveRenderer::disableRotationTransform()
{
    useRotationTransform = false;
}

// Metoda `enableTranslationTransform` w³¹cza stosowanie transformacji translacji (przesuniêcia) dla kolejnych operacji rysowania.
// Pozwala to na przesuwanie rysowanych obiektów.
void PrimitiveRenderer::enableTranslationTransform()
{
    useTranslationTransform = true;
}

// Metoda `disableTranslationTransform` wy³¹cza stosowanie transformacji translacji dla kolejnych operacji rysowania.
// Dzia³a przeciwnie do metody `enableTranslationTransform`, powracaj¹c do rysowania bez przesuwania.
void PrimitiveRenderer::disableTranslationTransform()
{
    useTranslationTransform = false;
}
