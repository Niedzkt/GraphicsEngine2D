#include "GameObject.h"
// Statyczna zmienna `windowSize` klasy `GameObject` przechowuje wymiary okna, wsp�lne dla wszystkich obiekt�w tej klasy.
sf::Vector2u GameObject::windowSize = sf::Vector2u(800, 600);
// Metoda statyczna `setWindowSize` umo�liwia ustawienie wymiar�w okna dla wszystkich obiekt�w `GameObject`.
void GameObject::setWindowSize(const sf::Vector2u& size)
{
	windowSize = size;
}
// Metoda statyczna `getWindowSize` zwraca aktualne wymiary okna dla obiekt�w `GameObject`.
sf::Vector2u GameObject::getWindowSize()
{
	return windowSize;
}
// Konstruktor klasy `GameObject` inicjalizuje obiekt z podstawowymi parametrami fizycznymi,
// takimi jak pozycja, pr�dko�� i przyspieszenie, z domy�lnymi warto�ciami.
GameObject::GameObject(float x = 0, float y = 0)
	:x(x),y(y),vx(0),vy(0),ax(0),ay(0)
{
}
// Metoda `update` aktualizuje stan obiektu na podstawie up�ywu czasu, obliczaj�c now� pozycj� na podstawie pr�dko�ci
// i przyspieszenia.
void GameObject::update(float deltaTime)
{
	vx += ax * deltaTime;
	vy += ay * deltaTime;
	x += vx * deltaTime;
	y += vy * deltaTime;
}
// Destruktor klasy `GameObject` wykonuje niezb�dne czynno�ci podczas niszczenia obiektu klasy `GameObject`.
GameObject::~GameObject()
{
}
