#pragma once
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Bullet.h"
#include "Player.h"
#include "AudioHandler.h"

class Enemy
{
public:
	Enemy(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Texture* bulletTexture, sf::Texture* powerUpsTexture);
	virtual ~Enemy() {};

	// Functions
	bool update(float deltaTime, Player* player_, AudioHandler* audio_); // When returns true game should end ! (player lost all lifes)
	void render(sf::RenderTarget* target_);
	void restart();

	Bullet* getBulletById(unsigned int id);

private:
	// Texture And animation
	sf::RectangleShape body;
	sf::Texture texture;
	Animation animation;
	unsigned int row;

	// For Logic
	float timeOfFireAnimation;
	unsigned int shootRandom;
	unsigned int bulletTypeRandom;
	unsigned int heartRandom;
	unsigned int shieldRandom;
	unsigned int starRandom;
	sf::Vector2f movement;

	bool shooting;
	bool moving;

	int maxNumberToGenerate;
	int startingNumberGenerator = 50;

	// Bullet and powerUps
	std::vector<Bullet*> bullets;
	sf::Texture* bulletTexture = nullptr;
	sf::Texture* powerUpsTexture = nullptr;
};

