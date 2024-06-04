#include "Player.h"

// Costructors / Destructors
Player::Player()
{
	this->initRect();
}

Player::~Player()
{
}

// Private Functions
void Player::initRect()
{
	// Rectangle init
	if (!(this->playerTxt.loadFromFile("Graphics/player.png"))) {
		std::cerr << "Error | Can't load player texture | player.png \n";
		exit(EXIT_FAILURE);
	}

	this->playerRect.setSize(sf::Vector2f(92.f, 207.f));
	this->playerRect.setTexture(&this->playerTxt);
	this->playerRect.setPosition(sf::Vector2f(70.f, 200.f));
	this->playerRect.setFillColor(sf::Color(255, 255, 255));

	// For gravity
	this->jumpHeight = 200;
	this->velocity.y = 0;

	// Player info
	this->score = 0.f;
	this->lifeCount = 3;

	// For Power Ups
	this->multiplayerTimer = 15.f;
	this->haveScoreMultiplayer = false;

	this->shieldTimer = 30.f;
	this->haveShield = false;
}

// Functions
void Player::render(sf::RenderTarget* target_)
{
	// Renders player Rect
	target_->draw(this->playerRect);
}

bool Player::onHit(BulletType bulletType, AudioHandler* audio_)
{
	if (bulletType == Heart) {
		audio_->playEffect(PowerUp);
		this->lifeCount++;
		return false;
	} // Life bullet

	if (bulletType == ShieldPower) {
		audio_->playEffect(PowerUp);
		this->addPowerUp(Shield);
		return false;
	} // Shield power Up

	if (bulletType == StarPower) {
		audio_->playEffect(PowerUp);
		this->addPowerUp(ScoreMultiplayer);
		return false;
	} // Score multiplayer

	// Decrementing lifes when doesn't have shield and hit by the bullet
	if (!this->haveShield) this->lifeCount -= bulletType + 1; // if bullet type is 0 (-1) / if bullet type is 1 (better bullet -2)
	else {
		this->removePowerUp(Shield);
		audio_->playEffect(ShieldBreak);
		return false;
	}

	if (this->lifeCount <= 0) {
		audio_->playEffect(Dead);
		return true;
	}

	audio_->playEffect(Hit);
	return false;
}

void Player::restart()
{
	this->score = 0.f;
	this->RealScore = 0;
	this->lifeCount = 3;
	this->removePowerUp(Shield);
	this->removePowerUp(ScoreMultiplayer);
}

std::string Player::getPowerUpTimerString(PowerUpType type)
{
	int timer = 0;

	if (type == Shield) timer = static_cast<int>(this->shieldTimer);
	if (type == ScoreMultiplayer) timer = static_cast<int>(this->multiplayerTimer);

	return std::to_string(timer);
}

void Player::addPowerUp(PowerUpType type)
{
	// Add proper power up

	if (type == Shield) {
		// If player doesn't have this power up yet set the position of him and set next position for another power up
		//if (!this->haveShield) {
		//	this->shieldPowerPos = this->positionOfPowerUp;
		//	this->positionOfPowerUp++;
		//}

		this->haveShield = true;
		this->shieldTimer = 30.f;
	}

	if (type == ScoreMultiplayer) {
		// If player doesn't have this power up yet set the position of him and set next position for another power ups
		//if (!this->haveScoreMultiplayer) {
		//	this->scoreMultiPos = this->positionOfPowerUp;
		//	this->positionOfPowerUp++;
		//}

		this->haveScoreMultiplayer = true;
		this->multiplayerTimer = 15.f;
	}
}

void Player::removePowerUp(PowerUpType type)
{
	//if (this->positionOfPowerUp != 0)
	//	this->positionOfPowerUp--;

	if (type == Shield)
		this->haveShield = false;
	if (type == ScoreMultiplayer)
		this->haveScoreMultiplayer = false;
}

bool Player::getPowerUpStatus(PowerUpType type)
{
	if (type == Shield) return this->haveShield;
	if (type == ScoreMultiplayer) return this->haveScoreMultiplayer;

	return false;
}

unsigned int Player::getPowerUpPosition(PowerUpType type) {
	if (type == Shield) return this->shieldPowerPos;
	if (type == ScoreMultiplayer) return this->scoreMultiPos;
}

void Player::onGroundCollision()
{
	// Stays on the ground
	velocity.y = 0.0f;
	canJump = true;
	onTheGround = true;
}

void Player::update(float deltaTime, AudioHandler* audio_)
{
	// Power Ups
	if (haveShield) {
		this->shieldTimer -= deltaTime;

		if (shieldTimer <= 0.f) {
			this->removePowerUp(Shield);
		}
	}

	if (haveScoreMultiplayer) {
		this->multiplayerTimer -= deltaTime;

		if (multiplayerTimer <= 0.f) {
			this->removePowerUp(ScoreMultiplayer);
		}
	}

	if (haveScoreMultiplayer) this->multiplayer = 2;
	else this->multiplayer = 1;

	// Something like Crouching system
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
		this->playerRect.setScale(sf::Vector2f(1.f, 0.7f));
		this->playerRect.setOrigin(this->playerRect.getSize().x / 2.f, this->playerRect.getGlobalBounds().height + 30);
	}
	else {
		this->playerRect.setScale(sf::Vector2f(1.f, 1.f));
		this->playerRect.setOrigin(this->playerRect.getSize().x / 2.f, this->playerRect.getGlobalBounds().height - 30);
	}

	// Jumping
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && canJump) {
		canJump = false;
		onTheGround = false;

		velocity.y = -sqrtf(2.0f * 981.f * jumpHeight);
		audio_->playEffect(Jump);
	}

	// Gravity
	if (!onTheGround) velocity.y += 981.f * deltaTime;
	playerRect.move(0.f, velocity.y * deltaTime);

	// Score 
	this->score += this->multiplayer * deltaTime;
	this->RealScore = static_cast<int>(score);

	// Level
		// Level up animation logic
		if (static_cast<int>(this->levelUpNotifTimer) % 2 == 0 && this->leveledUp >= 0.f)
			this->leveledUp = true;
		else
			this->leveledUp = false;

			// Decrement timer of level up animation
		if (this->levelUpNotifTimer >= -1.f)
			this->levelUpNotifTimer -= deltaTime * 3;
		//
	// Previouse level
	unsigned int lastLevel = this->level;
	// New level
	this->level = static_cast<int>(RealScore / 25);
	if (this->level > 12) this->level = 12;
	if (this->level > lastLevel) {
		audio_->playEffect(LevelUp);
		this->levelUpNotifTimer = 4.9f;
	}
}