#include "PrimitiveRenderer.h"
// Konstruktor klasy `PrimitiveRenderer` inicjalizuje obiekt z podanym oknem renderowania oraz domy�lnymi
// warto�ciami transformacji (skala, rotacja, translacja).
PrimitiveRenderer::PrimitiveRenderer(sf::RenderWindow& renderWindow)
    :window(renderWindow),
    scale(1.0f, 1.0f),
    useScaleTransform(true),
    useRotationTransform(true)
{
}
// Metoda `setScale` klasy `PrimitiveRenderer` ustawia skal� dla przysz�ych operacji rysowania.
// Przyjmuje warto�ci skali w osiach x i y, co pozwala na skalowanie rysowanych obiekt�w.
PrimitiveRenderer& PrimitiveRenderer::setScale(float sx, float sy)
{
    this->scale.x = sx;
    this->scale.y = sy;
    return *this;
}

// Metoda `setRotation` ustawia k�t rotacji dla przysz�ych operacji rysowania.
// K�t jest podany w radianach, co pozwala na obracanie rysowanych obiekt�w.
PrimitiveRenderer& PrimitiveRenderer::setRotation(float radians)
{
    rotation = radians;
    return *this;
}

// Metoda `setTranslation` ustawia translacj� (przesuni�cie) dla przysz�ych operacji rysowania.
// Przyjmuje warto�ci przesuni�cia w osiach x i y, co pozwala na przesuwanie rysowanych obiekt�w.
PrimitiveRenderer& PrimitiveRenderer::setTranslation(float dx, float dy)
{
    translation.x = dx;
    translation.y = dy;
    return *this;
}

// Metoda `drawLine` rysuje lini� mi�dzy dwoma punktami. Wykorzystuje wcze�niej ustawione transformacje
// (skala, rotacja, translacja) do modyfikacji wygl�du linii.
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

// Metoda `drawLine` rysuje lini� zwi�zane z podanym obiektem `GameObject`. Wykorzystuje obecne
// transformacje i pozycj� obiektu do okre�lenia pocz�tku i ko�ca linii.
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

// Metoda `drawRectangle` rysuje prostok�t o podanej pozycji, rozmiarze i kolorze.
// Tak jak w innych metodach, wykorzystuje wcze�niej ustawione transformacje.
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

// Metoda `drawPhysicsRectangle` rysuje prostok�t reprezentowany przez obiekt `MovingRectangle`.
// Wykorzystuje informacje o pozycji, wymiarach i kolorze prostok�ta oraz stosuje ustawione wcze�niej transformacje.
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

// Metoda `drawCircle` rysuje ko�o o podanym �rodku, promieniu i kolorze. Tak jak w poprzednich metodach,
// stosuje wcze�niej ustawione transformacje.
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

// Metoda `drawPhysicsCircle` rysuje ko�o reprezentowane przez obiekt `MovingCircle`.
// Wykorzystuje informacje o pozycji, promieniu i kolorze ko�a oraz stosuje ustawione wcze�niej transformacje.
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
// Jest to szczeg�lnie przydatne w sytuacjach, gdy potrzebna jest wi�ksza kontrola nad rysowaniem linii,
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

// Metoda `drawPolyline` rysuje lini� �aman� (polilini�) na podstawie serii punkt�w.
// Mo�na wybra�, czy linia ma by� rysowana za pomoc� klasycznego rysowania linii, czy algorytmem Bresenhama.
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

// Metoda `drawClosedPolyline` rysuje zamkni�t� lini� �aman� (polilini�) na podstawie serii punkt�w Point2D.
// Linia jest zamkni�ta poprzez po��czenie ostatniego punktu z pierwszym. Pozwala na wyb�r mi�dzy
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

// Metoda `drawCircleAlgorithm` rysuje ko�o, wykorzystuj�c algorytm rysowania ko�a oparty na r�wnaniu parametrycznym.
// Ko�o jest rysowane poprzez obliczanie punkt�w na jego obwodzie i umieszczanie pojedynczych pikseli w tych miejscach.
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

// Metoda `putPixel` rysuje pojedynczy piksel w okre�lonym miejscu. Jest u�ywana do rysowania bardziej z�o�onych
// kszta�t�w poprzez umieszczanie wielu pojedynczych pikseli.
void PrimitiveRenderer::putPixel(int x, int y, const sf::Color& color)
{
    sf::Vertex point(sf::Vector2f(static_cast<float>(x), static_cast<float>(y)), color);
    window.draw(&point, 1, sf::Points);
}

// Metoda `drawEllipse` rysuje elips� na podstawie zadanych parametr�w: �rodka, promieni w osi X i Y oraz koloru.
// Podobnie jak w przypadku ko�a, elipsa jest rysowana poprzez obliczanie i rysowanie pojedynczych pikseli.
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

// Metoda `drawPolygon` rysuje wielok�t na podstawie serii punkt�w Point2D. Wielok�t jest automatycznie zamkni�ty,
// ��cz�c ostatni punkt z pierwszym, a linie s� rysowane mi�dzy kolejnymi punktami.
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

// Metoda `fillRectangle` rysuje wype�niony prostok�t o okre�lonej pozycji, rozmiarze i kolorze.
void PrimitiveRenderer::fillRectangle(float x, float y, float width, float height, const sf::Color& color)
{
    sf::RectangleShape rectangle(sf::Vector2f(width, height));
    rectangle.setPosition(x, y);
    rectangle.setFillColor(color);
    window.draw(rectangle);
}

// Metoda `fillCircle` rysuje wype�nione ko�o o okre�lonym �rodku, promieniu i kolorze.
void PrimitiveRenderer::fillCircle(float x_center, float y_center, float radius, const sf::Color& color)
{
    sf::CircleShape circle(radius);
    circle.setPosition(x_center - radius, y_center - radius);
    circle.setFillColor(color);
    window.draw(circle);
}

// Metoda `fillPolygon` rysuje wype�niony wielok�t na podstawie serii punkt�w Point2D. Wype�nienie odbywa si�
// poprzez rysowanie sp�jnej, wewn�trznej przestrzeni wielok�ta.
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
// Umo�liwia modyfikacj� po�o�enia punktu zgodnie z aktualnymi ustawieniami transformacji obiektu.
sf::Vector2f PrimitiveRenderer::applyTransform(const sf::Vector2f& point)
{
    sf::Vector2f transformed = point;

    transformed.x = std::cos(rotation) * point.x - std::sin(rotation) * point.y;
    transformed.x = std::sin(rotation) * point.x + std::cos(rotation) * point.y;

    transformed.x *= scale.x;
    transformed.y *= scale.y;

    return transformed;
}

// Metoda `resetTransformation` resetuje wszystkie transformacje (skala, rotacja, translacja) do ich warto�ci domy�lnych.
// Jest to przydatne do przywr�cenia stanu domy�lnego przed kolejnymi operacjami rysowania.
void PrimitiveRenderer::resetTransformation()
{
    scale = sf::Vector2f(1.0f, 1.0f);
    rotation = 0.0f;
    translation = sf::Vector2f(0.0f, 0.0f);
}

// Metoda `enableScaleTransform` w��cza stosowanie transformacji skali dla kolejnych operacji rysowania.
// Pozwala to na skalowanie rysowanych obiekt�w.
void PrimitiveRenderer::enableScaleTransform()
{
    useScaleTransform = true;
}

// Metoda `disableScaleTransform` wy��cza stosowanie transformacji skali dla kolejnych operacji rysowania.
// Dzia�a przeciwnie do metody `enableScaleTransform`, powracaj�c do rysowania bez skalowania.
void PrimitiveRenderer::disableScaleTransform()
{
    useScaleTransform = false;
}

// Metoda `enableRotationTransform` w��cza stosowanie transformacji rotacji dla kolejnych operacji rysowania.
// Pozwala to na obracanie rysowanych obiekt�w.
void PrimitiveRenderer::enableRotationTransform()
{
    useRotationTransform = true;
}

// Metoda `disableRotationTransform` wy��cza stosowanie transformacji rotacji dla kolejnych operacji rysowania.
// Dzia�a przeciwnie do metody `enableRotationTransform`, powracaj�c do rysowania bez obracania.
void PrimitiveRenderer::disableRotationTransform()
{
    useRotationTransform = false;
}

// Metoda `enableTranslationTransform` w��cza stosowanie transformacji translacji (przesuni�cia) dla kolejnych operacji rysowania.
// Pozwala to na przesuwanie rysowanych obiekt�w.
void PrimitiveRenderer::enableTranslationTransform()
{
    useTranslationTransform = true;
}

// Metoda `disableTranslationTransform` wy��cza stosowanie transformacji translacji dla kolejnych operacji rysowania.
// Dzia�a przeciwnie do metody `enableTranslationTransform`, powracaj�c do rysowania bez przesuwania.
void PrimitiveRenderer::disableTranslationTransform()
{
    useTranslationTransform = false;
}
