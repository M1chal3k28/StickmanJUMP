#pragma once

#include <SFML/Graphics.hpp>

#include "Collider.h"

class Ground
{
private:
	// Ground Rect (hitbox)
	sf::RectangleShape groundRec;

	void initRec();

public:
	// Getters
	Collider getCollider() { return Collider(this->groundRec); }

	// Constructors / Destructors
	Ground();
	virtual ~Ground() {};

	// Functions
	void render(sf::RenderTarget* target_) { target_->draw(this->groundRec); };
};

