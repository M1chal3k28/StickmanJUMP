#include "Bullet.h"
#include <iostream>

Bullet::Bullet(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f startingPos, BulletType type, unsigned int id) :
	animation(texture, imageCount, switchTime)
{
	this->bulletType = type; // Determin type of bullet ( it can by power up or deadly bullet)
	this->id = id; // Id is important for vector manipulation

	// Bullet type check
		if (bulletType == Normal || bulletType == Better) {
			this->sizingOfTexture = sf::Vector2f(100.f, 15.f);
			this->row = type; // Row of texture in texture sheet
			this->velocity.x = -500.f;
		}
		else if (bulletType == Heart) {
			this->sizingOfTexture = sf::Vector2f(20.f, 20.f);
			this->row = type - 2; // Row of texture in texture sheet
			this->velocity.x = -300.f;
		}
		else if (bulletType == ShieldPower) {
			this->sizingOfTexture = sf::Vector2f(30.f, 30.f);
			this->row = type - 2; // Row of texture in texture sheet
			this->velocity.x = -300.f;
		}
		else if (bulletType == StarPower) {
			this->sizingOfTexture = sf::Vector2f(35.f, 35.f);
			this->row = type - 2; // Row of texture in texture sheet
			this->velocity.x = -300.f;
		}
	//

	texture->setSmooth(true);
	this->body.setSize(sf::Vector2f(sizingOfTexture));
	this->body.setTexture(texture);
	this->body.setPosition(startingPos);
}

void Bullet::update(float deltaTime)
{
	this->body.move(this->velocity.x * deltaTime, 0.0f);

	animation.update(this->row, deltaTime);
	this->body.setTextureRect(animation.uvRect);
}
