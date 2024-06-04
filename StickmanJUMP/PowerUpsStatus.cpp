#include "PowerUpsStatus.h"

PowerUpsStatus::PowerUpsStatus(PowerUpType type)
{
	selectedImage.x = 0;

	if (type == ScoreMultiplayer) this->selectedImage.y = 0;
	else if (type == Shield) this->selectedImage.y = 1;

	this->texture.loadFromFile("Graphics/powerUpsStatus.png");

	this->uvRect.width = this->texture.getSize().x / float(imageCount.x);
	this->uvRect.height = this->texture.getSize().y / float(imageCount.y);

	uvRect.left = selectedImage.x * uvRect.width;
	uvRect.top = selectedImage.y * uvRect.height;

	this->body.setTexture(&this->texture);
	this->body.setSize(sf::Vector2f(40.f, 40.f));
	this->body.setTextureRect(this->uvRect);
	this->body.setOrigin(body.getSize().x / 2.f, body.getGlobalBounds().height);
	this->body.setPosition(30.f, 130.f);
}

void PowerUpsStatus::setPosition(int row)
{
	this->body.setPosition(30.f + (41.f * row), 130.f);
}
