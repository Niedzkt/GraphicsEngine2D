#include "BitmapRenderer.h"

BitmapRenderer::BitmapRenderer(const std::string& filePath, const sf::Vector2f& position)
	:scale(1.0f,1.0f), rotation(0), translation(0,0)
{
	if (loadBitmap(filePath)) {
		setPosition(position);
	}
}

bool BitmapRenderer::loadBitmap(const std::string& filePath)
{
	if (!texture.loadFromFile(filePath)) {
		std::cout << "ERROR::BITMAP TEXTURE DOES NOT EXISTS" << std::endl;
		return false;
	}
	sprite.setTexture(texture);
	return true;
}

BitmapRenderer& BitmapRenderer::setPosition(const sf::Vector2f& position)
{
	sprite.setPosition(position + translation);
	return *this;
}

BitmapRenderer& BitmapRenderer::setScale(float sx, float sy)
{
	scale.x = sx;
	scale.y = sy;
	sprite.setScale(scale);
	return *this;
}

BitmapRenderer& BitmapRenderer::setRotation(float radians)
{
	rotation = radians;
	sprite.setRotation(rotation * 180 / PI);
	return *this;
}

BitmapRenderer& BitmapRenderer::setTranslation(float dx, float dy)
{
	translation.x = dx;
	translation.y = dy;
	sprite.setPosition(sprite.getPosition() + translation);
	return *this;
}

void BitmapRenderer::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}
