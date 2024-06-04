#pragma once
#include <SFML/Graphics.hpp>

#include "Animation.h"
#include "Collider.h"

enum BulletType {
	Normal,
	Better,
	Heart,
	ShieldPower,
	StarPower
};

class Bullet
{
public:
	Bullet(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f startingPos, BulletType type, unsigned int id);
	virtual ~Bullet() {};

	void update(float deltaTime);
	void render(sf::RenderTarget* target_) { target_->draw(this->body); };
	unsigned int getId() { return this->id; }
	BulletType getType() { return this->bulletType; }
	sf::RectangleShape* getBulletRect() { return &this->body; }
	sf::Vector2f getPosition() { return this->body.getPosition(); }

	Collider getCollider() { return Collider(this->body); }

private:
	sf::Vector2f velocity;
	sf::RectangleShape body;
	sf::Texture texture;
	sf::Vector2f sizingOfTexture;
	Animation animation;
	unsigned int row;
	unsigned int id;
	BulletType bulletType;
};

