#include "AnimatedBitmap.h"
// Konstruktor klasy `AnimatedBitmap` inicjalizuje obiekt z podstawowymi warto�ciami transformacji,
// oraz warto�ciami specyficznymi dla animacji, takimi jak czas trwania klatki, czas up�yni�ty i bie��ca klatka.
// Pr�buje r�wnie� za�adowa� animacj� z podanej �cie�ki i ustawia jej pozycj�.
AnimatedBitmap::AnimatedBitmap(const std::string& filePath, const sf::Vector2i& frameSize, int frameCount, float frameDuration, const sf::Vector2f& position)
	:scale(1.0f,1.0f), rotation(0), translation(0,0), frameDuration(frameDuration), elapsedTime(0), currentFrame(0)
{
	if (loadAnimation(filePath, frameSize, frameCount, frameDuration))
	{
		setPosition(position);
	}
}
// Metoda `loadAnimation` pr�buje za�adowa� tekstur� animacji z pliku. Je�li za�adowanie si� nie powiedzie,
// wy�wietla b��d. W przypadku powodzenia, inicjalizuje klatki animacji i ustawia tekstur� dla sprite'a.
bool AnimatedBitmap::loadAnimation(const std::string& filePath, const sf::Vector2i& frameSize, int frameCount, float frameDuration)
{
	if (!texture.loadFromFile(filePath))
	{
		std::cout << "ERROR::ANIMATED BITMAP TEXTURE DOES NOT EXISTS" << std::endl;
		return false;
	}

	frames.clear();
	for (int i = 0; i < frameCount; i++)
	{
		frames.emplace_back(sf::IntRect(i * frameSize.x, 0, frameSize.x, frameSize.y));
	}
	sprite.setTexture(texture);
	sprite.setTextureRect(frames[0]);
	return true;
}
// Metoda `update` aktualizuje stan animacji na podstawie up�ywu czasu. Prze��cza klatki animacji,
// kiedy up�ynie okre�lony czas trwania klatki.
void AnimatedBitmap::update(float deltaTime)
{
	elapsedTime += deltaTime;
	if (elapsedTime>=frameDuration)
	{
		elapsedTime -= frameDuration;
		currentFrame = (currentFrame + 1) % frames.size();
		sprite.setTextureRect(frames[currentFrame]);
	}
}
// Metoda `setPosition` ustawia pozycj� sprite'a animacji, uwzgl�dniaj�c bie��c� translacj�.
AnimatedBitmap& AnimatedBitmap::setPosition(const sf::Vector2f& position)
{
	sprite.setPosition(position + translation);
	return *this;
}
// Metoda `setScale` ustawia skal� sprite'a animacji. Ta skala jest stosowana do oryginalnych wymiar�w klatek animacji.
AnimatedBitmap& AnimatedBitmap::setScale(float sx, float sy)
{
	scale.x = sx;
	scale.y = sy;
	sprite.setScale(scale);
	return *this;
}
// Metoda `setRotation` ustawia rotacj� sprite'a animacji. Rotacja jest podana w radianach i konwertowana na stopnie.
AnimatedBitmap& AnimatedBitmap::setRotation(float radians)
{
	rotation = radians;
	sprite.setRotation(rotation * 180 / PI);
	return *this;
}
// Metoda `setTranslation` ustawia translacj� sprite'a animacji, kt�ra jest dodawana do bie��cej pozycji sprite'a.
AnimatedBitmap& AnimatedBitmap::setTranslation(float dx, float dy)
{
	translation.x = dx;
	translation.y = dy;
	sprite.setPosition(sprite.getPosition() + translation);
	return *this;
}
// Metoda `draw` rysuje sprite animacji w oknie renderowania SFML.
void AnimatedBitmap::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}
