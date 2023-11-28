#include "GameObject.h"
// Statyczna zmienna `windowSize` klasy `GameObject` przechowuje wymiary okna, wspólne dla wszystkich obiektów tej klasy.
sf::Vector2u GameObject::windowSize = sf::Vector2u(800, 600);
// Metoda statyczna `setWindowSize` umo¿liwia ustawienie wymiarów okna dla wszystkich obiektów `GameObject`.
void GameObject::setWindowSize(const sf::Vector2u& size)
{
	windowSize = size;
}
// Metoda statyczna `getWindowSize` zwraca aktualne wymiary okna dla obiektów `GameObject`.
sf::Vector2u GameObject::getWindowSize()
{
	return windowSize;
}
// Konstruktor klasy `GameObject` inicjalizuje obiekt z podstawowymi parametrami fizycznymi,
// takimi jak pozycja, prêdkoœæ i przyspieszenie, z domyœlnymi wartoœciami.
GameObject::GameObject(float x = 0, float y = 0)
	:x(x),y(y),vx(0),vy(0),ax(0),ay(0)
{
}
// Metoda `update` aktualizuje stan obiektu na podstawie up³ywu czasu, obliczaj¹c now¹ pozycjê na podstawie prêdkoœci
// i przyspieszenia.
void GameObject::update(float deltaTime)
{
	vx += ax * deltaTime;
	vy += ay * deltaTime;
	x += vx * deltaTime;
	y += vy * deltaTime;
}
// Destruktor klasy `GameObject` wykonuje niezbêdne czynnoœci podczas niszczenia obiektu klasy `GameObject`.
GameObject::~GameObject()
{
}
