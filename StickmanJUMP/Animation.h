#pragma once
#include <SFML/Graphics.hpp>

class Animation
{
public:
	Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
	virtual ~Animation() {};

	void update(int row, float deltaTime, bool fromZero);
	void update(int row, float deltaTime);

	sf::IntRect uvRect;

private:
	sf::Vector2u imageCount;
	sf::Vector2u currentImage;

	float totalTime;
	float switchTime;
};

