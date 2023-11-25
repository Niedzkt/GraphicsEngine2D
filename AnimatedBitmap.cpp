#include "AnimatedBitmap.h"

AnimatedBitmap::AnimatedBitmap(const std::string& filePath, const sf::Vector2i& frameSize, int frameCount, float frameDuration, const sf::Vector2f& position)
	:scale(1.0f,1.0f), rotation(0), translation(0,0), frameDuration(frameDuration), elapsedTime(0), currentFrame(0)
{
	if (loadAnimation(filePath, frameSize, frameCount, frameDuration))
	{
		setPosition(position);
	}
}

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

AnimatedBitmap& AnimatedBitmap::setPosition(const sf::Vector2f& position)
{
	sprite.setPosition(position + translation);
	return *this;
}

AnimatedBitmap& AnimatedBitmap::setScale(float sx, float sy)
{
	scale.x = sx;
	scale.y = sy;
	sprite.setScale(scale);
	return *this;
}

AnimatedBitmap& AnimatedBitmap::setRotation(float radians)
{
	rotation = radians;
	sprite.setRotation(rotation * 180 / PI);
	return *this;
}

AnimatedBitmap& AnimatedBitmap::setTranslation(float dx, float dy)
{
	translation.x = dx;
	translation.y = dy;
	sprite.setPosition(sprite.getPosition() + translation);
	return *this;
}

void AnimatedBitmap::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}
