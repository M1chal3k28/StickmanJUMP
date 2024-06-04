#pragma once

#include <iostream>
#include <map>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

#include "Collider.h"
#include "PowerUpsStatus.h"
#include "Bullet.h"
#include "AudioHandler.h"

class Player
{
private:
	// Player Rectangle / Texture
	sf::Texture playerTxt;
	sf::RectangleShape playerRect;

	// Variables of player
	sf::Vector2f velocity;
	bool canJump;
	float jumpHeight;
	bool onTheGround;
	int lifeCount;
	int RealScore;
	float score;
	int level;

	// For Power Ups
	bool haveShield;
	float shieldTimer;
	int multiplayer = 1;
	unsigned int positionOfPowerUp = 0;
	unsigned int shieldPowerPos;
	unsigned int scoreMultiPos;

	bool haveScoreMultiplayer;
	float multiplayerTimer;

	bool leveledUp;
	float levelUpNotifTimer = -1.f;

	// Private Functions
	void initRect();
	
public:

	// Getters
	Collider getCollider() { return Collider(this->playerRect); }
	sf::RectangleShape* getPlayerRect() { return &this->playerRect; }
	std::string getScoreString() { return std::to_string(this->RealScore); }
	std::string getLifesString() { return std::to_string(this->lifeCount); }
	std::string getLevelString() { return std::to_string(this->level); }

	int getLevelInt() { return this->level;  }
	int getScoreInt() { return this->RealScore; }
	unsigned int getPowerUpPosition(PowerUpType type);
	bool getLevelUpAnimationState() { return this->leveledUp; }

	// Constructors / Destructors
	Player();
	virtual ~Player();

	// Functions
	void update(float deltaTime, AudioHandler* audio_);
	void render(sf::RenderTarget * target_);
	void onGroundCollision();
	bool onHit(BulletType bulletType, AudioHandler* audio_); // Returns true when lifes == 0 / false when game can continue
	void addPowerUp(PowerUpType type);
	void removePowerUp(PowerUpType type);
	bool getPowerUpStatus(PowerUpType type);
	std::string getPowerUpTimerString(PowerUpType type);
	void restart();
};