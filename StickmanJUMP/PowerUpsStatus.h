#pragma once
#include <SFML/Graphics.hpp>

enum PowerUpType {
	Shield,
	ScoreMultiplayer
};

class PowerUpsStatus
{
public:
	PowerUpsStatus(PowerUpType type);
	virtual ~PowerUpsStatus() {};

	void render(sf::RenderTarget* target_) { target_->draw(this->body); }
	void setPosition(int row);
	sf::Vector2f getOrigin() { return this->body.getPosition(); }

private:
	sf::RectangleShape body;
	sf::Texture texture;

	sf::IntRect uvRect;
	sf::Vector2u imageCount = sf::Vector2u(1, 2);
	sf::Vector2u selectedImage;
};

