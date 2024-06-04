#include "Engine.h"

// Constructors / destructors
Engine::Engine()
{
	this->initVariables();
	this->initWindow();
}

Engine::~Engine()
{
	delete this->window;
	delete this->playerObj;
	delete this->groundObj;
	delete this->enemyHeadObj;
}

// Private functions
void Engine::initWindow()
{
	this->icon.loadFromFile("icon.ico");

	this->videoMode.height = 500;
	this->videoMode.width = 1000;

	this->window = new sf::RenderWindow(this->videoMode, "Stickman Jump", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(165);
	this->window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	this->title.setPosition(this->window->getSize().x / 2.f, 30.0f);
	this->clickSpaceToStart.setPosition(this->window->getSize().x / 2.f, 80.f);
	this->levelUpText.setPosition(this->window->getSize().x / 2.f, 150.f);
	this->recordBeatenText.setPosition(this->window->getSize().x / 2.f, 350.f);

	this->recordScoreText.setString("Record is: " + std::to_string(this->record));
	this->recordScoreText.setOrigin(static_cast<float>(recordScoreText.getGlobalBounds().getSize().x / 2.f), static_cast<float>(recordScoreText.getCharacterSize() / 2));
	this->recordScoreText.setPosition(this->window->getSize().x / 2.f, 400.f);
}

void Engine::initVariables()
{
	this->window = nullptr;

	this->menu = true;

	// Audio Handler
	this->audio = new AudioHandler();

	// Player
	this->playerObj = new Player();

	// Ground
	this->groundObj = new Ground();

	// Power ups 
	this->shieldStatus = new PowerUpsStatus(Shield);
	this->scoreMultiplayer = new PowerUpsStatus(ScoreMultiplayer);
		// Shield
	this->shieldTxt.loadFromFile("Graphics/shield.png");
	this->shieldObj.setSize(sf::Vector2f(60.f, 210.f));
	this->shieldObj.setTexture(&this->shieldTxt);

	// Background
	if (!(this->bgTxt.loadFromFile("Graphics/background.png"))) {
		std::cerr << "Error | Can't load background txt | background.png \n";
		exit(EXIT_FAILURE);
	}

	if (!(this->enemyBody.loadFromFile("Graphics/enemyBody.png"))) {
		std::cerr << "Error | Can't load enemy Body txt | enemyBody.png \n";
		exit(EXIT_FAILURE);
	}

	this->enemyBodySprite.setTexture(enemyBody);
	this->enemyBodySprite.setPosition(sf::Vector2f(920.f, 0.f));
	this->bgSprite.setTexture(bgTxt);

	// Enemy
	if (!(this->enemyHeadTxt.loadFromFile("Graphics/enemy.png"))) {
		std::cerr << "Error | Can't load enemy txt | enemy.png \n";
		exit(EXIT_FAILURE);
	}

	if (!(this->bulletTxt.loadFromFile("Graphics/bullet.png"))) {
		std::cerr << "Error | Can't load bullet txt | bullet.png \n";
		exit(EXIT_FAILURE);
	}

	if (!(this->powerUpsTxt.loadFromFile("Graphics/powerUps.png"))) {
		std::cerr << "Error | Can't load power ups txt | powerUps.png \n";
		exit(EXIT_FAILURE);
	}

	this->enemyHeadObj = new Enemy(&enemyHeadTxt, sf::Vector2u(4, 2), 0.3f, &bulletTxt, &powerUpsTxt);

	// Font init
	if (!(this->gameFont.loadFromFile("Fonts/Font.ttf"))) {
		std::cerr << "Error | Can't load font | Font.ttf \n";
		exit(EXIT_FAILURE);
	}

	// Text init
	this->score.setFont(this->gameFont);
	this->lifeCounter.setFont(this->gameFont);
	this->levelIndicator.setFont(this->gameFont);
	this->shieldTimerText.setFont(this->gameFont);
	this->scoreMultiText.setFont(this->gameFont);

	this->shieldTimerText.setCharacterSize(20);
	this->scoreMultiText.setCharacterSize(20);
	this->shieldTimerText.setFillColor(sf::Color::Black);
	this->scoreMultiText.setFillColor(sf::Color::Black);

	this->levelIndicator.setCharacterSize(50);
	this->score.setCharacterSize(50);
	this->score.setPosition(10.f, 10.f);
	this->lifeCounter.setCharacterSize(50);
	this->lifeCounter.setPosition(10.f, 40.f);

	this->levelUpText = sf::Text("Leveled up", this->gameFont, 50.f);
	this->levelUpText.setOrigin(static_cast<float>(levelUpText.getGlobalBounds().getSize().x / 2.f), static_cast<float>(levelUpText.getCharacterSize() / 2));

	// Menu inits

	// Text
	this->recordBeatenText = sf::Text("Record Beaten !", this->gameFont, 50.f);
	this->recordBeatenText.setOrigin(static_cast<float>(recordBeatenText.getGlobalBounds().getSize().x / 2.f), static_cast<float>(recordBeatenText.getCharacterSize() / 2));
	this->recordBeatenText.setFillColor(sf::Color(124, 200, 100));

	this->title = sf::Text("Stickman Jump", this->gameFont, 50.f);
	this->title.setOrigin(static_cast<float>(title.getGlobalBounds().getSize().x / 2.f), static_cast<float>(title.getCharacterSize() / 2));
	this->title.setFillColor(sf::Color(124, 200, 100));

	this->clickSpaceToStart = sf::Text("Click space to start playing", this->gameFont, 50.f);
	this->clickSpaceToStart.setOrigin(static_cast<float>(clickSpaceToStart.getGlobalBounds().getSize().x / 2.f), static_cast<float>(clickSpaceToStart.getCharacterSize() / 2));
	this->clickSpaceToStart.setFillColor(sf::Color(124, 200, 250));

	this->lastScoreText.setFont(this->gameFont);
	this->lastScoreText.setCharacterSize(50.f);
	this->lastScoreText.setFillColor(sf::Color(124, 200, 100));

	this->recordScoreText.setFont(this->gameFont);
	this->recordScoreText.setCharacterSize(50.f);
	this->recordScoreText.setFillColor(sf::Color(124, 200, 100));

	// Delta time
	this->deltaTime = 0.f;

	// Record from file
	this->record = this->readRecord();
}

void Engine::pollEvents()
{
	while (this->window->pollEvent(this->ev)) {
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;

		case sf::Event::KeyPressed:
			if (ev.key.code == sf::Keyboard::Space)
				if (menu) {
					this->menu = false;
					this->playerDead = false;
					this->audio->playLoopMusic();
				}
			if (ev.key.code == sf::Keyboard::Escape) {
				if (menu)
					this->window->close();
				if (!menu)
					this->restartGame();
			}
		}
	}
}

int Engine::readRecord()
{
	int record = 0;

	std::fstream file;

	file.open("Fonts/record.txt", std::ios::in);

	// if no record create file containing record
	if (!file.good()) {
		file.close();

		this->saveRecord(0);

		return 0;
	}

	// Check if gotten record is valid int !
	std::string allowed = "1234567890";
	std::string temp;
	file >> temp;

	for (char cT : temp) {
		bool found = false;

		for (char cA : allowed) {
			if (cT == cA) {
				found = true;
				break;
			}
		}

		// Error while reading | create new file and reset record
		if (!found) {
			file.close();

			this->saveRecord(0);

			return 0;
		}
	}

	record = stoi(temp);

	file.close();

	return record;
}

void Engine::saveRecord(int record)
{
	this->record = record;
	this->recordScoreText.setString("Record is: " + std::to_string(this->record));
	this->recordScoreText.setOrigin(static_cast<float>(recordScoreText.getGlobalBounds().getSize().x / 2.f), static_cast<float>(recordScoreText.getCharacterSize() / 2));

	std::fstream file;
	
	file.open("Fonts/record.txt", std::ios::out);

		file << record;
	
	file.close();
}

// Public functions
void Engine::update()
{
	this->pollEvents();

	if (!menu) {
		// Delta time reset
		this->deltaTime = this->clock.restart().asSeconds();
		if (this->deltaTime > 1.f / 20.f)
			this->deltaTime = 1.f / 20.f;

		this->playerObj->update(this->deltaTime, this->audio);

		this->score.setString("Score: " + this->playerObj->getScoreString());
		this->lifeCounter.setString("Lifes: x" + this->playerObj->getLifesString());
		this->levelIndicator.setString(this->playerObj->getLevelString() + " <- LEVEL");
		this->levelIndicator.setOrigin(levelIndicator.getGlobalBounds().getSize().x, 0.f);
		this->levelIndicator.setPosition(900.f, 10.f);

		this->playerDead = this->enemyHeadObj->update(this->deltaTime, this->playerObj, this->audio);

		if (this->playerObj->getCollider().checkCollision(groundObj->getCollider()))
			playerObj->onGroundCollision();

		if (this->playerDead) 
			// Restart game points and everything else 
			this->restartGame();

		// Power Ups 
		if (playerObj->getPowerUpStatus(Shield)) {
			// Set duration seconds text under the icon of power up
			this->shieldTimerText.setString(playerObj->getPowerUpTimerString(Shield) + "s");
			this->shieldTimerText.setOrigin(static_cast<float>(shieldTimerText.getGlobalBounds().getSize().x / 2.f), static_cast<float>(shieldTimerText.getCharacterSize() / 2));
			this->shieldTimerText.setPosition(this->shieldStatus->getOrigin().x, this->shieldStatus->getOrigin().y + 10.f);

			this->shieldObj.setPosition(playerObj->getPlayerRect()->getPosition().x + 50.f, playerObj->getPlayerRect()->getPosition().y - playerObj->getPlayerRect()->getSize().y + 30.f); // Positioning of shield texture
		
			this->shieldStatus->setPosition(0); // this->playerObj->getPowerUpPosition(Shield)
		}

		if (playerObj->getPowerUpStatus(ScoreMultiplayer)) {
			// Set duration seconds text under the icon of power up
			this->scoreMultiText.setString(playerObj->getPowerUpTimerString(ScoreMultiplayer) + "s");
			this->scoreMultiText.setOrigin(static_cast<float>(scoreMultiText.getGlobalBounds().getSize().x / 2.f), static_cast<float>(scoreMultiText.getCharacterSize() / 2));
			this->scoreMultiText.setPosition(this->scoreMultiplayer->getOrigin().x, this->scoreMultiplayer->getOrigin().y + 10.f);

			// set proper position of power up info
			this->scoreMultiplayer->setPosition(1); // this->playerObj->getPowerUpPosition(ScoreMultiplayer)
		}
	}
}

void Engine::render()
{
	/*
		- Clear
		- Render Objects
		- Display new Frame

		Renders the game objects
	*/

	this->window->clear(sf::Color(sf::Color::Blue));

	if (!menu) {
		// Ground hitbox
		this->groundObj->render(this->window);

		// Render Background
		this->window->draw(bgSprite);
		this->window->draw(enemyBodySprite);

		// Render Objects
		this->playerObj->render(this->window);
		this->enemyHeadObj->render(this->window);

		// Render Text
		this->window->draw(score);
		this->window->draw(lifeCounter);
		this->window->draw(levelIndicator);

		// Power Ups info
		if (playerObj->getPowerUpStatus(Shield)) { // If player has shield Display shield and power up info 
			this->shieldStatus->render(this->window);
			this->window->draw(this->shieldTimerText);
			this->window->draw(this->shieldObj);
		}

		if (playerObj->getPowerUpStatus(ScoreMultiplayer)) {
			scoreMultiplayer->render(this->window);
			this->window->draw(scoreMultiText);
		}

		if (this->playerObj->getLevelUpAnimationState())
			this->window->draw(this->levelUpText);
	}
	else {
		this->window->draw(this->title);
		this->window->draw(this->clickSpaceToStart);
		this->window->draw(this->lastScoreText);
		this->window->draw(this->recordScoreText);

		if (this->recordBeaten) {
			this->recordScoreText.setPosition(this->window->getSize().x / 2.f, 400.f);
			this->window->draw(this->recordBeatenText);
		}
	}

	// Display new frame
	this->window->display();
}

void Engine::restartGame()
{
	this->audio->stopLoopedMusic();
	this->menu = true;

	// Creating last score text for menu
	this->lastScore = this->playerObj->getScoreInt();
	this->lastScoreText.setString("Last score was: " + std::to_string(lastScore));
	this->lastScoreText.setOrigin(static_cast<float>(lastScoreText.getGlobalBounds().getSize().x / 2.f), static_cast<float>(lastScoreText.getCharacterSize() / 2));
	this->lastScoreText.setPosition(this->window->getSize().x / 2.f, 450.f);

	this->playerObj->restart();
	this->enemyHeadObj->restart();

	if (this->lastScore > this->record) {
		this->recordBeaten = true;
		this->saveRecord(this->lastScore);
	}
	else
		this->recordBeaten = false;
}

// Getters
const bool Engine::isRunning() const
{
	return this->window->isOpen();
}
