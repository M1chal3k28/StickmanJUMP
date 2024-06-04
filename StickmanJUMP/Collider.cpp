#include "Collider.h"

// Constructors / Destructors
Collider::Collider(sf::RectangleShape& body) :
	body(body)
{

}

Collider::~Collider()
{

}

// Functions
bool Collider::checkCollision(Collider other)
{
	sf::FloatRect otherBounds = other.body.getGlobalBounds();
	sf::FloatRect thisBounds = this->body.getGlobalBounds();

	// Check for Collision
	return thisBounds.intersects(otherBounds);
}
