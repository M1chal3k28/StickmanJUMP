#pragma once

#include <ctime>
#include <vector>
#include <fstream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
	
#include "Player.h"
#include "Ground.h"
#include "Enemy.h"
#include "PowerUpsStatus.h"
#include "AudioHandler.h"

class Engine
{
private:
	// Engine variables
	sf::Image icon;
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;
	sf::Clock clock;
	float deltaTime;
	bool menu;
	bool playerDead;
	bool recordBeaten = false;
	// Sound Buffer
	AudioHandler* audio;

	// Game variables
	int lastScore = 0;
	int record;

	// Font
	sf::Font gameFont;
	
	// Background
	sf::Texture bgTxt;
	sf::Sprite bgSprite;
	sf::Texture enemyBody;
	sf::Sprite enemyBodySprite;

	// Game Objects
		// Player Object
		Player* playerObj;
		
		// Other objects (Ground, enemies, text)
		Ground* groundObj;
		sf::Texture enemyHeadTxt; // Is needed for enemy animation to work properly
		sf::Texture bulletTxt; // Is needed for bullet animation to work properly
		sf::Texture powerUpsTxt; // For powerUps txt
		Enemy* enemyHeadObj;
		PowerUpsStatus* shieldStatus;
		PowerUpsStatus* scoreMultiplayer;
		sf::Texture shieldTxt;
		sf::RectangleShape shieldObj;
			// Texts
		sf::Text score;
		sf::Text lifeCounter;
		sf::Text levelIndicator;
		sf::Text shieldTimerText;
		sf::Text scoreMultiText;
		sf::Text levelUpText;

	// Menu Objects
		sf::Text title;
		sf::Text clickSpaceToStart;
		sf::Text lastScoreText;
		sf::Text recordScoreText;
		sf::Text recordBeatenText;

	// Private functions
	void initWindow();
	void initVariables();
	void pollEvents();

	int readRecord();
	void saveRecord(int record);

public:
	
	// Functions
	void update(); // When returns true game should end !
	void render();
	void restartGame();

	// Getters
	const bool isRunning() const;

	// Constructors / destructors
	Engine();
	virtual ~Engine();
};

