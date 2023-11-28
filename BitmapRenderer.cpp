#include "BitmapRenderer.h"

// Konstruktor klasy `BitmapRenderer` inicjalizuje obiekt z podstawowymi wartoœciami transformacji,
// takimi jak skala, rotacja i translacja. Próbuje równie¿ za³adowaæ bitmapê z podanej œcie¿ki i
// ustawia jej pozycjê.
BitmapRenderer::BitmapRenderer(const std::string& filePath, const sf::Vector2f& position)
	:scale(1.0f,1.0f), rotation(0), translation(0,0)
{
	if (loadBitmap(filePath)) {
		setPosition(position);
	}
}

// Metoda `loadBitmap` próbuje za³adowaæ teksturê bitmapy z pliku. Jeœli za³adowanie siê nie powiedzie,
// wyœwietla b³¹d. W przypadku powodzenia, tekstura jest przypisywana do sprite'a.
bool BitmapRenderer::loadBitmap(const std::string& filePath)
{
	if (!texture.loadFromFile(filePath)) {
		std::cout << "ERROR::BITMAP TEXTURE DOES NOT EXISTS" << std::endl;
		return false;
	}
	sprite.setTexture(texture);
	return true;
}

// Metoda `setPosition` ustawia pozycjê sprite'a bitmapy, uwzglêdniaj¹c bie¿¹c¹ translacjê.
BitmapRenderer& BitmapRenderer::setPosition(const sf::Vector2f& position)
{
	sprite.setPosition(position + translation);
	return *this;
}
// Metoda `setScale` ustawia skalê sprite'a bitmapy. Ta skala jest stosowana do oryginalnych wymiarów bitmapy.
BitmapRenderer& BitmapRenderer::setScale(float sx, float sy)
{
	scale.x = sx;
	scale.y = sy;
	sprite.setScale(scale);
	return *this;
}
// Metoda `setRotation` ustawia rotacjê sprite'a bitmapy. Rotacja jest podana w radianach i konwertowana na stopnie.
BitmapRenderer& BitmapRenderer::setRotation(float radians)
{
	rotation = radians;
	sprite.setRotation(rotation * 180 / PI);
	return *this;
}
// Metoda `setTranslation` ustawia translacjê sprite'a bitmapy, która jest dodawana do bie¿¹cej pozycji sprite'a.
BitmapRenderer& BitmapRenderer::setTranslation(float dx, float dy)
{
	translation.x = dx;
	translation.y = dy;
	sprite.setPosition(sprite.getPosition() + translation);
	return *this;
}
// Metoda `draw` rysuje sprite bitmapy w oknie renderowania SFML.
void BitmapRenderer::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}
