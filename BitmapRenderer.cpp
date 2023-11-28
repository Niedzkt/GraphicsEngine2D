#include "BitmapRenderer.h"

// Konstruktor klasy `BitmapRenderer` inicjalizuje obiekt z podstawowymi warto�ciami transformacji,
// takimi jak skala, rotacja i translacja. Pr�buje r�wnie� za�adowa� bitmap� z podanej �cie�ki i
// ustawia jej pozycj�.
BitmapRenderer::BitmapRenderer(const std::string& filePath, const sf::Vector2f& position)
	:scale(1.0f,1.0f), rotation(0), translation(0,0)
{
	if (loadBitmap(filePath)) {
		setPosition(position);
	}
}

// Metoda `loadBitmap` pr�buje za�adowa� tekstur� bitmapy z pliku. Je�li za�adowanie si� nie powiedzie,
// wy�wietla b��d. W przypadku powodzenia, tekstura jest przypisywana do sprite'a.
bool BitmapRenderer::loadBitmap(const std::string& filePath)
{
	if (!texture.loadFromFile(filePath)) {
		std::cout << "ERROR::BITMAP TEXTURE DOES NOT EXISTS" << std::endl;
		return false;
	}
	sprite.setTexture(texture);
	return true;
}

// Metoda `setPosition` ustawia pozycj� sprite'a bitmapy, uwzgl�dniaj�c bie��c� translacj�.
BitmapRenderer& BitmapRenderer::setPosition(const sf::Vector2f& position)
{
	sprite.setPosition(position + translation);
	return *this;
}
// Metoda `setScale` ustawia skal� sprite'a bitmapy. Ta skala jest stosowana do oryginalnych wymiar�w bitmapy.
BitmapRenderer& BitmapRenderer::setScale(float sx, float sy)
{
	scale.x = sx;
	scale.y = sy;
	sprite.setScale(scale);
	return *this;
}
// Metoda `setRotation` ustawia rotacj� sprite'a bitmapy. Rotacja jest podana w radianach i konwertowana na stopnie.
BitmapRenderer& BitmapRenderer::setRotation(float radians)
{
	rotation = radians;
	sprite.setRotation(rotation * 180 / PI);
	return *this;
}
// Metoda `setTranslation` ustawia translacj� sprite'a bitmapy, kt�ra jest dodawana do bie��cej pozycji sprite'a.
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
