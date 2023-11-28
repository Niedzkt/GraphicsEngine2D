#include "AnimatedBitmap.h"
// Konstruktor klasy `AnimatedBitmap` inicjalizuje obiekt z podstawowymi wartoœciami transformacji,
// oraz wartoœciami specyficznymi dla animacji, takimi jak czas trwania klatki, czas up³yniêty i bie¿¹ca klatka.
// Próbuje równie¿ za³adowaæ animacjê z podanej œcie¿ki i ustawia jej pozycjê.
AnimatedBitmap::AnimatedBitmap(const std::string& filePath, const sf::Vector2i& frameSize, int frameCount, float frameDuration, const sf::Vector2f& position)
	:scale(1.0f,1.0f), rotation(0), translation(0,0), frameDuration(frameDuration), elapsedTime(0), currentFrame(0)
{
	if (loadAnimation(filePath, frameSize, frameCount, frameDuration))
	{
		setPosition(position);
	}
}
// Metoda `loadAnimation` próbuje za³adowaæ teksturê animacji z pliku. Jeœli za³adowanie siê nie powiedzie,
// wyœwietla b³¹d. W przypadku powodzenia, inicjalizuje klatki animacji i ustawia teksturê dla sprite'a.
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
// Metoda `update` aktualizuje stan animacji na podstawie up³ywu czasu. Prze³¹cza klatki animacji,
// kiedy up³ynie okreœlony czas trwania klatki.
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
// Metoda `setPosition` ustawia pozycjê sprite'a animacji, uwzglêdniaj¹c bie¿¹c¹ translacjê.
AnimatedBitmap& AnimatedBitmap::setPosition(const sf::Vector2f& position)
{
	sprite.setPosition(position + translation);
	return *this;
}
// Metoda `setScale` ustawia skalê sprite'a animacji. Ta skala jest stosowana do oryginalnych wymiarów klatek animacji.
AnimatedBitmap& AnimatedBitmap::setScale(float sx, float sy)
{
	scale.x = sx;
	scale.y = sy;
	sprite.setScale(scale);
	return *this;
}
// Metoda `setRotation` ustawia rotacjê sprite'a animacji. Rotacja jest podana w radianach i konwertowana na stopnie.
AnimatedBitmap& AnimatedBitmap::setRotation(float radians)
{
	rotation = radians;
	sprite.setRotation(rotation * 180 / PI);
	return *this;
}
// Metoda `setTranslation` ustawia translacjê sprite'a animacji, która jest dodawana do bie¿¹cej pozycji sprite'a.
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
