#include "Enemy.h"

Enemy::Enemy(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Texture* bulletTexture, sf::Texture* powerUpsTexture) :
	animation(texture, imageCount, switchTime)
{
	// Bullet texture init
		this->bulletTexture = bulletTexture;
	//

	// Power ups texture init
		this->powerUpsTexture = powerUpsTexture;
	//

	this->row = 0;

	texture->setSmooth(true);
	this->body.setSize(sf::Vector2f(100.f, 100.f));
	this->body.setTexture(texture);
	this->body.setOrigin(0.f, this->body.getSize().y / 2.f);
	this->body.setPosition(sf::Vector2f(850.f, 20.f));

	this->shooting = false;
	this->moving = false;
	this->timeOfFireAnimation = 0.f;
	this->maxNumberToGenerate = 50;

	srand(time(NULL));

	this->shootRandom = 5001 + rand() % 6000;
	this->bulletTypeRandom = 101 + rand() % 200;
	this->heartRandom = 10;
	this->shieldRandom = 20;
	this->starRandom = 30;
}

bool Enemy::update(float deltaTime, Player* player_, AudioHandler* audio_)
{
	bool returnValue = false;

	// Variables needed for logic
	int level = player_->getLevelInt();
	BulletType bulletType = Normal;
	int randomNum = -1;
	bool fromZero = false;
	this->movement.x = 0.f;

	if (!this->moving) movement = sf::Vector2f(0.f, 0.f);

	// Generating random number when enemy isn't shooting
	if (!shooting) {
		// random num from 0 to max number to generate which increase every frame until shoot
		randomNum = rand() % this->maxNumberToGenerate;
		this->maxNumberToGenerate += this->startingNumberGenerator;
	}
	else if (this->timeOfFireAnimation >= 0.9f) {
		// Here's what happen after shoot animation end (bullet reales)
		shooting = false;
		this->maxNumberToGenerate = this->startingNumberGenerator;
		randomNum = rand() % this->maxNumberToGenerate;
		row = 0;

		// Bullet random set
		if (randomNum < bulletTypeRandom)
			bulletType = Normal;
		else
			bulletType = Better;

		// If random num exals to heart random bullet will be heart power up
		if (randomNum <= this->heartRandom)
			bulletType = Heart;
		else if (randomNum <= this->shieldRandom)
			bulletType = ShieldPower;
		else if (randomNum <= this->starRandom)
			bulletType = StarPower;

		// Adding bullet
			if(bulletType == Normal || bulletType == Better)
				this->bullets.push_back(new Bullet(this->bulletTexture, sf::Vector2u(5, 2), 0.1f, this->body.getPosition(), bulletType, this->bullets.size()));
			else 
				this->bullets.push_back(new Bullet(this->powerUpsTexture, sf::Vector2u(2, 3), 0.3f, this->body.getPosition(), bulletType, this->bullets.size()));
		//
		
		audio_->playEffect(Shoot);
	}
	else
		this->timeOfFireAnimation += deltaTime;

	// Check for shoot
	if (randomNum > shootRandom && !shooting) {
		this->row = 1;
		shooting = true;
		this->timeOfFireAnimation = 0;
		fromZero = true;
		this->moving = false;
	}

	// Check for movement 
	if (!moving) {
		unsigned int movementDirection = rand() % 2; // 1 or 0 / 1 means up / 0 means down 
		// Down movement
		if (movementDirection == 0) { // randomNum > movementRandom.x && randomNum <= movementRandom.y
			movement.y = 200.f;
			this->moving = true;
		}
		// Up movement
		else if (movementDirection == 1) { // randomNum < movementRandom.x && !moving
			movement.y = -200.f;
			this->moving = true;
		}
		// Score logic
		if (level == 2)
			this->movement.y += this->movement.y * 1.3f;
		else if (level == 3)
			this->movement.y += this->movement.y * 2.f;
		else if (level == 4)
			this->movement.y += this->movement.y * 3.f;
		else if (level == 5)
			this->movement.y += this->movement.y * 5.f;
		else if (level == 6)
			this->movement.y += this->movement.y * 7.f;
		else if (level == 7)
			this->movement.y += this->movement.y * 8.f;
		else if (level == 8)
			this->movement.y += this->movement.y * 3.f;
		else if (level == 9)
			this->movement.y += this->movement.y * 5.f;
		else if (level == 10)
			this->movement.y += this->movement.y * 6.f;
		else if (level == 11)
			this->movement.y += this->movement.y * 2.f;
		else if (level == 12)
			this->movement.y += this->movement.y * 7.f;
	}

	// Animation with fromZero boolean (if starts shooting animation should start from zero)
	animation.update(this->row, deltaTime, fromZero);
	this->body.setTextureRect(animation.uvRect);

	// Last if / if moving is true and it's not shooting it can move ! 
	if (this->moving && !this->shooting) {
		// if touches barriers change direction to opposite
		if (this->body.getGlobalBounds().top <= 100)
			this->movement.y = abs(this->movement.y);
		else if (this->body.getGlobalBounds().top >= 400)
			this->movement.y = -abs(this->movement.y);

		// actualy move enemy
		this->body.move(0.f, movement.y * deltaTime);
	}

	// Update bullets
	std::vector<unsigned int> idsToDelete;
	for (auto el : this->bullets) {
		el->update(deltaTime);
		if (el->getPosition().x < -300.f)
			idsToDelete.push_back(el->getId());

		if (player_->getCollider().checkCollision(el->getCollider())) { // On hit
			idsToDelete.push_back(el->getId());
			returnValue = player_->onHit(el->getType(), audio_);
		}
	}

	// Deleting bullets outside screen or those which touched player
	for (auto el : idsToDelete) {
		// position of bullet to delet in vector
		auto it = std::find(bullets.begin(), bullets.end(), getBulletById(el));
		// deleting it !
		bullets.erase(it);
	}

	// Check points amount
	if (level == 1) 
		this->startingNumberGenerator = 100;
	if (level == 2)
		this->startingNumberGenerator = 150;
	if (level == 3)
		this->startingNumberGenerator = 200;
	if (level == 4)
		this->startingNumberGenerator = 300;
	if (level == 5)
		this->startingNumberGenerator = 450;
	if (level == 6)
		this->startingNumberGenerator = 500;
	if (level == 7)
		this->startingNumberGenerator = 600;
	if (level == 8)
		this->startingNumberGenerator = 350;
	if (level == 9)
		this->startingNumberGenerator = 500;
	if (level == 10)
		this->startingNumberGenerator = 600;
	if (level == 11) {
		int randomnumber = rand() % 3;

		if (randomnumber == 0)
			this->heartRandom = 100;
		else if (randomnumber == 1)
			this->shieldRandom = 120;
		else if (randomnumber == 2)
			this->starRandom = 130;

		this->startingNumberGenerator = 300;
	}
	if (level == 12) {
		if (this->heartRandom == 100)
			this->heartRandom = 10;
		else if (this->shieldRandom == 120)
			this->shieldRandom = 20;
		else
			this->starRandom = 30;

		this->startingNumberGenerator = 800;
	}

	// Delete the player pointer !
		player_ = nullptr;
		delete player_;
	//

	return returnValue;
}

void Enemy::render(sf::RenderTarget* target_)
{
	target_->draw(this->body);
	for (auto el : this->bullets) {
		if (el != nullptr)
			el->render(target_);
	}
}

void Enemy::restart()
{
	this->bullets.clear();
	this->shootRandom = 5001 + rand() % 6000;
	this->bulletTypeRandom = 101 + rand() % 200;
	this->maxNumberToGenerate = 50;
	this->startingNumberGenerator = 50;
	this->movement.y = 200.f;
	this->shooting = false;
	this->row = 0;
}

Bullet* Enemy::getBulletById(unsigned int id)
{
	for (auto el : bullets) {
		if (el->getId() == id)
			return el;
	}
	return nullptr;
}